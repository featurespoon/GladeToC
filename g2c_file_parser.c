#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "g2c_helpers.h"
#include "g2c_file_parser.h"
#include "g2c_project.h"
#include "g2c_widget.h"

void parse_file( g2cFileParser *parser );
void parse_source_file (g2cFileParser *parser);
void parse_po_file (g2cFileParser *parser);
void parse_make_file (g2cFileParser *parser);
void check_main_file (g2cFileParser *parser);
void add_item_to_po_file (g2cFileParser *parser, gchar *item);
void add_item_to_make_file (g2cFileParser *parser, gchar *item);
gint compare_function( gconstpointer data, gconstpointer user_data );

g2cFileParser *
g2c_file_parser_new( const gchar *file_name, const g2cProject *project, FileType file_type )
{
  g2cFileParser *parser = NULL;
  gchar *xfile_name = NULL;
  
  g_assert (NULL != file_name);
  g_assert (NULL != project);

  parser = g_new0( g2cFileParser, 1 );
  xfile_name = g_strdelimit(g_strdup(file_name), "\\", '/' );
  parser->file_name = g_strdup( xfile_name );
  //parser->file_name = g_strconcat(project->directory,"/",file_name, NULL);
  //g_message("parser file name: %s\n", parser->file_name);
  parser->project = project;
  parser->file_type = file_type;
  parser->items = NULL;

  parse_file( parser );

  g_free( xfile_name );
  return parser;
}

void
g2c_file_parser_add_file(g2cFileParser *parser, const gchar *file_name, FileType file_type)
{
 gchar *xfile_name = NULL;
  
  g_assert (NULL != file_name);
  g_assert (NULL != parser);  
  
  xfile_name = g_strdelimit(g_strdup(file_name), "\\", '/' );
  parser->file_name = g_strdup( xfile_name );
  //g_message("parser file name: %s\n", parser->file_name);
  parser->file_type = file_type;
  
  parse_file( parser );

  g_free( xfile_name );
  return;  
}

void
g2c_file_parser_destroy( g2cFileParser *parser )
{
  if (NULL != parser->file_name )
    g_free (parser->file_name);

  g_list_foreach (parser->items,
                  g2c_list_element_free_cb,
                  NULL);

  g_free (parser);
}

void
g2c_file_parser_add_item (g2cFileParser *parser,
			  gchar         *item)
{
  g_assert (parser != NULL);
  g_assert (item   != NULL);

  /* Open the file and add this item */
  switch (parser->file_type)
    {
    case FT_SOURCE:
      break;
    case FT_PO:
      add_item_to_po_file (parser, item);
      break;
    case FT_MAKE:
      add_item_to_make_file (parser, item);
      break;
    case FT_MAIN:
      break;
    }
}

void 
add_item_to_po_file (g2cFileParser *parser, gchar *item)
{
  FILE  *tmp = NULL;

  g_assert (parser != NULL);
  g_assert (item != NULL);

  tmp = fopen (parser->file_name, "a");
  if (tmp == NULL)
    {
      g_error (strerror (errno), NULL);
    }

  /* Add the line */
  printf ("Adding %s to %s\n", item, parser->file_name);

  fwrite (item, strlen(item), sizeof(gchar), tmp);
  fwrite ("\n", 1, sizeof(gchar), tmp);

  fclose (tmp);
}

void 
add_item_to_make_file (g2cFileParser *parser, gchar *item)
{
  /* Add this item to Makefile.am.  Since this will be
   * the new last line, we need to add a \ to the next-
   * to-last line, then add this one.
   */
  FILE      *tmp          = NULL;
  gchar     *line         = g_malloc0( 1024 );
  gchar     *target_line  = NULL;
  gchar     *pos          = NULL;
  gboolean   first_line   = FALSE;
  gboolean   last_line    = FALSE;
  GString   *rest_of_file = NULL;
  gint       tell_pos     = 0;

  g_assert (parser != NULL);
  g_assert (item != NULL);

  tmp = fopen (parser->file_name, "r+");
  if (tmp == NULL)
    {
      g_error (strerror (errno), NULL);
    }

  /* Find the last (source) line. 
   * Read until we find the programname_SOURCES line 
   */
  target_line = g_strdup_printf ("%s_SOURCES", parser->project->program_name);
  while( !feof (tmp) && !first_line )
    {
      tell_pos = ftell (tmp);
      fgets (line,1024,tmp);

      pos = strstr (line, target_line);
      if (pos != NULL) first_line = TRUE;

      memset (line, 0, 1024);
    }
  g_free (target_line);

  /* Now read each entry */
  while( !feof (tmp) && !last_line )
    {
      fgets (line,1024,tmp);

      /* If this line doesn't end with a \, then it is the last line */
      pos = strchr (line, '\\'); 
      if ( pos == NULL) last_line = TRUE;

      memset (line, 0, 1024);
    }

  /* We are now positioned at the line right after the last line.
   * Save the position we are at, then read everything until 
   * the end of the file and save it */
  tell_pos = ftell (tmp);
  
  rest_of_file = g_string_new ("");
  while (!feof (tmp))
    {
      fgets (line, 1024, tmp);
      g_string_append (rest_of_file, line);
      memset (line, 0, 1024);		       
    }

  /* Move back to the saved position, minus 1, which gets us to the
   * end of the last source line */
  fseek (tmp, tell_pos-1, SEEK_SET);

  /* Add a \ to the last (source) line */
  fwrite (" \\\n", sizeof(gchar), 3, tmp);

  /* Add the new (source) line */
  printf ("Adding %s to %s\n", item, parser->file_name);

  fwrite ("\t", sizeof(gchar), 1, tmp);
  fwrite (item, sizeof(gchar), strlen(item), tmp);
  fwrite ("\n", sizeof(gchar), 1, tmp);

  /* Dump all of the stuff we saved at the end of the file */
  fwrite (rest_of_file->str, sizeof(gchar), rest_of_file->len, tmp);
  g_string_free (rest_of_file, TRUE);

  /* Close the file */
  fclose (tmp);
}

gboolean
g2c_file_parser_item_exists( g2cFileParser *parser,
			     gchar         *item )
{
  /* See if this function exists within the parsed file */
  GList *list = NULL;

  g_assert( NULL != parser );
  g_assert( NULL != item );

  /* Search the functions list */
  list = g_list_find_custom( parser->items,
                             item,
                             compare_function );

  return ( NULL != list );
}

void parse_file (g2cFileParser *parser)
{
  g_assert (parser != NULL);

  switch (parser->file_type)
    {
    case FT_SOURCE:
      parse_source_file (parser);
      break;
    case FT_PO:
      parse_po_file (parser);
      break;
    case FT_MAKE:
      parse_make_file (parser);
      break;
    case FT_MAIN:
      check_main_file (parser);
      break;
    }
}

void
parse_source_file( g2cFileParser *parser )
{
  /* Run ctags on the file in question, then take each line
   * in the returned tags file and put it the function
   * list of the parser 
   */
  FILE   *tag_file = NULL;
  gchar  *cmd      = NULL;
  gchar  *item     = g_malloc0( 1024 );
  gchar **line     = NULL;
  gchar *ret  = NULL;
  gint rstatus = 0;
  
  g_assert( NULL != parser );

  /* Create the command */
  
#ifdef WIN32
  cmd = g_strdup_printf( "C:/msys64/usr/bin/ctags -x --sort=no %s", g_shell_quote(parser->file_name) );
#else
  cmd = g_strdup_printf( "ctags -x --sort=no %s 2> /dev/null", g_shell_quote(parser->file_name) );
#endif  
  
  //g_message("Command file: %s\n", cmd);

  tag_file = popen( cmd, "r" );

  g_free( cmd );

  if (tag_file == NULL)
    {
      g_error (strerror (errno), NULL);
    }

  while( !feof( tag_file ) )
    {
      /* Now write out what we got */
      ret = fgets( item,
             1024,
             tag_file );
      if (ret == NULL) {         
         break;
      }
  
      line = g_strsplit( item, " ", 0 );
      
      if((line[0] != NULL) && (line[0][0] != '!'))
	{
	  parser->items = g_list_append( parser->items, g_strdup( line[0] ) );
          //g_message("Handler %s found in file\n", line[0] );
	}

      memset (item, 0, 1024);
      g_strfreev( line );
    }

  pclose( tag_file );
  g_free( item );
}

void
parse_po_file( g2cFileParser *parser )
{
  /* This function parses po/POTFILES.in, which has a bunch of lines
   * like this:
   * 
   * src/main.c
   * src/support.c
   * src/widget_gui.c
   * src/widget.c
   * 
   * We want to add lines for each of the (.c) files we process.
   * This call will grab all of the source lines.  This is
   * pretty easy, as all we need to do is grab lines that
   * aren't comments (those lines begin with a #)
   */
  FILE   *po_file = NULL;
  gchar  *item    = g_malloc0( 1024 );

  g_assert( NULL != parser );

  /* Create the command */
  po_file = fopen( parser->file_name, "r" );

  if (po_file == NULL)
    {
      g_error (strerror (errno), NULL);
    }

  while( !feof( po_file ) )
    {
      /* Now write out what we got */
      fgets( item,
             1024,
             po_file );

      item = g_strstrip (item);

      if ((item != NULL) && (strlen(item) > 0) && (item[0] != '#'))
	{
	  parser->items = g_list_append (parser->items, g_strdup (item));
	}
      
      memset (item, 0, 1024);
    }

  fclose (po_file);
  if (item != NULL) g_free (item);
  
  return;
}

void
parse_make_file( g2cFileParser *parser )
{
  /* This function parses src/Makefile.am, which has a bunch of lines
   * like this:
   * 
   * projectname_SOURCE = \
   *     main.c \
   *     support.c \
   *     widget_gui.c widget_gui.h \
   *     widget.c widget.h
   * 
   * We want to add lines for each of the (.c) files we process.
   * This call will grab all of the lines after projectname_SOURCES
   * until we reach a line without a \.  The \ will be removed from
   * all of the other lines before processing.  Multiple entries can 
   * be on one line, as long as they are separated by whitespace.  
   * Comments (those lines begin with a #) will be ignored.
   */
  FILE      *make_file   = NULL;
  gchar     *item        = g_malloc0( 1024 );
  gchar     *target_line = NULL;
  gchar     *pos         = NULL;
  gchar    **items       = NULL;
  gboolean   first_line  = FALSE;
  gboolean   last_line   = FALSE;
  gint       i           = 0;
  gint       tell_pos    = 0;

  g_assert( NULL != parser );

  /* Create the command */
  make_file = fopen( parser->file_name, "r" );

  if (make_file == NULL)
    {
      g_error (strerror (errno), NULL);
    }

  /* Read until we find the programname_SOURCES line */
  target_line = g_strdup_printf ("%s_SOURCES", parser->project->program_name);
  while( !feof (make_file) && !first_line )
    {
      tell_pos = ftell (make_file);

      fgets (item,
	     1024,
	     make_file);
      
      pos = strstr (item, target_line);
      if (pos != NULL)
	{
	  /* This is the line we want.  We need to reposition the
	   * file to just after the =.
	   */
	  first_line = TRUE;
	  
	  /* Find the = */
	  pos = strstr (pos, "=");

	  /* Move one past the = */
	  pos++; 

	  /* Move the file to this point */
	  fseek (make_file, tell_pos + pos - item, SEEK_SET);
	}
    }
  g_free (target_line);

  /* Now read each entry */
  while( !feof (make_file) && !last_line )
    {
      fgets (item,
             1024,
             make_file);

      item = g_strstrip (item);

      /* If this line doesn't end with a \, then it is the last line */
      pos = strchr (item, '\\'); 
      if ( pos == NULL)
	{
	  last_line = TRUE;
	}

      /* Ignore comments and empty lines */
      if ((item != NULL) && (strlen(item) > 0) && (item[0] != '#'))
	{
	  /* Split on whitespace */
	  items = g_strsplit (item, " ", 0);
	  	  
	  i = 0;
	  while ((items[i] != NULL) && (strcmp(items[i], "\\") != 0))
	    {
	      parser->items = g_list_append (parser->items, g_strdup (items[i++]));
	    }
	}

      g_strfreev (items);
      memset (item, 0, 1024);
    }

  fclose (make_file);
  if (item != NULL) g_free (item);

  return;
}

void 
check_main_file (g2cFileParser *parser)
{
  /* Ensure that the programname_main.c file exists   NOW REDUNDANT
   * If not, create it
   */
  struct  stat s_stat;
  FILE   *tmp       = NULL;
  g2cWidget *widget = NULL;  
  g2cWidget *dialogue_widget = NULL;
  GList *run        = NULL;
  gchar *type_name  = NULL;
  gchar *dialogue_type_name  = NULL; 
  
  

  //full_path = g_strconcat(parser->project->directory, "/", parser->file_name,NULL);
  if (-1 == stat (parser->file_name, &s_stat))
    {
      widget = parser->project->main_widget;
      g_assert(widget != NULL);
      type_name = g2c_transform_name( widget->name, NT_TYPENAME );
      /* Output a skeleton file */
      g_message( "Creating %s\n", parser->file_name );
      tmp = fopen (parser->file_name, "w");
      if (tmp == NULL) {
          g_error("Could not open file %s\n", parser->file_name);
          return;
      }
      fprintf (tmp, "#ifdef HAVE_CONFIG_H\n");
      fprintf (tmp, "#  include <config.h>\n");
      fprintf (tmp, "#endif\n\n");
      fprintf (tmp, "/*                Generated from %s                 */\n\n", parser->project->source_file);	
      fprintf (tmp, "#include <gtk/gtk.h>\n\n");	    
      fprintf (tmp, "#include \"%s.h\"\n\n", widget->name);
      fprintf (tmp, "int\n");
      fprintf (tmp, "main (int argc, char *argv[])\n");
      fprintf (tmp, "{\n");
      fprintf (tmp, "%s *%s = NULL;\n\n", type_name, widget->name);
      run = g_list_first(parser->project->dialogue_widgets);
      while (run != NULL) {
          dialogue_widget = (g2cWidget *) run->data;
          dialogue_type_name = g2c_transform_name( dialogue_widget->name, NT_TYPENAME );
          fprintf (tmp, "%s *%s = NULL;\n\n", dialogue_type_name, dialogue_widget->name);
          run = g_list_next(run);
      }
      fprintf (tmp, "#ifdef ENABLE_NLS\n");
      fprintf (tmp, "  bindtextdomain (PACKAGE, PACKAGE_LOCALE_DIR);\n");
      fprintf (tmp, "  textdomain (PACKAGE);\n");
      fprintf (tmp, "#endif\n");
      fprintf (tmp, "\n");      	
      //fprintf (tmp, "  gtk_set_locale ();\n");
      fprintf (tmp, "  gtk_init (&argc, &argv);\n\n");
      fprintf (tmp, "//  add_pixmap_directory (PACKAGE_DATA_DIR \"/pixmaps\");\n");
      fprintf (tmp, "//  add_pixmap_directory (PACKAGE_SOURCE_DIR \"/pixmaps\");\n");	
      fprintf (tmp, "  %s = %s_create ();\n", widget->name, widget->name);
      
      run = g_list_first(parser->project->dialogue_widgets);
      while (run != NULL) {
          dialogue_widget = (g2cWidget *) run->data;
          fprintf (tmp, "  %s = %s_create ();\n", dialogue_widget->name, dialogue_widget->name);
          run = g_list_next(run);
      }
      fprintf (tmp, "  gtk_main ();\n");
      fprintf (tmp, "  return 0;\n");
      fprintf (tmp, "}\n");

      fclose (tmp);
      g_free( type_name);
    } else {
      g_message( "Not replacing %s\n", parser->file_name );
    }
  //g_free(full_path);
}

void 
g2c_file_parser_update_main_file (g2cFileParser *parser, g2cWidget *widget)
{
  /* This function looks for three lines in $src/main.c:
   * 
   *   #include "widgetname.h"
   *   WidgetName *widgetname = NULL;
   *   widgetname = widgetname_create ();
   *
   * If not found, add each of the lines.
   *
   * Always add 
   *   WidgetName *widgetname = NULL;
   *
   * If widget->visible = TRUE, uncomment  
   *   widgetname = widgetname_create ();
   *
   * otherwise make it a comment /\* widgetname = widgetname_create (); *\/
   */

  FILE     *tmp          = NULL;
  gchar    *target_line  = NULL;
  gchar    *item         = g_malloc0( 1024 );
  gchar    *pos          = NULL;
  gboolean  found_line   = FALSE;
  gboolean  found_main   = FALSE;
  gboolean  found_brace  = FALSE;
  gint      last_pos     = 0;
  gint      cur_pos      = 0;
  gint      line_pos     = 0;
  gint      line_after_pos = 0;
  GString  *rest_of_file = NULL;
  GString  *line         = NULL;
  gchar    *type_name    = NULL;

  /* Open the main file */
  tmp = fopen (parser->file_name, "r+");

  if (tmp == NULL)
    {
      g_error (strerror (errno), NULL);
      return;
    }

  /************************************************************************ 
   * The first step is to add a #include statement (if it doesn't exist)  *
   *                                                                      *
   * The declaration will be of the form                                  *
   *    #include "widgetname.h"                                           *
   *                                                                      *
   * This line will be added right after the last #include statement      *
   ************************************************************************/

  /* Read until we find the #include "programname.h" line */
  target_line = g_strdup_printf ("#include \"%s.h\"", widget->name);
  while (!feof (tmp) && !found_line)
    {
      fgets (item,1024,tmp);
      
      if (strncmp (item, "#include", 8) == 0)
	{
	  /* Store the position of the line right after the #include */
	  last_pos = ftell (tmp);
	}

      pos = strstr (item, target_line);
      if (pos != NULL) found_line = TRUE;
    }

  if (!found_line)
    {
      /* We didn't find the line, so add it after the last #include */  

      /* Move to the point right after the last #include */
      fseek (tmp, last_pos, SEEK_SET);

      /* Copy everything from there to the end of the file */
      rest_of_file = g_string_new ("");
      while (!feof (tmp))
	{
	  fgets (item, 1024, tmp);
	  g_string_append (rest_of_file, item);
	  memset (item, 0, 1024);		       
	}
      
      fseek (tmp, last_pos, SEEK_SET);

      /* Add the #include line */
      line = g_string_new (g_strdup_printf ("#include \"%s.h\"\n", widget->name));
      fwrite (line->str, sizeof(gchar), line->len, tmp);
      g_string_free (line, TRUE);

      fwrite (rest_of_file->str, sizeof(gchar), rest_of_file->len, tmp);
      g_string_free (rest_of_file, TRUE);
    }
  
  g_free (target_line);

  /************************************************************************ 
   * The next step is to add a variable declaration (if it doesn't exist) *
   *                                                                      *
   * The declaration will be of the form                                  *
   *    WidgetName *widgetname = NULL;                                    *
   *                                                                      *
   * This line will be added just after the opening brace to main()       *
   ************************************************************************/

  type_name   = g2c_transform_name( widget->name, NT_TYPENAME );
  found_main  = FALSE;
  found_brace = FALSE;
  found_line  = FALSE;
  last_pos    = -1;

  /* Reset the file position to the start */
  fseek (tmp, 0, SEEK_SET);

  while (!feof (tmp) && !found_line)
    {
      fgets (item,1024,tmp);
  
      if (!found_main)
	{
	  /* Look for the gtk_main () loop */
	  if (strstr (item, "main") != NULL) 
	    if (strstr (item, "argc") != NULL)
	      if (strstr (item, "argv") != NULL)
		{
		  found_main = TRUE;
		}
	}
      else if (found_main && !found_brace)
	{
	  /* Look for the brace after main () */
	  if (strstr (item, "{") != NULL) 
	    {
	      /* Store the pointer right after the opening brace */
	      last_pos = ftell (tmp);
	      found_brace = TRUE;
	    }
	}
      else if (found_main && found_brace)
	{
	  /* Now we can look for the line */
	  if (strstr (item, type_name) != NULL)
	    if (strstr (item, widget->name) != NULL)
	      if (strstr (item, "=") != NULL)
		if (strstr (item, "NULL"))
		  {
		    /* We found the line! */
		    found_line = TRUE;
		  }
	}
    }

  if (!found_line)
    {
      /* We didn't find the line, so add it after the last #include */  

      /* Move to the point right after the last #include */
      fseek (tmp, last_pos, SEEK_SET);

      /* Copy everything from there to the end of the file */
      rest_of_file = g_string_new ("");
      while (!feof (tmp))
	{
	  fgets (item, 1024, tmp);
	  g_string_append (rest_of_file, item);
	  memset (item, 0, 1024);		       
	}
      
      fseek (tmp, last_pos, SEEK_SET);

      /* Add the declaration */
      line = g_string_new (g_strdup_printf ("  %s *%s = NULL;\n", 
					    type_name, 
					    widget->name));
      fwrite (line->str, sizeof(gchar), line->len, tmp);
      g_string_free (line, TRUE);

      fwrite (rest_of_file->str, sizeof(gchar), rest_of_file->len, tmp);
      g_string_free (rest_of_file, TRUE);
    }

  /************************************************************************ 
   * The next step is to add a variable assignment statement              *
   * (if it doesn't exist)                                                *
   *                                                                      *
   * The assignment statement will be of the form                         *
   *    widgetname = widgetname_create ();                                *
   *                                                                      *
   * This line will be added just before gtk_main() is called             *
   ************************************************************************/
  
  cur_pos    = 0;
  line_pos   = 0;
  line_after_pos = 0;
  found_line = FALSE;
  found_main = FALSE;

  /* Reset the file position to the start */
  fseek (tmp, 0, SEEK_SET);
  
  /* Find the line with gtk_main on it */
  while (!feof (tmp) && !found_line && !found_main)
    {
      /* Save the position right before this line */
      cur_pos = ftell (tmp);

      fgets (item,1024,tmp);
  
      /* Now we can look for the line */
      if (strstr (item, widget->name) != NULL)
	if (strstr (item, "=") != NULL)
	  if (strstr (item, "_create"))
	    if (strstr (item, "(") != NULL)
	      if (strstr (item, ")") != NULL)
		{
		  /* We found the line! */
		  found_line = TRUE;
		  line_pos = cur_pos;
		  line_after_pos = ftell (tmp);
		}
      
      if (!found_main)
	{
	  if (strstr (item, "gtk_main") != NULL) 
	    if (strstr (item, "(") != NULL)
	      if (strstr (item, ")") != NULL)
		{
		  found_main = TRUE;
		  last_pos   = cur_pos;
		}
	}
    }

  if (!found_main && !found_line)
    {
      /* Whoah, what happened? */
      
      g_printerr ("gtk_main() must be called within %s!\n"
		  "Couldnt add %s = %s_create() to %s\n", 
		  parser->file_name,
		  widget->name,
		  widget->name,
		  parser->file_name);
    }
  else if (!found_line && found_main)
    {
      /* We didn't find the line, so add it before gtk_main() */  
      
      gboolean visible = TRUE;

      if (g2c_widget_get_property (widget, "visible") != NULL)
	visible = g2c_get_bool (g2c_widget_get_property (widget, "visible"));

      /* Move to the point right before gtk_main() */
      fseek (tmp, last_pos, SEEK_SET);

      /* Copy everything from there to the end of the file */
      rest_of_file = g_string_new ("");
      while (!feof (tmp))
	{
	  fgets (item, 1024, tmp);
	  g_string_append (rest_of_file, item);
	  memset (item, 0, 1024);		       
	}
      
      /* Return to the insertion point */
      fseek (tmp, last_pos, SEEK_SET);

      /* Add the declaration */
      line = g_string_new (g_strdup_printf ("  %s%s = %s_create ();%s\n", 
					    visible ? "" : "/* ",
					    widget->name,
					    widget->name,
					    visible ? "" : " */"));
      fwrite (line->str, sizeof(gchar), line->len, tmp);
      g_string_free (line, TRUE);

      /* Write the rest of the file */
      fwrite (rest_of_file->str, sizeof(gchar), rest_of_file->len, tmp);
      g_string_free (rest_of_file, TRUE);
    }
  else if (found_line && found_main)
    {
      /* Make sure the line is commented is the widget's visible property
       * is FALSE, and uncommented if it is TRUE
       */

      gboolean visible = TRUE;
      
      if (g2c_widget_get_property (widget, "visible") != NULL)
	visible = g2c_get_bool (g2c_widget_get_property (widget, "visible"));
      
      /* Position the file right before the line */
      fseek (tmp, line_after_pos, SEEK_SET);

      /* Read the rest of the file */
      rest_of_file = g_string_new ("");
      while (!feof (tmp))
	{
	  fgets (item, 1024, tmp);
	  g_string_append (rest_of_file, item);
	  memset (item, 0, 1024);		       
	}

      /* Return to the line's position */
      fseek (tmp, line_pos, SEEK_SET);

      /* Add the assignment */
      line = g_string_new (g_strdup_printf ("  %s%s = %s_create ();%s\n", 
					    visible ? "" : "/* ",
					    widget->name,
					    widget->name,
					    visible ? "" : " */"));
      fwrite (line->str, sizeof(gchar), line->len, tmp);
      g_string_free (line, TRUE);

      /* Write the rest of the file */
      fwrite (rest_of_file->str, sizeof(gchar), rest_of_file->len, tmp);
      g_string_free (rest_of_file, TRUE);
    }
  
  /* Close the file */
  fclose (tmp);
}

gint
compare_function( gconstpointer data, gconstpointer user_data )
{
  return strcmp( (gchar*) data, (gchar*) user_data );
}



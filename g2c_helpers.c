#include "g2c_helpers.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <gtk/gtk.h>

static gint anon_counter = 0;

/*******************************************************************
 **                        Helper functions                       **
 *******************************************************************/
gchar *
spaces_to_ulines( gchar *input )
{
  int i = 0;

  for( i = 0; i < strlen( input ); i++ )
    {
      if( input[i] == ' ' ) input[i] = '_';
    }

  return input;
}

const xmlChar *
get_node_name( xmlNodePtr node )
{
  if( node == NULL )  return NULL;
  else return node->name;
}

const xmlChar *
get_attr_node_name( xmlAttrPtr node )
{
  if( node == NULL ) return NULL;
  else return node->name;
}

const xmlChar *
get_node_text( xmlNodePtr node )
{
  if     ( xmlIsBlankNode(  node ) ) return NULL;
  else if( !xmlNodeIsText( node->children ) ) return NULL;
  else return node->children->content;
}

const xmlNodePtr
get_next_node( xmlNodePtr node )
{
xmlNodePtr next_node;    
    if (node == NULL) return NULL;
    next_node = node->next;
    if ( xmlIsBlankNode(  next_node ) ) {
        next_node = next_node->next;
    }
    return next_node;
}

const xmlNodePtr
get_first_child( xmlNodePtr node )
{
xmlNodePtr next_node;    
    if (node == NULL) return NULL;
    next_node = node->children;
    if ( xmlIsBlankNode(  next_node ) ) {
        next_node = next_node->next;
    }
    return next_node;
}

xmlNode  * set_first_object(xmlNode *root_element )
{
 xmlNode  *node = root_element;
 
 /* root element name should be interface  */
        
    g_assert( strcmp(node->name,"interface") == 0 );
    
    node = get_first_child(node);      
          
    if (node->type == XML_COMMENT_NODE)   node = get_next_node(node);
    
    if ( strcmp(node->name,"requires") == 0 )  node = get_next_node(node);  /// glade 3.16.1 
    
    /* the node should now be an Element node with name object or template */  
    g_assert( node->type == XML_ELEMENT_NODE );
    g_assert( ( strcmp(node->name, "object") == 0 ) || ( strcmp(node->name,"template") == 0 ));      
    
    return node;
}

const xmlChar *
get_attr_node_text( xmlAttrPtr node )
{
  if     ( xmlIsBlankNode(  (xmlNodePtr)  node ) ) return NULL;
  else if( !xmlNodeIsText( node->children ) ) return NULL;
  else return node->children->content;
}

// www.tbi.univie.ac.at/~pmg/tutorials/gtk/gtk_2.0/gtk-object-properties.html

gboolean 
has_newline (const gchar *string)
{
int i;
int len = strlen(string);
    for (i = 0; i < len; i++) {
      if (string[i] == '\n') return TRUE;    
    }
    return FALSE;    
}

gchar *
g2c_stringify( const gchar *pstr )
{
  /* Take this string and wrap it in a _("%s") if
   * project->gettext_support is true. Otherwise use "%s".
   */
  gchar *result = NULL;
  gchar *temp = NULL;
  gchar  **lines    = NULL;
  guint i = 0;

  if( NULL != pstr )
    {
      if (has_newline(pstr)) {
          /*  deal with multi-line strings */
         lines = g_strsplit( pstr, "\n", 0 ); 
         while( NULL != lines[i] )
          {
             if (i == 0) {
                 temp = g_strdup_printf( "\"%s\\n\"",lines[0] );
             } else {
                 if (strlen(lines[i]) > 0) {
                   result = g_strconcat(temp, "\n\t\t\"", lines[i], "\\n\"", NULL);
                   g_free ( temp );
                   temp = result;
                 } else {
                   result = temp;
                 }
             }
             i++;
          }        
         
         g_strfreev( lines );
         return result;
      }
      if( CURRENT_PROJECT->gettext_support )
        {
          result = g_strdup_printf( "_(\"%s\")", g_strdelimit( (gchar *) pstr, "\"", '\'') );
        }
      else
        {
          result = g_strdup_printf( "\"%s\"", g_strdelimit( (gchar *) pstr, "\"", '\'') );
        }
    }
  else
    result = g_strdup( "\"\"" );

  return result; // Freed by caller
}

gboolean 
has_underscore (gchar *string)
{
int i;
int len = strlen(string);
    for (i = 0; i < len; i++) {
      if (string[i] == '_') return TRUE;    
    }
    return FALSE;    
}

gboolean 
isnumber(gchar *text)
{  /* number may have one decimal point or have one minus sign as first char   [i]n*[.[n*]] */
guint i = 0;
guint len = 0;
    if (text == NULL) return FALSE;
    len = strlen(text);
    if (text[i] == '-') i++;
    while (i < len) {
        if (!g_ascii_isdigit(text[i])) break;            
        i++;
    }
    if (i <len) {
        if (text[i] == '.') i++;            
    }
    while (i < len) {
        if (!g_ascii_isdigit(text[i++])) return FALSE;
    }
    return TRUE;
}

gboolean isinteger(gchar *text)
{   /*  only digits 0-9 allowed  */
guint i = 0;
guint len = 0;
    if (text == NULL) return FALSE;
    len = strlen(text);
    while (i < len) {
        if (!g_ascii_isdigit(text[i])) break;            
        i++;
    }
    if (i < len) return FALSE;
    return TRUE;
}

gboolean 
isalphanum(gchar *text)
{
guint i = 0;
guint len = 0;
    if (text == NULL) return FALSE;
    len = strlen(text);
    while (i < len) {
        if (!g_ascii_isalnum(text[i])) return FALSE;            
        i++;
    }
    return TRUE;
}

gchar *
remove_prefix(gchar * string)
{
gchar * str = NULL;
GString * Glabel = NULL;
GString * Gprefix = NULL;

    Glabel = g_string_new(string);
    Gprefix = g_string_new(string);
    Gprefix = g_string_truncate(Gprefix,4);
    if (strcmp(Gprefix->str, "gtk-") == 0)
        g_string_erase(Glabel, 0, 4);  // chops off 'gtk-'          
    str = g_strdup(Glabel->str);
    str[0] = g_ascii_toupper(str[0]);
    str =  g_strdelimit( str, "-", ' ' );
    g_string_free(Glabel, TRUE);
    g_string_free(Gprefix, TRUE);    
    return str;
}

void 
extract_signal(gchar **event, gchar **keystr, gchar **modifierstr, gchar *name)
{  /* e.g.  "accel-activate::&lt;cntrl&gt;-q"  =>  "accel-activate" and "&lt;cntrl&gt;-q"  */
gchar **parts = NULL;
gchar **fragments = NULL;
guint accelerator_key = 0;
GdkModifierType accelerator_mods = 0;
gchar acceler[20];
gchar *temp = NULL;
guint i;

     parts = g_strsplit(name, ":", -1);
     *event = g_strdup(parts[0]);
     if (parts[1] == NULL) {
         *keystr = g_strdup("");
         *modifierstr = g_strdup("");
         g_strfreev( parts );
         return;
     }
     g_assert(strlen(parts[1]) == 0);
     
    g_stpcpy(acceler, parts[2]);
    gtk_accelerator_parse(parts[2], &accelerator_key, &accelerator_mods);
    if ( (accelerator_key == 0) && (accelerator_mods == 0) ) {
        g_message("%s does not have a valid keystroke.\n", name);
        *keystr = g_strdup("");
        *modifierstr = g_strdup("");
        g_strfreev( parts );
        return;
    }
    fragments = g_strsplit(acceler, ">", -1);
    if ( (fragments[1] == 0) || (strlen(fragments[1]) == 0) ) {  /* if no modifier */
        *modifierstr = g_strdup("0");
        *keystr = g_strdup_printf( "GDK_KEY_%s", fragments[0] ); 
    } else {
        if ((accelerator_mods & GDK_SHIFT_MASK) != 0) {
            if (*modifierstr == NULL) {
               *modifierstr = g_strdup("GDK_SHIFT_MASK"); 
            } else {
                temp = *modifierstr;
                *modifierstr = g_strjoin (" | ", *modifierstr, "GDK_SHIFT_MASK", NULL);
                g_free ( temp );
            }
        } 
        if ((accelerator_mods & GDK_CONTROL_MASK) != 0) {
            if (*modifierstr == NULL) {
                *modifierstr = g_strdup("GDK_CONTROL_MASK");
            } else {
                *modifierstr = g_strjoin (" | ", *modifierstr, "GDK_CONTROL_MASK", NULL);
            }
        } 
        if ((accelerator_mods & GDK_MOD1_MASK) != 0) {
            if (*modifierstr == NULL) {
               *modifierstr = g_strdup("GDK_MOD1_MASK");
             } else {
               *modifierstr = g_strjoin (" | ", *modifierstr, "GDK_MOD1_MASK", NULL);
             }
        }
        if ((accelerator_mods & GDK_LOCK_MASK) != 0) {
            if (*modifierstr == NULL) {        
              *modifierstr = g_strdup("GDK_LOCK_MASK");
            } else {
               *modifierstr = g_strjoin (" | ", *modifierstr, "GDK_LOCK_MASK", NULL);
            }
        }
        if (*modifierstr == NULL) {
            g_message("%s does not have a valid keystroke.\n", name);
            //*keystr = g_strdup("");
            *modifierstr = g_strdup("0");
           //*modifierstr = g_strdup("GDK_UNKNOWN_MODIFIER");
        }
        for (i = 2; fragments[i] != NULL; i++) {}
        *keystr = g_strdup_printf( "GDK_KEY_%s", fragments[i-1] ); 
    }
     
     g_strfreev( parts );
     if (fragments != NULL)   g_strfreev( fragments );
}

void
g2c_hash_element_free_cb( gpointer key,
                          gpointer value,
                          gpointer user_data )
{
  g_free( key );
  g_free( value );
}

void
g2c_list_element_free_cb( gpointer data,
                          gpointer user_data )
{
  g_free( data );
}

gint
g2c_string_list_compare_cb (gconstpointer a,
			    gconstpointer b)
{
  return strcmp ((char*) a, (char*) b);
}

gchar *
g2c_transform_name( gchar *name, NameTransform transform )
{
  gchar   *result   = NULL;
  gchar   *concat   = NULL;
  gchar  **parts    = NULL;
  gint     i        = 0;
  gint     j        = 0;
  GString *s_result = NULL;
  gchar    next     = 0;

  switch( transform )
    {
    case NT_GUI:
      concat = g_strconcat( name, "_gui.h", NULL );
      result = g_utf8_strup( concat , strlen(concat));
      g_free( concat );
      result = g_strdelimit( result, ".", '_' );
      break;
    case NT_STANDARD:
      concat = g_strconcat( name, ".h", NULL );
      result = g_utf8_strup( concat, strlen(concat) );
      g_free( concat );
      result = g_strdelimit( result, ".", '_' );
      break;
    case NT_TYPENAME:
      /* This one is a little trickier.  We want to remove underscores, then
       * capitalize the letters that would come after the underscores, making
       * a proper type name.
       * 
       * Example:  my_new_widget ==> MyNewWidget
       */
      parts = g_strsplit( name, "_", 0 );

      /* The first letter of each string should be capitalized */

      while( NULL != parts[i] )
        {
          parts[i][0] = toupper( parts[i][0] );
          i++;
        }

      /* Put them all together */
      result = g_strjoinv( NULL, parts );

      /* Clean up */
      g_strfreev( parts );

      break;
    case NT_FUNCTION:
      /* When making gtk calls, you'll need to take a type name,
       * say GtkWidget, and call gtk_widget_whatever.  The input 
       * variable "name" is the type name for the widget.
       * This will transform "GtkWidget" to "gtk_widget".
       */
      s_result = g_string_new( "" );
      i        = 0;
      
      while( 0 != name[i] )
        {
          if( ( name[i] >= 'A' ) &&
              ( name[i] <= 'Z' ) )
            {
              next = tolower( name[i] );
              if( i != 0 ) g_string_append_c( s_result, '_' );
              g_string_append_c( s_result, next );
            }
          else
            {
              g_string_append_c( s_result, name[i] );
            }

          i++;
        }

      result = g_strdup( s_result->str );
      g_string_free( s_result, TRUE );
      break;
    case NT_CAPITALISE:
       /* Remove the beginning g, then capitalize all the remaining  */
       /* letters and prefix with G_TYPE_  e.g. guint => G_TYPE_UINT  */
      /* Exception:  gchararray => G_TYPE_STRING */
       if ( strcmp(name, "gchararray") == 0 ) {
           result = strdup("G_TYPE_STRING");
           break;
       }
       if ( strcmp(name, "GdkPixbuf") == 0 ) {
           result = strdup("GDK_TYPE_PIXBUF");
           break;
       }
       s_result = g_string_new( "" );
       i  =  1;
       
       while (name[i] != 0) {
           g_string_append_c( s_result, name[i++] );
       }
       g_string_ascii_up(s_result);
       g_string_prepend(s_result, "G_TYPE_");
       
      result = g_strdup( s_result->str );
      g_string_free( s_result, TRUE );        
      break;
    }

  return result; /* Freed by caller */
}

//gchar *
//get_big_type_name(gchar *type)
//{
//    
//}

gboolean
g2c_get_bool( const gchar *arg_value )
{
  if( NULL == arg_value )
    return FALSE;
  else if( g_ascii_strcasecmp( arg_value, "TRUE" ) == 0 )
    return TRUE;
  else
    return FALSE;
}

gchar *
g2c_get_bool_s( const gchar *arg_value )
{
  gchar *result = NULL;

  if( NULL == arg_value )
    result = g_strdup( "" );
  else if( ( strcasecmp( arg_value, "TRUE" ) == 0 ) ||
           ( strcasecmp( arg_value, "FALSE" ) == 0 ) )
    {
      result = g_ascii_strup( arg_value, strlen(arg_value) );
    }
  else
    result = g_strdup( arg_value );

  return result;
}

gchar *
g2c_get_bool_b ( const gboolean val )
{
    if (val == FALSE) return "FALSE";
    return "TRUE";
}

gchar *
g2c_format_argument( const gchar *arg_type_name,
                     const gchar *arg_name,
                     const gchar *arg_value )
{
  /* Using the type name, get the type of the argument, and
   * format the corresponding value based on the type.
   * For example, if the base type is GtkString, then the 
   * argument should be in quotes: "argument".  If the base
   * type is not a string, it should not have quotes: GTK_WINDOW_POPUP.
   * Null string values should be listed as "", and other null
   * values should return 0 or NULL (if a pointer type).
   * If the parameter does not have a known type, just use the value given.
   */

  gchar      *msg        = NULL;
  gchar      *result     = NULL;
  gchar      *temp       = NULL;
  GType       gtk_type;
  GtkArgInfo *arg_info   = NULL;
  gboolean numeric = TRUE;
  gchar  chbuf[10];
  int i;
  
  /* Get the GType, and make sure the class is loaded */
  gtk_type = g_type_from_name( arg_type_name );
  if (gtk_type != 0) 
      g_type_class_ref( gtk_type );  //  This function will demand-create the class if it doesn't exist already.

  if( NULL == arg_name ) return NULL;
    
  if( NULL == arg_value ) {
      return strdup("NULL");
  }
  
/*
  if ((isascii(arg_value[0]) == 0) || (isascii(arg_value[1]) == 0) ) {  // test if unicode or similar
      i = g_unichar_to_utf8((gunichar) arg_value[0], chbuf );
      chbuf[i] = '\0';
      return strdup(chbuf);
  }
*/
    
  if ((strcasecmp(arg_value,"true") == 0) || (strcasecmp(arg_value,"false") == 0)) {
      
      return g_utf8_strup(arg_value, strlen(arg_value));      
  }   
    
  for (i = 0; i <strlen(arg_value); i++) {
        if ((isdigit(arg_value[i]) == 0) && (arg_value[i] != '-') && (arg_value[i] != '.')) {
          numeric = FALSE; 
          break;
        }
  }
  if (numeric == TRUE) {      
       return strdup(arg_value);
  }    
    
  return g2c_stringify( arg_value );

}

gboolean
g2c_check_file_exists( gchar *filename )
{
  gboolean test = FALSE;
  FILE *file    = fopen( filename, "r" );

  test = ( NULL != file );

  if( test ) fclose( file );

  return test;
}

gchar *
round_float(gchar * value)
{
    if (value == NULL) return NULL;
    gdouble fvalue = strtod(value, NULL);
    return g_strdup_printf("%6.2f", fvalue);    
}

gchar *
make_enumeral(gchar * prefix, gchar * value)
{
gchar *upcase   = g_utf8_strup (value, strlen(value));
gchar *enumeral = g_strconcat( prefix, "_", g_strdelimit(upcase, ":-", '_' ), NULL );

    g_free( upcase );
    return enumeral;  /* caller must free */
}

void
proplist_add(g2cWidget *widget, const gchar* key, const gchar* value)
{
g2cProp *prop = g_new0( g2cProp, 1 );  //malloc (1, sizeof(g2cProp));
  prop->key = strdup(key);
  prop->value = strdup(value);
  widget->properties = g_list_append(widget->properties, (gpointer) prop);
}

void
attrlist_add(g2cWidget *widget, const gchar* key, const gchar* value)
{
g2cAttribute *attrib = g_new0( g2cAttribute, 1); 
  attrib->key = strdup(key);
  attrib->value = strdup(value);
  widget->attributes = g_list_append(widget->attributes, (gpointer) attrib);
}

gchar *
proplist_lookup(g2cWidget *widget, const gchar* key)  // return value is value or NULL
{
GList * item = g_list_first(widget->properties);
g2cProp *prop;
  while (item != NULL) {
      prop = (g2cProp *) item->data;
      if (strcmp(prop->key, key) == 0)
          return prop->value;
      item = item->next;
  }
  return NULL;
}

g2cProplist *
proplist_start(g2cWidget *widget)    //(start of iteration)
{
g2cProplist *proplist =  g_new0( g2cProplist, 1 ); //(g2cProplist *) malloc(1, sizeof(g2cProplist));
  proplist->widget = widget;
  proplist->key = NULL;
  proplist->value = NULL;
  proplist->position = g_list_first(widget->properties);
  return proplist;
}

gboolean
proplist_readnext(g2cProplist **proplist, gchar** key, gchar **value)  // if return value is FALSE, end of list
{
g2cProp *prop;
  if ((*proplist)->position == NULL) return FALSE;
  prop   = (g2cProp *) (*proplist)->position->data;  
  *key   = prop->key;   // no need to strdup: they are already stdup'ed in proplist_add
  *value = prop->value;
  (*proplist)->position = (*proplist)->position->next;
  return TRUE;
}

gboolean
proplist_end(g2cProplist *proplist)  //(end of iteration)
{
    g_free(proplist);
    return TRUE;
}

gboolean
proplist_destroy(g2cWidget *widget)
{
GList * item = g_list_first(widget->properties);
g2cProp *prop;
  while (item != NULL) {
      prop = (g2cProp *) item->data;
      if (NULL != prop->key) g_free(prop->key);
      if (NULL != prop->value) g_free(prop->value);
      g_free(prop);
      item = item->next;
  }
  g_list_free(widget->properties);
  return TRUE;    
}

gchar *make_widget_id()
{
    anon_counter++;
    return g_strdup_printf("widget%02d", anon_counter);
}

gboolean
file_exists(gchar* file_name)
{
struct stat s_stat;

    if( -1 == stat( file_name, &s_stat ) ) {
        if( ENOENT == errno )  {
            return FALSE;
        } else {
            g_error( "***file %s not accessible: error %d\n", file_name, errno);
        }
    } else {
        return TRUE;
    }
}  

void
g2c_copy_file(gchar *input, gchar *output)
{
FILE *file1;
FILE *file2;
gchar buffer[2048];

  file1 = fopen( input, "r" );
  if (file1 == NULL) {
      g_message ("File %s could not be opened. %s\n", input, strerror(errno));
      g_assert(file1 != NULL);  
  }

  file2 = fopen( output, "w" );
  if (file2 == NULL) {
      g_message ("File %s could not be opened. %s\n", output, strerror(errno));
      g_assert(file2 != NULL);  
  }

  while (fgets(buffer, 2047, file1) != NULL) {
	fputs(buffer,file2);
  };
  fclose( file2 );
  fclose( file1 );

}

void
coldata_add(GList **row, gint col_no, gchar* value)
{
g2cColdata *coldata = g_new0( g2cColdata, 1); 
    coldata->col_no = col_no;
    coldata->col_value = g_strdup(value);
    *row = g_list_append(*row, (gpointer) coldata);
}

void 
row_add(g2cWidget *widget, GList *row)
{
    widget->table = g_list_append(widget->table, (gpointer) row);
}

gchar*
make_column_value(g2cWidget *widget, gint pos, gchar *value)
{
GList *coltype = NULL;    
g2cColumn *column;
gint count = 0;
gchar *type = NULL;

    coltype = g_list_first(widget->columns);
    while (coltype != NULL) {
        column = (g2cColumn *) coltype->data;
        if (count == pos) {
           type = column->col_type;
           break;
        }
        count++;
        coltype = g_list_next(coltype);
    }
    g_assert(NULL != type);
    if ( ( strcmp(type,"gint") == 0 ) ||
         ( strcmp(type,"guint") == 0 ) ) {
        return value;
    } else if ( strcmp(type,"gboolean") == 0 ) {
        return g2c_get_bool_s(value);
    } else if ( strcmp(type,"gchararray") == 0 ) {
        return g2c_stringify(value);
    } else if ( strcmp(type,"GdkPixbuf") == 0 ) {
        return "pixbuf";
    }
    g_message("make_column_value: unexpected data type %s \n", type );
    return "";
}

void 
column_add(g2cWidget *main, gchar *col_name, gchar *col_type)
{
g2cColumn *col = g_new0( g2cColumn, 1);
    col->col_name = g_strdup(col_name);
    col->col_type = g_strdup(col_type);    
    main->columns = g_list_append(main->columns, (gpointer) col);
}

gchar *
icon_size_enum(gchar *size)
{   /*  g_free after use */
guint isize;
    if (g_ascii_isdigit(size[0])) {
        isize = atoi(size);    
        switch (isize) {
            case 0: return g_strdup("GTK_ICON_SIZE_INVALID");
            case 1: return g_strdup("GTK_ICON_SIZE_MENU");
            case 2: return g_strdup("GTK_ICON_SIZE_SMALL_TOOLBAR");
            case 3: return g_strdup("GTK_ICON_SIZE_LARGE_TOOLBAR");
            case 4: return g_strdup("GTK_ICON_SIZE_BUTTON");
            case 5: return g_strdup("GTK_ICON_SIZE_DND");
            case 6: return g_strdup("GTK_ICON_SIZE_DIALOG");
            default: return g_strdup("GTK_ICON_SIZE_INVALID");
        }
    } else {
        return make_enumeral("GTK_ICON_SIZE", size);
    }
}

gboolean
is_in_widget_list(GList *list, gchar *name)
{
GList *run = NULL;
g2cWidget *member = NULL;

    run = g_list_first(list);
     while (run != NULL) {
          member = (g2cWidget *) run->data;
          if (strcmp(member->name,name) == 0) {
              return TRUE;
          }
          run = g_list_next( run ); 
     }
    return FALSE;
}

gboolean is_widget_top_level(g2cWidget *global, gchar *name) 
{
GList *run = NULL;
g2cWidget *dialog = NULL;

    if ( strcmp( global->name, name ) == 0 )
        return TRUE;
    run = g_list_first(CURRENT_PROJECT->dialogue_widgets);
    while (run != NULL) {
        dialog = (g2cWidget *) run->data;
        if ( strcmp( dialog->name, name ) == 0 ) {
            return TRUE;
        }
        run = g_list_next(run);
    }
    return FALSE;                  
}

g2cWidget *get_dialog_widget_from_name(gchar *name)
{
GList *run;
g2cWidget *dialog;

    run = g_list_first(CURRENT_PROJECT->dialogue_widgets);
    while (run != NULL) {
        dialog = (g2cWidget *) run->data;
        if (strcmp(dialog->name, name) == 0) {
            return dialog;
        }        
        run = g_list_next(run);
    }
    if (strcmp(CURRENT_PROJECT->main_widget->name, name) == 0) {
        return CURRENT_PROJECT->main_widget;
    } else {
        return NULL;
    }
}

void
register_add(g2cWidget *main, gchar* name, g2cWidget *widget)
{
g2cRegister *reg =  g_new0( g2cRegister, 1 ); 
    reg->name = g_strdup(name);
    reg->widget = widget;
    reg->level = 0;
    main->regster = g_list_append(main->regster, (gpointer) reg);
    //g_message ("register %s\n", name);
}

void
register_free(g2cRegister *reg)
{
    g_free(reg->name);
    g_free(reg);
}

GList *
topregister_add(GList *topregster, g2cWidget *widget, gboolean bmain)
{
g2cTopRegister *reg =  g_new0( g2cTopRegister, 1 ); 
    reg->name = g_strdup(widget->name);
    reg->widget = widget;
    reg->level = 0;
    reg->bmain = bmain;    
    //g_message ("top register %s\n", name);
    return g_list_append(topregster, (gpointer) reg);
}

void
topregister_free(g2cTopRegister *reg)
{
    g_free(reg->name);
    g_free(reg);
}

void
free_top_register(gpointer data)
{
    topregister_free((g2cTopRegister *) data);
}

void
topregister_destroy(GList* topregster)
{
    g_list_free_full(topregster, free_top_register);
}

void 
top_requires_add(GList **top_list, gchar *requiring, gchar *required)
{
g2cRequires *req = g_new0( g2cRequires, 1);
    
    req->main = NULL;
    req->requiring = g_strdup(requiring);
    req->required = g_strdup(required);
    req->used = 0;
    *top_list = g_list_append(*top_list, (gpointer) req);
    //g_message ("top %s requires %s \n", requiring, required);
}

void
top_require_free(g2cRequires *require)
{
    g_free(require->requiring);
    g_free(require->required);
    g_free(require);
    return;
}

GList *
top_copy_requires(GList *requires)
{
GList *requires_item;
g2cRequires *require;
GList *new_list = NULL;
g2cRequires *req;

    requires_item = g_list_first(requires);
    while (requires_item != NULL) {
        require = (g2cRequires *) requires_item->data;         
        req = g_new0( g2cRequires, 1);
        req->main = NULL;
        req->requiring = g_strdup(require->requiring);
        req->required = g_strdup(require->required);
        req->used = 0;            
        new_list = g_list_append(new_list,  (gpointer) req);          
        requires_item = g_list_next( requires_item );    
    }
    return new_list;
}

void 
top_requires_destroy(GList *requires)
{
    g_list_free_full(requires, free_requires);
}

gboolean sort_top_list(GList **top_reg, GList **top_list)
{
g2cRequires *reqx;
GList *run;
g2cTopRegister *reg_requiring = NULL;
g2cTopRegister *reg_required = NULL;

gboolean bchange = FALSE;
guint count =0;
 
    if (top_detect_cycles(*top_list)) {
        return FALSE;
    }
    do {
        run = g_list_first(*top_list);
        bchange = FALSE;
        while (run != NULL) {           
            reqx = (g2cRequires *) run->data; 
            
            reg_requiring = find_top_widget_by_name(*top_reg, reqx->requiring);
            if (reg_requiring == NULL) {
                g_message("** widget %s requiring %s not found in sort***\n", reqx->requiring, reqx->required);
                return FALSE;
            }
            reg_required = find_top_widget_by_name(*top_reg, reqx->required);
            if (reg_required == NULL) {
                g_message("** widget %s required by %s not found in sort***\n", reqx->required, reqx->requiring);
                return FALSE;
            }
            if (reg_requiring->level <= reg_required->level) {
                reg_requiring->level = reg_required->level + 1;  // promote requiring widget
                //g_message("Widget %s promoted to level %d by %s\n", reqx->requiring, reg_requiring->level, reqx->required);
                bchange = TRUE;
            }
            run = g_list_next(run);
        }
        count++;
        if (count > 10) {
            g_message("Unable to complete sort: probable cycle\n");
            break;
        }
    } while (bchange == TRUE);
    return TRUE;
}

gboolean
top_detect_cycles(GList *top_requires_list)
{
GList *requires_item; 
g2cRequires *require;
GList *requires_copy = NULL;
GList *detect_copy = NULL;
GList *chain = NULL;
gchar *cycle;

    detect_copy = top_copy_requires( top_requires_list );
    requires_copy = top_copy_requires( top_requires_list );
    requires_item = g_list_first( detect_copy );
    while ( NULL != requires_item ) {
        require = (g2cRequires *) requires_item->data; 
        chain = g_list_append(chain, (gpointer) g_strdup(require->requiring));
        chain = g_list_append(chain, (gpointer) g_strdup(require->required));
        //g_message("build cycle chain from %s requires %s\n", require->requiring, require->required);
        cycle = build_cycle(&chain, detect_copy, requires_copy, require->required);
        if (cycle != NULL) {
            //g_message("   Cycle detected containing %s. \n", cycle);            
            return TRUE;
        }
        //print_out_chain(chain);
        delete_chain( chain ); 
        chain = NULL;
        //g_message("End of chain\n");
        requires_item = g_list_next( requires_item );
    }
    g_list_free_full(detect_copy, free_requires);
    g_list_free_full(requires_copy, free_requires);
    return FALSE;
}


gboolean is_dialogue_in_top_list(GList *top_list, gchar *name)
{
GList *run;  
g2cRequires *req;

    run = g_list_first(top_list);
    while (run != NULL)   {
        req = (g2cRequires *) run->data;
        if (strcmp(req->requiring, name) == 0) {
            return TRUE;
        }
        run = g_list_next( run );
    }
    return FALSE;      
}

/* widget is top-level window or dialog  */

void 
requires_add(g2cWidget *global, g2cWidget *widget, gchar *requiring, gchar *required)
{
g2cRequires *req = g_new0( g2cRequires, 1);
    req->main = widget;
    req->requiring = g_strdup(requiring);
    req->required = g_strdup(required);
    req->used = 0;
    global->requires = g_list_append(global->requires, (gpointer) req);
    //g_message ("%s requires %s for top-level %s\n", requiring, required, widget->name);
}

g2cRequires *
requires_copy(g2cRequires *require)
{
g2cRequires *req = g_new0( g2cRequires, 1);
    req->main = require->main;
    req->requiring = g_strdup(require->requiring);
    req->required = g_strdup(require->required);
    req->used = 0; 
    return req;
}

void
require_free(g2cRequires *require)
{
    g_free(require->requiring);
    g_free(require->required);
    g_free(require);
    return;
}

void print_out_register(g2cWidget *main)
{
GList *register_list;
g2cRegister *reg;

    register_list = g_list_first( main->regster );
    while ( NULL != register_list ) {
        reg = (g2cRegister *) register_list->data;
        g_message("%s %d\n", reg->name, reg->level);
        register_list = g_list_next( register_list );   
    }
}

void print_out_requires(GList *requires)
{
GList *require_item;
g2cRequires *require;

    require_item = g_list_first( requires );
    while ( NULL != require_item ) {
        require = (g2cRequires *) require_item->data;
        g_message("In %s, %s requires %s\n", require->main->name, require->requiring, require->required);
        require_item = g_list_next( require_item );   
    }
}

guint
get_max_register_level(g2cWidget *main)
{
GList *register_list;
g2cRegister *reg;
guint max_level = 0;

    register_list = g_list_first( main->regster );
    while ( NULL != register_list ) {
        reg = (g2cRegister *) register_list->data;        
        if ( reg->level > max_level ) max_level = reg->level;
        register_list = g_list_next( register_list );   
    } 
    return max_level;
}

guint
get_max_top_register_level(GList *register_list)
{
g2cTopRegister *reg;
GList *run = NULL;
guint max_level = 0;

    run = g_list_first( register_list );
    while ( NULL != run ) {
        reg = (g2cTopRegister *) run->data;        
        if ( reg->level > max_level ) max_level = reg->level;
        run = g_list_next( run );   
    } 
    return max_level;
}

g2cRegister *
find_widget_by_name(GList *register_list, gchar* name)
{
GList *register_item;
g2cRegister *reg;

    register_item = g_list_first( register_list );
    while ( NULL != register_item ) {
        reg = (g2cRegister *) register_item->data;        
        if ( strcmp(reg->name,name) == 0 ) {
            return reg;
        }
        register_item = g_list_next( register_item );   
    } 
    return NULL;    
}

g2cTopRegister *
find_top_widget_by_name(GList *register_list, gchar* name)
{
GList *register_item;
g2cTopRegister *reg;

    register_item = g_list_first( register_list );
    while ( NULL != register_item ) {
        reg = (g2cTopRegister *) register_item->data;        
        if ( strcmp(reg->name,name) == 0 ) {
            return reg;
        }
        register_item = g_list_next( register_item );   
    } 
    return NULL;    
}

void allocate_children(g2cWidget *global, g2cWidget *widget, g2cWidget *orphan)
{
GList *lchild;
g2cWidget *child;
    
    lchild = orphan->children;
    while (lchild != NULL) {
        child = (g2cWidget *) lchild->data;
        register_add(widget, child->name, child); 
        requires_add(global, widget, child->name, orphan->name);
        if (child->children != 0) {
            allocate_children(global, widget, child);
        }
        lchild = g_list_next( lchild );
    }       
}

/*  widget is top-level window or dialog  */
/*  orphan is widget as yet not allocated e.g. adjustment1 */
void allocate(g2cWidget *global, g2cWidget *widget, g2cWidget *orphan)
{
    if (strcmp(orphan->klass_name, "GtkAccelGroup") == 0) {
        widget->accel_widgets = g_list_append(widget->accel_widgets, orphan);
    } else if ( (strcmp(orphan->klass_name, "GtkMenu") == 0) ||                
                (strcmp(orphan->klass_name, "GtkPopover") == 0)  ||
                (strcmp(orphan->klass_name, "GtkPopoverMenu") == 0) ||
                (strcmp(orphan->klass_name, "GtkStatusIcon") == 0) )  {
        widget->popups = g_list_append(widget->popups, orphan);
    } else if ((strcmp(orphan->klass_name, "GtkListStore") == 0) || 
                (strcmp(orphan->klass_name, "GtkTreeStore") == 0)  ||  
                (strcmp(orphan->klass_name, "GtkTreeModelFilter") == 0)  || 
                (strcmp(orphan->klass_name, "GtkTreeModelSort") == 0)  || 
                (strcmp(orphan->klass_name, "GtkAdjustment") == 0) ||
                (strcmp(orphan->klass_name, "GtkTextBuffer") == 0) ||
                (strcmp(orphan->klass_name, "GtkTextTagTable") == 0) ||
                (strcmp(orphan->klass_name, "GtkEntryBuffer") == 0) ||
                (strcmp(orphan->klass_name, "GtkImage") == 0) ||
                (strcmp(orphan->klass_name, "GtkRecentFilter") == 0) ||
                (strcmp(orphan->klass_name, "GtkRecentManager") == 0) ||
                (strcmp(orphan->klass_name, "GtkEntryCompletion") == 0) ||
                (strcmp(orphan->klass_name, "GtkStack") == 0) ||
                (strcmp(orphan->klass_name, "GtkSizeGroup") == 0) ||
                (strcmp(orphan->klass_name, "GtkWindowGroup") == 0) ||
                (strcmp(orphan->klass_name, "GtkFileFilter") == 0) ||
                (strcmp(orphan->klass_name, "GtkLabel") == 0)  ) {
        widget->associates = g_list_append( widget->associates, orphan);
    } else {
        g_message("Unexpected orphan widget klass %s in allocation\n", orphan->klass_name);
    }
    register_add(widget, orphan->name, orphan);  
    allocate_children(global, widget, orphan);
}

gboolean is_widget_allocated(g2cWidget *global, g2cWidget *widget)
{
GList *run = NULL;
g2cWidget *dialog = NULL;

    if (  (is_in_widget_list(global->accel_widgets, widget->name) ) ||
          (is_in_widget_list(global->popups, widget->name) ) ||
          (is_in_widget_list(global->associates, widget->name) ) ) {
        return TRUE;
    }
    run = g_list_first(CURRENT_PROJECT->dialogue_widgets);
    while (run != NULL) {
            dialog = (g2cWidget *) run->data;
            if (  (is_in_widget_list(dialog->accel_widgets, widget->name) ) ||
                  (is_in_widget_list(dialog->popups, widget->name) ) ||
                  (is_in_widget_list(dialog->associates, widget->name) ) ) {
                return TRUE;
            }      
            run = g_list_next(run);
    }
    return FALSE;
}

/*  Go through the associates one by one and look for a requirement in the
 *  global list of requirements. If one is found, add to 
 *  associates for the widget against that requirement. If not found add to
 *  list of associates for the top level widget */
void allocate_orphans(g2cWidget *global, GList *associates)
{
GList *associate;
g2cWidget *orphan; 
GList *lreq;
g2cRequires *req;
g2cWidget *main_widget;   /*  top-level window or dialog */
gboolean allocated = FALSE;

    associate = g_list_first( associates );
    while ( associate != NULL ) {
        orphan = (g2cWidget *) associate->data;
        lreq = g_list_first( global->requires );
        allocated = FALSE;
        while (lreq != NULL) {
            req = (g2cRequires *) lreq->data;
            if (strcmp(orphan->name, req->required) == 0)  {
                main_widget = req->main;
                //  is main allocated or global or in the dialog_widgets? If not, skip
                if ( (is_widget_top_level(global, main_widget->name)  == TRUE)  ||
                     (is_widget_allocated(global, main_widget)  == TRUE) ) {
                    allocate(global, main_widget, orphan);                     
                    allocated = TRUE;
                    break;
                }
            }
            lreq = g_list_next( lreq );    
        }
        if (allocated == FALSE) {
           allocate(global, global, orphan);           
           //g_message("Default allocated %s to %s\n", orphan->name, global->name);
        }
        associate = g_list_next( associate );
    }
}

/*   analyse the register and requires list to ensure compilation in the right order */
/*   The register list has already been set up by scan_widgets_for_register  */
/*   The requires list has also been set up by scan_widgets_for_register  */
/*     which calls scan_properties_for_requires and scan_packing_for_requires */
void
analyse_requirements(g2cWidget *global, g2cWidget *main_widget)
{
guint Level = 1;
//GList *reg_list;
GList *register_list;
g2cRegister *reg;
gchar *current = NULL;
guint result;
guint max_level;
GList *popup_item;
g2cWidget *popup_widget;

    detect_cycles(global, main_widget);  // and if necessary remove one requires to break the cycle
    
    register_list = g_list_first( main_widget->regster );
    reg = (g2cRegister *) register_list->data;
    current = reg->name;
    reg->level = Level;
    
    popup_item = g_list_first(main_widget->popups);
    while (popup_item != NULL) {
        popup_widget = (g2cWidget *) popup_item->data;        
        reg = find_widget_by_name( main_widget->regster, popup_widget->name );
        reg->level = 1;
        popup_item = g_list_next( popup_item );
    }
    
    /*  top level widget now set up  */

    /*  scan requires list for requires entries where current is the required widget  */
    
    //scan_requires_list(main_widget, current, Level);
    max_level = get_max_register_level(main_widget);
    do {
      build_next_level(global, main_widget, Level, &result);
      Level++;
    } while (result > 0);

}
/*  used  */
void build_next_level(g2cWidget *global, g2cWidget *main_widget, guint level, guint *result)
{
guint next_level = level + 1; 
GList *layer_list = NULL;
GList *register_list;
g2cRegister *reg;
GList *requires_list; 
g2cRequires *require;
gboolean bFound;
guint returned_level = 0;
GList *layer_item1;
gchar *layer_name1;
GList *layer_item2;
gchar *layer_name2;
guint reglevel;

    *result = 0;
    // Build the layer list for current level
    register_list =  g_list_first( main_widget->regster );
    while ( NULL != register_list ) {
        reg = (g2cRegister *) register_list->data;
        reglevel = reg->level;
        if (reglevel == level) {
            layer_list = g_list_append(layer_list, (gpointer) reg->name);
        }        
        register_list = g_list_next( register_list );   
    }
    // look in requires list for item(s) where 'required' is in layer list
    requires_list = g_list_first( global->requires );
    while ( NULL != requires_list ) {
        require = (g2cRequires *) requires_list->data; 
        if (require->main == main_widget){
            if (require->used < 10) {
                bFound = find_in_layer(layer_list, require->required);
                if (bFound == TRUE) {
                    returned_level = set_widget_level(main_widget, require->requiring, next_level);
                    require->used++;               
                    if (returned_level > 0) {                
                        if (returned_level < next_level) {
                            g_message("Re-ordering suggestion: %s needs to be positioned in the Glade file before %s.\n", require->required, require->requiring );                       
                        }
                        (*result)++;
                    }
                }
            }
        }
        requires_list = g_list_next( requires_list );
    }
    // looks through layer list to find requires relationships between siblings/members
    
    layer_item1 = g_list_first( layer_list );
    while ( NULL != layer_item1 ) {
        layer_name1 = (gchar *) layer_item1->data;        
        layer_item2 = g_list_first( layer_list );
        while ( NULL != layer_item2 ) {
            layer_name2 = (gchar *) layer_item2->data;
            if (strcmp(layer_name1,layer_name2) != 0) {
                bFound = find_required(global, main_widget, layer_name1, layer_name2);
                if (bFound == TRUE) {
                    // demote layer_name1 which requires layer_name2
                    set_widget_level(main_widget, layer_name1, next_level);                    
                }
            }
            layer_item2 = g_list_next( layer_item2 );
        }        
        layer_item1 = g_list_next( layer_item1 );
    }
    /*  free layer list */
    //g_list_free_full( layer_list, free_layer_name );
    g_list_free( layer_list );
}

void 
free_layer_name(gpointer data)
{
    g_free( (gchar *) data);
}

/*  not used */
/*  create a new list of requires omitting any require matching  
    the supplied required and requiring */
GList *
list_remove(GList *list, gchar *requiring, gchar* required)
{
GList *requires_item; 
g2cRequires *require;
GList *new_list = NULL;
g2cRequires *req;

    requires_item = g_list_first( list );
    while ( NULL != requires_item ) {
        require = (g2cRequires *) requires_item->data; 
        if ((strcmp(require->required, required) != 0) ||
            (strcmp(require->requiring, requiring) != 0) )   {
            req = g_new0( g2cRequires, 1);
            req->main = require->main;
            req->requiring = g_strdup(require->requiring);
            req->required = g_strdup(require->required);
            req->used = 0;            
            new_list = g_list_append(new_list,  (gpointer) req);
        }        
        requires_item = g_list_next( requires_item );
    }
    return new_list;
}

//GList *
//list_copy(GList *list)
//{
//GList *requires_item; 
//g2cRequires *require;
//GList *new_list = NULL;
//g2cRequires *req;
//
//    requires_item = g_list_first( list );
//    while ( NULL != requires_item ) {
//        require = (g2cRequires *) requires_item->data;  
//        req = g_new0( g2cRequires, 1);
//        req->requiring = g_strdup(require->requiring);
//        req->required = g_strdup(require->required);
//        req->used = 0;            
//        new_list = g_list_append(new_list,  (gpointer) req);                
//        requires_item = g_list_next( requires_item );
//    }
//    return new_list;
//}

void
delete_chain(GList *chain)
{
GList *chain_member; 

    chain_member = g_list_first(chain);
    while (chain_member != NULL)  {
        g_free( chain_member->data );
        chain_member = g_list_next( chain_member );
    } 
    g_list_free (chain);
}

void print_out_chain(GList *chain)
{
GList *chain_item;
gchar *chain_member;

    chain_item = g_list_first(  chain );
    while ( NULL != chain_item ) {
        chain_member = (gchar *) chain_item->data;
        g_message(" %s ", chain_member);
        chain_item = g_list_next( chain_item );   
    }
    g_message("\n");
}
gboolean 
check_list_contains(GList **chain, gchar *required)
{
GList *chain_member; 
gchar *char_member;

    chain_member = g_list_first(*chain);
    while (chain_member != NULL)  {
        char_member = (gchar *) chain_member->data;
        if (strcmp(char_member, required) == 0) {
            return TRUE;
        }
        chain_member = g_list_next( chain_member );
    }
    return FALSE;
}

g2cRequires *
find_linked_require(GList *requires_copy_of, gchar *requiring)
{
GList *requires_item; 
g2cRequires *require;

    requires_item = g_list_first( requires_copy_of );
    while ( NULL != requires_item ) {
        require = (g2cRequires *) requires_item->data; 
        if (strcmp(require->requiring, requiring) == 0) {
            return requires_copy(require);
        }
        requires_item = g_list_next( requires_item );
    }
    return NULL;
}

// used by g_list_free_full
void free_requires(gpointer data)
{
    require_free((g2cRequires *) data);
}

gchar *
build_cycle(GList **chain, GList *detect_copy, GList *requires_copy, gchar *next)
{
gchar *required = NULL; 
gchar *requiring = NULL;
g2cRequires *require;
gboolean bFound;
gchar *cycle;
//GList  *old_requires = NULL;

    require = find_linked_require(requires_copy, next);  // returns g2cRequire where requiring = supplied next
    while (require != NULL) {  
        if (required != NULL) g_free( required );
        if (requiring != NULL) g_free( requiring );
        required = g_strdup(require->required);   
        requiring = g_strdup(require->requiring);  // = next first time round
        bFound = check_list_contains(chain, required);
        if (bFound == TRUE) {
            //this is a cycle:   remove require from main->requires
            g_message("chain: %s %s\n", required, requiring);
            print_out_chain(*chain);
            g_message("Cycle detected: suggest removing requirement of\n\t\twidget %s for widget %s\n", requiring, required);
            //old_requires = main->requires;
            //main->requires = list_remove(main->requires, requiring, required); 
            //g_list_free_full(old_requires, free_requires);
            if (requiring != NULL) g_free( requiring );
            return required;
        }
        *chain = g_list_append(*chain, (gpointer) g_strdup(required)); 
        require_free(require);
        require = find_linked_require(requires_copy, required);
    };
    if (requiring != NULL) g_free( requiring );
    if (required != NULL) g_free( required );
    return NULL;
}
/*  Copy the requires items only for the supplied top_window/dialog */
GList *copy_requires(g2cWidget *main_widget, GList *requires)
{
GList *requires_item;
g2cRequires *require;
GList *new_list = NULL;
g2cRequires *req;

    requires_item = g_list_first(requires);
    while (requires_item != NULL) {
        require = (g2cRequires *) requires_item->data; 
        if (strcmp(require->main->name, main_widget->name) == 0) {
            req = g_new0( g2cRequires, 1);
            req->main = require->main;
            req->requiring = g_strdup(require->requiring);
            req->required = g_strdup(require->required);
            req->used = 0;            
            new_list = g_list_append(new_list,  (gpointer) req);  
        }        
        requires_item = g_list_next( requires_item );    
    }
    return new_list;
}

gboolean
detect_cycles(g2cWidget *global, g2cWidget *main)
{
GList *requires_item; 
g2cRequires *require;
GList *requires_copy = NULL;
GList *detect_copy = NULL;
GList *chain = NULL;
gchar *cycle;

    detect_copy = copy_requires( main, global->requires );
    requires_copy = copy_requires( main, global->requires );
    requires_item = g_list_first( detect_copy );
    while ( NULL != requires_item ) {
        require = (g2cRequires *) requires_item->data; 
        chain = g_list_append(chain, (gpointer) g_strdup(require->requiring));
        chain = g_list_append(chain, (gpointer) g_strdup(require->required));
        //g_message("build cycle chain from %s requires %s\n", require->requiring, require->required);
        cycle = build_cycle(&chain, detect_copy, requires_copy, require->required);
        if (cycle != NULL) {
            //g_message("   Cycle detected containing %s. \n", cycle);  
            g_free( cycle );
            return FALSE;
        }
        //print_out_chain(chain);
        delete_chain( chain ); 
        chain = NULL;
        //g_message("End of chain\n");
        requires_item = g_list_next( requires_item );
    }
    g_list_free_full(detect_copy, free_requires);
    g_list_free_full(requires_copy, free_requires);
    return FALSE;
}

gboolean
find_required(g2cWidget *global, g2cWidget *main, gchar *requiring, gchar *misplaced)
{  // existence of requires item that links requiring item to misplaced (required)
GList *requires_list; 
g2cRequires *requires;
    
    requires_list = g_list_first( global->requires );
    while ( NULL != requires_list ) {
        requires = (g2cRequires *) requires_list->data;  
        if (strcmp(requires->main->name, main->name) == 0) {
            if (requires->used < 10) {
                if ((strcmp(requires->requiring,requiring) == 0) &&
                    (strcmp(requires->required,misplaced) == 0) ) {
                    requires->used++;
                    return TRUE;
                }
            }
        }
        requires_list = g_list_next( requires_list );
    }
    return FALSE;
}

/*  used  */
gint
set_widget_level(g2cWidget *main, gchar *name, gint level)
{   // scanning register list to set named item to the supplied level
GList *register_list;
g2cRegister *reg;

    register_list =  g_list_first( main->regster );
    while ( NULL != register_list ) {
        reg = (g2cRegister *) register_list->data;
        if (strcmp(reg->name, name) == 0 ) {
            if (reg->level != 0) {
                if (reg->level == level)  return level;
                //g_message("level changed for %s from %d to %d\n", name, reg->level, level);
                reg->level = level;
                return reg->level;
            } else {
                reg->level = level;
                return level;
            }
        }
        register_list = g_list_next( register_list );        
    }
    return 0;
}

/*  used  */
gboolean
find_in_layer(GList *layer_list, gchar *required)
{
GList *list_member;
gchar *layer_name;

    list_member = g_list_first(layer_list);
    while ( NULL != list_member ) {
       layer_name = (gchar *) list_member->data;
       if (strcmp(layer_name, required) == 0) {
           return TRUE;
       }          
       list_member = g_list_next(list_member);
    }
    return FALSE;
}
/*  NOT used  */
void
scan_requires_list(g2cWidget *main, gchar* current, gint level)
{
gint returned_level;
GList *requires_list; 
g2cRequires *requires;

    level++;
    requires_list = g_list_first( main->requires );
    while ( NULL != requires_list ) {
        requires = (g2cRequires *) requires_list->data;    
        if (strcmp(requires->required, current) == 0) {
            /*   then set the level of the requiring widget in the register to the new level no. */
            returned_level = set_widget_level(main, requires->requiring, level);
            if (returned_level == 0) {
                g_message("Failed to find requiring widget %s in register\n", requires->requiring);
                break;
            }
            if (returned_level < level) {
                //g_message("demotion of %s needed\n", requires->requiring );
                break;
            }
            scan_requires_list(main, requires->requiring, level);
        }
        requires_list = g_list_next( requires_list );
    } 
}
/*  not used  */
void check_requires(g2cWidget *main)
{
GList *widget_list;
g2cRequires *req;
g2cRegister *reg;

    widget_list = g_list_first( main->requires);
     while ( NULL != widget_list )   {        
        req  = (g2cRequires *) widget_list->data;
        reg = find_widget_by_name( main->regster, req->required );
        if (reg == NULL) {
            g_message("Required widget %s required by %s in %s missing\n", req->required, req->requiring, main->name);
        }
        widget_list = g_list_next( widget_list ); 
     }
    
}
/*       Sets up register list of widgets for each window/dialog        */
/*        The hierarchy of widgets is flattened                         */
/*        Each register entry is a struct which has the name and the widget object */
void
scan_widgets_for_register(g2cWidget *global, g2cWidget *main, g2cWidget *widget)
{
GList *widget_list;
g2cWidget *child;

    register_add(main, widget->name, widget);
    scan_properties_for_requires(global, main, widget);
    scan_packing_for_requires(global, main, widget);
    
    widget_list = g_list_first( widget->children );    
    while ( NULL != widget_list )   {         
          child = (g2cWidget *) widget_list->data;
          /*  recurse down  */
          scan_widgets_for_register(global, main, child);           
          widget_list = g_list_next( widget_list );
    }
    
    widget_list = g_list_first( widget->associates ); 
    while ( NULL != widget_list )   {         
          child = (g2cWidget *) widget_list->data;
          scan_widgets_for_register(global, main, child);
          widget_list = g_list_next( widget_list );
    }
    
//    widget_list = g_list_first( widget->accel_widgets );    
//    while ( NULL != widget_list )   {         
//          child = (g2cWidget *) widget_list->data;
//          scan_widgets_for_register(global, main, child);
//          widget_list = g_list_next( widget_list );
//    }
//    
//    widget_list = g_list_first( widget->popups );    
//    while ( NULL != widget_list )   {         
//          child = (g2cWidget *) widget_list->data;
//          scan_widgets_for_register(global, main, child);
//          widget_list = g_list_next( widget_list );
//    }
    //check_requires(main);
}

void
scan_orphans_for_register(g2cWidget *global, GList *orphans)
{
GList *orphan_list;
g2cWidget *orphan;
GList *widget_list;
g2cWidget *child;

    orphan_list = g_list_first( orphans ); 
    while (orphan_list != NULL) {
        orphan = (g2cWidget *) orphan_list->data;
        //register_add(global, global->name, orphan);
        scan_properties_for_requires(global, global, orphan);
        scan_sizegroup_for_requires(global, global, orphan);
        orphan_list = g_list_next(orphan_list);
        
        widget_list = g_list_first( orphan->children );    
        while ( NULL != widget_list )   {         
              child = (g2cWidget *) widget_list->data;
              /*  recurse down  */
              scan_widgets_for_register(global, orphan, child);           
              widget_list = g_list_next( widget_list );
        }
    } 
}

void 
scan_packing_for_requires(g2cWidget *global, g2cWidget *main, g2cWidget *widget)
{
    if ( widget->parent == NULL ) return;
    
    if ( (widget->parent->packing_type == BOX_PACKING) ||
         (widget->parent->packing_type == GRID_PACKING) ){
        requires_add(global, main, widget->name, widget->parent->name);
    }
    return;
}

void
scan_sizegroup_for_requires(g2cWidget *global, g2cWidget *main, g2cWidget *widget)
{
GList * item = NULL;
gchar *member = NULL;

    if ( widget->sizegroup == NULL) return;
    item = g_list_first(widget->sizegroup);
    while (item != NULL) {
        member = (gchar *) item->data;        
        requires_add(global, main, widget->name, member);
        item = item->next;
    }   /*  end while  */
}

void
scan_properties_for_requires(g2cWidget *global, g2cWidget *main, g2cWidget *widget)
{
GList * item = g_list_first(widget->properties);
g2cProp *prop;
  while (item != NULL) {
      prop = (g2cProp *) item->data;
      if (strcmp(prop->key,"stack") == 0) {      
        requires_add(global, main, widget->name, prop->value);
        if ((strcmp(widget->klass_name, "GtkStackSwitcher") != 0) &&
            (strcmp(widget->klass_name, "GtkStackSidebar") != 0) ) {
            //g_message("stack property found for %s\n", widget->klass_name );
        }
      }
      if (strcmp(prop->key,"menu_name") == 0) {      
        requires_add(global, main, widget->name, prop->value);
//        if (strcmp(widget->klass_name, "GtkModelButton") != 0) {
//            g_message("menu name property found for %s\n", widget->klass_name );
//        }
      }
      // property "group" is not being monitored because when a radiobutton, radiomenuitem
      // or radiotoolbutton is being created it may refer to an as yet undeclared radiobutton, 
      // radiomenuitem or radiotoolbutton without raising an error or warning.
      if (strcmp(prop->key,"buffer") == 0) {      
        requires_add(global, main, widget->name, prop->value);
        if ((strcmp(widget->klass_name, "GtkEntry") != 0) &&
            (strcmp(widget->klass_name, "GtkSearchEntry") != 0) &&
            (strcmp(widget->klass_name, "GtkTextView") != 0) &&
            (strcmp(widget->klass_name, "GtkSpinButton") != 0) ) {
            //g_message("buffer property found for %s\n", widget->klass_name );
        }
      }
      if (strcmp(prop->key,"completion") == 0) {      
        requires_add(global, main, widget->name, prop->value);
        if ((strcmp(widget->klass_name, "GtkEntry") != 0) &&
            (strcmp(widget->klass_name, "GtkSearchEntry") != 0) ) {
            //g_message("completion property found for %s\n", widget->klass_name );
        }
      }
      if (strcmp(prop->key,"model") == 0) {      
        requires_add(global, main, widget->name, prop->value);
        if ( (strcmp(widget->klass_name, "GtkTreeView") != 0) &&
             (strcmp(widget->klass_name, "GtkEntryCompletion") != 0) ) {
            //g_message("model name property found for %s\n", widget->klass_name );
        }
      }
      if (strcmp(prop->key,"accel_group") == 0) {      
        requires_add(global, main, widget->name, prop->value);
        if ((strcmp(widget->klass_name, "GtkMenu") != 0) &&
            (strcmp(widget->klass_name, "GtkImageMenuItem") != 0) ) {
            //g_message("accel_group property found for %s\n", widget->klass_name );
        }
      }
      if (strcmp(prop->key,"image") == 0) {      
        requires_add(global, main, widget->name, prop->value);
        if ((strcmp(widget->klass_name, "GtkButton") != 0) &&
            (strcmp(widget->klass_name, "GtkCheckbutton") != 0) &&
            (strcmp(widget->klass_name, "GtkTogglebutton") != 0) &&
            (strcmp(widget->klass_name, "GtkRadiobutton") != 0) ) {
            //g_message("image property found for %s\n", widget->klass_name );
        }
      }
      if (strcmp(prop->key,"adjustment") == 0) {      
        requires_add(global, main, widget->name, prop->value);
        if ((strcmp(widget->klass_name, "GtkScrollbar") != 0) &&
            (strcmp(widget->klass_name, "GtkSpinButton") != 0) &&
            (strcmp(widget->klass_name, "GtkScale") != 0) ) {
            //g_message("adjustment property found for %s\n", widget->klass_name );
        }
      }
      if (strcmp(prop->key,"hadjustment") == 0) {      
        requires_add(global, main, widget->name, prop->value);
        if ((strcmp(widget->klass_name, "GtkViewport") != 0) &&
            (strcmp(widget->klass_name, "GtkScrolledWindow") != 0) &&
            (strcmp(widget->klass_name, "GtkToolPalette") != 0) &&
            (strcmp(widget->klass_name, "GtkTreeview") != 0) ) {
            //g_message("hadjustment property found for %s\n", widget->klass_name );
        }
      }
      if (strcmp(prop->key,"vadjustment") == 0) {      
        requires_add(global, main, widget->name, prop->value);
        if ((strcmp(widget->klass_name, "GtkViewport") != 0) &&
            (strcmp(widget->klass_name, "GtkScrolledWindow") != 0) &&
            (strcmp(widget->klass_name, "GtkToolPalette") != 0) &&
            (strcmp(widget->klass_name, "GtkTreeview") != 0) ) {
            //g_message("vadjustment property %s found for %s\n", prop->value, widget->klass_name );
        }
      }
      if (strcmp(prop->key,"label_widget") == 0) {      
        requires_add(global, main, widget->name, prop->value);
        if ( (strcmp(widget->klass_name, "GtkToolButton") != 0) &&
             (strcmp(widget->klass_name, "GtkMenuToolButton") != 0) &&
             (strcmp(widget->klass_name, "GtkToggleToolButton") != 0) ) {
            //g_message("label_widget name property found for %s\n", widget->klass_name );
        }
      }
      if (strcmp(prop->key,"widget") == 0) {      
        requires_add(global, main, widget->name, prop->value);
        if (strcmp(widget->klass_name, "GtkTreeViewColumn") != 0) {
            //g_message("widget name property found for %s\n", widget->klass_name );
        }
      }
      if (strcmp(prop->key,"_submenu") == 0) {      
        requires_add(global, main, widget->name, prop->value);
        if (strcmp(widget->klass_name, "GtkBox") != 0) {
            //g_message("submenu name property found for %s\n", widget->klass_name );
        }
      }
      if (strcmp(prop->key,"popover") == 0) {      
        requires_add(global, main, widget->name, prop->value);
        //g_message("popover name property found for %s\n", widget->klass_name );
      }
      if (strcmp(prop->key,"filter") == 0) {      
        requires_add(global, main, widget->name, prop->value);
        //g_message("filter name property found for %s\n", widget->klass_name );
      }
      if (strcmp(prop->key,"recent_manager") == 0) {      
        requires_add(global, main, widget->name, prop->value);
        //g_message("recent_manager name property found for %s\n", widget->klass_name );
      }
      if (strcmp(prop->key,"transient_for") == 0) {      
        requires_add(global, main, widget->name, prop->value);
        //g_message("transient for property found for %s\n", widget->klass_name );
      }
      if (strcmp(prop->key,"popup") == 0) {      
        requires_add(global, main, widget->name, prop->value);
        //g_message("popup property found for %s\n", widget->klass_name );
      }
      /* no code is generated for relative_to */
      //if (strcmp(prop->key,"relative_to") == 0) {      
      //   requires_add(global, main, widget->name, prop->value);
         //g_message("relative_to property found for %s\n", widget->klass_name );
      //}
      if (strcmp(prop->key,"accel_widget") == 0) {      
         requires_add(global, main, widget->name, prop->value);
         //g_message("accel_widget property found for %s\n", widget->klass_name );
      }
      if (strcmp(prop->key,"align_widget") == 0) {      
         requires_add(global, main, widget->name, prop->value);
         //g_message("align_widget property found for %s\n", widget->klass_name );
      }
      if (strcmp(prop->key,"child_model") == 0) {      
         requires_add(global, main, widget->name, prop->value);
         //g_message("child_model property found for %s\n", widget->klass_name );
      }
      if (strcmp(prop->key,"tag_table") == 0) {      
         requires_add(global, main, widget->name, prop->value);
         //g_message("tag_table property found for %s\n", widget->klass_name );
      }
      if (strcmp(prop->key,"dialog") == 0) {      
         requires_add(global, main, widget->name, prop->value);
         g2cWidget *top_widget = g2c_widget_get_top_parent(widget);
         requires_add(global, main, top_widget->name, prop->value);
         //g_message("dialog property found for %s in %s\n", widget->klass_name, top_widget->name );
      }
      item = item->next;
  }   /*  end while  */
  return;    
}


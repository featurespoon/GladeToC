#include "g2c_helpers.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <gtk/gtk.h>

#include "config.h"

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
                 }
             }
             i++;
          }        
         
         g_strfreev( lines );
         return result;
      }
      if( CURRENT_PROJECT->gettext_support )
        {
          result = g_strdup_printf( "_(\"%s\")", pstr );
        }
      else
        {
          result = g_strdup_printf( "\"%s\"", pstr );
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
         return;
     }
     g_assert(strlen(parts[1]) == 0);
     g_stpcpy(acceler, parts[2]);
     gtk_accelerator_parse(parts[2], &accelerator_key, &accelerator_mods);
     fragments = g_strsplit(acceler, ">", -1);
     if (strlen(fragments[1]) == 0) {  /* if no modifier */
         *modifierstr = g_strdup("");
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
            *modifierstr = g_strdup("GDK_UNKNOWN_MODIFIER");
         }
         for (i = 2; fragments[i] != NULL; i++) {}
         *keystr = g_strdup_printf( "GDK_KEY_%s", fragments[i-1] ); 
     }
     g_strfreev( parts );
     g_strfreev( fragments );
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
  gchar  **parts    = NULL;
  gint     i        = 0;
  gint     j        = 0;
  GString *s_result = NULL;
  gchar    next     = 0;

  switch( transform )
    {
    case NT_GUI:
      result = g_strconcat( name, "_gui.h", NULL );
      g_utf8_strup( result , strlen(result));
      result = g_strdelimit( result, ".", '_' );
      break;
    case NT_STANDARD:
      result = g_strconcat( name, ".h", NULL );
      g_utf8_strup( result, strlen(result) );
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
    
  return g2c_stringify(arg_value);

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
    return g_strconcat( prefix, "_", g_strdelimit(g_utf8_strup (value, strlen(value) ),":-", '_' ), NULL );
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
 //     g_free(prop->key);
//      g_free(prop->value);
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
    

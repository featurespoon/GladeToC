#ifndef G2C_HELPERS_H
#define G2C_HELPERS_H

#include <glib.h>
#include <string.h>
#include <errno.h>
#include <libxml/parser.h>
#include "g2c_widget.h"
#include "g2c_project.h"

/* Helper types/enums */

typedef enum tag_NameTransform  
{ 
	NT_GUI,
	NT_STANDARD,
	NT_TYPENAME,
	NT_FUNCTION,
        NT_CAPITALISE
} NameTransform;

typedef struct _GtkArgInfo
{
  /* hash key portion */
  GType class_type;
  gchar *name;
  
  GType type;
  guint arg_flags;
  gchar *full_name;
  
  /* private fields */
  guint arg_id;
  guint seq_id;
} GtkArgInfo;

typedef struct _g2cProplist    // struct to base iterations on.
{
   g2cWidget *widget;
   gchar * key;
   gchar * value;
   GList *position;
} g2cProplist ;

typedef struct _g2cProp   // forms the data part of the list
{
   gchar * key;
   gchar * value;
} g2cProp;

typedef struct _g2cAttribute   //  label attribute
{
   gchar * key;
   gchar * value;
} g2cAttribute;

gchar *spaces_to_ulines( gchar *input );
const xmlChar *get_node_name( xmlNodePtr node );
const xmlChar *get_node_text( xmlNodePtr node );
const xmlChar *get_attr_node_name( xmlAttrPtr node );
const xmlChar *get_attr_node_text( xmlAttrPtr node );
const xmlNodePtr get_next_node( xmlNodePtr node );
const xmlNodePtr get_first_child( xmlNodePtr node );

gchar *g2c_stringify( const gchar *pstr );

gboolean has_newline (const gchar *string);

gboolean has_underscore (gchar *string);

gboolean isnumber(gchar *text);

gboolean isalphanum(gchar *text);

gchar *remove_prefix(gchar * string);

//void extract_signal(gchar **event, guint *key, GdkModifierType *modifier, gchar *name);
void extract_signal(gchar **event, gchar **keystr, gchar **modifierstr, gchar *name);

void g2c_hash_element_free_cb( gpointer key,
                               gpointer value,
                               gpointer user_data );

void g2c_list_element_free_cb( gpointer data,
                               gpointer user_data );

gint
g2c_string_list_compare_cb (gconstpointer a,
			    gconstpointer b);

gchar *
g2c_transform_name( gchar *name, NameTransform transform );

gchar *
g2c_format_argument( const gchar *arg_type_name, 
		     const gchar *arg_name,
		     const gchar *arg_value );

gboolean
g2c_get_bool( const gchar *arg_value );

gchar *
g2c_get_bool_s( const gchar *arg_value );

gchar *
g2c_get_bool_b ( const gboolean val );

gboolean 
g2c_check_file_exists( gchar *filename );

gchar *
round_float(gchar * value);

gchar *
make_enumeral(gchar * prefix, gchar * value);

GList*
proplist_new();   // probably not needed

void
proplist_add(g2cWidget *widget, const gchar* key, const gchar* value);

gchar *
proplist_lookup(g2cWidget *widget, const gchar* key);  // return value is value or NULL

g2cProplist *
proplist_start(g2cWidget *widget);     //(start of iteration)

gboolean
proplist_readnext(g2cProplist **proplist, gchar** key, gchar **value);  // if return value is FALSE, end of list

gboolean
proplist_end(g2cProplist *proplist);  //(end of iteration)

gboolean
proplist_destroy(g2cWidget *widget);

void
attrlist_add(g2cWidget *widget, const gchar* key, const gchar* value);

gchar *
get_big_type_name(gchar *type);

gchar *
make_widget_id();

gboolean
file_exists(gchar* file_name);

void
g2c_copy_file(gchar *input, gchar *output);

void 
column_add(g2cWidget *main, gchar *col_name, gchar *col_type);

void
coldata_add(GList **collist, gint col_no, gchar* value);

gchar*
make_column_value(g2cWidget *widget, gint pos, gchar *value);

gchar *
icon_size_enum(gchar *size);

gboolean
is_in_widget_list(GList *list, gchar *name);

void 
row_add(g2cWidget *widget, GList *row);

void
register_add(g2cWidget *main, gchar* name, g2cWidget *widget);

void
requires_add(g2cWidget *main, gchar *requires, gchar *required);

g2cRequires *
requires_copy(g2cRequires *require);

void
require_free(g2cRequires *require);

void 
free_requires(gpointer data);

void
scan_widgets_for_register(g2cWidget *main, g2cWidget *widget);

void
scan_properties_for_requires(g2cWidget *main, g2cWidget *widget);

void 
scan_packing_for_requires(g2cWidget *main, g2cWidget *widget);

g2cRegister *
find_widget_by_name(GList *register_list, gchar* name);

void
analyse_requirements(g2cWidget *main);

gint
set_widget_level(g2cWidget *main, gchar *name, gint level);

void
scan_requires_list(g2cWidget *main, gchar* current, gint level);

void 
build_next_level(g2cWidget *main, guint level, guint *result);

gboolean
find_in_layer(GList *layer_list, gchar *required);

gboolean
find_required(g2cWidget *main, gchar *requiring, gchar *misplaced);

guint
get_max_register_level(g2cWidget *main);

GList *
list_remove(GList *list, gchar *requiring, gchar* required);

GList *
list_copy(GList *list);

gboolean
detect_cycles(g2cWidget *main);

gchar *
build_cycle(GList **chain, g2cWidget *main, GList *detect_copy, GList *requires_copy, gchar *next);

gboolean 
check_list_contains(GList **chain, gchar *required);

g2cRequires *
find_linked_require(GList *requires_copy, gchar *requiring);

void 
print_out_register(g2cWidget *main);

void print_out_chain(GList *chain);

void print_out_requires(GList *requires);

#endif

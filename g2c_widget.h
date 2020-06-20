#ifndef G2C_WIDGET_H
#define G2C_WIDGET_H

#include <stdio.h>
#include <gtk/gtk.h>
#include <libxml/parser.h>
#include "g2c_signal.h"
#include "g2c_accel.h"
//#include "g2c_doc.h"

#define MAX_CREATE_PARAMS 10

int allocs;

typedef enum
{
  BOX_PACKING,
  GRID_PACKING,
  LABEL_PACKING
}  g2cPackType;

typedef enum
{
    PACK_START = 13,
    PACK_END
} g2cPackDirection;

typedef struct tag_g2cBoxPacking
  {
    gboolean expand;
    gboolean fill;
    guint    padding;
    gboolean homogeneous;
    g2cPackDirection pack_type;
  }
g2cBoxPacking;

typedef struct tag_g2cLabelPacking
  {
    gboolean tab_expand;
    gboolean tab_fill;
    gboolean reorderable;
    gboolean detachable;
    gchar   *menu_label;
  }
g2cLabelPacking;   // actually tab for notebook

typedef struct tag_g2cLayoutPacking
  {
    guint x;
    guint y;
  }
g2cLayoutPacking;

typedef struct tag_g2cStackPacking
{
    gchar *	icon_name;	
    gchar *	name;	
    gboolean	needs_attention;
    gint	position;	
    gchar *	title;
}
g2cStackPacking;

typedef struct tag_g2cTablePacking
  {
    guint     left_attach;
    guint     top_attach;
    guint     width;
    guint     height;
  }
g2cTablePacking;

typedef struct  tag_g2cPacking
  {
    g2cBoxPacking    box;
    g2cTablePacking  grid;
    g2cLabelPacking  tab;
    g2cLayoutPacking layout;
    g2cStackPacking  stack;
  } g2cPacking;
  
typedef struct tag_g2cItemData
{
    guint id;
    gchar *text;
} 
g2cItemData;
  
typedef struct tag_g2cActionWidget
{
    gchar *responseid;
    gchar *button_name;
} 
g2cActionWidget;

typedef struct tag_g2cWidget
  {
    GList                *associates;
    GList                *properties;
    GList                *children;
    GList                *signals;
    GList                *accelerators;
    GList                *accel_widgets;
    GList                *columns;
    GList                *table;
    GList                *css_classes;
    GList                *popups;
    GList                *comboboxtext_items;
    GList                *action_widgets;
    GList                *patterns;
    GList                *mime_types;
    GList                *attributes;
    struct tag_g2cWidget *parent;
    GType                klass;
    gchar                *klass_name;
    gchar                *name;
    g2cPackType           packing_type;
    g2cPacking            packing;
    guint                 order;
    gchar                *child_name;
    gboolean              internal;
    GList                *sizegroup;
    GList                *regster;
    GList                *requires;
  }
g2cWidget;

typedef struct tag_g2cRegister
{
    g2cWidget *widget;
    gchar *name;
    guint  level;
} 
g2cRegister;

typedef struct tag_g2cRequires
{
    g2cWidget *main;
    gchar *required;
    gchar *requiring;
    guint used;
}
g2cRequires;

typedef struct tag_g2cTopRegister
{
    g2cWidget *widget;
    gchar *name;
    gboolean bmain;
    guint  level;
} 
g2cTopRegister;

typedef struct tag_g2cColumn
{
    gchar *col_name;
    gchar *col_type;
}
g2cColumn;

typedef struct tag_g2cColdata
{
    gint col_no;
    gchar *col_value;
}
g2cColdata;

typedef struct tag_g2cProject
  {
    GHashTable *properties;
    GList      *top_level_widgets;
    GList      *dialogue_widgets;
    g2cWidget  *main_widget;
    gchar      *name;
    gchar      *program_name;
    gchar      *directory;
    gchar      *source_directory;
    gchar      *source_file;
    gchar      *resource_file;
    gchar      *pixmaps_directory;
    gboolean    gettext_support;
    //gboolean    gnome_support;
    //gboolean    gnome_help_support;
    gboolean    output_main_file;
    gboolean    output_support_files;
    gboolean    output_build_files;
    //gboolean    has_bonobo_controls;
    gboolean    gen_cmake;
    gboolean    no_parsing;
  }
g2cProject;

typedef struct tag_g2cDoc
  {
    xmlDocPtr   xmldoc;
    g2cProject *project;
    xmlNodePtr  current;
  }
g2cDoc;

typedef void (*g2cHandlerFunc)( g2cWidget *widget );
typedef void (*g2cCreateFunc)( g2cWidget *widget );

typedef struct tag_g2cCreateFunction
  {
    gchar *widget_class;
    gchar *create_function;
    gchar *parameters[MAX_CREATE_PARAMS];
    g2cCreateFunc handler;
  }
g2cCreateFunction;

typedef struct tag_g2cAfterParam
  {
    gchar *type;
 /*   gchar *param;
    gchar *params[MAX_CREATE_PARAMS];
    gchar *format;
    g2cHandlerFunc handler;  */
  }
g2cAfterParam;

typedef struct tag_g2cIgnoreParam
  {
    gchar *type;
    gchar *param;
  }
g2cIgnoreParam;

typedef struct tag_g2cRemapParam
  {
    gchar *type;
    gchar *old_param;
    gchar *new_param;
  }
g2cRemapParam;

typedef struct tag_g2cSpecialHandler
  {
    gchar *type;
    gchar *keyword;
    gchar *format;
    gchar *params[MAX_CREATE_PARAMS];
    gchar *conditional;
    g2cHandlerFunc handler;
  }
g2cSpecialHandler;

typedef struct tag_g2cCommonParam
  {
    gchar *property;
    gboolean use;
    gchar *prefix;
    gchar *alternative;
  }
g2cCommonParam;


/* static declarations */
void 
add_to_signal_list (gchar *signal_name);

void
clear_signal_list (void);

gboolean
is_in_signal_list (gchar *signal_name);

void 
notebook_packing( g2cWidget *widget, g2cWidget *box_widget );

/* Class functions */

g2cWidget *
g2c_widget_new( gchar *base );

void
g2c_widget_destroy( g2cWidget *widget );

g2cWidget *
g2c_widget_get_top_parent( g2cWidget *widget );

void
g2c_widget_set_order( g2cWidget *widget, gint order );

void
g2c_widget_set_property( g2cWidget *widget, 
                         const gchar *name,
                         const gchar *value );

void
g2c_widget_add_action_widget( g2cWidget *widget,
                         const gchar *button_name,
                         const gchar *response );
gchar*
g2c_widget_get_action_widget(g2cWidget *widget,
                         const gchar *response );

gchar*
g2c_widget_get_property( g2cWidget *widget,
                         const gchar *name );

void
g2c_widget_add_subwidget( g2cWidget *widget, g2cWidget *subwidget );

void
g2c_widget_add_signal( g2cWidget *widget,
                       g2cSignal *signal );

void
g2c_widget_add_accel( g2cWidget *widget,
                      g2cAccel  *accel );

void
g2c_widget_add_focus_target( g2cWidget *widget,
                             const gchar *focus_target );

void
g2c_widget_add_radio_group( g2cWidget   *widget,
                            const gchar *group_name );

void
g2c_widget_create_signal_handler_cb( g2cDoc *doc, g2cSignal * signal,
                                     g2cWidget *widget);

void
g2c_widget_create_signal_prototype_cb( gpointer data,
                                       gpointer user_data );

void
g2c_widget_create_signal_connect_cb( gpointer data,
                                     gpointer user_data );

void 
g2c_widget_create_closure_connect(g2cSignal * signal, 
                                  g2cWidget *accel_widget);

void
g2c_widget_create_closure_prototype( g2cSignal * signal,
                                     g2cWidget * widget );

void
g2c_widget_create_closure_handler( g2cSignal * signal,
                                   g2cWidget * widget );

void
g2c_widget_create_struct_cb( gpointer data,
                             gpointer user_data );

void
g2c_widget_create_accel_cb( gpointer data,
                            gpointer user_data );

void
g2c_widget_create_temp_declaration_cb( gpointer data,
                                       gpointer user_data );

void
g2c_widget_create_accel_declaration_cb( gpointer data,
                                        gpointer user_data );

void
g2c_widget_create_focus_accel_declaration_cb( gpointer data,
    gpointer user_data );

void
g2c_widget_create_arg_cb( gchar *name,
                          gchar *value,
                          g2cWidget * widget );

gchar *
g2c_widget_create_string( g2cWidget *widget );

void
g2c_widget_output_after_children_cb( gpointer key,
                                     gpointer data,
                                     gpointer user_data );

g2cWidget *
g2c_widget_find_by_name( g2cWidget *parent_widget, const gchar *widget_name );

g2cWidget *
g2c_widget_find_by_type_name( g2cWidget *parent_widget, const gchar *type_name );

g2cWidget *
g2c_widget_find_by_type( g2cWidget *parent_widget, GType type );

gboolean
g2c_widget_ignore_param( g2cWidget *widget,
                         gchar     *param );

gchar *
g2c_widget_remap_param( g2cWidget *widget,
                        gchar     *param );

gboolean
g2c_widget_special_handler( g2cWidget *widget,
                            gchar     *keyword );

gboolean
g2c_widget_common_param( g2cWidget *widget,
                            gchar *keyword,
                            gchar *old_keyword);

gchar *
find_signal_handler(g2cWidget *widget,
                    gchar *signal_name);

void 
push_to_stack( g2cWidget *widget, FILE *file );

#endif


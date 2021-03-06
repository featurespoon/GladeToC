#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <libxml/parser.h>
#include "g2c_helpers.h"
#include "g2c_message.h"
#include "g2c_doc.h"
#include "g2c_widget.h"


#define RECURSE_ALL   G_MAXINT
#define RECURSE_NONE  0

/******************************************************************
 **                    Function Prototypes                       **
 ******************************************************************/

static void       output_main_file( g2cDoc *doc, gchar *file_name, GList *topreglist );
static void       output_window_call(g2cWidget *widget,  FILE *file);
static void       output_dialog_widget_call(g2cWidget *dialogue_widget, gchar *main, FILE *file);
static void       parse_project_properties( g2cDoc *doc );
static void       parse_top_level_widgets( g2cDoc *doc );
static g2cWidget *parse_widget( g2cDoc *doc, g2cWidget *parent, gboolean internal, 
                    gboolean poverlay, gboolean pexpand, g2cPackDirection child_pack );
static g2cSignal *parse_signal( g2cDoc *doc );
static g2cAccel  *parse_accel( g2cDoc *doc );
static void       parse_packing( g2cDoc *doc, g2cWidget *widget );
static void       parse_items( xmlNodePtr node, g2cWidget *widget );
static void       parse_patterns( xmlNodePtr node, g2cWidget *widget );
static void       parse_mime_types( xmlNodePtr node, g2cWidget *widget );
static void       parse_attributes( xmlNodePtr node, g2cWidget *widget );
static void       parse_data( xmlNodePtr node, g2cWidget *widget );
static void       parse_rows( xmlNodePtr node, GList **rows );
static void       parse_sizegroup( xmlNodePtr node, g2cWidget *widget );
static gchar     *get_dir_prefix( g2cDoc *doc );

static void       init_types( g2cDoc *doc );
static void       output_widget_create( g2cWidget *widget, FILE *file );
static void       output_widget_files( g2cWidget *widget, g2cDoc *doc, 
                    gboolean bWindow, g2cWidget *parent_widget );
static void       output_widget_gui_h( g2cWidget *widget, g2cDoc *doc );
static void       output_widget_gui_c( g2cWidget *widget, g2cDoc *doc, g2cWidget *parent_widget );
static void       output_widget_h( g2cWidget *widget, g2cDoc *doc );
static void       output_widget_c( g2cWidget *widget, g2cDoc *doc );
static void       output_cmake_file(g2cDoc *doc);
static void       output_resource_file( g2cWidget *main_widget, g2cDoc *doc );
static void       output_data_create(g2cDoc *doc, g2cWidget *widget,  FILE  *file);
static void       output_signal_connect( g2cWidget *widget,  FILE *file );
static void       output_signal_prototype( g2cWidget *widget, FILE *file );
static void       output_signal_handler( g2cDoc *doc, g2cWidget *widget, FILE *file );
static void       output_widget_struct( g2cWidget *widget, FILE *file );
static void       output_temp_declarations( g2cWidget *widget, FILE *file );
static void       output_accelerator_declarations( g2cWidget *widget, FILE *file );
static void       output_focus_accelerator_declarations( g2cWidget *widget, FILE *file );
static void       output_accelerators( g2cWidget *widget, FILE *file );
static void       output_combobox_items ( g2cWidget *widget, FILE* file );
static void       output_patterns ( g2cWidget *widget, FILE* file );
static void       output_sizegroup ( g2cWidget *widget, FILE* file );
static void       output_mime_types ( g2cWidget *widget, FILE *file );
static void       output_attributes ( g2cWidget *widget, FILE* file );
static void       output_pango_attribute( g2cWidget *widget, gchar* name, gchar* value, FILE* file );
static void       output_menu_item( g2cWidget *widget, FILE* file );
static void       output_menu( g2cWidget *widget, FILE* file );
static void       output_model_enum(g2cWidget* widget, FILE  *file);
static void       output_model_populater(g2cWidget* widget, gchar* type_name, FILE *file);
static void       output_paned_pack_child ( g2cWidget *widget, FILE* file );
static void       output_toolbar_widget( g2cWidget *widget, FILE *file );
static void       output_style( g2cWidget *widget);
static void       handle_file_compare( gchar *temp_file_name, gchar *file_name );


static void
init_types( g2cDoc *doc )
{
  GTK_TYPE_WIDGET;
  GTK_TYPE_CONTAINER;
  GTK_TYPE_BIN;
  GTK_TYPE_ABOUT_DIALOG;
  GTK_TYPE_ACCEL_GROUP;
  GTK_TYPE_ACCEL_LABEL;
  GTK_TYPE_ACTION_BAR;
  GTK_TYPE_ADJUSTMENT;
/*  GTK_TYPE_ALIGNMENT;  */
  GTK_TYPE_APP_CHOOSER_BUTTON;
  GTK_TYPE_ASPECT_FRAME;
  GTK_TYPE_ASSISTANT;
  GTK_TYPE_BOX;
  GTK_TYPE_BUTTON;
  GTK_TYPE_BUTTON_BOX;
  GTK_TYPE_CALENDAR;
  GTK_TYPE_CHECK_BUTTON;
  GTK_TYPE_COLOR_BUTTON;
  GTK_TYPE_COLOR_CHOOSER_DIALOG;
  GTK_TYPE_COLOR_CHOOSER_WIDGET;
  GTK_TYPE_COMBO_BOX;
  GTK_TYPE_COMBO_BOX_TEXT;
  GTK_TYPE_DIALOG;
  GTK_TYPE_DRAWING_AREA;
  GTK_TYPE_ENTRY;
  GTK_TYPE_ENTRY_BUFFER;
  GTK_TYPE_ENTRY_COMPLETION;
  GTK_TYPE_EVENT_BOX;
  GTK_TYPE_EXPANDER;
  GTK_TYPE_FILE_CHOOSER_BUTTON;
  GTK_TYPE_FILE_CHOOSER_DIALOG;
  GTK_TYPE_FILE_CHOOSER_WIDGET;
  GTK_TYPE_FILE_FILTER;
  GTK_TYPE_FIXED;
  GTK_TYPE_FLOW_BOX;
  GTK_TYPE_FONT_BUTTON;
  GTK_TYPE_FONT_CHOOSER_DIALOG;
  GTK_TYPE_FONT_CHOOSER_WIDGET;
  GTK_TYPE_FRAME;
  GTK_TYPE_GRID;
  GTK_TYPE_HEADER_BAR;
  GTK_TYPE_ICON_VIEW;
  GTK_TYPE_IMAGE;
  GTK_TYPE_INFO_BAR;
  GTK_TYPE_LABEL;
  GTK_TYPE_LAYOUT;
  GTK_TYPE_LEVEL_BAR;
  GTK_TYPE_LINK_BUTTON;
  GTK_TYPE_LIST_BOX;
  GTK_TYPE_LIST_STORE;
  GTK_TYPE_MENU;
  GTK_TYPE_MENU_BAR;
  GTK_TYPE_MENU_BUTTON;
  GTK_TYPE_MESSAGE_DIALOG;
  GTK_TYPE_MODEL_BUTTON;
  GTK_TYPE_NOTEBOOK;
  GTK_TYPE_OFFSCREEN_WINDOW;
  GTK_TYPE_OVERLAY;
  GTK_TYPE_PANED;
  GTK_TYPE_PLACES_SIDEBAR;
  GTK_TYPE_POPOVER;
  GTK_TYPE_POPOVER_MENU;
  GTK_TYPE_PROGRESS_BAR;
  GTK_TYPE_RADIO_BUTTON;
  GTK_TYPE_RECENT_CHOOSER_DIALOG;
  GTK_TYPE_RECENT_CHOOSER_WIDGET;
  GTK_TYPE_REVEALER;
  GTK_TYPE_SCALE;
  GTK_TYPE_SCALE_BUTTON;
  GTK_TYPE_SCROLLBAR;
  GTK_TYPE_SCROLLED_WINDOW;
  GTK_TYPE_SEARCH_BAR;
  GTK_TYPE_SEARCH_ENTRY;
  GTK_TYPE_SEPARATOR;
  GTK_TYPE_SIZE_GROUP;
  GTK_TYPE_SPIN_BUTTON;
  GTK_TYPE_SPINNER;
  GTK_TYPE_STACK;
  GTK_TYPE_STACK_SIDEBAR;
  GTK_TYPE_STACK_SWITCHER;
  GTK_TYPE_STATUS_ICON;
  GTK_TYPE_SWITCH;
  GTK_TYPE_TEXT_BUFFER;
  GTK_TYPE_TEXT_TAG;
  GTK_TYPE_TEXT_TAG_TABLE;
  GTK_TYPE_TEXT_VIEW;
  GTK_TYPE_TOGGLE_BUTTON;
  GTK_TYPE_TOOLBAR;
  GTK_TYPE_TOOL_PALETTE;
  GTK_TYPE_TREE_MODEL_FILTER;
  GTK_TYPE_TREE_MODEL_SORT;
  GTK_TYPE_TREE_STORE;
  GTK_TYPE_TREE_VIEW ;
  GTK_TYPE_VIEWPORT;
  GTK_TYPE_VOLUME_BUTTON;
  GTK_TYPE_WINDOW;
  GTK_TYPE_WINDOW_GROUP;

}



/******************************************************************
 **                      Class Functions                         **
 ******************************************************************/

g2cDoc *
g2c_doc_new( gchar *xml_file_name )
{
gchar wdir[PATH_MAX];    
g2cDoc *doc = g_new0( g2cDoc, 1 );
gchar *cwd = NULL;

  /* Every document gets a project.  One per customer please. */
  doc->project = g2c_project_new();

  CURRENT_PROJECT = doc->project;
  doc->project->source_directory = NULL;
   
  // if def WIN32
  //doc->project->directory = g_strdup("C:\\NetBeansProjects\\g2c");
  // if Linux
  //doc->project->directory = g_strdup("/home/barry/NetBeansProjects/gen");
  
  doc->project->directory = g_strdup(getcwd(wdir, PATH_MAX));

  /* Open the XML document and save a pointer to it in the struct */
  doc->xmldoc  = xmlParseFile( xml_file_name );
  if (doc->xmldoc == NULL) {
      g_message("Could not process glade file %s\n", xml_file_name);
      cwd =  g_get_current_dir();
      g_message("Current working directory: %s\n", cwd);
      g_free( cwd );
      return NULL;
  }
  doc->current = NULL;

  return doc;
}


void
g2c_doc_destroy( g2cDoc *doc )
{
  /* Where is the call to release the xmlDoc pointer? */
  if( doc->xmldoc )  xmlFreeDoc( doc->xmldoc );
  
  if( doc->project ) g2c_project_destroy( doc->project );
  doc->current = NULL;
  
  g_free( doc );
}

int
g2c_doc_parse( g2cDoc *doc )
{
  xmlNodePtr project_node = NULL;

  /* First line should be <?xml version="1.0"> */
  g_message( "XML Version: %s\n", doc->xmldoc->version );

  doc->current = xmlDocGetRootElement( doc->xmldoc );
  g_assert( NULL != doc->current );

  /* Root node should be <GTK-Interface> */
  /* If there was a comment it has been skipped */
        
  if( strcmp( get_node_name( doc->current ), "interface" ) != 0 )
    {
      g_error( "This is not a glade file!" );
      return 1;
    }

  project_node = set_first_object(doc->current);
  /* on exit the returned node should be an object */

  /* Get all of the widget types.  */
  //init_types( doc );

  /* Now parse any top-level widgets */
  doc->current = project_node;
  if( NULL != doc->current )
    parse_top_level_widgets( doc );
  return 0;
}

int
g2c_doc_output( g2cDoc *doc )
{
  gchar *filename = NULL;
  GList *run = NULL;
  GList *orphans = NULL;
  GList *top_list = NULL;
  GList *topreglist = NULL;
  g2cRequires *require;
  g2cWidget *main_widget = NULL;
  g2cWidget *widget = NULL;
  gchar *handlers_filename = NULL;
  gchar *control_file_name = NULL;
  
  /*****  Restructure the widgets  ******/
  /*  Collect the liststores etc. under the main window or dialog widget - orphans  */
  
  run = g_list_first(doc->project->top_level_widgets);
  while (run != NULL) {
      widget = (g2cWidget *) run->data;
      if ((strcmp(widget->klass_name, "GtkListStore") == 0) || 
          (strcmp(widget->klass_name, "GtkTreeStore") == 0)  ||          
          (strcmp(widget->klass_name, "GtkAdjustment") == 0) ||
          (strcmp(widget->klass_name, "GtkTextBuffer") == 0) ||
          (strcmp(widget->klass_name, "GtkTextTagTable") == 0) ||
          (strcmp(widget->klass_name, "GtkEntryBuffer") == 0) ||
          (strcmp(widget->klass_name, "GtkImage") == 0) ||
          (strcmp(widget->klass_name, "GtkRecentFilter") == 0) ||
          (strcmp(widget->klass_name, "GtkRecentManager") == 0) ||
          (strcmp(widget->klass_name, "GtkEntryCompletion") == 0) ||
          (strcmp(widget->klass_name, "GtkStack") == 0) ||
          (strcmp(widget->klass_name, "GtkFileFilter") == 0) ||
          (strcmp(widget->klass_name, "GtkTreeModelSort") == 0) ||
          (strcmp(widget->klass_name, "GtkTreeModelFilter") == 0) ||
          (strcmp(widget->klass_name, "GtkLabel") == 0) ||
          (strcmp(widget->klass_name, "GtkAccelGroup") == 0) ||
          (strcmp(widget->klass_name, "GtkMenu") == 0) ||
          (strcmp(widget->klass_name, "GtkSizeGroup") == 0) ||
          (strcmp(widget->klass_name, "GtkWindowGroup") == 0) ||
          (strcmp(widget->klass_name, "GtkPopover") == 0)  ||
          (strcmp(widget->klass_name, "GtkPopoverMenu") == 0) ||
          (strcmp(widget->klass_name, "GtkStatusIcon") == 0) ) {
          orphans = g_list_append(orphans, widget);
      }
      
      /*  identify the main window  */
      if ((strcmp(widget->klass_name, "GtkWindow") == 0) ||
          (strcmp(widget->klass_name, "GtkApplicationWindow") == 0) ||
          (strcmp(widget->klass_name, "GtkAssistant") == 0) ) {  // hopefully there's no more than one
          g_assert (doc->project->main_widget == NULL);
          doc->project->main_widget = widget;
          MAIN_WINDOW = widget->name;
      } 
      /*  collect the dialogues  */  
      if ((strcmp(widget->klass_name, "GtkDialog") == 0) || 
          (strcmp(widget->klass_name, "GtkFileChooserDialog") == 0) ||
          (strcmp(widget->klass_name, "GtkAboutDialog") == 0) ||
          (strcmp(widget->klass_name, "GtkFontChooserDialog") == 0) ||
          (strcmp(widget->klass_name, "GtkColorChooserDialog") == 0) || 
          (strcmp(widget->klass_name, "GtkRecentChooserDialog") == 0) ||
          (strcmp(widget->klass_name, "GtkMessageDialog") == 0)  || 
          (strcmp(widget->klass_name, "GtkAppChooserDialog") == 0) ||
          (strcmp(widget->klass_name, "GtkOffscreenWindow") == 0) ) {
          doc->project->dialogue_widgets = g_list_append(doc->project->dialogue_widgets, widget);
      }
      run = g_list_next(run);
  }
    
  /*       Sets up register of widgets, and requires,  for each window/dialog           */
  /*         Note: the global requires list is only set up under the top_level window   */
  
  main_widget = doc->project->main_widget;
  
  scan_widgets_for_register(main_widget, main_widget, main_widget);
  scan_orphans_for_register(main_widget, orphans);
  
  topreglist = topregister_add(topreglist, main_widget, TRUE);

  run = g_list_first(doc->project->dialogue_widgets);
  while (run != NULL) {
          widget = (g2cWidget *) run->data;
          scan_widgets_for_register(main_widget, widget, widget);          
          topreglist = topregister_add(topreglist, widget, FALSE);
          run = g_list_next(run);
  }
  //print_out_requires(main_widget->requires);
  /*     Now give the orphans a home   */
  
  allocate_orphans(main_widget, orphans);
  
  g_list_free( orphans );
  
  /*                 ***  End of restructuring                *** */
  
  /*                   End of  register of widgets               */ 
 
  /*   now analyse the register and requires list to ensure compilation in the right order */
  
  analyse_requirements(main_widget, main_widget); 
  //print_out_register(main_widget);
 
  
  
  run = g_list_first(doc->project->dialogue_widgets);
  while (run != NULL) {
          widget = (g2cWidget *) run->data;
          analyse_requirements(main_widget, widget); 
          //g_message("REGISTER for dialog %s\n", widget->name);
          //print_out_register(widget);
          run = g_list_next(run);
  }
  
  //  set up top_list from requires list (mainly transient_for)
  run = g_list_first(main_widget->requires);
  while (run != NULL) {
      require = (g2cRequires *) run->data;
      if ( (is_widget_top_level(main_widget, require->required)) &&
           (is_widget_top_level(main_widget, require->requiring)) )  {
          top_requires_add(&top_list, require->requiring, require->required);
      }
      
      run = g_list_next(run);
  }
  
  //  sort top_list for dialogues etc.
  
   if (!sort_top_list(&topreglist, &top_list)) {
       g_message("generated file output aborted\n");
       return 1;  // cycle detected
   }
  
   top_requires_destroy(top_list);
  /*                   End of analysis and re-ordering of widgets               */ 
  
  /* Write out the main.c file */
#ifdef WIN32
  if ( (g_str_has_prefix(doc->project->source_directory, "C:")) ||
       (g_str_has_prefix(doc->project->source_directory, "D:")) ) {
      filename = g_strdup_printf ("%s/%s_main.c",
			 doc->project->source_directory,
			 doc->project->program_name);
  } else {
    filename = g_strdup_printf ("%s/%s/%s_main.c", 
                           doc->project->directory,
                           doc->project->source_directory,
                           doc->project->program_name);
  }
#else
  if (g_str_has_prefix(doc->project->source_directory, "/"))  {
    filename = g_strdup_printf ("%s/%s_main.c",
                           doc->project->source_directory,
                           doc->project->program_name);  
  } else {
      filename = g_strdup_printf ("%s/%s/%s_main.c", 
                           doc->project->directory,
                           doc->project->source_directory,
                           doc->project->program_name);  
  }
#endif
  if( doc->project->output_main_file )
    output_main_file( doc, filename, topreglist ); 
   
   topregister_destroy(topreglist);

  /* Parse $src/control.c */
   
  if ( doc->project->no_parsing == FALSE) {
  
  /*  Parse previous $src/control.c which holds the signal handlers */
    handlers_filename = g_strconcat( doc->project->source_directory, "/", "control.c", NULL );
    if( g2c_check_file_exists( handlers_filename) ) { 
      CURRENT_SOURCE_PARSER = g2c_file_parser_new (handlers_filename, doc->project, FT_SOURCE); 
    }  
    g_free (handlers_filename);
  /*  and then $src/model.c which may hold list- and tree-store populaters */
    handlers_filename = g_strconcat( doc->project->source_directory, "/", "model.c", NULL );
    if( g2c_check_file_exists( handlers_filename) ) { 
        if (NULL == CURRENT_SOURCE_PARSER) {
           CURRENT_SOURCE_PARSER = g2c_file_parser_new (handlers_filename, doc->project, FT_SOURCE); 
        }
        else {
            g2c_file_parser_add_file (CURRENT_SOURCE_PARSER, handlers_filename, FT_SOURCE);
        }
    }  
    g_free (handlers_filename);
  
  }
  
  g_free (filename);

  /* For the top level GtkWindow widget, write a source file.
   * Use the directory specified in using the "directory" and
   * "source_directory" in the project properties.  If the 
   * "directory" is NULL, use the current directory.
   */
  
  /* Need to create the files in the 'source' directory */
  DIR_PREFIX = get_dir_prefix( doc );
  
  output_widget_files(main_widget, doc, TRUE, NULL);
  
  /*  repeat for each dialogue widget */
  run = g_list_first(doc->project->dialogue_widgets);
  while (run != NULL) {
      widget = (g2cWidget *) run->data;      
      output_widget_files(widget, doc, FALSE, main_widget);                 
      run = g_list_next(run);
  }
  control_file_name = g_strconcat( DIR_PREFIX, "/",  "control.c", NULL );
  if( !g2c_check_file_exists( control_file_name) ) { 
     //copy window1.c (filename) to control.c control_file_name )
     g_message( "Creating %s\n", control_file_name );
     filename = g_strconcat( DIR_PREFIX, "/", main_widget->name, ".c", NULL );
     g2c_copy_file(filename, control_file_name);
     g_free (filename);
  }
  g_free (control_file_name);
  
  if (doc->project->gen_cmake == TRUE) {
    output_cmake_file(doc);
  }
  if (doc->project->resource_list != NULL) {
    output_resource_file( main_widget, doc );
  }
  g_free( DIR_PREFIX );
  if (CURRENT_SOURCE_PARSER != NULL) 
    g2c_file_parser_destroy (CURRENT_SOURCE_PARSER);
  
  CURRENT_SOURCE_PARSER = NULL;
  return 0;
}

static gchar*
get_dir_prefix( g2cDoc *doc )
{
  gchar *directory        = NULL;
  gchar *dir_prefix       = NULL;

  //g_print("source directory: %s\n", doc->project->source_directory);
  if ( (!g_str_has_prefix(doc->project->source_directory, "C:"))  &&
       (!g_str_has_prefix(doc->project->source_directory, "D:")) ) {
    if( NULL != doc->project->directory )
      directory = g_strdup( doc->project->directory );
    else
      directory = g_get_current_dir();
    }
#ifdef WIN32
  if ( (g_str_has_prefix(doc->project->source_directory, "C:")) ||
       (g_str_has_prefix(doc->project->source_directory, "D:"))  ) {
      dir_prefix = g_strdup(doc->project->source_directory);  
  } else {
      dir_prefix = g_strjoin( "/",
                            directory,
                            doc->project->source_directory,
                            NULL );  
  }
#else 
  if (g_str_has_prefix(doc->project->source_directory, "/")) {
      dir_prefix = g_strdup(doc->project->source_directory); 
  } else {  
      dir_prefix = g_strjoin( "/",
                            directory,
                            doc->project->source_directory,
                            NULL );
    }
#endif

  if (NULL != directory) g_free( directory );

  return dir_prefix; /* Freed by caller */
}

static void
parse_project_properties( g2cDoc *doc )
{
  /* Get the first top-level widget */
  doc->current = doc->current->children;

  while( NULL != doc->current )
    {
      /* Skip blank nodes */
      if( xmlIsBlankNode( doc->current ) )
        {
          doc->current = doc->current->next;
          continue;
        }

      /* Set the project property */
      {
        g2c_project_set_property( doc->project,
                                  get_node_name( doc->current ),
                                  get_node_text( doc->current ) );
      }

      doc->current = doc->current->next;
    }
}

static void
parse_top_level_widgets( g2cDoc *doc )
{
  xmlNodePtr  top    = NULL;
  g2cWidget  *widget = NULL;

  top = doc->current;

  /* doc->current should be set to the first widget */
  while( NULL != top )
    {
      widget = parse_widget( doc, NULL, FALSE, FALSE, FALSE, 0 );
      
      if (widget != NULL) 
         g2c_project_add_top_level_widget( doc->project, widget );

      top = get_next_node(top);
      doc->current = top;
    }
}

/*    This function recurses down a tree structure of widgets    */
static g2cWidget *
parse_widget( g2cDoc *doc, g2cWidget *parent, gboolean internal, gboolean poverlay, gboolean pexpand, g2cPackDirection child_pack )
{
  xmlNodePtr node        = NULL;
  gchar     *class_name  = NULL;
  g2cWidget *widget      = NULL;
  g2cWidget *subwidget   = NULL;
  g2cSignal *signal      = NULL;
  g2cAccel  *accel       = NULL;
  xmlAttr   *attr        = NULL;
  int        order       = 0;
  xmlNodePtr object_node = NULL;
  xmlNodePtr child_node  = NULL;
  xmlNodePtr temp_node   = NULL;
  gchar     *col_type    = NULL;
  gchar     *child_attr  = NULL;
  gboolean   binternal   = FALSE;
  gboolean   boverlay    = FALSE;
  gboolean   bexpand     = FALSE;
  gboolean   bcenter     = FALSE;
  gchar     *text        = NULL;
  gchar     *css_text    = NULL;
  gchar     *comment     = NULL;
  gchar     **parts;
  gchar     *col_name    = NULL;
  g2cPackDirection pack_type  = 0;
  
  /*  On entry doc->current points to an 'object' Element (or possibly 'template') */

  /* Get the attributes of the object: class and id */
  attr = doc->current->properties;
  /* Parse the class, create a new widget */
  g_assert( strcmp( get_attr_node_name( attr ), "class" ) == 0 );
  class_name = g_strdup( get_attr_node_text( attr ) );  
  attr = attr->next;
  if (attr == NULL) { 
      widget = g2c_widget_new( class_name );
      widget->name = make_widget_id();
      g_message("No id given for widget %s. Using %s\n", class_name, widget->name);
  } else 
  if ( strcmp( get_attr_node_name( attr ), "id" ) == 0 ) {
    widget = g2c_widget_new( class_name );
    widget->name = g_strdelimit(g_strdup( get_attr_node_text( attr ) ), ":-", '_');           
  } else {   /* for template */
    g_assert( strcmp( get_attr_node_name( attr ), "parent" ) == 0 );
    widget = g2c_widget_new( g_strdelimit(g_strdup( get_attr_node_text( attr ) ), ":-", '_') );
    widget->name = class_name; 
  }  
  
  g_assert( NULL != widget->klass_name );

  if( 0 == widget->klass )
    g_message( "*** No class found in gtk for %s\n", widget->klass_name );
  
  widget->internal = internal;
  if  (child_pack != 0)  {
      widget->packing_type = LABEL_PACKING;
      widget->packing.box.pack_type = child_pack;
  }
  widget->parent = parent;
  
  if (poverlay == TRUE)
      g2c_widget_set_property( widget, "_overlay","True" );
  if (pexpand == TRUE)
      g2c_widget_set_property( widget, "_expand","True" );

  doc->current = get_first_child(doc->current);
  /*  doc->current should now point to a chain of properties  */

  /* Mark the current position in the document, children of the object */  
  
  node = doc->current;    

  /* Get the rest of the properties */
  while( NULL != node )  {    
      
      if ( strcmp( get_node_name( node ), "property" ) == 0 )
      {
         attr = node->properties;
          if (attr != NULL) {
             temp_node = attr->children;
             if ((temp_node != NULL) && (node->children != NULL)) {
                  text = node->children->content;
                  g2c_widget_set_property( widget,
                                   temp_node->content,
                                   text);
             }
          } 
      } else if( strcmp( get_node_name( node ), "accel-groups" ) == 0 )
      {
          temp_node = get_first_child (node);          
          attr = temp_node->properties;   
          if( xmlNodeIsText( attr->children ) ) {            
            text = attr->children->content;
            g2c_widget_set_property( widget, "accel_group", text);
          }
          
      } else if( strcmp( get_node_name( node ), "child" ) == 0 )    // only child nodes after chain of properties
        {
          attr = node->properties;
          binternal = FALSE;
          child_attr = g_strdup(get_attr_node_name( attr ));
          if (child_attr != NULL) {
              /*  child_attr should be 'internal-child' but could be 'type' */
              /*  get_attr_node_text( attr ) will give you 'vbox' or 'action-area' but not needed */
              if (strcmp(child_attr, "internal-child")  == 0 ) {
                 binternal = TRUE;
              }
              if (strcmp(child_attr, "type")  == 0 ) {
                  if (strcmp(get_attr_node_text( attr ), "overlay") == 0) {
                      boverlay = TRUE;
                  }
                  if (strcmp(get_attr_node_text( attr ), "label") == 0) {
                      bexpand = TRUE;
                  }
                  if (strcmp(get_attr_node_text( attr ), "action-start") == 0) {                      
                      pack_type = PACK_START;
                      //binternal = TRUE;
                  }
                  if (strcmp(get_attr_node_text( attr ), "action-end") == 0) {
                      pack_type = PACK_END;
                      //binternal = TRUE;
                  }
                  if (strcmp(get_attr_node_text( attr ), "center") == 0) { 
                      bcenter = TRUE;                  
                  }
              }
              g_free( child_attr );
          }
          child_node = node;
          object_node = get_first_child(node);   // save child of "child"             
          doc->current =  object_node;          // which should be an object           
          
          if (strcasecmp(doc->current->name,"object") == 0) {             
          
              subwidget = parse_widget( doc, widget, binternal, boverlay, bexpand, pack_type );  // so PUSH widgets 
              if (subwidget == NULL) {
                  return NULL;
              }
              // POP returns here:
              g2c_widget_add_subwidget( widget, subwidget );
              g2c_widget_set_order( subwidget, order++ );   
              
              if (bcenter == TRUE) {
                  g2c_widget_set_property(subwidget,"_center", widget->name);
                  bcenter = FALSE;
              }

              doc->current = object_node;   // restore
              node = get_next_node(object_node);   // now packing node
              
              if (node != NULL) { 
                  attr = node->properties;
                  if (attr != NULL) {
                     temp_node = attr->children;
                     if ((temp_node != NULL) && (node->children != NULL)) {
                          g2c_widget_set_property( widget,
                                           temp_node->content,
                                           node->children->content );
                     }
                  } 
                  if ( strcmp( get_node_name( node ), "packing" ) == 0 ) {
                      doc->current = get_first_child(node);   // first packing property

                      /*  on entry doc->current must point to the first packing property */
                      parse_packing( doc, subwidget );   // process chain of packing properties to the end
                      /* on exit doc->current will always be NULL */
                  } else if ( strcmp( get_node_name( node ), "attributes" ) == 0 ) {
                      doc->current = get_first_child(node);   // first [and only] attribute
                      while (doc->current != NULL) {
                        if ( strcmp( get_node_name( doc->current ), "attribute" ) == 0 ) {
                            attr = doc->current->properties;
                            if (attr != NULL) {
                                g2c_widget_set_property( subwidget, 
                                    g_strdelimit( (gchar *) get_attr_node_text( attr ), "-",'_'), 
                                    get_node_text( doc->current ) ); 
                            }
                        }
                        /*  step to next attribute   */
                        doc->current = get_next_node(doc->current);
                      }
                     /* it is possible for this not to be the only attribute here, 
                      * and that would be due to an incorrect setting in Glade. 
                      * We convert them to properties anyway.  */
                  }
              }
          } else {
             // g_message("%s found\n", doc->current->name);  // prob placeholder
          }
          node = child_node;
          /* node now points to the child.  The ->next below moves on the the next child if any */           
        }
      else if ( strcmp( get_node_name( node ), "style" ) == 0 )
      {
          child_node = get_first_child(node); 
          while (child_node != NULL) {
              g_assert( strcmp( get_node_name( child_node ), "class" ) == 0 );
              attr = child_node->properties;
              g_assert( strcmp( get_attr_node_name( attr ), "name" ) == 0 );
              css_text =  g_strdup( get_attr_node_text( attr ) );              
              widget->css_classes = g_list_append( widget->css_classes, g_strdelimit(css_text,"\"",'\''));
              child_node = get_next_node(child_node);
          }
          /*  node still points to the style element but its 'next' will be NULL and so will POP */
      }
      else if( strcmp( get_node_name( node ), "columns" ) == 0 )
      {
          child_node = get_first_child(node); 
          while (child_node != NULL) {
              if (child_node->type == XML_COMMENT_NODE) {
                  comment = (gchar *) child_node->content;
                  parts = g_strsplit(comment, " ", 0);
                  col_name = g_strdup(parts[2]);
                  g_strfreev( parts );
                  child_node = get_next_node(child_node);
              }
              g_assert( strcmp( get_node_name( child_node ), "column" ) == 0 );  
              attr = child_node->properties;
              g_assert( strcmp( get_attr_node_name( attr ), "type" ) == 0 );
              col_type = g_strdup( get_attr_node_text( attr ) );
              column_add(widget, col_name, col_type);              
              child_node = get_next_node(child_node);
              if ( NULL != col_name ) g_free( col_name );
              g_free( col_type );
          }
          /*  node still points to the columns element but its 'next' will be NULL and so will POP */
      }
      else if( strcmp( get_node_name( node ), "action-widgets" ) == 0 )
        {
          child_node = get_first_child(node); 
          while (child_node != NULL) {
              g_assert( strcmp( get_node_name( child_node ), "action-widget" ) == 0 ); 
               attr = child_node->properties;
               if (attr != NULL) {
                   temp_node = attr->children;
                   if ((temp_node != NULL) && (child_node->children != NULL)) {
                      g2c_widget_add_action_widget( widget,
                              child_node->children->content,
                              temp_node->content ); 
                   }
                }                      
              child_node = get_next_node(child_node);
          }
        }
      else if( strcmp( get_node_name( node ), "signal" ) == 0 )
        {          
          signal = parse_signal( doc );          
          g2c_widget_add_signal( widget, signal );
        }
      else if( strcmp( get_node_name( node ), "accelerator" ) == 0 )
        {
          accel = parse_accel( doc );
          g2c_widget_add_accel( widget, accel );
        } 
      else if( strcmp( get_node_name( node ), "items" ) == 0 )
        {                 
          parse_items( node, widget );   // process chain of items to the end          
        }
      else if( strcmp( get_node_name( node ), "patterns" ) == 0 )
        {                 
          parse_patterns( node, widget );   // process chain of patterns to the end          
        }
      else if( strcmp( get_node_name( node ), "mime-types" ) == 0 )
        { 
          parse_mime_types( node, widget );   // process chain of mime_types to the end              
        }
      else if( strcmp( get_node_name( node ), "attributes" ) == 0 )
        { 
          parse_attributes( node, widget );   // process chain of attributes to the end              
        }
      else if( strcmp( get_node_name( node ), "data" ) == 0 )
        { 
          parse_data( node, widget );   // process chain of rows of liststore data to the end              
        }
      else if( strcmp( get_node_name( node ), "widgets" ) == 0 )
        { 
          parse_sizegroup( node, widget );   // process chain of rows of widgets in sizegroup to the end 
        }
      
      node = get_next_node(node);       
      if( node == NULL )  break;  // POP because no more property or child nodes
      doc->current = node;
    }  /* while node is not NULL */
 
  return widget;
}

static void       
parse_items( xmlNodePtr node, g2cWidget *widget )
{
xmlAttr *attr   =  NULL;
xmlNodePtr child_node = NULL;
guint    id     = 0;
gchar   *data   = NULL;
GList   *comboboxtext_items = NULL;
g2cItemData *itemdata = NULL;

     g_assert ( strcmp( widget->klass_name, "GtkComboBoxText" ) == 0 );
       
     child_node = get_first_child(node); 
     while (child_node != NULL) {       
                     
          g_assert( strcmp( get_node_name( child_node ), "item" ) == 0 );  
          attr = child_node->properties;
          
          if ( strcmp( get_attr_node_name( attr ), "id" ) == 0 )         
              id   = atoi    ( get_attr_node_text( attr ) );
          data = g_strdup( get_node_text( child_node ) );
          
          itemdata = (g2cItemData *) g_new0 (g2cItemData, 1);
          itemdata->id = id;
          itemdata->text = data;
          comboboxtext_items = g_list_append(comboboxtext_items, itemdata );
           
         /*  step to next item   */
          child_node = get_next_node(child_node);          
     }
     widget->comboboxtext_items = comboboxtext_items;
  
}

static void       
parse_patterns( xmlNodePtr node, g2cWidget *widget )
{
xmlNodePtr child_node = NULL;
gchar   *data   = NULL;
GList   *patterns = NULL;

     g_assert ( ( strcmp( widget->klass_name, "GtkFileFilter" ) == 0 ) || 
                ( strcmp( widget->klass_name, "GtkRecentFilter" ) == 0) );
       
     child_node = get_first_child(node); 
     while (child_node != NULL) {       
                     
          g_assert( strcmp( get_node_name( child_node ), "pattern" ) == 0 ); 
          
          data = g_strdup( get_node_text( child_node ) );                    
          patterns = g_list_append(patterns, data );           
         /*  step to next pattern  */
          child_node = get_next_node(child_node);          
     }
     widget->patterns = patterns;
  
}

static void       
parse_rows( xmlNodePtr node, GList **rows )
{
xmlNodePtr child_node = NULL;
xmlNodePtr temp_node = NULL;

gchar   *data   = NULL;
xmlAttrPtr attr = NULL;
gchar *attr2 = NULL;
gint colno;
gchar *value = NULL;

    child_node = get_first_child(node); 
    while (child_node != NULL) {   
        attr2 = (gchar *) get_node_name( child_node );
        g_assert( strcmp( attr2, "col" ) == 0 );
        attr = child_node->properties;
          if (attr != NULL) {
             temp_node = attr->children;
             if ((temp_node != NULL) && (child_node->children != NULL)) {                     
                  colno = atoi(temp_node->content);
                  value = child_node->children->content;
                  coldata_add(rows, colno, value);
             }
          }
        child_node = get_next_node(child_node); 
    }
}

static void       
parse_data( xmlNodePtr node, g2cWidget *widget )
{   /*  rows in a table definition  */
xmlNodePtr child_node = NULL;
gchar *attr = NULL;
GList *row = NULL;

    child_node = get_first_child(node); 
    while (child_node != NULL) {   
        attr = (gchar *) get_node_name( child_node );
        g_assert( strcmp( attr, "row" ) == 0 ); 
        row = NULL;
        parse_rows( child_node, &row );   // process chain of cols to the end
        row_add(widget, row);
        child_node = get_next_node(child_node);  
    }
}

static void       
parse_attributes( xmlNodePtr node, g2cWidget *widget )
{
xmlNodePtr child_node = NULL;
xmlNodePtr temp_node = NULL;

gchar   *data   = NULL;
GList   *attributes = NULL;
xmlAttrPtr attr = NULL;
//gchar *attr2 = NULL;
gchar *name = NULL;
gchar *value = NULL;


    child_node = get_first_child(node); 
    while (child_node != NULL) {   
        //attr2 = (gchar *) get_node_name( child_node );
        g_assert( strcmp( get_node_name( child_node ), "attribute" ) == 0 ); 
          attr = child_node->properties;
          if (attr != NULL) {
             temp_node = attr->children;
             if (temp_node != NULL) {                                                   
                  name = temp_node->content;                  
             }
             attr = attr->next;
             temp_node = attr->children;
             if (temp_node != NULL)  {
                 value = temp_node->content; 
             }
             attrlist_add(widget, g_strdelimit(name, "-",'_'), value);
          } 
                 
         /*  step to next attribute   */
         child_node = get_next_node(child_node);          
    }
   // widget->attributes = attributes ;
}

static void       
parse_mime_types( xmlNodePtr node, g2cWidget *widget )
{
xmlNodePtr child_node = NULL;
gchar   *data   = NULL;
GList   *mime_types = NULL;

     g_assert ( ( strcmp( widget->klass_name, "GtkFileFilter" ) == 0 ) || 
                ( strcmp( widget->klass_name, "GtkRecentFilter" ) == 0) );
       
     child_node = get_first_child(node); 
     while (child_node != NULL) {       
                     
          g_assert( strcmp( get_node_name( child_node ), "mime-type" ) == 0 ); 
          
          data = g_strdup( get_node_text( child_node ) );                    
          mime_types = g_list_append(mime_types, data );           
         /*  step to next mime_type   */
          child_node = get_next_node(child_node);          
     }
     widget->mime_types = mime_types ;     
  
}

static void       
parse_sizegroup( xmlNodePtr node, g2cWidget *widget )
{
xmlNodePtr child_node = NULL;
xmlAttr   *attr        = NULL;
gchar   *data   = NULL;
GList   *sizegroup = NULL;
    
     g_assert ( strcmp( widget->klass_name, "GtkSizeGroup" ) == 0 );
       
     child_node = get_first_child(node); 
     while (child_node != NULL) {       
                     
          g_assert( strcmp( get_node_name( child_node ), "widget" ) == 0 ); 
          attr = child_node->properties;
          
          g_assert( strcmp( get_attr_node_name( attr ), "name" ) == 0 );
          data = g_strdup( get_attr_node_text( attr ) ); 
           
          sizegroup = g_list_append(sizegroup, data );           
         /*  step to next widget  */
          child_node = get_next_node(child_node);          
     }
     widget->sizegroup = sizegroup;
  
}

static void
parse_packing( g2cDoc *doc, g2cWidget *widget )
{
xmlAttr * attr   =  NULL;
gboolean flag = FALSE;
g2cPackDirection direction = PACK_START;
gchar *pack    = NULL;
gchar *pattr = NULL;
gchar *menu = NULL;

/*  on entry doc->current points to the first packing property */

  /* The good stuff starts with this node's children */
  
  /*   GTK_TYPE_BOX should perform the packing function  */

  if ( ( g_type_is_a( widget->parent->klass, GTK_TYPE_BOX ) ) ||
       ( g_type_is_a( widget->parent->klass, GTK_TYPE_TOOLBAR ) )  ||
       ( g_type_is_a( widget->parent->klass, GTK_TYPE_HEADER_BAR ) ) )
    {
      widget->packing_type = BOX_PACKING;
      widget->packing.box.pack_type = PACK_START;
      
      while (doc->current != NULL) {                   
          
          /* Parse the expand, fill  padding pack_type    */
          
          if ( strcmp( get_node_name( doc->current ), "property" ) == 0 ) {
              attr = doc->current->properties; 
              //pattr = get_attr_node_text( attr );
              if ( strcmp( get_attr_node_text( attr ), "expand" ) == 0 ) {
                  flag = ( strcmp( get_node_text( doc->current ), "True" ) == 0 );
                  widget->packing.box.expand = ( flag ) ? TRUE : FALSE;
              }
              if( strcmp( get_attr_node_text( attr ), "fill" ) == 0 ) {

                  flag = ( strcmp( get_node_text( doc->current ), "True" ) == 0 );
                  widget->packing.box.fill = ( flag ) ? TRUE : FALSE;
              }
              if ( strcmp( get_attr_node_text( attr ), "pack_type" ) == 0 ) {
                  pack = g_strdup( get_node_text( doc->current ) );
                  if ( strcmp(pack , "end" ) == 0 )
                      direction =  PACK_END;
                  else
                      direction = PACK_START;
                  widget->packing.box.pack_type = direction;
                  g_free(pack);
              } 
              if ( strcmp( get_attr_node_text( attr ), "padding" ) == 0 ) {     
                  widget->packing.box.padding = atoi( get_node_text( doc->current ) );
              } 
              if ( strcmp( get_attr_node_text( attr ), "homogeneous" ) == 0 ) { 
                  flag = ( strcmp( get_node_text( doc->current ), "True" ) == 0 );
                  widget->packing.box.homogeneous = ( flag ) ? TRUE : FALSE;
              }
              if ( strcmp( get_attr_node_text( attr ), "non_homogeneous" ) == 0 ) { 
                  flag = ( strcmp( get_node_text( doc->current ), "True" ) == 0 );
                  widget->packing.box.non_homogeneous = ( flag ) ? TRUE : FALSE;
              }
              if ( strcmp( get_attr_node_text( attr ), "secondary" ) == 0 ) { 
                  flag = ( strcmp( get_node_text( doc->current ), "True" ) == 0 );
                  widget->packing.box.secondary = ( flag ) ? TRUE : FALSE;
              }
              // position will be ignored
          }                           
          /*  step to next property   */
          doc->current = get_next_node(doc->current);  
           
      }  /* while doc->current is not NULL  */
    }
  else if( g_type_is_a( widget->parent->klass, GTK_TYPE_GRID ) )
    {
      widget->packing_type = GRID_PACKING;
      /*  default values if width and height absent */
      widget->packing.grid.width = 1;
      widget->packing.grid.height = 1;
      
      while (doc->current != NULL) {  
          
          if ( strcmp( get_node_name( doc->current ), "property" ) == 0 ) {
              attr = doc->current->properties; 
              /* Parse the packing info */
              if ( strcmp( get_attr_node_text( attr ), "left_attach" ) == 0 ) {
                  widget->packing.grid.left_attach = atoi( get_node_text( doc->current ) );
              }
              if ( strcmp( get_attr_node_text( attr ), "width" ) == 0 ) {
                 widget->packing.grid.width = atoi( get_node_text( doc->current ) );
              }
              if ( strcmp( get_attr_node_text( attr ), "top_attach" ) == 0 ) {
                 widget->packing.grid.top_attach = atoi( get_node_text( doc->current ) );
              }
              if ( strcmp( get_attr_node_text( attr ), "height" ) == 0 ) {
                 widget->packing.grid.height = atoi( get_node_text( doc->current ) );
              }  
         }
          /*  step to next property   */
         doc->current = get_next_node(doc->current);  
      }
    }
  else if (g_type_is_a( widget->parent->klass, GTK_TYPE_NOTEBOOK ) )   /*  (g_type_is_a( widget->klass, GTK_TYPE_LABEL )) &&  */
    {
      while (doc->current != NULL) { 
       if ( strcmp( get_node_name( doc->current ), "property" ) == 0 ) {
              attr = doc->current->properties; 
              if ( strcmp( get_attr_node_text( attr ), "tab_fill" ) == 0 ) {
                 flag = ( strcmp( get_node_text( doc->current ), "True" ) == 0 );
                  widget->packing.tab.tab_fill = ( flag ) ? TRUE : FALSE;
              }
              if ( strcmp( get_attr_node_text( attr ), "tab_expand" ) == 0 ) {
                 flag = ( strcmp( get_node_text( doc->current ), "True" ) == 0 );
                  widget->packing.tab.tab_expand = ( flag ) ? TRUE : FALSE;
              }
              if ( strcmp( get_attr_node_text( attr ), "reorderable" ) == 0 ) {
                 flag = ( strcmp( get_node_text( doc->current ), "True" ) == 0 );
                  widget->packing.tab.reorderable = ( flag ) ? TRUE : FALSE;
              }
              if ( strcmp( get_attr_node_text( attr ), "detachable" ) == 0 ) {
                 flag = ( strcmp( get_node_text( doc->current ), "True" ) == 0 );
                  widget->packing.tab.detachable = ( flag ) ? TRUE : FALSE;
              }
              if ( strcmp( get_attr_node_text( attr ), "menu_label" ) == 0 ) {
                  menu = g_strdup( get_node_text( doc->current ) );
                  if (menu != NULL) {
                     widget->packing.tab.menu_label =  menu;                     
                  }
              }
       }
       doc->current = get_next_node(doc->current);  
      }
    }
  else if( (g_type_is_a( widget->parent->klass, GTK_TYPE_LAYOUT ) ) ||
           (g_type_is_a( widget->parent->klass, GTK_TYPE_FIXED  ) ) ) 
  {
      while (doc->current != NULL) { 
         if ( strcmp( get_node_name( doc->current ), "property" ) == 0 ) {
           attr = doc->current->properties; 
           if ( strcmp( get_attr_node_text( attr ), "x" ) == 0 ) {
                 widget->packing.layout.x = atoi( get_node_text( doc->current ) );
           } 
           if ( strcmp( get_attr_node_text( attr ), "y" ) == 0 ) {
                 widget->packing.layout.y = atoi( get_node_text( doc->current ) );
           } 
         }
         doc->current = get_next_node(doc->current);
      }  /* end while */
  }
 else if( g_type_is_a( widget->parent->klass, GTK_TYPE_ASSISTANT ) ) 
  {
     while (doc->current != NULL) { 
         if ( strcmp( get_node_name( doc->current ), "property" ) == 0 ) {
           attr = doc->current->properties;
           if ( strcmp( get_attr_node_text( attr ), "page_type" ) == 0 ) {
              g2c_widget_set_property (widget, "_page_type", get_node_text( doc->current ) );
           }
           if ( strcmp( get_attr_node_text( attr ), "title" ) == 0 ) {
              g2c_widget_set_property (widget, "_page_title", get_node_text( doc->current ) );
           } 
           if ( strcmp( get_attr_node_text( attr ), "complete" ) == 0 ) {
              g2c_widget_set_property (widget, "_page_complete", get_node_text( doc->current ) );
           } 
         } 
         doc->current = get_next_node(doc->current);
     }  /* end while */
  }
else if( g_type_is_a( widget->parent->klass, GTK_TYPE_PANED ) ) 
  {
    while (doc->current != NULL) { 
         if ( strcmp( get_node_name( doc->current ), "property" ) == 0 ) {
           attr = doc->current->properties;
           if ( strcmp( get_attr_node_text( attr ), "resize" ) == 0 ) {
              g2c_widget_set_property (widget, "_resize", get_node_text( doc->current ) );
           }
           if ( strcmp( get_attr_node_text( attr ), "shrink" ) == 0 ) {
              g2c_widget_set_property (widget, "_shrink", get_node_text( doc->current ) );
           }            
         } 
         doc->current = get_next_node(doc->current);
     }  /* end while */
  }
else if( g_type_is_a( widget->parent->klass, GTK_TYPE_STACK ) )
{
    while (doc->current != NULL) { 
        if ( strcmp( get_node_name( doc->current ), "property" ) == 0 ) {
           attr = doc->current->properties;
           if ( strcmp( get_attr_node_text( attr ), "name" ) == 0 ) {              
              widget->packing.stack.name = g_strdup(get_node_text( doc->current ));
           } 
           if ( strcmp( get_attr_node_text( attr ), "title" ) == 0 ) {               
              widget->packing.stack.title = g_strdup(get_node_text( doc->current ));
           } 
           if ( strcmp( get_attr_node_text( attr ), "icon_name" ) == 0 ) {                            
              widget->packing.stack .icon_name = g_strdup(get_node_text( doc->current ));
           }
           if ( strcmp( get_attr_node_text( attr ), "position"  ) == 0 ) { 
              widget->packing.stack.position = atoi(get_node_text( doc->current ) );
           }
           if ( strcmp( get_attr_node_text( attr ), "needs_attention" ) == 0 ) {
              flag = ( strcmp( get_node_text( doc->current ), "True" ) == 0 );
              widget->packing.stack.needs_attention = ( flag ) ? TRUE : FALSE ;
           }
        }
        doc->current = get_next_node(doc->current);
    }   /*  end while */
}
else if( g_type_is_a( widget->parent->klass, GTK_TYPE_POPOVER_MENU ) ) 
 {
    while (doc->current != NULL) { 
        if ( strcmp( get_node_name( doc->current ), "property" ) == 0 ) {
           attr = doc->current->properties;
           if ( strcmp( get_attr_node_text( attr ), "submenu" ) == 0 ) { 
               g2c_widget_set_property (widget, "_submenu", get_node_text( doc->current ) );              
           }
           if ( strcmp( get_attr_node_text( attr ), "position" ) == 0 ) { 
               g2c_widget_set_property (widget, "_position", get_node_text( doc->current ) );              
           } 
        }   
        doc->current = get_next_node(doc->current);    
    }  /*  end while */
 }
else if( g_type_is_a( widget->parent->klass, GTK_TYPE_OVERLAY ) ) 
 {
     while (doc->current != NULL) { 
         if ( strcmp( get_node_name( doc->current ), "property" ) == 0 ) {
            attr = doc->current->properties;
            if ( strcmp( get_attr_node_text( attr ), "pass_through" ) == 0 ) { 
               g2c_widget_set_property (widget, "_pass_through", get_node_text( doc->current ) );              
           }  
           /*   index is ignored  */  
         }
         doc->current = get_next_node(doc->current);    
     }
 } 
}

static g2cAccel *
parse_accel( g2cDoc *doc )
{
  xmlAttr * attr   =  NULL;
  g2cAccel *accel  = g2c_accel_new();

  /* The good stuff starts with this node's children */
  //doc->current = doc->current->children; 
  attr = doc->current->properties;  

  g_assert( strcmp( get_attr_node_name( attr ), "key" ) == 0 );
  g2c_accel_set_key( accel, get_attr_node_text( attr ) );
  g_assert( NULL != accel->key );

  attr = attr->next;

  g_assert( strcmp( get_attr_node_name( attr ), "signal" ) == 0 );
  g2c_accel_set_signal( accel, get_attr_node_text( attr ) );
  g_assert( NULL != accel->signal );

  attr = attr->next;
  
  if (attr != NULL) {   
  /* Parse the name and class */
    g_assert( strcmp( get_attr_node_name( attr ), "modifiers" ) == 0 );
    g2c_accel_set_modifiers( accel, get_attr_node_text( attr ) );
    g_assert( NULL != accel->modifiers );
  } else {
    g2c_accel_set_modifiers( accel, "");  
  }
  return accel;
}

static g2cSignal *
parse_signal( g2cDoc *doc )
{
  xmlAttr * attr   =  NULL;
  g2cSignal *signal = g2c_signal_new();
  gchar *attr_text = NULL;
//  gchar **parts = NULL;

  /* The good stuff starts with this node's children */
  attr = doc->current->properties;   

  /* Parse the name and class */
  g_assert( strcmp( get_attr_node_name( attr ), "name" ) == 0 );
  attr_text = g_strdup(get_attr_node_text( attr ) );
//  parts = g_strsplit(attr_text, "-", 2);
//  if (strcmp(parts[0], "accel") == 0) {
//     g2c_signal_set_name( &signal, parts[1]);
//  } else 
     g2c_signal_set_name( &signal, g_strdelimit(attr_text, "-",'_'));
//  g_strfreev( parts );
  g_free ( attr_text );
  g_assert( NULL != signal->name );
  
  attr = attr->next;
  g_assert( strcmp( get_attr_node_name( attr ), "handler" ) == 0 );
  g2c_signal_set_handler( &signal, get_attr_node_text( attr ) );
  
  attr = attr->next;
  attr_text = g_strdup(get_attr_node_name( attr ));
  if (strcmp( attr_text, "object" ) == 0) {
     g2c_signal_set_object( &signal, get_attr_node_text( attr ) );
     attr = attr->next;
  }
  g_assert( strcmp( get_attr_node_name( attr ), "swapped" ) == 0);
  g2c_signal_set_swapped( &signal, get_attr_node_text( attr ) );
  g_free( attr_text );
  /*
  g_assert( strcmp( get_node_name( doc->current ), "last_modification_time" ) == 0 );
  g2c_signal_set_timestamp( signal, get_node_text( doc->current ) );
   
  g_assert( NULL != signal->timestamp );

  doc->current = doc->current->next;

  if( strcmp( get_node_name( doc->current ), "object" ) == 0 )
    {
      g2c_signal_set_object( signal, get_node_text( doc->current ) );
      g_assert( NULL != signal->object );

      doc->current = doc->current->next;
    }

  if( strcmp( get_node_name( doc->current ), "after" ) == 0 )
    {
      g2c_signal_set_after( signal, get_node_text( doc->current ) );

      doc->current = doc->current->next;
    }

  if( strcmp( get_node_name( doc->current ), "data" ) == 0 )
    {
      g2c_signal_set_data( signal, get_node_text( doc->current ) );
      g_assert( NULL != signal->data );

      doc->current = doc->current->next;
    }
*/  

  return signal;
}

static void
output_widget_files( g2cWidget *widget, g2cDoc *doc, gboolean bWindow, g2cWidget *parent_widget )
{
    /*  called once for each GtkWindow and GtkDialog */

  g_assert( NULL != widget );
  g_assert( NULL != doc );
  
  /* There are two sets of files created for the GtkWindow or GtkDialog widget:
   * 
   * widget_gui.h	struct containing gui; gui create/destroy prototypes
   * widget_gui.c 	implementation of the gui constructor/destructor
   * only for main window:
   *   widget.h 	struct containing pointer to gui struct; create/destroy prototypes
   *   widget.c 	implementation of constructor/destructor: calls widget_gui_create()
   *
   */  

  output_widget_gui_h(widget, doc );
  
  output_widget_gui_c(widget, doc, parent_widget );

  if (bWindow == TRUE) {       
       output_widget_h(widget, doc );
       
       output_widget_c(widget, doc );
  }

}

static void       
output_widget_gui_h( g2cWidget *main_widget, g2cDoc *doc )
{
  FILE  *file       = 0;  
  gchar *file_name  = NULL;
  gchar *gui_name   = NULL;
  gchar *type_name  = NULL;
  gchar *temp_name = NULL;
  g2cWidget *widget = NULL;
  //g2cWidget *widget2= NULL;
  GList *run        = NULL;
  GList *signal_run  = NULL;
  g2cSignal *signal2 = NULL;
  
/* Get the transformed names for the widget */
  gui_name  = g2c_transform_name( main_widget->name, NT_GUI );
  type_name = g2c_transform_name( main_widget->name, NT_TYPENAME );  
  
  /* Write widget_gui.h
   * 
   * #ifndef WIDGET_NAME_GUI_H 
   * #define WIDGET_NAME_GUI_H
   *
   * #include <gtk/gtk.h>
   *
   * typedef struct tag_WidgetNameGui
   * {
   *   <widgets>
   * } WidgetNameGui;
   * 
   * WidgetNameGui* widget_name_gui_create( WidgetName *owner );
   * void 	   widget_name_gui_destroy( WidgetNameGui *widget_name_gui );
   * 
   * ***Signal handlers ***
   *
   * void signal_handler_a( ... );
   * void signal_handler_b( ... );
   *
   * #endif
   *  
   */

  /* This file is always blown away then written, so now existence checks are necessary */
  file_name = g_strconcat( DIR_PREFIX, "/", main_widget->name, "_gui.h", NULL );

  
  g_message( "Creating %s\n", file_name );

  file      = fopen( file_name, "w" );

  if (file == NULL)
    {
      printf ("File %s could not be opened. %s\n", file_name, strerror(errno));
      g_assert(file != NULL);
    }

  CURRENT_FILE   = file;

  /* #ifndef WIDGET_NAME_GUI_H
   * #define WIDGET_NAME_GUI_H */
  fprintf( file, "#ifndef %s\n", gui_name );
  fprintf( file, "#define %s\n", gui_name );
  fprintf( file, "\n" );
  g_free( gui_name );

  /* #include <gtk/gtk.h> */
  fprintf( file, "#include <gtk/gtk.h>\n" );
  fprintf( file, "\n" );
  /* typedef struct tag_WidgetNameGui  */
  fprintf( file, "typedef struct tag_%sGui\n", type_name );
  fprintf( file, "{\n" );

  /* GtkAccelGroup *accelerators */
  fprintf( file, "\t%-20s *%s;\n", "GtkAccelGroup", "accel_group" );
  run = main_widget->accel_widgets;
  while (run != NULL) {
      widget = (g2cWidget *) run->data;      
      output_widget_struct( widget, file );                 
      run = run->next;      
  g2cSignal *signal2 = NULL;
  }  

  /* <widgets> - the top-level widget and its subwidgets */
  output_widget_struct( main_widget, file ); 
  /* output all the associate widgets  */
  run = main_widget->associates;
  while (run != NULL) {
      widget = (g2cWidget *) run->data;      
      output_widget_struct( widget, file );                 
      run = run->next;
  }  
  run = main_widget->popups;
  while (run != NULL) {
      widget = (g2cWidget *) run->data;      
      output_widget_struct( widget, file );                 
      run = run->next;
  }  
  
  /* } WidgetNameGui; */
  fprintf( file, "} %sGui;\n", type_name );
  fprintf( file, "\n" );

  /* WidgetNameGui *widget_name_gui_create( void ); */
  fprintf( file, "%sGui *%s_gui_create (gpointer owner);\n", type_name, main_widget->name );
  fprintf( file, "\n" );

  /* void widget_name_gui_destroy( WidgetNameGui *gui ); */
  fprintf( file, "void %s_gui_destroy (%sGui *%s);\n", main_widget->name, type_name, main_widget->name );
  fprintf( file, "\n" );

  /* Signals prototypes */
  /* void signal_handler_a( ... ); */
  clear_signal_list ();
  output_signal_prototype( main_widget, file );
  /*  Add for GtkMenu etc.  */
  run = main_widget->popups;
  while (run != NULL) {
      widget = (g2cWidget *) run->data;      
      output_signal_prototype( widget, file );                 
      run = run->next;
  }  
  clear_signal_list ();
  
  run = main_widget->accel_widgets;
  while (run != NULL) {
      widget = (g2cWidget *) run->data;  
      signal_run = widget->signals;
      while (signal_run != NULL) {
         signal2 = (g2cSignal *) signal_run->data; 
         g2c_widget_create_closure_prototype(signal2, main_widget);         
         signal_run = signal_run->next;
      }
      run = run->next;
  } 
  clear_signal_list ();
  
  /*  output populate model prototypes */

  run = main_widget->associates;
  while (run != NULL) {
      widget = (g2cWidget *) run->data;
      if ((strcmp(widget->klass_name, "GtkListStore") == 0) ||
          (strcmp(widget->klass_name, "GtkTreeStore") == 0))   {
          fprintf( file, "void populate_%s(%sGui *gui, GtkTreeModel* liststore);\n\n",                   
                  widget->name,
                  type_name);
      }      
      run = run->next;
  }
  if (    (strcmp(main_widget->klass_name, "GtkFileChooserDialog") != 0 ) &&
          (strcmp(main_widget->klass_name, "GtkAboutDialog") != 0) &&
          (strcmp(main_widget->klass_name, "GtkFontChooserDialog") != 0) &&
          (strcmp(main_widget->klass_name, "GtkColorChooserDialog") != 0) && 
          (strcmp(main_widget->klass_name, "GtkRecentChooserDialog") != 0) &&
          (strcmp(main_widget->klass_name, "GtkAppChooserDialog") != 0) &&
          (strcmp(main_widget->klass_name, "GtkMessageDialog") != 0) &&
          (strcmp(main_widget->klass_name, "GtkOffscreenWindow") != 0) )
  {
     fprintf( file, "void initialise_%s (%sGui *%s);\n\n",
              main_widget->name, type_name, main_widget->name );
  }
  /* #endif */
  fprintf( file, "#endif" );
  fprintf( file, "\n" );

  fclose( file );
  CURRENT_FILE = NULL;

  g_free( type_name );
  g_free( file_name );
  
    
}    /* end output_widget_gui_h  */

static void       
output_widget_gui_c( g2cWidget *main_widget, g2cDoc *doc, g2cWidget *parent_widget )
{
  FILE  *file       = 0;
  gchar *file_name  = NULL;
  gchar *type_name  = NULL;
  gchar *include_name  = NULL;
  g2cWidget *widget = NULL;
  GList *run        = NULL;
  GList *signal_run  = NULL;
  g2cSignal *signal2 = NULL;
  guint max_level;
  guint level;
  GList *register_list;
  g2cRegister *reg;
  
/* Get the transformed name for the widget */
  type_name = g2c_transform_name( main_widget->name, NT_TYPENAME );  
  
  /* Write widget_gui.c
   *    widget->klass_name
   *
   * #include <sys/types.h>
   * #include <sys/stat.h>
   * #include <unistd.h>
   * #include <string.h>
   *
   * #include <gtk/gtk.h>
   * #include <gdk/gdkkeysyms.h>
   *
   * #include "widget_gui.h"
   * #include "model.h"
   *
   * WidgetNameGui *widget_name_gui_create( void )
   * {
   *   WidgetNameGui *gui = g_new0( WidgetNameGui, 1 );
   *
   *   WIDGET CREATION CODE
   *
   *   ACCELERATOR CODE
   *
   *   SIGNAL CONNECTION CODE
   *
   *   POPULATION OF MODEL STORES
   * 
   *   return gui;
   * }
   * 
   * void widget_name_gui_destroy( WidgetNameGui *widget_name )
   * {
   *   WIDGET DESTRUCTION CODE
   * }
   * 
   * #endif
   *  
   */

  file_name      = g_strconcat( DIR_PREFIX, "/", main_widget->name, "_gui.c", NULL );
  
  g_message( "Creating %s\n", file_name );
 
  file = fopen( file_name, "w" );
  if (file == NULL) {
      g_message ("File %s could not be opened. %s\n", file_name, strerror(errno));
      g_assert(file != NULL);  
  }
  CURRENT_FILE   = file;

  /* #include <stuff> */

  fprintf( file,           
           "#include <sys/types.h>\n"
           "#include <sys/stat.h>\n"
           "#include <unistd.h>\n"
           "#include <string.h>\n"
           "\n"
           "#include <gdk/gdkkeysyms.h>\n"
           "#include <gtk/gtk.h>\n"
           "#include <glib.h>\n"
           "\n" );
  fprintf (file, "/*                Generated from %s                 */\n\n", 
          doc->project->source_file);

  /* #include widget_name_gui.h */
  fprintf( file, "#include \"%s_gui.h\"\n", main_widget->name );
  if (parent_widget != NULL) {
     fprintf( file, "#include \"%s.h\"\n", parent_widget->name );
  } else {
     fprintf( file, "#include \"%s.h\"\n", main_widget->name ); 
  }
  include_name = g_strconcat( DIR_PREFIX, "/","model.h", NULL );
  if (file_exists(include_name))
    fprintf( file,  "#include \"model.h\"\n");
  g_free( include_name );
  include_name = g_strconcat( DIR_PREFIX, "/","control.h", NULL );
  if (file_exists(include_name))
    fprintf( file,  "#include \"control.h\"\n");
  g_free( include_name );
  fprintf( file, "\n" );

  /* WidgetNameGui *widget_name_gui_create( void ) */
  fprintf( file, "%sGui *%s_gui_create (gpointer owner)\n", type_name, main_widget->name );
  fprintf( file, "{\n" );

  /* Output temporary declarations */
  output_temp_declarations( main_widget, file );
  
  run = main_widget->popups;
  while (run != NULL) {
      widget = (g2cWidget *) run->data;      
      output_temp_declarations( widget, file );                 
      run = run->next;
  }  

  /* WidgetNameGui *gui = g_new0( WidgetNameGui, 1 ); */
  fprintf( file, "%sGui *gui = g_new0 (%sGui, 1);\n", type_name, type_name );
  fprintf( file, "\n" );

  /* Accelerators */
  fprintf( file, "\tgui->accel_group = gtk_accel_group_new ();\n" );
  fprintf( file, "\tg_object_set_data (G_OBJECT (gui->accel_group), \"owner\", owner);\n");
  /* --------------------- */
//  run = main_widget->accel_widgets;
//  while (run != NULL) {
//      widget = (g2cWidget *) run->data;      
//      output_widget_create( widget, file, RECURSE_ALL, FALSE );                 
//      run = run->next;
//  } 
//  fprintf( file, "\n" );
//  run = main_widget->associates;
//  while (run != NULL) {
//      widget = (g2cWidget *) run->data;      
//      output_widget_create( widget, file, RECURSE_ALL, FALSE );          
//      run = run->next;
//  } 
//  fprintf( file, "\n" );
//  run = main_widget->popups;
//  while (run != NULL) {
//      widget = (g2cWidget *) run->data;      
//      output_widget_create( widget, file, RECURSE_ALL, FALSE );                 
//      run = run->next;
//  }  
    /* WIDGET CREATION CODE */
  max_level = get_max_register_level(main_widget);
  
  fprintf( file, "\n\t/* Widget construction */\n" );
  
  for (level = 0; level <= max_level; level++) {
      
    fprintf( file, "\t/* Widgets at level %d */\n", level );
    
    register_list = g_list_first( main_widget->regster );
    while ( NULL != register_list ) {
        reg = (g2cRegister *) register_list->data;
        if (reg->level == level) {   
            
            output_widget_create( reg->widget, file );  
            
        }
        register_list = g_list_next( register_list );  
    } 
  }
  
  /* ---------------------------------------- */
  
  if (doc->project->main_widget == main_widget) {
      fprintf( file,
               "\tgtk_widget_show (GTK_WIDGET (gui->%s));\n\n",
                main_widget->name );
  }
 
  /* ACCELERATOR CODE */
  if ( (strcmp(main_widget->klass_name, "GtkPopoverMenu") != 0) && 
       (strcmp(main_widget->klass_name, "GtkPopover") != 0) ) {
    fprintf( file, "\n\t/* Accelerators */\n" );
    fprintf( file, "\n\tgtk_window_add_accel_group (GTK_WINDOW(gui->%s), gui->accel_group);\n", main_widget->name );
    run = main_widget->accel_widgets;
    while (run != NULL) {
        widget = (g2cWidget *) run->data;      
        fprintf( file,
                "\tgtk_window_add_accel_group (GTK_WINDOW(gui->%s), gui->%s);\n",
                            main_widget->name,
                            widget->name);            
        run = run->next;
    } 
  fprintf( file, "\n"); 
  }
  
  //fprintf( file, "\tgtk_window_add_accel_group (GTK_WINDOW (gui->%s), gui->accel_group);\n", main_widget->name );

  /* SIGNAL CONNECTION CODE */
  fprintf( file, "\n\t/* Signal connections */\n" );
  if (doc->project->main_widget == main_widget) {
      fprintf( file, "\tg_signal_connect_swapped (G_OBJECT (gui->%s), \"destroy\",\n" ,main_widget->name );
      fprintf( file, "\t\tG_CALLBACK (gtk_main_quit), NULL);\n\n" );
  }
  output_signal_connect( main_widget, file );
  
  /*  For GtkMenu etc.  */
  run = main_widget->popups;
  while (run != NULL) {
      widget = (g2cWidget *) run->data;      
      output_signal_connect( widget, file ); 
      output_accelerators( widget, file);
      run = run->next;
  }  
  
  output_accelerators( main_widget, file );
  
  run = main_widget->accel_widgets;
  while (run != NULL) {
      widget = (g2cWidget *) run->data;  
      signal_run = widget->signals;
      while (signal_run != NULL) {
         signal2 = (g2cSignal *) signal_run->data; 
         g2c_widget_create_closure_connect(signal2, widget);                 
         signal_run = signal_run->next;
      }
      run = run->next;
  } 
  
  /* MODEL POPULATION CODE */
  if (main_widget->associates != NULL)
    fprintf( file, "\n\t/* Population of Stores */\n\n" );
  
  run = main_widget->associates;
  while (run != NULL) {
      widget = (g2cWidget *) run->data;
      if ((strcmp(widget->klass_name, "GtkListStore") == 0) ||
          (strcmp(widget->klass_name, "GtkTreeStore") == 0))   {
          fprintf( file, "\tpopulate_%s(gui, GTK_TREE_MODEL(gui->%s));\n\n",                   
                  widget->name,
                  widget->name);
      }      
      run = run->next;
  }
  if ( (strcmp(main_widget->klass_name, "GtkFileChooserDialog") != 0 ) &&
        (strcmp(main_widget->klass_name, "GtkAboutDialog") != 0) &&
        (strcmp(main_widget->klass_name, "GtkFontChooserDialog") != 0) &&
        (strcmp(main_widget->klass_name, "GtkColorChooserDialog") != 0) && 
        (strcmp(main_widget->klass_name, "GtkRecentChooserDialog") != 0) &&
        (strcmp(main_widget->klass_name, "GtkAppChooserDialog") != 0) &&
        (strcmp(main_widget->klass_name, "GtkMessageDialog") != 0) &&
        (strcmp(main_widget->klass_name, "GtkOffscreenWindow") != 0))
  {
      fprintf( file, "\tinitialise_%s (gui);\n\n",
              main_widget->name );
  }
  /* return gui; */
  fprintf( file, "\treturn gui;\n" );
  fprintf( file, "}\n" );
  fprintf( file, "\n" );
  

  /* void widget_name_gui_destroy( WidgetNameGui *gui ) */
  fprintf( file, "void %s_gui_destroy (%sGui *gui)\n",
           main_widget->name,
           type_name );
  fprintf( file, "{\n" );

  /* gtk_widget_destroy( gui->widget_name ); */
  fprintf( file, "\tgtk_widget_destroy (GTK_WIDGET (gui->%s));\n", main_widget->name );

  /* g_free( gui ); */
  fprintf( file, "\tg_free (gui);\n" );
  fprintf( file, "\treturn;\n" );
  fprintf( file, "}\n" );
  fprintf( file, "\n" );

  fclose( file );
  CURRENT_FILE = NULL;
  
  g_free( type_name );
  g_free( file_name );
    
    
}  /* end output_widget_gui_c  */

static void       
output_widget_h( g2cWidget *main_widget, g2cDoc *doc )
{
  FILE  *file       = 0;
  gchar *file_name  = NULL;
  gchar *std_name   = NULL;
  gchar *type_name  = NULL;
  gchar *dialogue_type_name  = NULL;
  g2cWidget *widget = NULL;
  g2cWidget *dialog_widget = NULL;
  GList *run        = NULL;  
  GList *model_run  = NULL;
  
/* Get the transformed names for the widget */
  std_name  = g2c_transform_name( main_widget->name, NT_STANDARD );
  type_name = g2c_transform_name( main_widget->name, NT_TYPENAME );  
 
  
  /* Write widget.h
   * 
   * #ifndef WIDGET_NAME_H 
   * #define WIDGET_NAME_H
   * 
   * #include <gtk/gtk.h>
   * #include "widget_gui.h"
   * 
   * typedef struct tag_WidgetName
   * {
   * 		WidgetNameGui *gui;
   *            DialogNameGui *dialognamegui;  ...
   * 		\* Put all your stuff here! *\
   * } WidgetName;
   * 
   * void 	 widget_name_terminate( WidgetName *widget_name );
   * 
   * #endif
   *  
   */

  file_name = g_strconcat( DIR_PREFIX, "/", main_widget->name, ".h", NULL );

      
  file = fopen( file_name, "w" );
  if (file == NULL) {
      printf ("File %s could not be opened. %s\n", file_name, strerror(errno));
      g_assert(file != NULL);  
  }
  CURRENT_FILE = file;

  g_message( "Creating %s\n", file_name );

  fprintf( file, "#ifndef %s\n", std_name );
  fprintf( file, "#define %s\n", std_name );
  fprintf( file, "\n" );
  fprintf( file, "#include <gtk/gtk.h>\n" );
  g_free( std_name  );
  
  fprintf( file, "#include \"%s_gui.h\"\n", main_widget->name );
  run = g_list_first(doc->project->dialogue_widgets);
  while (run != NULL) {
      widget = (g2cWidget *) run->data;    
      fprintf( file, "#include \"%s_gui.h\"\n", widget->name );
      run = g_list_next(run);
  }
  fprintf( file, "\n" );
  // Output column enumerations for liststores
  
  run = main_widget->associates;
  while (run != NULL) {
        widget = (g2cWidget *) run->data;
      	if ((strcmp(widget->klass_name, "GtkListStore") == 0) ||
            (strcmp(widget->klass_name, "GtkTreeStore") == 0))   {
		output_model_enum(widget, file);
	}
        run = run->next;
  }
  //   and for any stores in dialogues
  run = g_list_first(doc->project->dialogue_widgets);
  while (run != NULL) {
    widget = (g2cWidget *) run->data; 
    model_run = widget->associates;
    while (model_run != NULL) {
      dialog_widget = (g2cWidget *) model_run->data;
      if ((strcmp(dialog_widget->klass_name, "GtkListStore") == 0) ||
          (strcmp(dialog_widget->klass_name, "GtkTreeStore") == 0))   {
		output_model_enum(dialog_widget, file);
	}
      model_run = g_list_next(model_run);
    }
    run = g_list_next(run);
  }
  
  fprintf( file, "\n" );
  fprintf( file, "typedef struct tag_%s\n", type_name );
  fprintf( file, "{\n" );
  fprintf( file, "\t%sGui *gui;\n", type_name );
  
  run = g_list_first(doc->project->dialogue_widgets);
  while (run != NULL) {
      widget = (g2cWidget *) run->data;          
      dialogue_type_name = g2c_transform_name( widget->name, NT_TYPENAME );
      fprintf( file, "\t%sGui *%sgui;\n", dialogue_type_name, widget->name );   
      g_free( dialogue_type_name );
      run = g_list_next(run);
  } 
  
  //fprintf( file, "\t/* Put all your stuff here! */\n" );
  fprintf( file, "} %s;\n", type_name );
  fprintf( file, "\n" );
  
  fprintf( file, "void %s_terminate (%s *%s);\n", main_widget->name, type_name, main_widget->name );
  fprintf( file, "\n" );
  
  fprintf( file, "#endif" );
  fprintf( file, "\n" );

  fclose( file );
  CURRENT_FILE = NULL;
    
  g_free( type_name ); 
  g_free( file_name );  
    
}  /* end output_widget_h  */

static void       
output_cmake_file(g2cDoc *doc)
{
FILE  *file       = 0;
gchar *separator = NULL;
gchar *pos = NULL;
gchar *project_name = NULL;
gchar *file_name  = NULL;
gchar *mainfilename = NULL;
gchar *window_file_name = NULL;
gchar *dialog_file_name = NULL;
gchar *control_file_name = NULL;
gchar *model_file_name = NULL;
GList *run = NULL;
g2cWidget *widget = NULL;

    file_name = g_strconcat( DIR_PREFIX, "/CMakeLists.txt",  NULL );
    /*  
	 *  CMakeLists.txt
	 *
	 *  cmake_minimum_required (VERSION 2.8.4)
	 *  cmake_policy(SET CMP0015 NEW)
	 *  cmake_policy(SET CMP0081 OLD)
	 *  project (<project> C)
	 *  find_package(PkgConfig REQUIRED)
	 *  pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
	 *  set(INC_DIRS "${GTK3_INCLUDE_DIRS}")
	 *  string(REPLACE "C:" "../.." INC_DIRS "${INC_DIRS}")
	 *  include_directories( ${INC_DIRS} )
	 *  set(GTK3_LIB_DIRS "${GTK3_LIBRARY_DIRS}")
	 *  string(REPLACE "C:" "../../.." GTK3_LIB_DIRS "${GTK3_LIB_DIRS}")
	 *  link_directories(${GTK3_LIB_DIRS})
	 *  link_libraries(${GTK3_LIBRARIES})
	 *  add_definitions(${GTK3_CFLAGS_OTHER})
         *  set(OPTIONSs "-Wall -g -Wno-deprecated-declarations")
         *  set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${OPTIONSs}")
         *  add_definitions( -DWIN32 )
	 *  
	 *  SET (SOURCES g2c<main>.c 
	 *			window1_gui.c 
         *			dialog1_gui.c 
	 *			control.c 	 
	 *			model.c)
	 *  add_library(lib1 OBJECT ${SOURCES} )
	 *  add_executable(<prog> $<TARGET_OBJECTS:lib1> )
	 */
	 
    file = fopen( file_name, "w" );
    if (file == NULL) {
      g_message ("File %s could not be opened. %s\n", file_name, strerror(errno));
      g_assert(file != NULL);  
    }
    CURRENT_FILE = file;

    g_message( "Creating %s\n", file_name );
 
#ifdef WIN32  
    separator = g_strdup("\\");
#else
    separator = g_strdup("/");
#endif    
    pos = g_strrstr(doc->project->source_directory, "\\");
    if (pos != NULL) {
        project_name = g_strdup(pos+1);
    } else {
        pos = g_strrstr(doc->project->source_directory, "/");
        if (pos != NULL) {
             project_name = g_strdup(pos+1);
        } else {
           project_name = g_strdup(doc->project->source_directory);
        }
    }
	
    fprintf( file, "cmake_minimum_required (VERSION 2.8.4)\n" );
    fprintf( file, "cmake_policy(SET CMP0015 NEW)\n" );
#ifdef WIN32    
    fprintf( file, "cmake_policy(SET CMP0081 OLD)\n" );
#endif	
    fprintf( file, "project (%s C)\n", project_name );
	
    fprintf( file, "find_package(PkgConfig REQUIRED)\n" );
    fprintf( file, "pkg_check_modules(GTK3 REQUIRED gtk+-3.0)\n" );
#ifdef WIN32    
    fprintf( file, "set(INC_DIRS \"${GTK3_INCLUDE_DIRS}\")\n" );
    fprintf( file, "string(REPLACE \"C:\" \"../../..\" INC_DIRS \"${INC_DIRS}\")\n" );
    fprintf( file, "include_directories( ${INC_DIRS} )\n" );
    fprintf( file, "set(GTK3_LIB_DIRS \"${GTK3_LIBRARY_DIRS}\")\n" );
    fprintf( file, "string(REPLACE \"C:\" \"../../..\" GTK3_LIB_DIRS \"${GTK3_LIB_DIRS}\")\n" );
    fprintf( file, "link_directories(${GTK3_LIB_DIRS})\n" );
#else
    fprintf( file, "include_directories( ${GTK3_INCLUDE_DIRS} )\n" );
    fprintf( file, "link_directories(${GTK3_LIBRARY_DIRS})\n" );
#endif    
    fprintf( file, "link_libraries(${GTK3_LIBRARIES})\n" );
    fprintf( file, "add_definitions(${GTK3_CFLAGS_OTHER})\n" );
#ifdef SOURCE_DEBUG    
    fprintf( file, "set(OPTIONS \"-Wall -g -Wno-deprecated-declarations\")\n" );
#else
    fprintf( file, "set(OPTIONS \"-Wall -Wno-deprecated-declarations\")\n" );
#endif    
    fprintf( file, "set(CMAKE_C_FLAGS   \"${CMAKE_C_FLAGS} ${OPTIONS}\")\n" );
#ifdef WIN32
    fprintf( file, "set(EXE_OPTIONS \"-mwindows\")\n");
    fprintf( file, "set(CMAKE_EXE_LINKER_FLAGS \"${CMAKE_EXE_LINKER_FLAGS} ${EXE_OPTIONS}\")\n");
    fprintf( file, "add_definitions( -DWIN32 )\n" );
#endif
	
    mainfilename = g_strdup_printf ("%s_main.c", doc->project->program_name);
    
    fprintf(file, "SET(SOURCES %s\n", mainfilename );   

    window_file_name = g_strconcat( doc->project->main_widget->name, "_gui.c", NULL );  
    fprintf( file, "\t\t\t%s\n", window_file_name );
    run = g_list_first(doc->project->dialogue_widgets);
    while (run != NULL) {
    	widget = (g2cWidget *) run->data; 
    	dialog_file_name = g_strconcat( widget->name, "_gui.c", NULL );
    	fprintf( file, "\t\t\t%s\n", dialog_file_name );	
    	g_free( dialog_file_name );		
    	run = g_list_next(run);
    }
    control_file_name = g_strconcat( DIR_PREFIX, "/",  "control.c", NULL );
    fprintf( file, "\t\t\tcontrol.c\n" );
    model_file_name = g_strconcat( DIR_PREFIX, "/",  "model.c", NULL ); 
    if( file_exists( model_file_name ) ) {    
        fprintf( file, "\t\t\tmodel.c\n" );
    }  
    fprintf( file, "\t\t\t)\n" );
    
    fprintf( file, "add_library(lib1 OBJECT ${SOURCES} )\n");
    
    if (doc->project->resource_file != NULL) {
        fprintf( file, "set (CMAKE_RC_COMPILER \"/c/msys64/mingw64/bin/windres.exe\")\n");
        fprintf( file, "set (RC_SOURCE %s)\n", doc->project->resource_file);
        fprintf( file, "set (RC_OBJ ${RC_SOURCE}.obj)\n");
        fprintf( file, "add_custom_command(OUTPUT ${RC_OBJ} PRE_LINK \n");
        fprintf( file, "\t\tCOMMAND ${CMAKE_RC_COMPILER} ARGS -o${RC_OBJ} -i${RC_SOURCE} -O coff\n");
        fprintf( file, "\t\tDEPENDS lib1\n");
        fprintf( file, "\t\t)\n");
        fprintf( file, "add_executable( %s ${RC_OBJ}  $<TARGET_OBJECTS:lib1> )\n", doc->project->program_name );
    } else if (doc->project->resource_list != NULL) {
        fprintf( file, "set (CMAKE_RESOURCE_COMPILER \"glib-compile-resources.exe\")\n" );
        fprintf( file, "set (RESOURCE %s_res)\n", doc->project->main_widget->name);
        fprintf( file, "set (RESXML ${RESOURCE}.gresource.xml)\n");
        fprintf( file, "add_custom_command(OUTPUT ${RESOURCE}.c PRE_LINK \n");
        fprintf( file, "\t\t\tCOMMAND ${CMAKE_RESOURCE_COMPILER} ARGS --generate-source ${RESXML}\n");
        fprintf( file, "\t\t\tDEPENDS lib1 ${RESXML}\n");
        fprintf( file, "\t\t\t)\n");
        fprintf( file, "add_executable( %s ${RESOURCE}.c $<TARGET_OBJECTS:lib1> )\n", doc->project->program_name );        
    } else {
        fprintf( file, "add_executable( %s $<TARGET_OBJECTS:lib1> )\n", doc->project->program_name );
    }
	
    g_free( file_name );
    g_free( mainfilename );
    g_free( window_file_name );
    g_free( control_file_name );
    g_free( model_file_name );
    g_free( project_name );
    g_free( separator );
	
    fclose( CURRENT_FILE );    
    return;
}

static void
output_data_create(g2cDoc *doc, g2cWidget *widget,  FILE  *file)
{
gchar *type_name  = NULL;
GList *run = NULL;
g2cWidget *dialogue_widget = NULL;

  /* Get the transformed name for the widget */
  type_name = g2c_transform_name( widget->name, NT_TYPENAME );   
  
  fprintf( file,
           "\t%s->gui = %s_gui_create ((gpointer) %s);\n",
           widget->name,
           widget->name,
           widget->name );
  fprintf( file, "\n" );
  fprintf( file,
           "\tif (%s->gui == NULL) return 0;\n",
           widget->name );
  run = g_list_first(doc->project->dialogue_widgets);
  while (run != NULL) {
      dialogue_widget = (g2cWidget *) run->data; 
      fprintf( file, "\t%s->%sgui = %s_gui_create ((gpointer) %s);\n", 
              widget->name,
              dialogue_widget->name,
              dialogue_widget->name,
              widget->name );
      fprintf( file,
           "\tif (%s->gui == NULL) return 0;\n",
           dialogue_widget->name );
      run = g_list_next(run);
  }   
  fprintf( file, "void %s_destroy (%s *%s)\n", widget->name, type_name, widget->name );
  fprintf( file, "{\n" );
  fprintf( file, "\tgtk_widget_destroy (GTK_WIDGET(%s->gui->%s));\n",
           widget->name, widget->name );
  run = g_list_first(doc->project->dialogue_widgets);
  while (run != NULL) {
      dialogue_widget = (g2cWidget *) run->data; 
      fprintf( file, "\tgtk_widget_destroy (GTK_WIDGET(%s->%sgui->%s));\n", 
              widget->name,
              dialogue_widget->name,
              dialogue_widget->name );
      run = g_list_next(run);
  }   
  fprintf( file, "\tg_free (%s);\n", widget->name );
  fprintf( file, "}\n\n" ); 
  
   g_free( type_name );
}

static void       
output_widget_c( g2cWidget *main_widget, g2cDoc *doc )
{
  FILE  *file       = 0;
  gchar *file_name  = NULL;
  gchar *type_name  = NULL;
  gchar *dialogue_type_name = NULL;
  gchar *initialise_name = NULL;
  gboolean init_exists;
  g2cWidget *widget = NULL;
  g2cWidget *dialog_widget = NULL;
  GList *run = NULL;
  GList *model_run = NULL;
  GList *signal_run  = NULL;
  g2cSignal *signal2 = NULL;
  
 
  type_name = g2c_transform_name( main_widget->name, NT_TYPENAME );  
  
  /* Write widget.c
   * 
   * #include <gtk/gtk.h>
   * #include "widgetname_gui.h"
   * #include "widgetname.h"
   * 
   * ***Signal handlers ***
   *
   * void signal_handler_a( ... ) { ... }
   * void signal_handler_b( ... ) { ... }
   * 
   * ***   Population Store skeletons ***
   * 
   * void populate_liststore1 ( ... ) { ... }
   * 
   * #endif
   *  
   */
  file_name = g_strconcat( DIR_PREFIX, "/", main_widget->name, ".c", NULL );
      
  file = fopen( file_name, "w" );
  if (file == NULL) {
      g_message ("File %s could not be opened. %s\n", file_name, strerror(errno));
      g_assert(file != NULL);  
  }
  CURRENT_FILE = file;

  g_message( "Creating %s\n", file_name );
  
  fprintf( file, "#include <gtk/gtk.h>\n" );
  fprintf( file, "#include \"%s.h\"\n", main_widget->name );
  fprintf( file, "#include \"%s_gui.h\"\n", main_widget->name ); 
  
  run = g_list_first(doc->project->dialogue_widgets);
  while (run != NULL) {
      widget = (g2cWidget *) run->data; 
      fprintf( file, "#include \"%s_gui.h\"\n", widget->name );
      run = g_list_next(run);
  }    
  fprintf( file, "\n" );  
  
  initialise_name = g_strdup_printf("initialise_%s", main_widget->name);
  init_exists = FALSE;
//  if ( NULL != CURRENT_SOURCE_PARSER ) {
//        if ( g2c_file_parser_item_exists( CURRENT_SOURCE_PARSER, initialise_name ) ) {
//            //g_print("  initialiser '%s' already exists. Not included in generated file.\n", initialise_name);
//            init_exists = TRUE;
//        }
//  }
  g_free( initialise_name );
  if (init_exists == FALSE) {
    fprintf( file, "void initialise_%s (%sGui *%s)\n",
            main_widget->name, type_name, main_widget->name );
    fprintf( file, "{\n\n");
    fprintf( file, "\treturn;\n");
    fprintf( file, "}\n\n");  
  }
  
  run = g_list_first(doc->project->dialogue_widgets);
  while (run != NULL) {
      widget = (g2cWidget *) run->data; 
      if ( (strcmp(widget->klass_name, "GtkFileChooserDialog") != 0 ) &&
           (strcmp(widget->klass_name, "GtkAboutDialog") != 0) &&
           (strcmp(widget->klass_name, "GtkFontChooserDialog") != 0) &&
           (strcmp(widget->klass_name, "GtkColorChooserDialog") != 0) && 
           (strcmp(widget->klass_name, "GtkRecentChooserDialog") != 0) &&
           (strcmp(widget->klass_name, "GtkAppChooserDialog") != 0) &&
           (strcmp(widget->klass_name, "GtkMessageDialog") != 0) &&
           (strcmp(widget->klass_name, "GtkOffscreenWindow") != 0) )
      {
          dialogue_type_name = g2c_transform_name( widget->name, NT_TYPENAME );
          initialise_name = g_strdup_printf("initialise_%s", widget->name);
          init_exists = FALSE;
          if ( NULL != CURRENT_SOURCE_PARSER ) {
              if ( g2c_file_parser_item_exists( CURRENT_SOURCE_PARSER, initialise_name ) ) {                 
                  init_exists = TRUE;
              } else {
                  g_print("  initialiser '%s' is new. Included in generated file.\n", initialise_name);
              }
          }
          g_free( initialise_name );
          if (init_exists == FALSE) {
            fprintf( file, "void initialise_%s (%sGui *%s)\n",
                widget->name, dialogue_type_name, widget->name );
                fprintf( file, "{\n\n");
                fprintf( file, "\treturn;\n");
                fprintf( file, "}\n\n");
           }
           g_free( dialogue_type_name );
      }
      run = g_list_next(run);
  }    
  fprintf( file, "\n" );
    
  output_signal_handler( doc, main_widget, file );
  
  /*  For GtkMenu etc.  */
  run = main_widget->popups;
  while (run != NULL) {
      widget = (g2cWidget *) run->data;      
      output_signal_handler( doc, widget, file );                 
      run = run->next;
  }  
  
  run = g_list_first(doc->project->dialogue_widgets);
  while (run != NULL) {
      widget = (g2cWidget *) run->data; 
      fprintf( file, "\t/*  Signal handlers for Dialogue %s */\n", widget->name );
      output_signal_handler( doc, widget, file );
      
      run = g_list_next(run);
  } 
  
  fprintf( file, "\t/*    Accelerator handlers   */\n" );
  clear_signal_list ();
  run = main_widget->accel_widgets;
  while (run != NULL) {
      widget = (g2cWidget *) run->data;  
      signal_run = widget->signals;
      while (signal_run != NULL) {
         signal2 = (g2cSignal *) signal_run->data; 
         g2c_widget_create_closure_handler(signal2, main_widget);         
         signal_run = signal_run->next;
      }
      run = run->next;
  } 
  clear_signal_list ();
  
  /*  output populate model handlers */

  if (main_widget->associates != NULL )
     fprintf( file, "\n\t/*      Model populaters     */\n\n" );
  run = main_widget->associates;
  while (run != NULL) {
      widget = (g2cWidget *) run->data;
      output_model_populater(widget, type_name, file);
      run = run->next;
  }
  
  run = g_list_first(doc->project->dialogue_widgets);
  while (run != NULL) {
    widget = (g2cWidget *) run->data; 
    dialogue_type_name = g2c_transform_name( widget->name, NT_TYPENAME );	
    model_run = widget->associates;
    while (model_run != NULL) {
      dialog_widget = (g2cWidget *) model_run->data;
      output_model_populater(dialog_widget, dialogue_type_name, file);
      model_run = g_list_next(model_run);
    }
    g_free( dialogue_type_name );
    run = g_list_next(run);
  }

  /* Make sure there is a newline at the end of the file (gcc needs it) */
  g_free( file_name );
  g_free( type_name );
  fclose( CURRENT_FILE );    
    
}   /* end output_widget_c  */

void 
output_resource_file( g2cWidget *main_widget, g2cDoc *doc )
{
FILE  *file       = 0;
gchar *file_name  = NULL;
GList *run        = NULL;
gchar *image_file = NULL;

/* Write widget.gresource.xml
   * 
   *     <?xml version="1.0" encoding="UTF-8"?>
   *       <gresources>
   *         <gresource prefix="/images">
   *           <file>filename1</file>
   *           <file>filename2</file>
   *            ...
   *        </gresource>
   *      </gresources>
   *
   *  
   */
  file_name = g_strconcat( DIR_PREFIX, "/", main_widget->name, "_res.gresource.xml", NULL );
      
  file = fopen( file_name, "w" );
  if (file == NULL) {
      g_message ("File %s could not be opened. %s\n", file_name, strerror(errno));
      g_assert(file != NULL);  
  }
  CURRENT_FILE = file;

  g_message( "Creating %s\n", file_name );
   
  fprintf( file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" );
  fprintf( file, "\t<gresources>\n");
  fprintf( file, "\t\t<gresource prefix=\"/images\">\n");
  run = g_list_first( doc->project->resource_list );
  while ( run != NULL ) {
      image_file = (gchar *) run->data;
      fprintf( file, "\t\t\t<file>%s</file>\n", image_file);
      run = g_list_next( run );
  }
  fprintf( file, "\t\t</gresource>\n");
  fprintf( file, "\t</gresources>\n");
  
  fclose( CURRENT_FILE ); 
}

static void
output_model_enum(g2cWidget* widget, FILE  *file)
{
GList *coltype = NULL;    
g2cColumn *column;
gboolean firstcol;
gchar *colcase = NULL;
gchar *namecase = NULL;

    fprintf( file,"enum\n");
    fprintf( file,"{\n");
    if (widget->columns == NULL) {
        g_message("No columns defined for liststore %s\n", widget->name);
    }
    firstcol = TRUE;
    coltype = g_list_first(widget->columns);
    while (coltype != NULL) {
        column = (g2cColumn *) coltype->data;
        colcase = g_ascii_strup(column->col_name, -1);
        if (firstcol == TRUE) {
          fprintf( file,"\tCOL_%s = 0,\n",  colcase);
          firstcol = FALSE;
        } else {
          fprintf( file,"\tCOL_%s,\n", colcase );  
        }  
        g_free( colcase );
        coltype = g_list_next(coltype);
    }
    namecase = g_ascii_strup(widget->name, -1);
    fprintf( file, "\tNUMCOLS_%s\n", namecase );
    g_free( namecase );
    fprintf( file,"};\n");
}

static void
output_model_populater(g2cWidget* widget, gchar* type_name, FILE  *file)
{
gchar *populater = NULL;
GList *row  = NULL;
GList *cols = NULL;
GList *col  = NULL;
g2cColdata *coldata;
gchar *column_value = NULL;
gint pixbufcol = -1;
gchar *pixbuffile = NULL;
gboolean pixbuffirst = TRUE;

    populater = g_strdup_printf("populate_%s", widget->name);
    if ((strcmp(widget->klass_name, "GtkListStore") == 0) ||
        (strcmp(widget->klass_name, "GtkTreeStore") == 0))   {
        if ( NULL != CURRENT_SOURCE_PARSER )
        {
              if ( g2c_file_parser_item_exists( CURRENT_SOURCE_PARSER, populater ) ) {                  
                  g_free( populater );
                  return;
              } else {
                  g_print("  Populater '%s' is new. Included in generated file.\n", populater);
              }
        }
          //output_model_enum(widget, file);
          fprintf( file,"\n\n");
          fprintf( file, "void populate_%s(%sGui *gui,\n\t\t GtkTreeModel*\t liststore)\n",                  
                  widget->name,
                  type_name);
          fprintf( file, "{\n");
          if (widget->table == NULL) fprintf (file, "/*\n");
          fprintf( file, "GtkTreeIter    iter;\n");
          fprintf( file, "GtkListStore  *store = (GtkListStore *) liststore;\n\n");         
          if (widget->table == NULL) fprintf (file, "*/\n");
         
          row = g_list_first(widget->table);
          while (row != NULL) {
              fprintf( file, "\tgtk_list_store_append (store, &iter);\n");
              fprintf( file, "\tgtk_list_store_set (store, &iter,\n");             
              cols = (GList *) row->data;
              col = g_list_first(cols);
              while (col != NULL) {
                  coldata = (g2cColdata *) col->data;
                  column_value = make_column_value(widget, coldata->col_no, coldata->col_value);
                  if (strcmp(column_value,"pixbuf") != 0) {
                    fprintf( file, "\t\t%d,%s,\n", coldata->col_no, column_value); 
                  } else {
                      pixbufcol = coldata->col_no;
                      pixbuffile = coldata->col_value;
                  }
                  col = g_list_next(col);
              }
              fprintf( file, "\t\t-1);\n\n");
              if (pixbufcol >= 0) {
                  if (pixbuffirst == TRUE) {
                    fprintf( file, "GdkPixbuf *pixbuf1;\nGError *pixbuf1_error = NULL;\n");
                    pixbuffirst = FALSE;
                  }
                  fprintf( file, "\tpixbuf1 = gdk_pixbuf_new_from_file(\"%s\", &pixbuf1_error);\n", pixbuffile);
                  fprintf( file, "\tgtk_list_store_set (store, &iter, %d, pixbuf1, -1);\n\n", pixbufcol);                  
              }
              row = g_list_next(row);
          }          
          fprintf( file, "\treturn;\n");
          fprintf( file, "}\n\n");
    }  
    g_free( populater );
}

static void
output_widget_create( g2cWidget *widget,
                      FILE *file )
/*   Output the create string for the widget.  */
/*      plus connections to containers         */
/*      plus properties                        */
{
  gchar     *func_name        = NULL;
  gboolean   pack_create      = TRUE;
  gchar     *create_string    = NULL;
  GList     *children         = NULL;
  gchar     *pack_type        = NULL;
  gboolean  properties_only = FALSE;
  
  g2cProplist *proplist = NULL;
  gboolean    propmore = TRUE;
  gchar     *key;
  gchar     *value;
  g2cWidget *label_widget = NULL;

  g_assert( NULL != widget );
  g_assert( NULL != file );

  func_name = g2c_transform_name( widget->klass_name, NT_FUNCTION );

  /* Output the create string for the widget.
   * Some really strange constructors, namely ones with dependencies,
   * are in the else clauses. 
   * 
   * Also, for certain widgets the widget has been pre-created by the framework.
   * Examples are dialog action areas.  The constructors for
   * these functions are handled elsewhere.  In all cases, the properties_only 
   * flag will be set to TRUE, and the constructor logic will be bypassed.
   *        
   */

  /* In some cases, we don't want to make a create string.  Usually this is because
   * the widget is created indirectly, such as when a button is added to a toolbar
   */
#ifdef SOURCE_DEBUG
  //fprintf( file, "\tg_print(\"Handling %s\\n\");\n",
  //         widget->name );
#endif

  
        
//          /* Gtk Menu Item */
//          if( g_type_is_a( widget->klass, GTK_TYPE_MENU_ITEM ) &&
//              ( NULL == g2c_widget_get_property( widget, "label" ) ) )
//            {              
//                
//              /* Just create the item */
//              fprintf( file,
//                       "\tgui->%s = (%s*) gtk_menu_item_new ();\n",
//                       widget->name, widget->klass_name );
//                
//            }          
//          else
//            {
            /*              The standard create string is simply:                 */
            /*                 gui->widget_name = widget_type_new();              */
            /*  or one of the variations given in create_functions in g2c_widget.c */
  
            if (strcmp(widget->klass_name, "AtkObject") == 0)
            {
                properties_only = TRUE;
            }
      if (!properties_only) {
          
            
              create_string = g2c_widget_create_string( widget );

              if( NULL != create_string )
                {
                  fprintf( file, (char *)  create_string, NULL );
                  g_free( create_string );
                }              
//            }

          if( NULL != widget->parent )
            {
              if( g_type_is_a( widget->klass, GTK_TYPE_MENU ) )
                {
                  /* Handle a menu */
                  output_menu( widget, file );
                }
              else if( g_type_is_a( widget->klass, GTK_TYPE_MENU_ITEM ) )
                {
                  /* Handle the connection of a menu item to its parent */
                  output_menu_item( widget, file );

                }
              else if( g_type_is_a( widget->parent->klass, GTK_TYPE_BUTTON ) )
                {
                  if ( (strcmp( widget->parent->klass_name, "GtkScaleButton")  != 0) &&
                       (strcmp( widget->parent->klass_name, "GtkVolumeButton") != 0) ) {
                        if ((strcmp( widget->parent->klass_name, "GtkCheckButton"  ) != 0 ) &&
                            (strcmp( widget->parent->klass_name, "GtkToggleButton" ) != 0 ) ) {  
                              fprintf( file,
                                      "\tgtk_container_remove(GTK_CONTAINER(gui->%s),\n"
                                      "\t         gtk_bin_get_child(GTK_BIN(gui->%s)));\n",
                                      widget->parent->name,
                                      widget->parent->name);
                        }
                        fprintf( file,
                                "\tgtk_container_add(GTK_CONTAINER(gui->%s), GTK_WIDGET(gui->%s));\n",
                                widget->parent->name,
                                widget->name);
                  }
                }
              else if( g_type_is_a( widget->parent->klass, GTK_TYPE_TOOLBAR ) )
                {
                  /* This is a child widget of a GtkToolbar */
                  output_toolbar_widget( widget, file );
                }
              else if (( strcmp( widget->parent->klass_name, "GtkViewport"        ) == 0 ) ||
                       ( strcmp( widget->parent->klass_name, "GtkOffscreenWindow" ) == 0 ) ||
                       ( strcmp( widget->parent->klass_name, "GtkAssistant"       ) == 0 ) ||
                       ( strcmp( widget->parent->klass_name, "GtkRevealer"        ) == 0 ) ||                       
                       ( strcmp( widget->parent->klass_name, "GtkListBoxRow"      ) == 0 ) ||
                       ( strcmp( widget->parent->klass_name, "GtkMenuButton"      ) == 0 ) ||
                       ( strcmp( widget->parent->klass_name, "GtkSearchBar"       ) == 0 ) ||
                       ( strcmp( widget->parent->klass_name, "GtkAlignment"       ) == 0 ) ||
                       ( strcmp( widget->parent->klass_name, "GtkEventBox"        ) == 0 ) ) 
              {
                  fprintf( file,
                        "\tgtk_container_add(GTK_CONTAINER(gui->%s), GTK_WIDGET(gui->%s));\n",
                        widget->parent->name,
                        widget->name);
              }
              else if  ( strcmp( widget->parent->klass_name, "GtkActionBar") == 0 )  {
                 value = g2c_widget_get_property( widget,"_center");  /* Add center child set  */
                 if (value == NULL) {
                    fprintf( file,
                        "\tgtk_container_add(GTK_CONTAINER(gui->%s), GTK_WIDGET(gui->%s));\n",
                        widget->parent->name,
                        widget->name); 
                 } else {
                    fprintf( file,
                               "\tgtk_action_bar_set_center_widget(GTK_ACTION_BAR(gui->%s), GTK_WIDGET(gui->%s));\n",
                               widget->parent->name,
                               widget->name);  
                 }
              }
              else if ( strcmp( widget->parent->klass_name, "GtkPaned" ) == 0 )  {
                  /* This is one of the two child widgets of a GtkPaned */
                  output_paned_pack_child ( widget, file );
              }
              else if( g_type_is_a( widget->parent->klass, GTK_TYPE_FIXED ) )  {
                  fprintf( file,
                           "\tgtk_fixed_put (GTK_FIXED (gui->%s), GTK_WIDGET (gui->%s), %d, %d);\n",
                           widget->parent->name,
                           widget->name,
                           widget->packing.layout.x,
                           widget->packing.layout.y );
              }
              else if (( strcmp( widget->klass_name, "GtkTreeViewColumn" ) == 0 ) &&
                       ( strcmp( widget->parent->klass_name, "GtkTreeView" ) == 0 ))  {
                  fprintf( file,
                        "\tgtk_tree_view_append_column(GTK_TREE_VIEW(gui->%s),\n"
                        "\t                            GTK_TREE_VIEW_COLUMN(gui->%s));\n",
                        widget->parent->name,
                        widget->name);
                  value = g2c_widget_get_property(widget->parent, "expander_column");
                  if ((value != NULL) && (strcmp(widget->name,value) == 0) ) {
                     fprintf( file,
                        "\tgtk_tree_view_set_expander_column(GTK_TREE_VIEW(gui->%s),\n"
			"\t                                  GTK_TREE_VIEW_COLUMN(gui->%s));\n",
                        widget->parent->name,
                        widget->name);     
                  }
              }
              else if (( strcmp( widget->klass_name, "GtkListBoxRow" ) == 0 ) &&
                       ( strcmp( widget->parent->klass_name, "GtkListBox" ) == 0 ))  {
                  fprintf( file,
                        "\tgtk_list_box_insert(GTK_LIST_BOX(gui->%s), GTK_WIDGET(gui->%s), -1);\n",
                        widget->parent->name,
                        widget->name);
              }
              else if (( strcmp( widget->klass_name, "GtkToolItemGroup" ) == 0 ) &&
                       ( strcmp( widget->parent->klass_name, "GtkToolPalette" ) == 0 ))  {
                  fprintf( file,
                        "\tgtk_container_add(GTK_CONTAINER(gui->%s), GTK_WIDGET(gui->%s));\n",
                        widget->parent->name,
                        widget->name);
              }
              else if ( strcmp( widget->parent->klass_name, "GtkToolItemGroup" ) == 0 )  {
                  fprintf( file,
                        "\tgtk_tool_item_group_insert(GTK_TOOL_ITEM_GROUP(gui->%s), GTK_TOOL_ITEM(gui->%s), -1);\n",
                        widget->parent->name,
                        widget->name);
              }
              else if ( strcmp( widget->parent->klass_name, "GtkToolItem" ) == 0 )  {
                  fprintf( file,
                        "\tgtk_container_add(GTK_CONTAINER(gui->%s), GTK_WIDGET(gui->%s));\n",
                        widget->parent->name,
                        widget->name);
              }
              else if ( ( strcmp( widget->klass_name, "GtkEntry" ) == 0 )  &&                     
                        ( widget->parent->parent != NULL) && 
                        ( strcmp( widget->parent->parent->klass_name, "GtkSearchBar" ) == 0 ) )  {
                            fprintf( file,
                              "\tgtk_search_bar_connect_entry(GTK_SEARCH_BAR(gui->%s), GTK_ENTRY(gui->%s));\n",
                              widget->parent->parent->name,
                              widget->name);
                      
              }
              else if ( strcmp( widget->parent->klass_name, "GtkExpander" ) == 0 )   {
                  value = g2c_widget_get_property( widget, "_expand" );
                  if (value == NULL) {    
                    fprintf( file,
                          "\tgtk_container_add(GTK_CONTAINER(gui->%s),\n"
                          "\t                  GTK_WIDGET(gui->%s));\n",
                          widget->parent->name,
                          widget->name);
                  } else {  /*  <child type="label">  */
                     fprintf( file,
                                   "\tgtk_expander_set_label_widget(GTK_EXPANDER(gui->%s),\n"
                                   "\t                           GTK_WIDGET(gui->%s));\n",
                                    widget->parent->name,
                                    widget->name); 
                  }
              }
              else if( g_type_is_a( widget->parent->klass, GTK_TYPE_FRAME ) ) {
                  if ( strcmp( widget->klass_name, "GtkLabel" ) == 0  ) {
                      fprintf( file,
                                   "\tgtk_frame_set_label_widget(GTK_FRAME(gui->%s),\n"
                                   "\t                           GTK_WIDGET(gui->%s));\n",
                                    widget->parent->name,
                                    widget->name);
                              
                  } else {
                           fprintf( file,
                                       "\tgtk_container_add (GTK_CONTAINER (gui->%s),\n"
                                       "\t                   GTK_WIDGET (gui->%s));\n",
                                       widget->parent->name,
                                       widget->name);
                  }
              }
              else if ( strcmp( widget->parent->klass_name, "GtkOverlay" ) == 0 )  {
                  value = g2c_widget_get_property( widget, "_overlay" );
                  if (value == NULL) {
                    fprintf( file,
                           "\tgtk_container_add (GTK_CONTAINER (gui->%s),\n"
                           "\t                   GTK_WIDGET (gui->%s));\n",
                           widget->parent->name,
                           widget->name);                       
                  } else {   /*  <child type="overlay">  */
                     fprintf( file,
                           "\tgtk_overlay_add_overlay (GTK_OVERLAY (gui->%s),\n"
                           "\t                   GTK_WIDGET (gui->%s));\n",
                           widget->parent->name,
                           widget->name);
                  }
                  /*  needs to be placed after the show top level widget  */
//                  value = g2c_widget_get_property( widget, "_pass_through" );
//                  if (value != NULL) {
//                     fprintf( file,
//                             "\tgdk_window_set_pass_through( gtk_widget_get_window( GTK_WIDGET(gui->%s) ), TRUE);\n",
//                             widget->name );
//                  }
              }
              else if (( strcmp( widget->parent->klass_name, "GtkFlowBoxChild" ) == 0 ) && 
                       ( widget->parent->parent != NULL) &&  
                       ( strcmp( widget->parent->parent->klass_name, "GtkFlowBox" ) == 0 ) ) {
                     fprintf( file,
                        "\tgtk_flow_box_insert(GTK_FLOW_BOX(gui->%s), GTK_WIDGET(gui->%s), -1);\n",
                        widget->parent->parent->name,
                        widget->name);
              }
              else if ( ( strcmp( widget->klass_name, "GtkTextTag" ) == 0 ) &&
                        ( strcmp( widget->parent->klass_name, "GtkTextTagTable" ) == 0 ) ) {
                      fprintf( file,
                          "\tgtk_text_tag_table_add(GTK_TEXT_TAG_TABLE(gui->%s),\n"
                          "\t\t\tGTK_TEXT_TAG(gui->%s));\n",
                          widget->parent->name,
                          widget->name);
              }
              /* Pack the widget, if necessary */
             else if( !widget->klass || !widget->parent->klass ) {
                g_message( "%s:%d, %s:%d\n",
                         widget->klass_name,
                         (int) widget->klass,
                         widget->parent->klass_name,
                         (int) widget->parent->klass );
             }

              if( ( g_type_is_a( widget->parent->klass,  GTK_TYPE_CONTAINER ) ) &&
                  ( !g_type_is_a( widget->klass,         GTK_TYPE_MENU_ITEM ) ) &&
                  ( !g_type_is_a( widget->klass,         GTK_TYPE_MENU      ) ) &&
                  ( !g_type_is_a( widget->parent->klass, GTK_TYPE_TOOLBAR   ) ) &&
                  ( strcmp( widget->parent->klass_name, "GtkComboBox" ) != 0     ) )
                {
                  if( g_type_is_a( widget->parent->klass, GTK_TYPE_BOX ) ) {
                      pack_create = TRUE;
                      /*  Don't generate packing if the parent is a ButtonBox which is internal to a Dialog */
                     if  (( strcmp( widget->parent->klass_name, "GtkButtonBox" ) == 0  ) &&
                          ( widget->parent->internal == TRUE ) )  pack_create = FALSE;
                      /*  Don't generate packing if the enclosure is a ButtonBox which is internal to a Dialog */
                      if  (( strcmp( widget->klass_name, "GtkButtonBox" ) == 0  ) &&
                          ( widget->internal == TRUE ) )  pack_create = FALSE;
                      /*  Don't generate packing if the enclosure is a Box which is internal to a InfoBar */
                      if  (( strcmp( widget->klass_name, "GtkBox" ) == 0  ) &&
                          ( widget->internal == TRUE ) )  pack_create = FALSE;
                      /*  Don't generate packing if the child is centred within the box */
                      value = g2c_widget_get_property( widget,"_center");  /* Add center child set  */
                      if (value != NULL) pack_create = FALSE;
                      
                      if (pack_create == TRUE)
                      {
                      /* gtk_box_pack_end (GTK_BOX (the_parent), widget_name, expand, fill, padding); */
                      if (widget->packing.box.pack_type == PACK_START) 
                         pack_type = strdup("start");
                      else
                         pack_type = strdup("end");

                      fprintf( file,
                               "\tgtk_box_pack_%s (GTK_BOX (gui->%s), \n"
                               "\t                    GTK_WIDGET (gui->%s), %s, %s, %d);\n",
                               pack_type, 
                               widget->parent->name,
                               widget->name,
                               widget->packing.box.expand ? "TRUE" : "FALSE",
                               widget->packing.box.fill   ? "TRUE" : "FALSE",
                               widget->packing.box.padding );
                      g_free(pack_type);
                    }  /*  Alternatively, the widget is centred in the container  */
                    value = g2c_widget_get_property( widget,"_center");
                    if (value != NULL) {
                        if (( strcmp( widget->parent->klass_name, "GtkBox"       ) == 0  )  ||
                            ( strcmp( widget->parent->klass_name, "GtkButtonBox" ) == 0  ) )
                           {
                            /*  ignores GtkInfoBar - content and action-area cannot be centred */
                          fprintf( file,
                               "\tgtk_box_set_center_widget(GTK_BOX(gui->%s),\n"
                               "\t                          GTK_WIDGET(gui->%s));\n",
                               widget->parent->name,
                               widget->name);
                        }  
                    }
                    if ( strcmp( widget->parent->klass_name, "GtkButtonBox" ) == 0 ) {
                        if (widget->packing.box.secondary == TRUE) {
                            fprintf( file,
                               "\tgtk_button_box_set_child_secondary (GTK_BUTTON_BOX(gui->%s),\n" 
	                       "\t                                    GTK_WIDGET(gui->%s), TRUE);\n",
                               widget->parent->name,
                               widget->name);     
                        }
                         if (widget->packing.box.non_homogeneous == TRUE) {
                             fprintf( file,
                               "\tgtk_button_box_set_child_non_homogeneous (GTK_BUTTON_BOX(gui->%s), \n"
	                       "\t                                          GTK_WIDGET (gui->%s), TRUE);\n",
                               widget->parent->name,
                               widget->name);         
                         }
                    }
                  }
                  else if( g_type_is_a( widget->parent->klass, GTK_TYPE_LAYOUT ) )
                    {
                      fprintf( file,
                               "\tgtk_layout_put (GTK_LAYOUT (gui->%s), GTK_WIDGET (gui->%s), %d, %d);\n",
                               widget->parent->name,
                               widget->name,
                               widget->packing.layout.x,
                               widget->packing.layout.y );
                    }                  
                  else  if( g_type_is_a( widget->parent->klass, GTK_TYPE_GRID ) )
                    {
                      fprintf( file,
                               "\tgtk_grid_attach (GTK_GRID (gui->%s ), \n"
                               "\t                  GTK_WIDGET(gui->%s ),\n"
                               "\t                  %d, %d, %d, %d);\n",                               
                               widget->parent->name,
                               widget->name,
                               widget->packing.grid.left_attach,
                               widget->packing.grid.top_attach,
                               widget->packing.grid.width,
                               widget->packing.grid.height );
                      
                    }
                  else if( g_type_is_a( widget->parent->klass, GTK_TYPE_NOTEBOOK ) )
                    {
                      /* Labels are added in this statement, so don't add them again */
                      if( !g_type_is_a( widget->klass, GTK_TYPE_LABEL ) )  /* i.e. widget has to be a box */
                        {
                          value =  g2c_widget_get_property( widget, "_tab_label" );
                          if (value != NULL) {
                            fprintf( file,
                                     "\tgtk_notebook_append_page (GTK_NOTEBOOK (gui->%s),\n"
                                     "\t                          GTK_WIDGET (gui->%s),\n"
                                     "\t                          GTK_WIDGET (gui->%s));\n",
                                     widget->parent->name,   /* notebook */
                                     widget->name,           /*  box  */
                                     g2c_widget_get_property( widget, "_tab_label" ) );   /*  label  */                            
                              
                            label_widget = g2c_widget_find_by_name (widget->parent,value );
                          
                            notebook_packing ( label_widget, widget );
                            
                          }
                        }
                      // action widgets of GtkNotebook
                      if ( (widget->packing_type == LABEL_PACKING) && (widget->packing.box.pack_type != 0) ) {
                          if (widget->packing.box.pack_type == PACK_START) {
                             value = g_strdup("GTK_PACK_START");
                          } else if (widget->packing.box.pack_type == PACK_END) {
                             value = g_strdup("GTK_PACK_END"); 
                          } else {
                              g_message("Notebook action widget fails\n");
                          }
                          fprintf( file,
                                   "\tgtk_notebook_set_action_widget (GTK_NOTEBOOK (gui->%s),\n"
                                   "\t                                GTK_WIDGET (gui->%s),\n"
                                    "\t                                %s);\n",
                                     widget->parent->name,   /* notebook */
                                     widget->name,           /*  action widget  */
                                     value);                 /* start or end  */
                           g_free( value ); 
                           
                           notebook_packing ( widget, NULL );
                      }
                    }
                  else if( g_type_is_a( widget->parent->klass, GTK_TYPE_STACK ) )
                    {
                      if( !g_type_is_a( widget->klass, GTK_TYPE_LABEL ) )  /* i.e. widget has to be a box */
                        {
                          push_to_stack( widget, file );                      
                        }
                    }
//                  else if( g_type_is_a( widget->parent->klass, GTK_TYPE_ASPECT_FRAME ) )
//                    {
//                       fprintf( file,
//                                   "\tgtk_container_add (GTK_CONTAINER (gui->%s),\n"
//                                   "\t                   GTK_WIDGET (gui->%s));\n",
//                                   widget->parent->name,
//                                   widget->name);
//                    }
                  else if( g_type_is_a( widget->parent->klass, GTK_TYPE_ASSISTANT ) )
                  {
                     if ( ( g_type_is_a( widget->klass, GTK_TYPE_LABEL ) ) ||
                          ( g_type_is_a( widget->klass, GTK_TYPE_CONTAINER   ) ) ) {
                         fprintf( file,
                                   "\tgtk_assistant_append_page (GTK_ASSISTANT(gui->%s), GTK_WIDGET(gui->%s));\n",
                                   widget->parent->name,
                                   widget->name);
                         value = g2c_widget_get_property( widget, "_page_type" );
                         if (value != NULL) {
                            fprintf( file,
                                   "\tgtk_assistant_set_page_type (GTK_ASSISTANT(gui->%s), GTK_WIDGET(gui->%s), %s);\n",
                                   widget->parent->name,
                                   widget->name,
                                   g_strconcat("GTK_ASSISTANT_PAGE_", g_utf8_strup (value, strlen(value)), NULL) );
                         } else {
                            fprintf( file,
                                   "\tgtk_assistant_set_page_type (GTK_ASSISTANT(gui->%s), GTK_WIDGET(gui->%s), %s);\n",
                                   widget->parent->name,
                                   widget->name,
                                   "GTK_ASSISTANT_PAGE_CONTENT"); 
                         }
                         value = g2c_widget_get_property( widget, "_page_title" );
                         if (value != NULL) {
                           fprintf( file,
                                   "\tgtk_assistant_set_page_title (GTK_ASSISTANT(gui->%s), GTK_WIDGET(gui->%s),\" %s\");\n",
                                    widget->parent->name,
                                    widget->name,
                                    value);
                         }
                         value = g2c_widget_get_property( widget, "_page_complete" );
                         if (value != NULL) {
                           fprintf( file,
                                   "\tgtk_assistant_set_page_complete (GTK_ASSISTANT(gui->%s), GTK_WIDGET(gui->%s), %s);\n",
                                    widget->parent->name,
                                    widget->name,
                                    g2c_get_bool_s(value));
                         }
                     } 
                     
                  }  else if( g_type_is_a( widget->parent->klass, GTK_TYPE_HEADER_BAR ) )
                  {
                      if (widget->packing.box.pack_type == PACK_END) 
                         pack_type = strdup("end");
                      else
                         pack_type = strdup("start");

                      fprintf( file,
                               "\tgtk_header_bar_pack_%s (GTK_HEADER_BAR (gui->%s), \n"
                               "\t                    GTK_WIDGET (gui->%s));\n",
                               pack_type, 
                               widget->parent->name,
                               widget->name );
                      g_free(pack_type);
                  } 
                  
              }
              if ( widget->parent != NULL)  
                     if ((strcmp(widget->parent->klass_name, "GtkWindow") == 0) ||
                         (strcmp(widget->parent->klass_name, "GtkScrolledWindow") == 0) ||                             
                         (strcmp(widget->parent->klass_name, "GtkApplicationWindow") == 0) ||                             
                         (strcmp(widget->parent->klass_name, "GtkPopoverMenu") == 0)  ||                             
                         (strcmp(widget->parent->klass_name, "GtkPopover") == 0) )
                      {
                        if ( strcmp( widget->klass_name, "GtkHeaderBar" ) == 0 )  {
                           fprintf( file,
                                 "\tgtk_window_set_titlebar(GTK_WINDOW(gui->%s),\n"
                                 "\t                        GTK_WIDGET(gui->%s));\n",
                                 widget->parent->name,
                                 widget->name);
                        } else {         
                            fprintf( file,
                               "\tgtk_container_add (GTK_CONTAINER (gui->%s),\n"
                               "\t                   GTK_WIDGET (gui->%s));\n",
                               widget->parent->name,
                               widget->name );
                        }
                      }                           
            }
            
      }    
    

  /* Write out the properties */

  if (widget->internal == FALSE) {
      proplist = proplist_start(widget);
      propmore = proplist_readnext(&proplist, &key, &value);
      while (propmore == TRUE) {
          g2c_widget_create_arg_cb(key, value, widget);
          propmore = proplist_readnext(&proplist, &key, &value);      
      }
      proplist_end(proplist);
      /* output any css styles */
      
      if (widget->css_classes != NULL) {        
         output_style(widget);    
      }
  }
  if ((strcmp( widget->klass_name, "GtkComboBoxText" ) == 0 ) &&
          (widget->comboboxtext_items != NULL)) {
      output_combobox_items ( widget, file );
  }
  
  if ( ( (strcmp( widget->klass_name, "GtkFileFilter"   ) == 0 ) ||
         (strcmp( widget->klass_name, "GtkRecentFilter" ) == 0 )    ) &&
          (widget->patterns != NULL) ) {
      output_patterns ( widget, file );
  }
  
  if ( ( (strcmp( widget->klass_name, "GtkFileFilter"   ) == 0 ) ||
         (strcmp( widget->klass_name, "GtkRecentFilter" ) == 0 )    ) &&
          (widget->mime_types != NULL) ) {
      output_mime_types ( widget, file );
  }
  
  if ( ( (strcmp( widget->klass_name, "GtkLabel"   ) == 0 ) ||
         (strcmp( widget->klass_name, "GtkAccelLabel" ) == 0 )    ) &&
          (widget->attributes != NULL) ) {
      output_attributes ( widget, file );
  }
  
  if ((strcmp( widget->klass_name, "GtkSizeGroup" ) == 0 ) &&
          (widget->sizegroup != NULL)) {
      output_sizegroup ( widget, file );
  }
  
    /* This provides a way to get the owning class from this widget */
    
    if (widget->internal == FALSE) {
       fprintf( file,
             "\tg_object_set_data (G_OBJECT (gui->%s), \"owner\", owner);\n\n",
             widget->name );
    }
     
      /* Recursively handle the children of this widget */
//      children = g_list_first( widget->children );
//
//      while( ( NULL != children ) && ( recurse_levels > 0 ) )
//        {
//          /* Call this function recursively. */
//          output_widget_create( children->data, file );
//
//          children = g_list_next( children );
//        }

//      recurse_levels--;
      
    

  if( NULL != func_name ) g_free( func_name );
}

static void
output_temp_declarations( g2cWidget *widget, FILE *file )
{
  g_assert( NULL != widget );
  g_assert( NULL != file );
  
  if (widget->parent == NULL) {
    g2c_widget_create_temp_declaration_cb( (gpointer) widget, (gpointer) NULL);
  }

  g_list_foreach( (gpointer) widget->children,
                  (GFunc   ) g2c_widget_create_temp_declaration_cb,
                  (gpointer) NULL );
  
  g_list_foreach( (gpointer) widget->associates,
                  (GFunc   ) g2c_widget_create_temp_declaration_cb,
                  (gpointer) NULL );

  g_list_foreach( (gpointer) widget->children,
                  (GFunc)    output_temp_declarations,
                  (gpointer) file );
  
  g_list_foreach( (gpointer) widget->associates,
                  (GFunc)    output_temp_declarations,
                  (gpointer) file );
}

static void
output_accelerator_declarations( g2cWidget *widget, FILE *file )
{
  g_assert( NULL != widget );
  g_assert( NULL != file );

  g_list_foreach( (gpointer) widget->children,
                  (GFunc   ) g2c_widget_create_accel_declaration_cb,
                  (gpointer) NULL );

  /* These only appear in top-level widgets, so no recursion is necessary */
  g_list_foreach( (gpointer) widget->children,
                  (GFunc)    output_accelerator_declarations,
                  (gpointer) file );
}

static void
output_focus_accelerator_declarations( g2cWidget *widget, FILE *file )
{
  g_assert( NULL != widget );
  g_assert( NULL != file );

  g_list_foreach( widget->accelerators,
                  g2c_widget_create_focus_accel_declaration_cb,
                  widget );

  /* These only appear in top-level widgets, so no recursion is necessary */
}

static void
output_accelerators( g2cWidget *widget, FILE *file )
{
  g_assert( NULL != widget );
  g_assert( NULL != file );

  g_list_foreach( widget->accelerators,
                  g2c_widget_create_accel_cb,
                  widget );

  /* Recursively handle the children of this widget */
  g_list_foreach( (gpointer) widget->children,
                  (GFunc)    output_accelerators,
                  (gpointer) file );
}

static void
output_signal_handler( g2cDoc *doc, g2cWidget *widget, FILE *file )
{
GList *signaldata  = NULL;
GList *child       = NULL;

  g_assert( NULL != widget );
  g_assert( NULL != file );

  signaldata = g_list_first(widget->signals);
  while (signaldata != NULL) {
     g2c_widget_create_signal_handler_cb(doc, (g2cSignal *) signaldata->data, widget);
     signaldata = g_list_next(signaldata);
  }  
     
    /* Recursively handle the children of this widget */
  child = g_list_first(widget->children);
  while (child != NULL) {  
    output_signal_handler(doc, (g2cWidget *) child->data, file);
    child = g_list_next(child);
  }   
}

static void
output_signal_connect( g2cWidget *widget, FILE *file )
{
  g_assert( NULL != widget );
  g_assert( NULL != file );

  g_list_foreach( widget->signals,
                  g2c_widget_create_signal_connect_cb,
                  widget );

  /* Recursively handle the children of this widget */
  g_list_foreach( (gpointer) widget->children,
                  (GFunc)    output_signal_connect,
                  (gpointer) file );
}

static void
output_signal_prototype( g2cWidget *widget, FILE *file )
{    
  g_assert( NULL != widget );
  g_assert( NULL != file );
  

  g_list_foreach( widget->signals,
                  g2c_widget_create_signal_prototype_cb,
                  widget );

  /* Recursively handle the children of this widget */
  g_list_foreach( (gpointer) widget->children,
                  (GFunc)    output_signal_prototype,
                  (gpointer) file );
}

static void
output_widget_struct( g2cWidget *widget, FILE *file )
{
gchar * temp_name;
  g_assert( NULL != widget );
  g_assert( NULL != file );

  widget->name = g_strdelimit( widget->name, ":-", '_' );
  fprintf( CURRENT_FILE,
           "\t%-20s *%s;\n",
           widget->klass_name,
           widget->name );

  if( g_type_is_a( widget->klass, GTK_TYPE_MENU ) )
    {
      /* Create an accelerator group */
      fprintf( CURRENT_FILE,
               "\t%-20s *%s_accel_group;\n",
               "GtkAccelGroup",
               widget->name );
    }
  
  /*  For buttons with images from stock declare the image objects */  
  if ( (strcmp(widget->klass_name, "GtkButton") == 0)  ||
       (strcmp(widget->klass_name, "GtkToggleButton") == 0)  ||
       (strcmp(widget->klass_name, "GtkFontButton") == 0)  ||
       (strcmp(widget->klass_name, "GtkColorButton") == 0)  ||
       (strcmp(widget->klass_name, "GtkLinkButton") == 0)  ||
       (strcmp(widget->klass_name, "GtkLockButton") == 0)  ||
       (strcmp(widget->klass_name, "GtkModelButton") == 0)  ||
       (strcmp(widget->klass_name, "GtkScaleButton") == 0)  ||
       (strcmp(widget->klass_name, "GtkCheckButton") == 0)  ||
       (strcmp(widget->klass_name, "GtkRadioButton") == 0) ) { 
      
      temp_name = g2c_widget_get_property( widget, "use_stock" );
      if (temp_name != NULL) {
          fprintf( file,"\t%-20s *%simage;\n", "GtkWidget", widget->name);
          
      }
  } 
  if ( (strcmp(widget->klass_name, "GtkToolButton") == 0) ||
       (strcmp(widget->klass_name, "GtkMenuToolButton") == 0) ||
       (strcmp(widget->klass_name, "GtkToggleToolButton") == 0) ) {  
      temp_name = g2c_widget_get_property( widget, "stock_id" );
      if (temp_name != NULL) {
          fprintf( file,"\t%-20s *%simage;\n", "GtkWidget", widget->name);
          
      }
  }  
  /* for menu items with images from stock */
  if (strcmp(widget->klass_name, "GtkImageMenuItem") == 0) {  
      temp_name = g2c_widget_get_property( widget, "use_stock" );
      if (temp_name != NULL) {
          fprintf( file,"\t%-20s *%sbox;\n", "GtkBox", widget->name);
          fprintf( file,"\t%-20s *%simage;\n", "GtkWidget", widget->name);
          fprintf( file,"\t%-20s *%slabel;\n", "GtkLabel", widget->name);
          fprintf( file,"\t%-20s *%saccelgroup;\n", "GtkAccelGroup", widget->name);
      }
  }  
  
  if ((strcmp(widget->klass_name, "GtkRadioMenuItem") == 0) &&
          (g2c_widget_get_property( widget, "group" ) == NULL))
  {  
      fprintf( file,"\t%-20s *%sgroup;\n", "GSList", widget->name);
  }

  /* Recursively handle the children of this widget */
  g_list_foreach( (gpointer) widget->children,
                  (GFunc)    output_widget_struct,
                  (gpointer) file );
}

static void
output_toolbar_widget( g2cWidget *widget, FILE* file )
{
  gchar *widget_type   = NULL;
  gchar *pixmap_widget = NULL;

  g_assert( NULL != widget );
  g_assert( NULL != file );

 
  /* How shall the pixmap be created? */
  if( NULL != g2c_widget_get_property( widget, "icon" ) )
    {     
        
     pixmap_widget = g_strdup_printf( "create_pixmap (GTK_WIDGET (gui->%s), \"%s/%s\")",
                                           widget->name,
                                           CURRENT_PROJECT->pixmaps_directory,
                                           g2c_widget_get_property( widget, "icon" ) );
        
    }

  /* If this widget starts a new group, then add a spacer */
  if( NULL != g2c_widget_get_property( widget, "new_group" ) )
    {
      /* Output a spacer */
      fprintf( file,
               "\tgtk_toolbar_append_space (GTK_TOOLBAR (gui->%s));\n",
               widget->parent->name );
    }

  
   
      fprintf( file,
               "\tgtk_toolbar_insert (GTK_TOOLBAR (gui->%s),\n"
               "\t                    GTK_TOOL_ITEM (gui->%s), -1);\n",              
               widget->parent->name,
               widget->name );
   
      fprintf( file,
               "\tgtk_tool_item_set_homogeneous (GTK_TOOL_ITEM (gui->%s), %s);\n",
               widget->name, 
               widget->packing.box.homogeneous ? "TRUE" : "FALSE"  ); 
      fprintf( file,
               "\tgtk_tool_item_set_expand (GTK_TOOL_ITEM (gui->%s), %s);\n",
               widget->name, 
               widget->packing.box.expand ? "TRUE" : "FALSE"  );
      
  if( NULL != widget_type   ) g_free( widget_type );
  if( NULL != pixmap_widget ) g_free( pixmap_widget );
}

static void
output_combobox_items ( g2cWidget *widget, FILE* file )
{
GList       *run  = NULL;
g2cItemData *data = NULL;
 
      run = g_list_first( widget->comboboxtext_items );
      while ( run != NULL) {
          data = (g2cItemData *) run->data;
          fprintf( file,
               "\tgtk_combo_box_text_insert (GTK_COMBO_BOX_TEXT (gui->%s),"
                   "-1, \"%d\", \"%s\");\n",
                  widget->name, data->id, data->text);
          run = g_list_next( run );
      }
    
}

static void
output_patterns ( g2cWidget *widget, FILE* file )
{
GList  *run  = NULL;
gchar  *data = NULL;
gchar  *func_name = g2c_transform_name(widget->klass_name, NT_FUNCTION);
gchar  *type_name = g_utf8_strup(func_name, strlen(func_name));
 
      run = g_list_first( widget->patterns );
      while ( run != NULL) {
          data = (gchar *) run->data;
          fprintf( file,
               "\t%s_add_pattern (%s(gui->%s), \"%s\");\n",                    
                  func_name, type_name, widget->name, data);
          run = g_list_next( run );
      }
      g_free( func_name );
      g_free( type_name );
}

void 
output_mime_types ( g2cWidget *widget, FILE* file )
{
GList *run = NULL; 
gchar *mime_type = NULL;
gchar  *func_name = g2c_transform_name(widget->klass_name, NT_FUNCTION);
gchar  *type_name = g_utf8_strup(func_name, strlen(func_name));
    g_assert( NULL != widget );
    
    run = g_list_first( widget->mime_types );
    while ( NULL != run )   {
         mime_type = (gchar *) run->data;
         fprintf( file,
             "\t%s_add_mime_type (%s (gui->%s), \"%s\");\n",
                 func_name, type_name, widget->name, mime_type);
         run = g_list_next( run );
    }
    
}

void 
output_attributes ( g2cWidget *widget, FILE* file )
{
GList *run = NULL; 
g2cAttribute *attribute = NULL;
    run = g_list_first( widget->attributes );
    while ( NULL != run )   {
        attribute = (g2cAttribute*) run->data;
        output_pango_attribute (widget, attribute->key, attribute->value, file );       
        run = g_list_next( run );
    }
    fprintf( file,
                 "\tgtk_label_set_attributes(GTK_LABEL(gui->%s), %s_attrlist);\n",
            widget->name, widget->name);
    fprintf( file,
                 "\tpango_attr_list_unref(%s_attrlist);\n", widget->name);	
}

void 
output_sizegroup( g2cWidget *widget, FILE* file )
{
GList *run = NULL; 
gchar *member = NULL;

    g_assert( NULL != widget );
    
    run = g_list_first( widget->sizegroup );
    while ( NULL != run )   {
         member = (gchar *) run->data;
         fprintf( file,
             "\tgtk_size_group_add_widget (GTK_SIZE_GROUP (gui->%s), GTK_WIDGET(gui->%s));\n",
                 widget->name, member);
         run = g_list_next( run );
    }    
}

void
output_pango_attribute( g2cWidget *widget, gchar* name, gchar* value, FILE* file )
{
GString *colour = NULL; 
GString *red  = NULL;
GString *green = NULL;
GString *blue = NULL;

    fprintf( file,
                 "\tpango_attr_list_insert(%s_attrlist,\n", 
                widget->name);
            
    if (strcmp(name, "font_desc") ==  0) {
        fprintf( file,
                 "\t\tpango_attr_font_desc_new( pango_font_description_from_string (\"%s\") ) );\n",
                 value);
    } else if (strcmp(name, "style") ==  0) {
        fprintf( file,
                 "\t\tpango_attr_style_new ( %s ));\n",
                   make_enumeral("PANGO_STYLE", value));
    } else if (strcmp(name, "weight") ==  0) {
        fprintf( file,
                 "\t\tpango_attr_weight_new ( %s ));\n",
                  make_enumeral("PANGO_WEIGHT", value));
    } else if (strcmp(name, "variant") ==  0) {
        fprintf( file,
                 "\t\tpango_attr_variant_new ( %s ));\n",
                 make_enumeral("PANGO_VARIANT", value));
    } else if (strcmp(name, "stretch") ==  0) {
        fprintf( file,
                 "\t\tpango_attr_stretch_new ( %s ));\n",
                 make_enumeral("PANGO_STRETCH", value));
    } else if (strcmp(name, "gravity") ==  0) {
        fprintf( file,
                 "\t\tpango_attr_gravity_new ( %s ));\n",
                 make_enumeral("PANGO_GRAVITY", value));
    } else if (strcmp(name, "gravity_hint") ==  0) {
        fprintf( file,
                 "\t\tpango_attr_gravity_hint_new ( %s ));\n",
                 make_enumeral("PANGO_GRAVITY_HINT", value));
    } else if ( (strcmp(name, "foreground") ==  0) ||
                (strcmp(name, "background") ==  0) ||
                (strcmp(name, "underline_color") ==  0) ||
                (strcmp(name, "strikethrough_color") ==  0) )   {
        colour = g_string_new(value);
        g_string_erase(colour, 0, 1);  /*  #fcfce9e94f4f => fcfce9e94f4f  */
        red = g_string_new (colour->str);
        g_string_truncate(red, 4);
        green = g_string_new (colour->str);
        g_string_truncate(green, 8);
        g_string_erase(green, 0, 4);
        blue = g_string_new (colour->str);
        g_string_erase(blue, 0, 8);
        fprintf( file,
                 "\t\tpango_attr_%s_new ( 0x%s, 0x%s, 0x%s ));\n",
                  name, red->str, green->str, blue->str );
        g_string_free(colour, TRUE);
        g_string_free(red, TRUE);
        g_string_free(green, TRUE);
        g_string_free(blue, TRUE);
    } else if (strcmp(name, "scale") ==  0) {
        fprintf( file,
                 "\t\tpango_attr_scale_new ( %s ));\n",
                  value);
    } else if (strcmp(name, "size") ==  0) {
        fprintf( file,
                 "\t\tpango_attr_size_new ( %s * PANGO_SCALE ));\n",
                 value);
    } else if (strcmp(name, "absolute_size") ==  0) {
        fprintf( file,
                 "\t\tpango_attr_size_new_absolute( %s * PANGO_SCALE ));\n",
                 value);
    } else if (strcmp(name, "underline") ==  0) {
        fprintf( file,
                 "\t\tpango_attr_underline_new ( PANGO_UNDERLINE_SINGLE ));\n"
                  );
    } else if (strcmp(name, "strikethrough") ==  0) {
        fprintf( file,
                 "\t\tpango_attr_strikethrough_new( TRUE ));\n"
                 );
    } else return;

}

static void
output_menu( g2cWidget *widget, FILE* file )
{
  if( g_type_is_a( widget->parent->klass, GTK_TYPE_MENU_ITEM ) )
    {
      fprintf( file,
               "\tgtk_menu_item_set_submenu (GTK_MENU_ITEM (gui->%s), GTK_WIDGET (gui->%s));\n",
               widget->parent->name,
               widget->name );
    }
}

static void
output_menu_item( g2cWidget *widget, FILE* file )
{
  
  if( strcmp( widget->parent->klass_name, "GtkMenuBar" ) == 0 )
    {
      /* Append to the menubar */
      fprintf( file,
               "\tgtk_menu_shell_append (GTK_MENU_SHELL (gui->%s), GTK_WIDGET (gui->%s));\n",
               widget->parent->name,
               widget->name );
    }
  else if( g_type_is_a( widget->parent->klass, GTK_TYPE_MENU ) )
    {
      fprintf( file,
               "\tgtk_menu_shell_append (GTK_MENU_SHELL (gui->%s), GTK_WIDGET (gui->%s));\n",
               widget->parent->name,
               widget->name );

      if( NULL == g2c_widget_get_property( widget, "label" )  )
        {
          fprintf( file,
                   "\tgtk_widget_set_sensitive (GTK_WIDGET (gui->%s), TRUE);\n",
                   widget->name );
        }
    }
  else
    {
      g_message( "Shouldn't be here! %s %s %d\n",
               widget->name,
               widget->parent->klass_name,
               (int) widget->parent->klass );

      g_assert_not_reached();
    }
}

static void       
output_paned_pack_child ( g2cWidget *widget, FILE* file )
{
GList *run = NULL; 
gchar *resize = NULL;
gchar *shrink = NULL;
gchar *child_pack = NULL;
g2cWidget *child = NULL;

     resize = g2c_widget_get_property( widget, "_resize" );
     if (resize == NULL) 
         resize = g_strdup("FALSE");
     shrink = g2c_widget_get_property( widget, "_shrink" );
     if (shrink == NULL) 
         shrink = g_strdup("FALSE");
     run = g_list_first( widget->parent->children );
     if (run != NULL) {
         child = (g2cWidget *) run->data;
         if (strcmp(child->name, widget->name) == 0) {
             child_pack = g_strdup("pack1");
         } else {
             child_pack = g_strdup("pack2");
         }
         fprintf( file,
                   "\tgtk_paned_%s (GTK_PANED (gui->%s), GTK_WIDGET(gui->%s), %s, %s);\n",
                   child_pack, 
                   widget->parent->name,
                   widget->name,
                   g2c_get_bool_s ( (const gchar *) resize),
                   g2c_get_bool_s ( (const gchar *) shrink) );
     }
    
}

static void
handle_file_compare( gchar *temp_file_name, gchar *file_name )
{
  /* Run ctags on the file in question, then take each line
   * in the returned tags file and put it the function
   * list of the parser 
   */
  FILE   *file     = NULL;
  gchar  *cmd      = NULL;
  gchar  *cmd_res  = g_malloc0( 1024 );

  /* Create the command */
  cmd = g_strdup_printf( "diff --ignore-all-space --ignore-blank-lines --brief %s %s",
                         temp_file_name,
                         file_name );
  file = popen( cmd, "r" );
  g_free( cmd );
  cmd = NULL;

  /* If there was any resulting text, then the files were different */
  fgets( cmd_res, 1024, file );
  cmd_res = g_strchomp( cmd_res );

  if( strlen( cmd_res ) > 0 )
    {
      /* Copy the temp file to the old file */
      g_message( "Writing %s\n", file_name );
      cmd = g_strdup_printf( "mv -f %s %s",
                             temp_file_name,
                             file_name );
      system( cmd );
    }

  pclose( file );
  if( NULL != cmd )     g_free( cmd );
  if( NULL != cmd_res ) g_free( cmd_res );
}

void
output_window_call(g2cWidget *widget,  FILE *file)
{
fprintf( file,
           "  %s->gui = %s_gui_create ((gpointer) %s);\n",
           widget->name,
           widget->name,
           widget->name );
  fprintf( file,
           "  if (%s->gui == NULL) return 0;\n",
           widget->name );    
}

void
output_dialog_widget_call(g2cWidget *dialogue_widget, gchar *main, FILE *file)
{
      fprintf( file, "  %s->%sgui = %s_gui_create ((gpointer) %s);\n", 
              main,
              dialogue_widget->name,
              dialogue_widget->name,
              main );
      fprintf( file,
           "  if (%s->%sgui == NULL) return 0;\n",
           main, dialogue_widget->name );    
}

void
output_main_file ( g2cDoc *doc, gchar *file_name, GList *topreglist )
{
  FILE   *file       = NULL;
  g2cWidget *widget = NULL;  
  g2cWidget *dialogue_widget = NULL;
  g2cRequires *req;
  g2cTopRegister *reg = NULL;
  GList *run        = NULL;
  gchar *type_name  = NULL;
  guint max_level = 0;
  guint level = 0;
    
  
  widget = doc->project->main_widget;
  if (widget == NULL) return;
  type_name = g2c_transform_name( widget->name, NT_TYPENAME );
  
  /*  Output the main program file project_main.c
   *    
   * #include <gtk/gtk.h>
   *
   * #include "widget.h"
   * #include "widget_gui.h"
   * 
   * int
   * main (int argc, char *argv[])
   * {
   * WidgetName *widgetname = NULL;
   * 
   *   gtk_init (&argc, &argv);
   * 
   *   widgetname = g_new0 (WidgetName, 1);
   *   widgetname->gui = widgetname_gui_create ((gpointer) widgetname)
   *   [repeat for each GtkDialog]
   * 
   *   gtk_main ();
   *   return 0;
   * }
   * 
   * void widgetname_terminate (WidgetName *widgetname)
   * {
   * 	widgetname_gui_destroy (widgetname->gui);
   *   [repeat for each GtkDialog]
   * 	g_free (widgetname);
   * 	gtk_main_quit();
   * }
   */
  
  g_message( "Creating %s\n", file_name );
  file = fopen (file_name, "w");
  if (file == NULL) {
      g_error("Could not open file %s\n", file_name);
      return;
  }
  fprintf (file, "/*                Generated from %s                 */\n\n", doc->project->source_file);	
  fprintf (file, "#include <gtk/gtk.h>\n");	    
  fprintf (file, "#include \"%s.h\"\n", widget->name);
  fprintf( file, "#include \"%s_gui.h\"\n", widget->name );

  fprintf( file, "\n" );
  fprintf (file, "int\n");
  fprintf (file, "main (int argc, char *argv[])\n");
  fprintf (file, "{\n");
  fprintf (file, "%s *%s = NULL;\n\n", type_name, widget->name);

  fprintf (file, "#ifdef ENABLE_NLS\n");
  fprintf (file, "  bindtextdomain (PACKAGE, PACKAGE_LOCALE_DIR);\n");
  fprintf (file, "  textdomain (PACKAGE);\n");
  fprintf (file, "#endif\n");
  fprintf (file, "\n");      	
  fprintf (file, "  gtk_init (&argc, &argv);\n\n");
  	
  fprintf( file, "  %s = g_new0 (%s, 1);\n", widget->name, type_name );
  
  // for members of topreglist in order of level
  
  max_level = get_max_top_register_level(topreglist);
  
  for (level = 0; level <= max_level; level++) {
    run = g_list_first(topreglist);
    while (run != NULL) {
        reg = (g2cTopRegister *) run->data; 
        if (reg->level == level) {
            dialogue_widget = reg->widget;             
            if (reg->bmain == TRUE) {
               output_window_call(dialogue_widget, file);
            } else {                
               output_dialog_widget_call(dialogue_widget, widget->name, file);                   
            }
        }
        run = g_list_next(run);
    } 
  }
  
  fprintf (file, "\n" );
  fprintf (file, "  gtk_main ();\n");
  fprintf (file, "  return 0;\n");
  fprintf (file, "}\n\n");
  
  fprintf( file, "void %s_terminate (%s *%s)\n", widget->name, type_name, widget->name );
  fprintf( file, "{\n" );  
  run = g_list_first(doc->project->dialogue_widgets);
  while (run != NULL) {
      dialogue_widget = (g2cWidget *) run->data; 
      fprintf( file, "  %s_gui_destroy (%s->%sgui);\n",               
              dialogue_widget->name,
              widget->name,
              dialogue_widget->name );
      run = g_list_next(run);
  }
  fprintf( file, "  %s_gui_destroy (%s->gui);\n",
           widget->name, widget->name );
  fprintf( file, "  g_free (%s);\n", widget->name );
  fprintf( file, "  gtk_main_quit();\n");
  fprintf( file, "}\n" );

  fclose (file);
  g_free( type_name);
    
  
  return;
}   /*  output_main_file  */

static void  output_style( g2cWidget *widget)
{
GList *css_class = NULL;
        fprintf( CURRENT_FILE,
               "\tgtk_css_provider_load_from_data (%s_provider, ",
                widget->name);
        css_class =  g_list_first(widget->css_classes);
        while (css_class != NULL) {            
            fprintf( CURRENT_FILE, "\n\t\t\t\"%s\"", (gchar *) css_class->data);
            css_class = css_class->next;
        }
            fprintf( CURRENT_FILE, ",\n\t\t\t -1, NULL);\n");
        fprintf( CURRENT_FILE,
                "\tgtk_style_context_add_provider (gtk_widget_get_style_context (GTK_WIDGET(gui->%s)),\n",
                widget->name);
        fprintf( CURRENT_FILE,
                "\t\tGTK_STYLE_PROVIDER (%s_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);\n",
                widget->name);                 
    
}

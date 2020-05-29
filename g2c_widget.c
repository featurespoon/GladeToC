#include <string.h>
#include <stdio.h>
#include "g2c_widget.h"
#include "g2c_doc.h"
#include "g2c_signal.h"
#include "g2c_helpers.h"
#include "g2c_signals.h"


typedef struct _GtkSignalQuery
{
  GType	   object_type;
  guint		   signal_id;
  const gchar	  *signal_name;
  guint		   is_user_signal : 1;
  //GtkSignalRunType signal_flags;
  GType	   return_val;
  guint		   nparams;
  const GType	  *params;
} GtkSignalQuery;

/* This list contains a signal handler names that have already been added */
static GList *signal_list = NULL;

/* Special handler prototypes */
void about_authors ( g2cWidget *widget );
void about_artists ( g2cWidget *widget );
void about_documenters ( g2cWidget *widget );
void about_license_type ( g2cWidget *widget );
void attach_action ( g2cWidget *widget );
void background_rgb ( g2cWidget *widget );
void baseline_position ( g2cWidget *widget );
void bin_label_handler( g2cWidget *widget );
void button_label( g2cWidget *widget );
void button_relief ( g2cWidget *widget );
void button_use_stock( g2cWidget *widget );
void calendar_set_display_options( g2cWidget *widget );
void cell_background_rgb ( g2cWidget *widget );
void colour_chooser_rgba ( g2cWidget *widget );
void common_tooltip_markup ( g2cWidget *widget );
void common_events ( g2cWidget *widget );
void dialog_transient( g2cWidget *widget );
void dialog_type_hint ( g2cWidget *widget );
void entry_markup ( g2cWidget *widget );
void entry_markup2 ( g2cWidget *widget );
void entry_primary_pixbuf ( g2cWidget *widget );
void entry_secondary_pixbuf ( g2cWidget *widget );
void file_chooser_filter( g2cWidget *widget );
void flowbox_selection_mode( g2cWidget *widget );
void font_size_points ( g2cWidget *widget );
void font_size_scale ( g2cWidget *widget );
void foreground_rgb ( g2cWidget *widget );
void frame_label_xalign ( g2cWidget *widget );
void frame_label_yalign ( g2cWidget *widget );
void grab_default ( g2cWidget *widget );
void icon_size ( g2cWidget *widget );
void iconview_selection_mode ( g2cWidget *widget );
void image_from_stock( g2cWidget *widget );
void input_hints( g2cWidget *widget );
void input_purpose( g2cWidget *widget );
void infobar_message_type( g2cWidget *widget );
//void label_label_handler( g2cWidget *widget );    
void label_label_justify( g2cWidget *widget );
void label_label_align( g2cWidget *widget );
void label_label_ellipsize ( g2cWidget *widget );
void label_label_wrap ( g2cWidget *widget );
void label_use_markup( g2cWidget *widget ); 
void label_ellipsize ( g2cWidget *widget );
void layout_height ( g2cWidget *widget );
void layout_width ( g2cWidget *widget );
void listbox_selection_mode ( g2cWidget *widget );
void menu_anchor_hint( g2cWidget *widget );
void menu_bar_direction( g2cWidget *widget );
void menu_item_use_stock ( g2cWidget *widget );
void menu_label( g2cWidget *widget );
void menu_item_label( g2cWidget *widget );
void menu_type_hint( g2cWidget *widget );
void menu_button_popup( g2cWidget *widget );
void message_dialog_secondary_text ( g2cWidget *widget );
void notebook_packing( g2cWidget *widget, g2cWidget *box_widget );
void pack_renderer( g2cWidget *widget );
void pack_combo_box_column( g2cWidget *widget );
void paragraph_background_rgb( g2cWidget *widget );
void popover_submenu( g2cWidget *widget );
void range_lower_sensitivity( g2cWidget *widget );
void range_upper_sensitivity( g2cWidget *widget );
void recent_chooser_sort_type( g2cWidget *widget );
void recent_manager_filename( g2cWidget *widget );
void scale_value_pos( g2cWidget *widget );
void scale_button_icons ( g2cWidget *widget ); 
void scrolled_window_placement ( g2cWidget *widget );
void set_gtk_button_box_style( g2cWidget *widget );
void set_popover_position ( g2cWidget *widget );
void set_menu_button_direction ( g2cWidget *widget );
void shadow_type( g2cWidget *widget );
void stack_transition( g2cWidget *widget );
void strikethrough_rgb( g2cWidget *widget );
void text_tag_justification( g2cWidget *widget );
void text_buffer_text ( g2cWidget *widget );
void text_tag_direction( g2cWidget *widget );
void text_view_wrap( g2cWidget *widget );
void toolbar_style ( g2cWidget *widget );
void transition_type ( g2cWidget *widget );
void tree_selection_mode( g2cWidget *widget );
void tree_grid_lines ( g2cWidget *widget ); 
void underline_rgb( g2cWidget *widget );
void view_column_alignment ( g2cWidget *widget );
void volume_button_adjustment ( g2cWidget *widget ); 
void volume_button_size ( g2cWidget *widget ); 
void window_icon ( g2cWidget *widget );

/* Creation handler prototypes */
void create_custom_widget( g2cWidget *widget );
void create_gtk_alignment( g2cWidget *widget );
void create_gtk_app_chooser_dialog ( g2cWidget *widget );
void create_gtk_aspect_frame( g2cWidget *widget );
void create_gtk_box( g2cWidget *widget );
void create_gtk_button( g2cWidget *widget );
void create_gtk_cellrenderertoggle( g2cWidget *widget );
void create_gtk_combobox( g2cWidget *widget );
void create_gtk_entry( g2cWidget *widget );
void create_gtk_file_chooser ( g2cWidget *widget );
void create_gtk_file_chooser_button ( g2cWidget *widget );
void create_gtk_frame( g2cWidget *widget );
void create_gtk_iconview( g2cWidget *widget );
void create_gtk_image( g2cWidget *widget );
void create_gtk_label( g2cWidget *widget );
void create_gtk_link_button( g2cWidget *widget );
void create_gtk_liststore( g2cWidget *widget );
void create_gtk_lockbutton( g2cWidget *widget );
void create_gtk_message_dialog ( g2cWidget *widget  );
void create_gtk_model_button( g2cWidget *widget );
void create_gtk_paned ( g2cWidget *widget );
void create_gtk_popover( g2cWidget *widget );
void create_gtk_popovermenu( g2cWidget *widget );
void create_gtk_radio_button( g2cWidget *widget );
void create_gtk_radio_menu_item( g2cWidget *widget );
void create_gtk_radio_tool_button ( g2cWidget *widget );
void create_gtk_recent_chooser_dialog ( g2cWidget *widget );
void create_gtk_scale( g2cWidget *widget );
void create_gtk_scale_button( g2cWidget *widget );
void create_gtk_scrollbar( g2cWidget *widget );
void create_gtk_scrolled_window( g2cWidget *widget );
void create_gtk_separator ( g2cWidget *widget );
void create_gtk_sizegroup ( g2cWidget *widget );
void create_gtk_spin_button( g2cWidget *widget );
void create_gtk_text_buffer( g2cWidget *widget );
void create_gtk_tree_selection( g2cWidget *widget );
void create_gtk_treemodel_filter( g2cWidget *widget );
void create_gtk_treemodel_sort( g2cWidget *widget );
void create_gtk_treeview( g2cWidget *widget );
void create_gtk_window( g2cWidget *widget );

/* Other functions */
guint position_after_last_brace( FILE *file );

/* Table of create functions */
static g2cCreateFunction create_functions[] =
  {
    { "Custom", NULL,
      { NULL },
      create_custom_widget },

    { "GtkAccelLabel", NULL,
      {  NULL },
      create_gtk_label },
      
    { "GtkAdjustment", "gtk_adjustment_new(0.0, 0.0, 0.0, 0.0, 0.0, 0.0)",
      { NULL },
        NULL},

    { "GtkAlignment", NULL,
      { NULL },
      create_gtk_alignment },
      
    { "GtkAppChooserDialog", NULL,
      { NULL },
      create_gtk_app_chooser_dialog }, 
      
    { "GtkAppChooserButton", "gtk_app_chooser_button_new (%s)",
      { "content_type", NULL },
      NULL },

    { "GtkAspectFrame", NULL,
      { NULL },
      create_gtk_aspect_frame },

    { "GtkButton", NULL,
      { NULL },
      create_gtk_button },
      
    { "GtkCheckButton", "gtk_check_button_new_with_label (%s)",
      { "label", NULL },
      NULL },

    { "GtkCheckMenuItem", "gtk_check_menu_item_new_with_label (%s)",
      { "label", NULL },
      NULL },
      
    { "GtkImageMenuItem", NULL,
      { NULL },
      menu_label },

    { "GtkColorChooserDialog", "gtk_color_chooser_dialog_new (NULL, NULL)",
      { NULL },
      NULL },

    { "GtkDial", "gtk_dial_new (GTK_ADJUSTMENT (gtk_adjustment_new (%s, %s, %s, %s, %s, %s)))",
      { "value", "lower", "upper", "step", "page", "page_size", NULL },
      NULL },

    { "GtkEntry", NULL,
      { NULL },
      create_gtk_entry },

    { "GtkEntryBuffer", "gtk_entry_buffer_new (NULL, -1)",
      { NULL },
      NULL },
      
    { "GtkEntryCompletion", "gtk_entry_completion_new ()",
      { NULL },
      NULL },  
      
    { "GtkFileChooserDialog", NULL,
      { NULL },
      create_gtk_file_chooser },
      
    { "GtkFileChooserWidget", NULL,
      { NULL },
      create_gtk_file_chooser },  
      
    { "GtkFileChooserButton", NULL,
      { NULL },
      create_gtk_file_chooser_button },

    { "GtkFontChooserDialog", "gtk_font_chooser_dialog_new (NULL, NULL)",
      { NULL },
      NULL },
      
    { "GtkFrame", NULL,
      { NULL },
      create_gtk_frame },

    { "GtkBox", NULL,
      {  NULL },
      create_gtk_box },

    { "GtkButtonBox", NULL,
      { NULL },
      create_gtk_box }, 
      
    { "GtkCellRendererToggle", NULL,
      { NULL },
      create_gtk_cellrenderertoggle },   
      
    { "GtkComboBox", NULL,
      { NULL },
      create_gtk_combobox }, 
      
    { "GtkComboBoxText", NULL,
      { NULL },
      create_gtk_combobox }, 

    { "GtkIconView", NULL,
      { NULL },
      create_gtk_iconview },
      
    { "GtkImage", NULL,
      {  NULL },
      create_gtk_image },

    { "GtkLabel", NULL,
      { NULL },       
      create_gtk_label },
	  
    { "GtkLayout", "gtk_layout_new (NULL,NULL)",
      { NULL },
      NULL },
      
    { "GtkLinkButton", NULL,
      {  NULL },
      create_gtk_link_button },
      
    { "GtkListStore", NULL,
      { NULL },
      create_gtk_liststore },
      
    { "GtkLockButton", NULL,
      { NULL },
      create_gtk_lockbutton },  
      
    { "GtkTreeStore", NULL,
      { NULL },
      create_gtk_liststore },  

    { "GtkMenuItem", NULL,
      { NULL },
      menu_label },

    { "GtkMessageDialog",NULL ,
      { NULL },
      create_gtk_message_dialog },
      
    { "GtkPaned", NULL,
      { NULL },
      create_gtk_paned },
  
    { "GtkPopover", NULL,
      { NULL },
      create_gtk_popover },
      
    { "GtkPopoverMenu", NULL,
      { NULL },
      create_gtk_popovermenu },

    // { "GtkPreview", "gtk_preview_new (%s)",
      // { "type", NULL },
      // NULL },

    { "GtkRadioButton", NULL,
      { NULL },
      create_gtk_radio_button },
      
    { "GtkModelButton", NULL,
      { NULL },
      create_gtk_model_button },  

    { "GtkRadioMenuItem",NULL,
      { NULL },
      create_gtk_radio_menu_item },

    { "GtkRadioToolButton", NULL,
      { NULL },
      create_gtk_radio_tool_button },
   
    { "GtkRecentChooserDialog", NULL,
      { NULL },      
      create_gtk_recent_chooser_dialog },
      
    { "GtkRecentChooserWidget", NULL,
      { NULL },      
      create_gtk_recent_chooser_dialog },  
      
     { "GtkRecentManager", "gtk_recent_manager_new ()",
      { NULL },
      NULL },     
      
    { "GtkScale", NULL,
      {  NULL },
      create_gtk_scale },  
      
    { "GtkScaleButton", NULL,
      {  NULL },
      create_gtk_scale_button }, 

    { "GtkScrollbar", NULL,
      {  NULL },
      create_gtk_scrollbar },
      
    { "GtkScrolledWindow", NULL,
      {  NULL },
      create_gtk_scrolled_window },
      
    { "GtkSeparator", NULL,
      { NULL },
      create_gtk_separator },
      
    { "GtkSizeGroup", NULL,
      { NULL },
      create_gtk_sizegroup },  
      
    { "GtkSpinButton", NULL,
      { NULL },
      create_gtk_spin_button },

    { "GtkText", "gtk_text_new (NULL, NULL)",
      { NULL },
      NULL },
      
    { "GtkTextBuffer", NULL,
      { NULL },
      create_gtk_text_buffer },
      
    { "GtkTextTag", "gtk_text_tag_new(%s)",
      { "name", NULL },
       NULL },    
      
    { "GtkTextTagTable", "gtk_text_tag_table_new()",
       { NULL },
       NULL },         
     
    { "GtkToggleButton", "gtk_toggle_button_new_with_label (%s)",
      { "label", NULL },
      NULL },  
      
    { "GtkToolButton", "gtk_tool_button_new (NULL, NULL)",
      { NULL },
      NULL },
      
    { "GtkTreeSelection",NULL ,
      { NULL },
      create_gtk_tree_selection },
      
    { "GtkTreeModelSort", NULL,
      { NULL },
      create_gtk_treemodel_sort },  
      
    { "GtkTreeModelFilter", NULL,
      { NULL },
      create_gtk_treemodel_filter },     
    { "GtkMenuToolButton", "gtk_menu_tool_button_new (NULL, NULL)",
      { NULL },
      NULL },
            
    { "GtkToolItemGroup", "gtk_tool_item_group_new (NULL)",
       { NULL },
       NULL },     
      
    { "GtkTreeView", NULL,
      { NULL },
      create_gtk_treeview },

    { "GtkViewport", "gtk_viewport_new (NULL, NULL)",
      { NULL },
      NULL },

    { "GtkVRuler", "gtk_vruler_new ()",
      { NULL },
      NULL },

    { "GtkWindow", NULL,
      { NULL },
      create_gtk_window },

    { NULL, NULL,
      { NULL },
      NULL }
  };

/*  Common properties that are now deprecated for all widgets */
static g2cAfterParam after_params[] =
  {
    { "resize_mode"  },
    { "_overlay" },
    { "_page_type" },
    { "_page_title" },
    { "_page_complete" },
    { "_resize" },
    { "_shrink" },
    { NULL }
  };

/* Table of parameters to ignore */
static g2cIgnoreParam ignore_params[] =
  {
    { "Custom", "creation_function" },
    { "Custom", "string1" },
    { "Custom", "string2" },
    { "Custom", "int1" },
    { "Custom", "int2" },
    { "Custom", "last_modification_time" },
	{ "GtkAboutDialog", "translator_credits" },
    { "GtkAccelLabel", "label" },
	{ "GtkAccelLabel", "use_underline" },
    { "GtkAlignment", "xalign" },
    { "GtkAlignment", "yalign" }, 
    { "GtkAlignment", "xscale" },
    { "GtkAlignment", "yscale" },
    { "GtkAlignment", "right_padding" },
    { "GtkAlignment", "left_padding" },
    { "GtkAlignment", "top_padding" },
    { "GtkAlignment", "bottom_padding" },
    { "GtkAppChooserDialog", "content_type"},
    { "GtkAppChooserButton", "content_type"},
    { "GtkAspectFrame", "label" },
    { "GtkAspectFrame", "xalign" },
    { "GtkAspectFrame", "yalign" },
    { "GtkAspectFrame", "ratio" },
    { "GtkAspectFrame", "obey_child" },
    { "GtkWidget", "_tab_label" },
    { "GtkBox", "can_focus"},   /* because this is a common widget property */
    { "GtkBox", "orientation" },
    { "GtkBox", "spacing" },
    { "GtkBox", "_position" },   /*  popovermenu  */
    { "GtkButton", "label" },   /*  in button create */
    { "GtkButton", "can_focus" },  /*  widget  */
    { "GtkButton", "use_action_appearance" },  /*  deprecated  */
    { "GtkButton", "related_action" },  /*  deprecated  */
    { "GtkButton", "receives_default" },  /*  widget  */
    { "GtkButton", "xalign" },    /*  deprecated  */
    { "GtkButton", "yalign" },    /*  deprecated  */
    { "GtkButton", "focus_on_click" }, /*  widget  */
	{ "GtkButton", "use_underline" },   /*  in button create */
    { "GtkButtonBox", "child_min_height" },
    { "GtkButtonBox", "child_ipad_y" },
    { "GtkCalendar", "show_day_names" },
    { "GtkCalendar", "no_month_change" },
    { "GtkCalendar", "show_week_numbers" },
    { "GtkCalendar", "week_start_monday" },
    { "GtkCellRendererText", "placeholder_text" },
    { "GtkCellRendererToggle", "active" },
    { "GtkCellRendererSpin", "climb_rate" },
    { "GtkCheckButton", "can_focus" },
    { "GtkCheckButton", "xalign" },
    { "GtkCheckMenuItem", "label"},
    { "GtkCheckMenuItem", "accel_group"},
    { "GtkCheckMenuItem", "use_underline"},
    { "GtkCellRendererSpinner", "Editable"}, 
    { "GtkColorButton", "alpha" },
    { "GtkColorChooserDialog", "type" },
    { "GtkComboBox", "has_entry" },
    { "GtkComboBox", "model" },
    { "GtkComboBox", "can_focus" },
    { "GtkComboBoxText", "has_entry" }, 
    { "GtkDialog", "type" },
    { "GtkDialog", "has_resize_grip" },
    { "GtkDialog", "accel_group" },
    { "GtkEntry", "can_focus"},
    { "GtkEntry","invisible_char_set" }, 
    { "GtkEntry","invisible_char" }, 
    { "GtkEntry", "shadow_type"},   // deprecated
    { "GtkEntry", "yalign" },
   /* { "GtkEntry","completion" }, */
    { "GtkFileChooserDialog", "action"},
    { "GtkFileChooserDialog", "title"},
    { "GtkFileChooserButton", "action"},
    { "GtkFileChooserButton", "title"},
    { "GtkFontChooserDialog", "type" },
    { "GtkFontChooserDialog", "language"},
    { "GtkFontChooserWidget", "language"},
    { "GtkFontButton", "language" },
    { "GtkImage", "icon_size" },
    { "GtkImage", "image_visual" },
    { "GtkImage", "image_type" },
    { "GtkImage", "image_width" },
    { "GtkImage", "image_height" }, 
    { "GtkImage", "resource" },
    { "GtkImage", "pixbuf" },    /* see create_gtk_image  */
    { "GtkImage", "icon_name" }, /* see create_gtk_image  */
    { "GtkImageMenuItem", "label"},
    { "GtkImageMenuItem", "image"},
    { "GtkImageMenuItem", "always_show_image"},
    { "GtkImageMenuItem", "use_underline"},       
    { "GtkImageMenuItem", "accel_group"},        
    { "GtkLabel", "focus_target" },
//    { "GtkLabel", "xalign" },   /* in version 3.16 of gtk-3 */
//    { "GtkLabel", "yalign" },
    { "GtkLabel", "can_focus"},
    { "GtkLabel", "_page_complete" },
    { "GtkLabel", "_page_title" },
    { "GtkLabel", "_page_type" },
    { "GtkLabel", "use_underline" },
    { "GtkLabel", "label" },
    { "GtkLinkButton", "uri" },
    { "GtkLinkButton", "label" },
    { "GtkMenuBar", "shadow_type"},  // deprecated
    { "GtkMenuBar", "child_pack_direction" },  /* menu_bar_direction */
    { "GtkMenu", "tearoff_state"},  // deprecated
    { "GtkMenu", "tearoff_title"},  // deprecated
    { "GtkMenuItem", "stock_item" },
    { "GtkMenuItem", "stock_icon" },
    { "GtkMenuItem", "icon" },
//    { "GtkMenuButton", "popover" },
    { "GtkMessageDialog", "buttons" },
    { "GtkMessageDialog", "message_type" },
    { "GtkMessageDialog", "use_markup" },
    { "GtkMessageDialog", "secondary_use_markup" },
    { "GtkMessageDialog", "text" },
    { "GtkNotebook", "label" },
    { "GtkPaned", "orientation" },   /* in create  */
    { "GtkPaned", "position_set" },  /* in create  */
    { "GtkPlacesSidebar", "show_connect_to_server" },   /* deprecated */
    { "GtkPlacesSidebar", "window_placement_set" },
    { "GtkPopover", "relative_to" },
    { "GtkProgessBar", "lower" },
    { "GtkProgessBar", "upper" },
    { "GtkRadioButton", "group" },
    { "GtkRadioButton", "label" },
    { "GtkRadioMenuItem", "group" },
    { "GtkRadioToolButton", "group" },
    { "GtkRadioMenuItem", "draw_as_radio"},
    { "GtkRadioMenuItem", "use_underline"},
    { "GtkRadioMenuItem", "accel_group"},
    { "GtkRecentChooserDialog", "recent_manager"},
    { "GtkRecentChooserDialog", "type" },
    { "GtkRuler", "upper" },
    { "GtkRuler", "position" },
    { "GtkRuler", "lower" },    
    { "GtkScale", "orientation" },
    { "GtkScale", "adjustment" },
    { "GtkScrollbar", "orientation" },
    { "GtkScrollbar", "adjustment" },
    { "GtkScrolledWindow", "hscrollbar_policy" },
    { "GtkScrolledWindow", "vscrollbar_policy" },
    { "GtkScrolledWindow", "can_focus"},
    { "GtkSearchEntry", "shadow_type"},   // deprecated
    { "GtkSeparator", "can_focus" },
    { "GtkSizeGroup", "mode" },  /* in create_gtk_sizegroup  */
    { "GtkSpinButton", "value" },
//    { "GtkSpinButton", "lower" },
//    { "GtkSpinButton", "upper" },
//    { "GtkSpinButton", "page" },
//    { "GtkSpinButton", "page_size" },
//    { "GtkSpinButton", "step" },
    { "GtkSpinButton", "climb_rate" },
    { "GtkSpinButton", "digits" },
    { "GtkSpinButton", "max_length" },
    { "GtkSpinButton", "show_emoji_icon" },
    { "GtkTextView", "hscroll_policy" },
    { "GtkTextView", "vscroll_policy" },
    { "GtkTextBuffer", "tag_table" },   /* used in GtkTextBuffer create  */
    { "GtkToggleButton", "label"},
    { "GtkToolbar", "orientation" },  
    { "GtkToolbar", "type" },
    { "GtkTreeModelSort", "model" },
    { "GtkTreeModelFilter", "child_model" },
    { "GtkTreeView", "can_focus"},
    { "GtkTreeView", "width_request"},
    { "GtkTreeView", "height_request"},
    { "GtkTreeView", "model"}, 
    { "GtkTreeView", "hscroll_policy" },
    { "GtkTreeView", "vscroll_policy" },
    { "GtkTreeView", "rules_hint" },
    { "GtkTreeView", "fixed_height_mode" },
    { "GtkWidget", "child_name" },
    { "GtkWidget", "new_group" },
    { "GtkWidget", "value" },
//    { "GtkWindow", "type" },
    { "GtkWindow", "accel_group" },
    { "GtkWindow", "startup_id" },   /*  causes segmentation fault  */
    { "GtkWindow", "has_resize_grip" },  /* deprecated  */
    { NULL, NULL }
  };  /* ignore_params */

/* Some parameters have arguments that are named differently than Glade XML */
/* Some parameters common to all classes have had their names changed */
static g2cRemapParam remap_params[] =
  {
    { "GtkWindow", "window_position", "position" }, 
    { "GtkDialog", "window_position", "position" }, 
    { "GtkFontChooserDialog", "window_position", "position" },
    { "GtkColorChooserDialog", "window_position", "position" }, 
    { "GtkRecentChooserDialog", "window_position", "position" }, 
    { "GtkMessageDialog", "window_position", "position" }, 
    { "GtkEntry", "text_max_length", "max_length" },   
    { "GtkHandleBox", "shadow_type", "shadow" },
    { "GtkLabel", "wrap", "line_wrap" },
    { "GtkRange", "policy", "update_policy" },
//    { "GtkToolPalette", "toolbar_style", "style"},
    { "GtkSearchBar", "search_mode_enabled", "search_mode"},
    { "common", "margin_left", "margin_start"},
    { "common", "margin_right", "margin_end"},
    
    { NULL, NULL, NULL }
  };

/* Handle arguments that do not have Gtk arg equivalents
 * Format: { type, keyword, format, { params }, conditional, handler }
 */
static g2cSpecialHandler special_handlers[] =
  {
      { "Common", "tooltip_markup",
        NULL,
      { NULL },
        NULL,
        common_tooltip_markup },
		
    { "Common", "events",
        NULL,
      { NULL },
        NULL,
        common_events },    		
        
    { "Common", "has_default",
      "\tgtk_widget_grab_default (GTK_WIDGET(gui->%s));\n",
      { "name", NULL },
         NULL,
         NULL },
         
    {"GtkAccelLabel", "accel_widget",
      "\tgtk_accel_label_set_accel_widget (GTK_ACCEL_LABEL(gui->%s), GTK_WIDGET(gui->%s));\n",
    {"name", "accel_widget", NULL },
      NULL,
      NULL },

    { "GtkAboutDialog", "authors",
      NULL,
    { NULL },
      NULL,
      about_authors },
    { "GtkAboutDialog", "artists",
      NULL,
    { NULL },
      NULL,
      about_artists },
 
   { "GtkAboutDialog", "documenters",
      NULL,
    { NULL },
      NULL,
      about_documenters }, 
	  
	{ "GtkAboutDialog", "version",
         "\tgtk_about_dialog_set_version (GTK_ABOUT_DIALOG(gui->%s), \"%s\");\n",
      { "name", "version", NULL },
         NULL,
         NULL },  
    { "GtkAccelLabel", "use_markup",
      NULL,
      {  NULL },
      NULL,
      label_use_markup }, 
/*    { "GtkAccelLabel", "use_underline",
      "\tgtk_label_set_use_underline(GTK_LABEL(gui->%s), %s);\n",
      { "name", "use_underline", NULL },
      NULL,
      NULL }, */
	  
	      
    { "GtkAboutDialog", "version",
         "\tgtk_about_dialog_set_version (\"%s\");\n",
      { "version", NULL },
         NULL,
         NULL },
      
    { "GtkAboutDialog", "license_type",
      NULL,
    { NULL },
      NULL,  
      about_license_type },
	  
    { "GtkAccelLabel", "wrap",
      "\tg_object_set(G_OBJECT(gui->%s),\"wrap\", %s,NULL);\n",
      { "name", "wrap", NULL },
      NULL,
      NULL }, 
    { "GtkAccelLabel", "selectable",
      "\tgtk_label_set_selectable(GTK_LABEL(gui->%s), %s);\n",
      { "name", "selectable", NULL },
      NULL,
      NULL },  
    { "GtkBox", "baseline_position",
      NULL,
    { NULL },
      NULL,
      baseline_position }, 
    { "GtkBox", "_submenu",
      NULL,
    { NULL },
      NULL,
      popover_submenu },  
    { "GtkButton", "height_request",
      "\tg_object_set(G_OBJECT(gui->%s),\"height_request\", %s,NULL);\n",
      { "name", "height_request", NULL },
      NULL,
      NULL },
    { "GtkButton", "width_request",
      "\tg_object_set(G_OBJECT(gui->%s),\"width_request\", %s,NULL);\n",
      { "name", "width_request", NULL },
      NULL,
      NULL },
      
    { "GtkButton", "action_name",
        NULL,
       {  NULL },
       NULL,
       attach_action}, 
 
    { "GtkButton", "use_stock",
      NULL,
      { NULL },
      NULL,
      button_use_stock },
         
    { "GtkButton", "label",
      NULL,
      { NULL },
      NULL,
      button_label },
      
    { "GtkButton", "relief",
      NULL,
      { NULL },
      NULL,
      button_relief },
      
    { "GtkButton", "image",
      "\tgtk_button_set_image (GTK_BUTTON (gui->%s), GTK_WIDGET(gui->%s));\n",
      { "name", "image", NULL },
      NULL,
      NULL },
      
    { "GtkButton", "always_show_image",
       "\tgtk_button_set_always_show_image (GTK_BUTTON (gui->%s), %s);\n",
      { "name", "always_show_image", NULL },
      NULL,
      NULL }, 
      
    { "GtkButton", "use_underline",
      "\tgtk_button_set_use_underline (GTK_BUTTON (gui->%s), %s);\n",
      { "name", "use_underline", NULL },
      NULL,
      NULL },  
      
    { "GtkBox", "homogeneous",
      "\tgtk_box_set_homogeneous(GTK_BOX (gui->%s), %s);\n",
    { "name", "homogeneous", NULL},
      NULL,
      NULL},  
  
    { "GtkButtonBox", "child_min_width",
      "\tgtk_button_box_set_child_size (GTK_BUTTON_BOX (gui->%s), %s, %s);\n",
      { "name", "child_min_width", "child_min_height", NULL, NULL },
      NULL,
      NULL },

    { "GtkButtonBox", "child_ipad_x",
      "\tgtk_button_box_set_child_ipadding (GTK_BUTTON_BOX (gui->%s), %s, %s);\n",
      { "name", "child_ipad_x", "child_ipad_y", NULL, NULL },
      NULL,
      NULL },

    { "GtkButtonBox", "layout_style",
      NULL,
      { NULL },
      NULL,
       set_gtk_button_box_style},
      
    { "GtkCalendar", "day",
      "\tg_object_set(G_OBJECT(gui->%s),\"day\", %s, NULL);\n",
      { "name", "day", NULL },
      NULL,
      NULL },  
       
    { "GtkCalendar", "month",
      "\tg_object_set(G_OBJECT(gui->%s),\"month\", %s, NULL);\n",
      { "name", "month", NULL },
      NULL,
      NULL }, 
      
    { "GtkCalendar", "year",
      "\tg_object_set(G_OBJECT(gui->%s),\"year\", %s, NULL);\n",
      { "name", "year", NULL },
      NULL,
      NULL }, 
      
    { "GtkCalendar", "no_month_change",
      "\tgtk_calendar_set_display_options(GTK_CALENDAR(gui->%s),GTK_CALENDAR_NO_MONTH_CHANGE);\n",
      { "name", NULL },
      NULL,
      NULL }, 
      
    { "GtkCalendar", "show_day_names",
      "\tgtk_calendar_set_display_options(GTK_CALENDAR(gui->%s),GTK_CALENDAR_SHOW_DAY_NAMES);\n",
      { "name", NULL },
      NULL,
      NULL },  
      
    { "GtkCalendar", "show_details",
      "\tgtk_calendar_set_display_options(GTK_CALENDAR(gui->%s),GTK_CALENDAR_SHOW_DETAILS);\n",
      { "name", NULL },
      NULL,
      NULL },  

     { "GtkCalendar", "show_heading",
      NULL,
      { NULL },
      NULL,
      calendar_set_display_options },
      
    { "GtkCalendar", "show_week_numbers",
      "\tgtk_calendar_set_display_options(GTK_CALENDAR(gui->%s),GTK_CALENDAR_SHOW_WEEK_NUMBERS);\n",
      { "name", NULL },
      NULL,
      NULL },   
       
    { "GtkCellRendererSpin", "adjustment",
       "\tg_object_set(G_OBJECT(gui->%s),\"adjustment\", gui->%s, NULL);\n",
       { "name","adjustment", NULL },
       NULL,
       NULL},
      
    { "GtkCellRendererSpin", "editable",
       "\tg_object_set(G_OBJECT(gui->%s),\"editable\", %s, NULL);\n",
       { "name","editable", NULL },
       NULL,
       NULL},
    
    { "GtkCellRendererSpin", "background",
       "\tg_object_set(G_OBJECT(gui->%s),\"background\", \"%s\", NULL   );\n",
       { "name","background", NULL },
       NULL,
       NULL},
       
     { "GtkCellRendererSpin", "height",
       "\tg_object_set(G_OBJECT(gui->%s),\"height\", \"%s\", NULL   );\n",
       { "name","height", NULL },
       NULL,
       NULL},
       
     { "GtkCellRendererSpin", "width",
       "\tg_object_set(G_OBJECT(gui->%s),\"width\", \"%s\", NULL   );\n",
       { "name","width", NULL },
       NULL,
       NULL},  
       
    { "GtkCellRendererSpin", "size",
       "\tg_object_set(G_OBJECT(gui->%s),\"size\", %s, NULL   );\n",
       { "name","size", NULL },
       NULL,
       NULL},   
       
    { "GtkCellRendererSpin", "digits",
       "\tg_object_set(G_OBJECT(gui->%s),\"digits\", %s, NULL   );\n",
       { "name","digits", NULL },
       NULL,
       NULL},  
       
    { "GtkCellRenderer", "cell_background_rgba",
       NULL,
       { NULL },
       NULL,
       cell_background_rgb}, 
       
    { "GtkCellRendererSpin", "background_rgba",
       NULL,
       { NULL },
       NULL,
       background_rgb}, 
       
    { "GtkCellRendererSpin", "foreground_rgba",
       NULL,
       { NULL },
       NULL,
       foreground_rgb},    
       
    { "GtkCellRendererText", "editable",
       "\tg_object_set(G_OBJECT(gui->%s),\"editable\", %s, NULL);\n",
       { "name","editable", NULL },
       NULL,
       NULL},
       
    { "GtkCellRendererText", "background",
       "\tg_object_set(G_OBJECT(gui->%s),\"background\", \"%s\", NULL   );\n",
       { "name","background", NULL },
       NULL,
       NULL}, 
       
    { "GtkCellRendererText", "background_rgba",
       NULL,
       { NULL },
       NULL,
       background_rgb},

    { "GtkCellRendererText", "cell_background_rgba",
       NULL,
       { NULL },
       NULL,
       background_rgb}, 	   
       
    { "GtkCellRendererText", "foreground_rgba",
       NULL,
       { NULL },
       NULL,
       foreground_rgb},    
       
    { "GtkCellRendererText", "width_chars",
       "\tg_object_set(G_OBJECT(gui->%s),\"width_chars\", %s, NULL);\n",
       { "name","width_chars", NULL },
       NULL,
       NULL}, 
       
      { "GtkCellRendererText", "size",
       "\tg_object_set(G_OBJECT(gui->%s),\"size\", %s, NULL);\n",
       { "name","size", NULL },
       NULL,
       NULL}, 
       
     { "GtkCellRendererText", "size_points",
       NULL,
       { NULL },
       NULL,
       font_size_points},   
       
     { "GtkCellRendererText", "scale",
       NULL,
       { NULL },
       NULL,
       font_size_scale}, 
       
      { "GtkCellRendererText", "rise",
       "\tg_object_set(G_OBJECT(gui->%s),\"rise\", %s, NULL);\n",
       { "name","rise", NULL },
       NULL,
       NULL},   
       
    { "GtkCellRendererText", "alignment",
       "\tg_object_set(G_OBJECT(gui->%s),\"alignment\", PANGO_ALIGN_%s, NULL);\n",
       { "name","alignment", NULL },
       NULL,
       NULL},    
       
    { "GtkCellRendererSpin", "text",
       NULL,
       { NULL },
       NULL,
       pack_renderer},
       
    { "GtkCellRendererText", "text",
       NULL,
       { NULL },
       NULL,
       pack_renderer},
       
    { "GtkCellRendererToggle", "text",
       NULL,
       { NULL },
       NULL,
       pack_renderer},
       
    { "GtkCellRendererCombo", "text",
       NULL,
       { NULL },
       NULL,
       pack_renderer}, 
       
    { "GtkCellRendererAccel", "text",
       NULL,
       { NULL },
       NULL,
       pack_renderer},   
       
    { "GtkCellRendererAccel", "foreground_rgba",
       NULL,
       { NULL },
       NULL,
       foreground_rgb},   
       
    { "GtkCellRendererAccel", "background_rgba",
       NULL,
       { NULL },
       NULL,
       background_rgb},      
       
     { "GtkCellRendererToggle", "indicator_size",
       "\tg_object_set(G_OBJECT(gui->%s),\"indicator-size\", %s, NULL);\n",
       { "name","indicator_size", NULL },
       NULL,
       NULL},
       
    { "GtkCellRendererToggle", "cell_background",
       "\tg_object_set(G_OBJECT(gui->%s),\"cell-background\", %s, NULL);\n",
       { "name","$cell_background", NULL },
       NULL,
       NULL}, 
       
     { "GtkCellRendererToggle", "width",
       "\tg_object_set(G_OBJECT(gui->%s),\"width\", %s, NULL);\n",
       { "name","width", NULL },
       NULL,
       NULL}, 
       
    { "GtkCellRendererToggle", "inconsistent",
       "\tg_object_set(G_OBJECT(gui->%s),\"inconsistent\", %s, NULL);\n",
       { "name","inconsistent", NULL },
       NULL,
       NULL}, 
       
//    { "GtkCellRendererToggle", "cell_background_rgba",
//       NULL,
//       { NULL },
//       NULL,
//       background_rgb}, 
       
//     { "GtkCellRendererPixbuf", "cell_background_rgba",
//       NULL,
//       { NULL },
//       NULL,
//       background_rgb},  
       
    { "GtkCellRendererCombo", "background_rgba",
       NULL,
       { NULL },
       NULL,
       background_rgb}, 
      
    { "GtkCellRendererCombo", "foreground_rgba",
       NULL,
       { NULL },
       NULL,
       foreground_rgb},       
       
    { "GtkCellRendererCombo", "text_column",
        "\tg_object_set(G_OBJECT(gui->%s),\"text-column\", %s, NULL);\n",
       { "name", "text_column", NULL },
       NULL,
       NULL}, 
       
    { "GtkCellRendererCombo", "model",
        "\tg_object_set(G_OBJECT(gui->%s),\"model\", GTK_TREE_MODEL(gui->%s), NULL);\n",
       { "name", "model", NULL },
       NULL,
       NULL}, 
       
    { "GtkCellRendererAccel", "accel_key",
       "\tg_object_set(G_OBJECT(gui->%s),\"accel-key\", %s, NULL);\n",
       { "name","accel_key", NULL },
       NULL,
       NULL},   
       
    { "GtkCellRendererAccel", "accel_mods",
       "\tg_object_set(G_OBJECT(gui->%s),\"accel-mods\", %s, NULL);\n",
       { "name","accel_mods", NULL },
       NULL,
       NULL},  
       
    { "GtkCellRendererAccel", "accel_mode",
       "\tg_object_set(G_OBJECT(gui->%s),\"accel-mode\", GTK_CELL_RENDERER_ACCEL_MODE_OTHER, NULL);\n",
       { "name", NULL },
       NULL,
       NULL}, 
       
    { "GtkCellRendererAccel", "keycode",
       "\tg_object_set(G_OBJECT(gui->%s),\"keycode\", %s, NULL);\n",
       { "name","keycode", NULL },
       NULL,
       NULL},  
       
    { "GtkCellRendererPixbuf", "icon_name",
       "\tg_object_set(G_OBJECT(gui->%s),\"icon_name\", %s, NULL);\n",
       { "name","$icon_name", NULL },
       NULL,
       NULL},     

    { "GtkCheckButton", "active",
      "\tgtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (gui->%s), %s);\n",
      { "name", "active", NULL, NULL, NULL },
      NULL,
      NULL },
      
    { "GtkCheckButton", "draw_indicator",
      "\tg_object_set(G_OBJECT(gui->%s),\"draw_indicator\", %s,NULL);\n",
      { "name", "draw_indicator", NULL },
      NULL,
      NULL },
      
    { "GtkCheckButton", "label",
      NULL,
      { NULL },
      NULL,
      button_label },  

    { "GtkCheckMenuItem", "always_show_toggle",
      "\tgtk_check_menu_item_set_show_toggle (GTK_CHECK_MENU_ITEM (gui->%s), %s);\n",
      { "name", "always_show_toggle", NULL, NULL, NULL },
      NULL,
      NULL },

    { "GtkCheckMenuItem", "active",
      "\tgtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (gui->%s), %s);\n",
      { "name", "active", NULL, NULL, NULL },
      "active",
      NULL },
           
      { "GtkColorChooserDialog", "rgba",
         NULL,
      {  NULL },
         NULL,
         colour_chooser_rgba },
         
      { "GtkColorButton", "rgba",
         NULL,
      {  NULL },
         NULL,
         colour_chooser_rgba },
         
      { "GtkColorChooserWidget", "rgba",
         NULL,
      {  NULL },
         NULL,
         colour_chooser_rgba },   

      { "GtkColorButton", "use_alpha",
      "\tgtk_color_chooser_set_use_alpha (GTK_COLOR_CHOOSER (gui->%s), %s);\n",
      { "name", "use_alpha", NULL },
      NULL,
      NULL },    

    { "GtkContainer", "border_width",
      "\tgtk_container_set_border_width (GTK_CONTAINER (gui->%s), %s);\n",
      { "name", "border_width", NULL },
      NULL,
      NULL },
      
    { "GtkDialog", "type_hint",
       NULL,
      { NULL },
       NULL,
      dialog_type_hint },
      
    { "GtkDialog", "title",
      "\tgtk_window_set_title (GTK_WINDOW (gui->%s), %s);\n",
      { "name", "$title", NULL },
      NULL,
      NULL },
      
     { "GtkDialog", "transient_for",   /* also applies to child dialog classes */
         NULL,
      {  NULL },
         NULL,
         dialog_transient },

    { "GtkDialog", "resizable",
      "\tgtk_window_set_resizable (GTK_WINDOW (gui->%s), %s);\n",
      { "name", "resizable", NULL },
      NULL,
      NULL },
/*  These GtkEntry items will also work for child classes  GtkSearchEntry and GtkSpinButton */  
         
    { "GtkEntry", "text",
      "\tgtk_entry_set_text (GTK_ENTRY (gui->%s), %s);\n",
      { "name", "$text", NULL },
      NULL,
      NULL },
      
     { "GtkEntry", "input_hints",
      NULL,
      { NULL },
      NULL,
      input_hints }, 
      
    { "GtkEntry", "input_purpose",
      NULL,
      { NULL },
      NULL,
      input_purpose },   
            
    { "GtkEntry", "xalign",
      "\tgtk_entry_set_alignment(GTK_ENTRY(gui->%s), %s);\n",
      { "name","xalign", NULL },
        NULL,
        NULL },
      
    { "GtkEntry", "visibility",
      "\tgtk_entry_set_visibility(GTK_ENTRY(gui->%s), %s);\n",
      { "name","visibility", NULL },
        NULL,
        NULL },  
        
    { "GtkEntry", "activates_default",
      "\tgtk_entry_set_activates_default(GTK_ENTRY(gui->%s), %s);\n",
      { "name","activates_default", NULL },
        NULL,
        NULL }, 
        
    { "GtkEntry", "overwrite_mode",
      "\tgtk_entry_set_overwrite_mode(GTK_ENTRY(gui->%s), %s);\n",
      { "name","overwrite_mode", NULL },
        NULL,
        NULL },      
      
    { "GtkEntry", "primary_icon_tooltip_markup",
      NULL,
      { NULL },
        NULL,
        entry_markup },
        
     { "GtkEntry", "secondary_icon_tooltip_markup",
      NULL,
      { NULL },
        NULL,
        entry_markup2 },   
    { "GtkEntry", "primary_icon_pixbuf",
      NULL,
      { NULL },
        NULL,
        entry_primary_pixbuf }, 
        
    { "GtkEntry", "secondary_icon_pixbuf",
      NULL,
      { NULL },
        NULL,
        entry_secondary_pixbuf }, 
      
    { "GtkEntry","buffer",
        "\tgtk_entry_set_buffer (GTK_ENTRY(gui->%s), GTK_ENTRY_BUFFER (gui->%s));\n",
    { "name", "buffer", NULL },
        NULL,
        NULL},
        
    { "GtkEntry","completion",
        "\tgtk_entry_set_completion (GTK_ENTRY(gui->%s), GTK_ENTRY_COMPLETION (gui->%s));\n",
    { "name", "completion", NULL },
        NULL,
        NULL}, 
        
    { "GtkEntry", "progress_fraction",
      "\tgtk_entry_set_progress_fraction (GTK_ENTRY (gui->%s), %s);\n",
      { "name", "progress_fraction", NULL },
      NULL,
      NULL }, 
      
    { "GtkEntry", "progress_pulse_step",
      "\tgtk_entry_set_progress_pulse_step (GTK_ENTRY (gui->%s), %s);\n",
      { "name", "progress_pulse_step", NULL },
      NULL,
      NULL },
      
    { "GtkEntry","max_length",
        "\tgtk_entry_set_max_length (GTK_ENTRY(gui->%s), %s );\n",
    { "name", "max_length", NULL },
        NULL,
        NULL},           
        
    { "GtkEntryBuffer", "text",
      "\tgtk_entry_buffer_set_text (GTK_ENTRY_BUFFER (gui->%s), %s, -1);\n",
      { "name", "$text", NULL },
      NULL,
      NULL },
        
    { "GtkEntryCompletion", "model",
      "\tgtk_entry_completion_set_model (GTK_ENTRY_COMPLETION (gui->%s), GTK_TREE_MODEL(gui->%s));\n",
      { "name", "model", NULL },
      NULL,
      NULL },  
        
    { "GtkFileChooser", "filter",
      NULL,
      {  NULL },
      NULL,
      file_chooser_filter },
      
    { "GtkFileChooserDialog", "create_folders",
      "\tgtk_file_chooser_set_create_folders (GTK_FILE_CHOOSER (gui->%s), %s);\n",
      { "name", "create_folders", NULL },
      NULL,
      NULL },  
      
    { "GtkFileChooserDialog", "preview_widget_active",
      "\tgtk_file_chooser_set_preview_widget_active (GTK_FILE_CHOOSER (gui->%s), %s);\n",
      { "name", "preview_widget_active", NULL },
      NULL,
      NULL }, 
      
    { "GtkFileChooserDialog", "use_preview_label",
      "\tgtk_file_chooser_set_use_preview_label (GTK_FILE_CHOOSER (gui->%s), %s);\n",
      { "name", "use_preview_label", NULL },
      NULL,
      NULL }, 
      
    { "GtkFileChooserDialog", "do_overwrite_confirmation",
      "\tgtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (gui->%s), %s);\n",
      { "name", "do_overwrite_confirmation", NULL },
      NULL,
      NULL },  
      
    { "GtkFileChooserDialog", "local_only",
      "\tgtk_file_chooser_set_local_only (GTK_FILE_CHOOSER (gui->%s), %s);\n",
      { "name", "local_only", NULL },
      NULL,
      NULL }, 
      
    { "GtkFileChooserDialog", "select_multiple",
      "\tgtk_file_chooser_set_select_multiple (GTK_FILE_CHOOSER (gui->%s), %s);\n",
      { "name", "select_multiple", NULL },
      NULL,
      NULL }, 
      
    { "GtkFileChooserDialog", "show_hidden",
      "\tgtk_file_chooser_set_show_hidden (GTK_FILE_CHOOSER (gui->%s), %s);\n",
      { "name", "show_hidden", NULL },
      NULL,
      NULL },   
      
//     { "GtkFileChooserButton", "filter",
//      "\tgtk_file_chooser_set_filter (GTK_FILE_CHOOSER (gui->%s), GTK_FILE_FILTER(gui->%s));\n",
//      { "name", "filter", NULL },
//      NULL,
//      NULL },
      
    { "GtkFileChooserWidget", "search_mode",
      "\tg_object_set(G_OBJECT(gui->%s), \"search-mode\", %s, NULL);\n",
      { "name", "search_mode", NULL },
      NULL,
      NULL },  
      
    { "GtkFlowBox", "selection_mode",
       NULL,
      { NULL },
      NULL,
      flowbox_selection_mode },   
      
     { "GtkFontButton", "font",
      "\tgtk_font_chooser_set_font (GTK_FONT_CHOOSER (gui->%s), %s);\n",
      { "name", "$font", NULL },
      NULL,
      NULL },
      
//      { "GtkFontChooser", "language",
//        "\tgtk_font_chooser_set_language(GTK_FONT_CHOOSER(gui->%s), %s);\n",
//      { "name", "$language", NULL },
//      NULL,
//      NULL },

     { "GtkFontChooser", "show_preview_entry",
      "\tgtk_font_chooser_set_show_preview_entry (GTK_FONT_CHOOSER (gui->%s), %s);\n",
      { "name", "show_preview_entry", NULL },
      NULL,
      NULL },
      
    { "GtkFrame", "label_xalign",  
       NULL, 
      {NULL},
       NULL,
      frame_label_xalign},
         
    { "GtkFrame", "label_yalign",  
       NULL, 
      {NULL},
       NULL,
      frame_label_yalign},
      
    { "GtkFrame", "shadow_type",
      NULL,
      { NULL },
      NULL,
      shadow_type }, 
      
    { "GtkIconView", "model",
      "\tgtk_icon_view_set_model(GTK_ICON_VIEW(gui->%s),  GTK_TREE_MODEL(gui->%s));\n",
      { "name", "model", NULL },
      NULL,
      NULL },  
      
    { "GtkIconView", "selection_mode",
       NULL,
      { NULL },
      NULL,
      iconview_selection_mode }, 
      
    { "GtkIconView", "hadjustment",
       "\tgtk_scrollable_set_hadjustment(GTK_SCROLLABLE(gui->%s), GTK_ADJUSTMENT(gui->%s));\n",
       { "name", "hadjustment", NULL },
        NULL,
        NULL },
            
    { "GtkIconView", "vadjustment",
       "\tgtk_scrollable_set_vadjustment(GTK_SCROLLABLE(gui->%s), GTK_ADJUSTMENT(gui->%s));\n",
       { "name", "vadjustment", NULL },
        NULL,
        NULL },
               
    { "GtkIconView", "hscroll_policy",
       "\tgtk_scrollable_set_hscroll_policy(GTK_SCROLLABLE(gui->%s), GTK_SCROLL_NATURAL);\n",
       { "name", NULL },
        NULL,
        NULL },             
               
    { "GtkIconView", "vscroll_policy",
       "\tgtk_scrollable_set_vscroll_policy(GTK_SCROLLABLE(gui->%s), GTK_SCROLL_NATURAL);\n",
       { "name", NULL },
        NULL,
        NULL }, 
               
    { "GtkIconView", "item_orientation",
       "\tgtk_icon_view_set_item_orientation(GTK_ICON_VIEW(gui->%s), GTK_ORIENTATION_HORIZONTAL);\n",
       { "name", NULL },
        NULL,
        NULL },            
      
    { "GtkImageMenuItem", "use_stock",
      NULL,
      { NULL },
      NULL,
      menu_item_use_stock },
      
/*
    { "GtkImageMenuItem", "accel_path",
      "\tgtk_menu_item_set_accel_path (GTK_MENU_ITEM (gui->%s), %s);\n",
      { "name", "$accel_path", NULL },
      NULL,
      NULL },
*/
   
//    { "GtkImage", "pixbuf",   /*  ignored  */
//      NULL,
//      { NULL },
//      NULL,
//      image_from_pixbuf },
//      
//    { "GtkImage", "resource",   /*  ignored  */
//      NULL,
//      { NULL },
//      NULL,
//      image_from_pixbuf },  
      
     { "GtkImage", "stock",
      NULL,
      { NULL },
      NULL,
      image_from_stock }, 
      
     { "GtkImage", "icon_name",
      NULL,
      { NULL },
      NULL,
      image_from_stock }, 
      
    { "GtkImage", "icon_size",
      "\tg_object_set(G_OBJECT(gui->%s), \"icon-size\", %s, NULL);\n",
      { "name", "icon_size", NULL },
      NULL,
      NULL }, 
      
    { "GtkInfoBar", "message_type",
      NULL,
      { NULL },
      NULL,
      infobar_message_type },  
      
/*    { "GtkLabel", "halign",
      "\tgtk_widget_set_halign(GTK_WIDGET(gui->%s), %s);\n",
      { "name", "halign", NULL },
      NULL,
      NULL },      

     { "GtkLabel", "xalign",
      "\tg_object_set(G_OBJECT(gui->%s), \"xalign\", %s, NULL);\n",
      { "name", "xalign", NULL },
      NULL,
      NULL },
      
     { "GtkLabel", "yalign",
      "\tg_object_set(G_OBJECT(gui->%s), \"yalign\", %s, NULL);\n",
      { "name", "yalign", NULL },
      NULL,
      NULL },

    { "GtkLabel", "halign",
      NULL,
      { NULL },
      NULL,
      label_label_align }, 
*/
      
    { "GtkLabel", "ellipsize",
      NULL,
      { NULL },
      NULL,
      label_label_ellipsize },
      
    { "GtkLabel", "single_line_mode",   /*  applies to GtkAccelLabel as well  */
      "\tgtk_label_set_single_line_mode(GTK_LABEL(gui->%s), %s);\n",
      { "name", "single_line_mode", NULL },
      NULL,
      NULL },  
      
    { "GtkLabel", "max_width_chars",
      "\tgtk_label_set_max_width_chars(GTK_LABEL(gui->%s), %s);\n",
      { "name", "max_width_chars", NULL },
      NULL,
      NULL },
      
     { "GtkLabel", "width_chars",
      "\tgtk_label_set_width_chars(GTK_LABEL(gui->%s), %s);\n",
      { "name", "width_chars", NULL },
      NULL,
      NULL },  
      
     { "GtkLabel", "use_markup",
      NULL,
      { NULL },
      NULL,
      label_use_markup }, 
      
    { "GtkLabel", "wrap_mode",
       NULL,
       {  NULL },
       NULL,
       label_label_wrap},     
	  
    { "GtkLayout", "width",
      NULL,
      {  NULL },
      NULL,
      layout_width },
      
    { "GtkLayout", "height",
      NULL,
      {  NULL },
      NULL,
      layout_height },  
      
    { "GtkLayout", "hadjustment",
      "\tgtk_scrollable_set_hadjustment (GTK_SCROLLABLE (gui->%s), GTK_ADJUSTMENT(gui->%s));\n",
      { "name", "hadjustment", NULL },
      NULL },
      
    { "GtkLayout", "vadjustment",
      "\tgtk_scrollable_set_vadjustment (GTK_SCROLLABLE (gui->%s), GTK_ADJUSTMENT(gui->%s));\n",
      { "name", "vadjustment", NULL },
      NULL },
      
    { "GtkLevelBar", "mode",
      "\tgtk_level_bar_set_mode (GTK_LEVEL_BAR (gui->%s), GTK_LEVEL_BAR_MODE_DISCRETE);\n",
      { "name",  NULL },
      NULL }, 
      
    { "GtkListBox", "selection_mode",
      NULL,
      { NULL },
      NULL,
      listbox_selection_mode },   
      
    { "GtkListBoxRow", "action_name",
      NULL,
      {  NULL },
      NULL,
      attach_action },   

    { "GtkMenu", "anchor_hints",
      NULL,
      {  NULL },
      NULL,
      menu_anchor_hint },      
      
    { "GtkMenu", "menu_type_hint",
      NULL,
      {  NULL },
      NULL,
      menu_type_hint }, 
      
    { "GtkMenuBar", "pack_direction",
       NULL,
       {  NULL },
       NULL,
       menu_bar_direction},  
      
    { "GtkMenuButton", "inconsistent",
       "\tg_object_set(G_OBJECT(gui->%s),\"inconsistent\", %s, NULL);\n",
       { "name","inconsistent", NULL },
       NULL,
       NULL}, 
      
    { "GtkMenuButton", "draw_indicator",
       "\tg_object_set(G_OBJECT(gui->%s),\"draw_indicator\", %s, NULL);\n",
       { "name","draw_indicator", NULL },
       NULL,
       NULL}, 
       
     { "GtkMenuButton", "align_widget",
       "\tgtk_menu_button_set_align_widget(GTK_MENU_BUTTON(gui->%s), GTK_WIDGET(gui->%s));\n",
       { "name","align_widget", NULL },
       NULL,
       NULL},   
       
     { "GtkMenuButton", "direction",
       NULL,
       {  NULL },
       NULL,
       set_menu_button_direction}, 
       
     { "GtkMenuItem", "right_justified",
      "\tgtk_widget_set_halign(GTK_WIDGET(gui->%s), GTK_ALIGN_END);\n",
      { "name", NULL },
      NULL,
      NULL },   
       
     { "GtkMenuItem", "label",
       NULL,
       {  NULL },
       NULL,
       menu_item_label}, 
      
     { "GtkMenuItem", "action_name",
       NULL,
       {  NULL },
       NULL,
       attach_action},  
       
     { "GtkMenuShell", "take_focus" ,   /*  for GtkMenuBar  */
       "\tgtk_menu_shell_set_take_focus(GTK_MENU_SHELL(gui->%s), %s);\n",
     { "name", "take_focus", NULL },
       NULL,
       NULL },      
      
     { "GtkCheckMenuItem", "right_justified",
      "\tgtk_widget_set_halign(GTK_WIDGET(gui->%s), GTK_ALIGN_END);\n", 
      { "name", NULL },
      NULL,
      NULL },  
      
    { "GtkRadioMenuItem", "right_justified",
      "\tgtk_widget_set_halign(GTK_WIDGET(gui->%s), GTK_ALIGN_END);\n",
      { "name", NULL },
      NULL,
      NULL },   
       
/*  These  are specific to modelbutton:  */      
    { "GtkModelButton", "text",
       "\tg_object_set(G_OBJECT(gui->%s),\"text\", %s, NULL);\n",
       { "name","$text", NULL },
       NULL,
       NULL}, 
      
    { "GtkModelButton", "inverted",
       "\tg_object_set(G_OBJECT(gui->%s),\"inverted\", %s, NULL);\n",
       { "name","inverted", NULL },
       NULL,
       NULL},
       
     { "GtkModelButton", "centered",
       "\tg_object_set(G_OBJECT(gui->%s),\"centered\", %s, NULL);\n",
       { "name","centered", NULL },
       NULL,
       NULL},  
       
     { "GtkModelButton", "use_markup",
       "\tg_object_set(G_OBJECT(gui->%s),\"use_markup\", %s, NULL);\n",
       { "name","use_markup", NULL },
       NULL,
       NULL},  
       
     { "GtkModelButton", "menu_name",
       "\tg_object_set(G_OBJECT(gui->%s),\"menu-name\", %s, NULL);\n",
       { "name","$menu_name", NULL },
       NULL,
       NULL},     
       
     { "GtkPopover", "position",
       NULL,
       {  NULL },
       NULL,
       set_popover_position},  
       
     { "GtkPopover", "constrain_to",
       "\tgtk_popover_set_constrain_to(GTK_POPOVER(gui->%s),GTK_POPOVER_CONSTRAINT_NONE);\n",
       { "name", NULL },
       NULL,
       NULL}, 
       
    { "GtkPopover", "transitions_enabled",
       "\tgtk_popover_set_transitions_enabled(GTK_POPOVER(gui->%s),%s);\n",
       { "name", "transitions_enabled", NULL },
       NULL,
       NULL}, 
       
    { "GtkPopover", "modal",
       "\tgtk_popover_set_modal(GTK_POPOVER(gui->%s), %s);\n",
       { "name","modal",  NULL },
       NULL,
       NULL}, 
       
//    { "GtkRecentManager", "filename",
//       "\tg_object_set(G_OBJECT(gui->%s), \"filename\", \"%s\", NULL);\n",
//       { "name","filename",  NULL },
//       NULL,
//       NULL},    
       
    { "GtkScale", "value_pos",
      NULL,
      { NULL },
      NULL,
      scale_value_pos },     
      
    { "GtkScrolledWindow", "hadjustment",
      "\tgtk_scrolled_window_set_hadjustment (GTK_SCROLLED_WINDOW (gui->%s), GTK_ADJUSTMENT(gui->%s));\n",
      { "name", "hadjustment", NULL },
      NULL }, 
      
    { "GtkScrolledWindow", "vadjustment",
      "\tgtk_scrolled_window_set_vadjustment (GTK_SCROLLED_WINDOW (gui->%s), GTK_ADJUSTMENT(gui->%s));\n",
      { "name", "vadjustment", NULL },
      NULL }, 
      
    { "GtkStack", "transition_type",
      NULL,
      { NULL },
      NULL,
      stack_transition },   
      
    { "GtkStackSwitcher", "icon_size",
      "\tg_object_set(G_OBJECT(gui->%s), \"icon-size\", %s, NULL);\n",
      { "name", "icon_size", NULL },
      NULL,
      NULL },
      
    { "GtkStatusIcon", "file",
       "\tgtk_status_icon_set_from_file(GTK_STATUS_ICON(gui->%s), \"%s\");\n",
      { "name", "file", NULL },
      NULL,
      NULL }, 
      
    { "GtkStatusIcon", "pixbuf",
       "\tgtk_status_icon_set_from_file(GTK_STATUS_ICON(gui->%s), \"%s\");\n",
      { "name", "pixbuf", NULL },
      NULL,
      NULL },  
      
    { "GtkStatusIcon", "stock",     
       "\tgtk_status_icon_set_from_stock(GTK_STATUS_ICON(gui->%s), %s);\n",
      { "name", "stock", NULL },
      NULL,
      NULL },
      
    { "GtkStatusIcon", "has_tooltip",     
       "\tgtk_status_icon_set_has_tooltip(GTK_STATUS_ICON(gui->%s), %s);\n",
      { "name", "has_tooltip", NULL },
      NULL,
      NULL },
      
    { "GtkStatusIcon", "icon_name",     
       "\tgtk_status_icon_set_from_icon_name(GTK_STATUS_ICON(gui->%s), \"%s\");\n",
      { "name", "icon_name", NULL },
      NULL,
      NULL },   
      
    { "GtkStatusIcon", "tooltip_text",     
       "\tgtk_status_icon_set_tooltip_text(GTK_STATUS_ICON(gui->%s), \"%s\");\n",
      { "name", "tooltip_text", NULL },
      NULL,
      NULL },     
      
    { "GtkSwitch", "action_name",
      NULL,
      {  NULL },
      NULL,
      attach_action },
      
    { "GtkTextTag", "accumulative_margin",
       "\tg_object_set(G_OBJECT(gui->%s),\"accumulative_margin\", %s, NULL);\n",
       { "name","accumulative_margin", NULL },
       NULL,
       NULL},  
      
    { "GtkTextTag", "background_rgba",
       NULL,
       { NULL },
       NULL,
       background_rgb},

    { "GtkTextTag", "foreground_rgba",
       NULL,
       { NULL },
       NULL,
       foreground_rgb},
       
    { "GtkTextTag", "font",
       "\tg_object_set(G_OBJECT(gui->%s),\"font\", \"%s\", NULL);\n",
       { "name","font", NULL },
       NULL,
       NULL}, 
            
    { "GtkTextTag", "size",
       "\tg_object_set(G_OBJECT(gui->%s),\"size\", %s, NULL);\n",
       { "name","size", NULL },
       NULL,
       NULL},

    { "GtkTextTag", "size_points",
       NULL,
       { NULL },
       NULL,
       font_size_points},   
       
    { "GtkTextTag", "scale",
       NULL,
       { NULL },
       NULL,
       font_size_scale}, 

    { "GtkTextTag", "rise",
       "\tg_object_set(G_OBJECT(gui->%s),\"rise\", %s, NULL);\n",
       { "name","rise", NULL },
       NULL,
       NULL}, 

    { "GtkTextTag", "pixels_above_lines",
       "\tg_object_set(G_OBJECT(gui->%s),\"pixels_above_lines\", %s, NULL);\n",
       { "name","pixels_above_lines", NULL },
       NULL,
       NULL}, 

    { "GtkTextTag", "pixels_below_lines",
       "\tg_object_set(G_OBJECT(gui->%s),\"pixels_below_lines\", %s, NULL);\n",
       { "name","pixels_below_lines", NULL },
       NULL,
       NULL}, 

    { "GtkTextTag", "pixels_inside_wrap",
       "\tg_object_set(G_OBJECT(gui->%s),\"pixels_inside_wrap\", %s, NULL);\n",
       { "name","pixels_inside_wrap", NULL },
       NULL,
       NULL},
       
    { "GtkTextTag", "justification",
       NULL,
       { NULL },
       NULL,
       text_tag_justification},    
       
   { "GtkTextTag", "direction",
       NULL,
       { NULL },
       NULL,
       text_tag_direction},       

    { "GtkTextTag", "left_margin",
       "\tg_object_set(G_OBJECT(gui->%s),\"left-margin\", %s, NULL);\n",
       { "name","left_margin", NULL },
       NULL,
       NULL},

    { "GtkTextTag", "right_margin",
       "\tg_object_set(G_OBJECT(gui->%s),\"right-margin\", %s, NULL);\n",
       { "name","right_margin", NULL },
       NULL,
       NULL},

     { "GtkTextTag", "letter_spacing",
       "\tg_object_set(G_OBJECT(gui->%s),\"letter_spacing\", %s, NULL);\n",
       { "name","letter_spacing", NULL },
       NULL,
       NULL},
       
    { "GtkTextTag", "indent",
       "\tg_object_set(G_OBJECT(gui->%s),\"indent\", %s, NULL);\n",
       { "name","indent", NULL },
       NULL,
       NULL},
       
    { "GtkTextTag", "strikethrough_rgba",
       NULL,
       { NULL },
       NULL,
       strikethrough_rgb}, 
       
    { "GtkTextTag", "underline_rgba",
       NULL,
       { NULL },
       NULL,
       underline_rgb}, 
       
    { "GtkTextTag", "paragraph_background",
       "\tg_object_set(G_OBJECT(gui->%s),\"paragraph_background\", %s, NULL);\n",
       { "name","$paragraph_background", NULL },
       NULL,
       NULL},   
       
    { "GtkTextTag", "paragraph_background_rgba",
       NULL,
       { NULL },
       NULL,
       paragraph_background_rgb},    
       
    { "GtkTextTag", "background_full_height",
       "\tg_object_set(G_OBJECT(gui->%s),\"background_full_height\", %s, NULL);\n",
       { "name","background_full_height", NULL },
       NULL,
       NULL},
       
    { "GtkTextTag", "language",
       "\tg_object_set(G_OBJECT(gui->%s),\"language\", \"%s\", NULL);\n",
       { "name","language", NULL },
       NULL,
       NULL},
       
    { "GtkTextTag", "strikethrough_rgba_set",
       "\tg_object_set(G_OBJECT(gui->%s),\"strikethrough_rgba_set\", %s, NULL);\n",
       { "name","strikethrough_rgba_set", NULL },
       NULL,
       NULL},
       
    { "GtkTextTag", "underline_rgba_set",
       "\tg_object_set(G_OBJECT(gui->%s),\"underline_rgba_set\", %s, NULL);\n",
       { "name","underline_rgba_set", NULL },
       NULL,
       NULL}, 
       
     { "GtkTextTag", "fallback_set",
       "\tg_object_set(G_OBJECT(gui->%s),\"fallback_set\", %s, NULL);\n",
       { "name","fallback_set", NULL },
       NULL,
       NULL}, 
       
    { "GtkTextTag", "letter_spacing_set",
       "\tg_object_set(G_OBJECT(gui->%s),\"letter_spacing_set\", %s, NULL);\n",
       { "name","letter_spacing_set", NULL },
       NULL,
       NULL},    
       
    { "GtkTextTag", "font_features_set",
       "\tg_object_set(G_OBJECT(gui->%s),\"font_features_set\", %s, NULL);\n",
       { "name","font_features_set", NULL },
       NULL,
       NULL},       
       
    { "GtkTextView", "editable",
       "\tgtk_text_view_set_editable(GTK_TEXT_VIEW(gui->%s), %s);\n",
       { "name", "editable", NULL },
       NULL,
       NULL},     
       
    { "GtkTextView", "wrap_mode",
       NULL,
       {  NULL },
       NULL,
       text_view_wrap},    
       
    { "GtkToolItem", "action_name",
       NULL,
       {  NULL },
       NULL,
       attach_action},    
      
    { "GtkViewport", "hadjustment",
      "\tgtk_scrollable_set_hadjustment (GTK_SCROLLABLE (gui->%s), GTK_ADJUSTMENT(gui->%s));\n",
      { "name", "hadjustment", NULL },
      NULL }, 
      
    { "GtkViewport", "vadjustment",
      "\tgtk_scrollable_set_vadjustment (GTK_SCROLLABLE (gui->%s), GTK_ADJUSTMENT(gui->%s));\n",
      { "name", "vadjustment", NULL },
      NULL },     
      
    { "GtkViewport", "hscroll_policy",
      "\tgtk_scrollable_set_hscroll_policy (GTK_SCROLLABLE (gui->%s), GTK_SCROLL_NATURAL);\n",
      { "name", NULL },
      NULL },
      
    { "GtkViewport", "vscroll_policy",
      "\tgtk_scrollable_set_vscroll_policy (GTK_SCROLLABLE (gui->%s), GTK_SCROLL_NATURAL);\n",
      { "name", NULL },
      NULL },
      
    { "GtkLayout", "hscroll_policy",
      "\tgtk_scrollable_set_hscroll_policy (GTK_SCROLLABLE (gui->%s), GTK_SCROLL_NATURAL);\n",
      { "name", NULL },
      NULL },
      
    { "GtkLayout", "vscroll_policy",
      "\tgtk_scrollable_set_vscroll_policy (GTK_SCROLLABLE (gui->%s), GTK_SCROLL_NATURAL);\n",
      { "name", NULL },
      NULL },

    { "GtkLayout", "hstep",
      "\tGTK_ADJUSTMENT (GTK_LAYOUT (gui->%s)->hadjustment)->step_increment = %s;\n",
      { "name", "hstep", NULL },
      NULL },

    { "GtkLayout", "vstep",
      "\tGTK_ADJUSTMENT (GTK_LAYOUT (gui->%s)->vadjustment)->step_increment = %s;\n",
      { "name", "vstep", NULL },
      NULL },
      
    { "GtkMenuButton", "label",
      NULL,
      { NULL },
      NULL,
      button_label },  
        
    { "GtkMenuButton", "popup",
            NULL,
      { NULL },
      NULL,
      menu_button_popup },
      
     { "GtkMenuButton", "popover",
      "\tgtk_menu_button_set_popover (GTK_MENU_BUTTON (gui->%s), GTK_WIDGET (gui->%s));\n",
      { "name", "popover", NULL },
      NULL,
      NULL },  

    { "GtkMenuItem", "right_justify",
      "\tgtk_menu_item_right_justify (GTK_MENU_ITEM (gui->%s));\n",
      { "name", NULL },
      "right_justify",
      NULL },
      
     { "GtkMenuToolButton", "label",
      "\tgtk_tool_button_set_label (GTK_TOOL_BUTTON (gui->%s), %s);\n",
      { "name", "$label", NULL },
      NULL,
      NULL },
     
    { "GtkMenuToolButton", "use_underline",
      "\tgtk_tool_button_set_use_underline (GTK_TOOL_BUTTON (gui->%s), %s);\n",
      { "name", "use_underline", NULL },
      NULL,
      NULL },
      
    { "GtkMenuToolButton", "is_important",
      "\tgtk_tool_item_set_is_important (GTK_TOOL_ITEM (gui->%s), %s);\n",
      { "name", "is_important", NULL },
      NULL,
      NULL }, 
      
    { "GtkMenuToolButton", "visible_horizontal",
      "\tgtk_tool_item_set_visible_horizontal (GTK_TOOL_ITEM (gui->%s), %s);\n",
      { "name", "visible_horizontal", NULL },
      NULL,
      NULL },  
      
    { "GtkMenuToolButton", "visible_vertical",
      "\tgtk_tool_item_set_visible_vertical (GTK_TOOL_ITEM (gui->%s), %s);\n",
      { "name", "visible_vertical", NULL },
      NULL,
      NULL }, 
      
    { "GtkMessageDialog", "secondary_text",
         NULL,
      { NULL },
         NULL,
         message_dialog_secondary_text },
         
    { "GtkNotebook", "enable_popup",
      "\tgtk_notebook_popup_enable (gui->%s);\n",
    { "name", NULL},
      NULL,
      NULL },

    { "GtkPaned", "position",
      "\tgtk_paned_set_position (GTK_PANED (gui->%s), %s);\n",
      { "name", "position", NULL, NULL, NULL },
      NULL,
      NULL },

    { "GtkPlacesSidebar", "open_flags",
      "\tgtk_places_sidebar_set_open_flags(GTK_PLACES_SIDEBAR(gui->%s), %s);\n",
      { "name", "open_flags", NULL },
      NULL,
      NULL },    
      
    { "GtkPlacesSidebar", "shadow_type",
      NULL,
      { NULL },
      NULL,
      shadow_type }, 
      
    { "GtkPlacesSidebar", "show_starred_location",
      "\tg_object_set(G_OBJECT(gui->%s), \"show-starred-location\", %s, NULL);\n",
      { "name", "show_starred_location", NULL },
      NULL,
      NULL },        

    { "GtkProgressBar", "text",
      "\tgtk_progress_bar_set_text (GTK_PROGRESS_BAR (gui->%s), %s);\n",
      { "name", "$text", NULL },
      NULL,
      NULL },

    { "GtkProgressBar", "inverted",
      "\tgtk_progress_bar_set_inverted (GTK_PROGRESS_BAR (gui->%s), %s);\n",
      { "name", "inverted", NULL },
      NULL,
      NULL },
      
    { "GtkRadioButton", "label",
      NULL,
      { NULL },
      NULL,
      button_label },  
      
    { "GtkRadioToolButton", "is_important",
      "\tgtk_tool_item_set_is_important (GTK_TOOL_ITEM (gui->%s), %s);\n",
      { "name", "is_important", NULL },
      NULL,
      NULL },
      
    { "GtkRadioToolButton", "active",
      "\tgtk_toggle_tool_button_set_active (GTK_TOGGLE_TOOL_BUTTON (gui->%s), %s);\n",
      { "name", "active", NULL, NULL, NULL },
      NULL,
      NULL }, 
      
    { "GtkRange", "inverted",
      "\tgtk_range_set_inverted(GTK_RANGE(gui->%s), %s);\n",
      { "name", "inverted", NULL },
      NULL,
      NULL },  
      
    { "GtkRange", "lower_stepper_sensitivity",
      NULL,
      {  NULL },
      NULL,
      range_lower_sensitivity },  
      
    { "GtkRange", "upper_stepper_sensitivity",
       NULL,
      {  NULL },
      NULL,
      range_upper_sensitivity }, 
      
    { "GtkRange", "show_fill_level",
      "\tgtk_range_set_show_fill_level(GTK_RANGE(gui->%s), %s);\n",
      { "name", "show_fill_level", NULL },
      NULL,
      NULL }, 
      
    { "GtkRange", "fill_level",
      "\tgtk_range_set_fill_level(GTK_RANGE(gui->%s), %s);\n",
      { "name", "fill_level", NULL },
      NULL,
      NULL },  
      
    { "GtkRange", "restrict_to_fill_level",
      "\tgtk_range_set_restrict_to_fill_level(GTK_RANGE(gui->%s), %s);\n",
      { "name", "restrict_to_fill_level", NULL },
      NULL,
      NULL },    
      
    { "GtkRange", "round_digits",
      "\tgtk_range_set_round_digits(GTK_RANGE(gui->%s), %s);\n",
      { "name", "round_digits", NULL },
      NULL,
      NULL },    
      
    { "GtkRecentChooser", "limit",
         "\tgtk_recent_chooser_set_limit (GTK_RECENT_CHOOSER(gui->%s), %s);\n",
      { "name", "limit", NULL },
         NULL,
         NULL },
         
    { "GtkRecentChooser", "filter",
         NULL,
      {  NULL },
         NULL,
         file_chooser_filter },
         
    { "GtkRecentChooser", "select_multiple",
         "\tgtk_recent_chooser_set_select_multiple (GTK_RECENT_CHOOSER(gui->%s), %s);\n",
      { "name", "select_multiple", NULL },
         NULL,
         NULL },
         
    { "GtkRecentChooser", "show_private",
         "\tgtk_recent_chooser_set_show_private (GTK_RECENT_CHOOSER(gui->%s), %s);\n",
      { "name", "show_private", NULL },
         NULL,
         NULL },
         
    { "GtkRecentChooser", "show_tips",
         "\tgtk_recent_chooser_set_show_tips (GTK_RECENT_CHOOSER(gui->%s), %s);\n",
      { "name", "show_tips", NULL },
         NULL,
         NULL },
         
     { "GtkRecentChooser", "show_not_found",
         "\tgtk_recent_chooser_set_show_not_found (GTK_RECENT_CHOOSER(gui->%s), %s);\n",
      { "name", "show_not_found", NULL },
         NULL,
         NULL },
         
     { "GtkRecentChooser", "sort_type",
         NULL,
      {  NULL },
         NULL,
         recent_chooser_sort_type }, 
         
     { "GtkRecentManager", "filename",
        NULL,
      { "name", "$filename", NULL },
         NULL,
         recent_manager_filename },
         
     { "GtkRevealer", "transition_type",
      NULL,
      { NULL },
      NULL,
      transition_type },     

    { "GtkScaleButton", "adjustment",
      NULL,
      { NULL },
      NULL,
      volume_button_adjustment },
      
    { "GtkScaleButton", "icons",
      NULL,
      { NULL },
      NULL,
      scale_button_icons },  
      
    { "GtkScaleButton", "size",
      NULL,
      { NULL },
      NULL,
      volume_button_size }, 
      
    { "GtkScrolledWindow", "kinetic_scrolling",
      "\tgtk_scrolled_window_set_kinetic_scrolling(GTK_SCROLLED_WINDOW(gui->%s), %s);\n",
      { "name", "kinetic_scrolling", NULL },
       NULL,
       NULL },     
      
    { "GtkScrolledWindow", "min_content_width",
      "\tgtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(gui->%s), %s);\n",
      { "name", "min_content_width", NULL },
       NULL,
       NULL },
      
    { "GtkScrolledWindow", "min_content_height",
      "\tgtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(gui->%s), %s);\n",
      { "name", "min_content_height", NULL },
       NULL,
       NULL },
       
    { "GtkScrolledWindow", "max_content_width",
      "\tgtk_scrolled_window_set_max_content_width(GTK_SCROLLED_WINDOW(gui->%s), %s);\n",
      { "name", "max_content_width", NULL },
       NULL,
       NULL },
      
    { "GtkScrolledWindow", "max_content_height",
      "\tgtk_scrolled_window_set_max_content_height(GTK_SCROLLED_WINDOW(gui->%s), %s);\n",
      { "name", "max_content_height", NULL },
       NULL,
       NULL }, 
       
     { "GtkScrolledWindow", "overlay_scrolling",
      "\tgtk_scrolled_window_set_overlay_scrolling(GTK_SCROLLED_WINDOW(gui->%s), %s);\n",
      { "name", "overlay_scrolling", NULL },
       NULL,
       NULL },   
    
     { "GtkScrolledWindow", "propagate_natural_height",
      "\tgtk_scrolled_window_set_propagate_natural_height(GTK_SCROLLED_WINDOW(gui->%s), %s);\n",
      { "name", "propagate_natural_height", NULL },
       NULL,
       NULL },   
       
    { "GtkScrolledWindow", "propagate_natural_width",
      "\tgtk_scrolled_window_set_propagate_natural_width(GTK_SCROLLED_WINDOW(gui->%s), %s);\n",
      { "name", "propagate_natural_width", NULL },
       NULL,
       NULL },   
      
    { "GtkScrolledWindow", "shadow_type",
      NULL,
      { NULL },
      NULL,
      shadow_type },       
      
    { "GtkScrolledWindow","window_placement",
       NULL,
      { NULL },
       NULL,
      scrolled_window_placement },  
      
    { "GtkSeparatorToolItem", "is_important",
      "\tgtk_tool_item_set_is_important (GTK_TOOL_ITEM (gui->%s), %s);\n",
      { "name", "is_important", NULL },
      NULL,
      NULL },
      
    { "GtkSeparatorToolItem", "visible_horizontal",
      "\tgtk_tool_item_set_visible_horizontal (GTK_TOOL_ITEM (gui->%s), %s);\n",
      { "name", "visible_horizontal", NULL },
      NULL,
      NULL },  
      
    { "GtkSeparatorToolItem", "visible_vertical",
      "\tgtk_tool_item_set_visible_vertical (GTK_TOOL_ITEM (gui->%s), %s);\n",
      { "name", "visible_vertical", NULL },
      NULL,
      NULL }, 
      
//    { "GtkSpinButton", "max_width_chars",
//      "\tg_object_set (G_OBJECT (gui->%s), %s, NULL);\n",
//      { "name", "max_width_chars", NULL },
//      NULL,
//      NULL }, 
//      
//    { "GtkSpinButton", "value",
//      "\tgtk_spin_button_set_value (GTK_SPIN_BUTTON (gui->%s), %s.0);\n",
//      { "name", "value", NULL },
//      NULL,
//      NULL }, 
      
    { "GtkSpinButton", "adjustment",
      "\tgtk_spin_button_set_adjustment (GTK_SPIN_BUTTON (gui->%s), GTK_ADJUSTMENT(gui->%s));\n",
      { "name", "adjustment", NULL },
      NULL,
      NULL },  
      
    { "GtkSpinButton", "snap",
      "\tgtk_spin_button_set_snap_to_ticks (GTK_SPIN_BUTTON (gui->%s), %s);\n",
      { "name", "snap", NULL, NULL, NULL },
      NULL,
      NULL },
      
    { "GtkSpinner", "active",
      "\tg_object_set (G_OBJECT (gui->%s), \"active\", %s, NULL);\n",
      { "name", "active", NULL },
      NULL,
      NULL },
      
    { "GtkStackSidebar", "stack",
       "\tgtk_stack_sidebar_set_stack (GTK_STACK_SIDEBAR (gui->%s),\n"
            "\t\t\tGTK_STACK(gui->%s));\n",
      { "name", "stack", NULL },
      NULL,
      NULL },   
      
    { "GtkStackSwitcher", "stack",
       "\tgtk_stack_switcher_set_stack (GTK_STACK_SWITCHER (gui->%s),\n"
            "\t\t\tGTK_STACK(gui->%s));\n",
      { "name", "stack", NULL },
      NULL,
      NULL },   

    { "GtkText", "text",
      "\tgtk_text_insert (GTK_TEXT (gui->%s), NULL, NULL, NULL, %s);\n",
      { "name", "$text", NULL },
      NULL,
      NULL },
      
    { "GtkTextView", "buffer",
      "\tgtk_text_view_set_buffer (GTK_TEXT_VIEW (gui->%s),\n"
            "\t\t\tGTK_TEXT_BUFFER(gui->%s));\n",
      { "name", "buffer", NULL },
      NULL,
      NULL },
      
    { "GtkTextView", "input_hints",
      NULL,
      { NULL },
      NULL,
      input_hints },
 
    { "GtkTextView", "input_purpose",
        NULL,
      { NULL },
        NULL,
       input_purpose },   
      
    { "GtkTextView", "hadjustment",
      "\tgtk_scrollable_set_hadjustment (GTK_SCROLLABLE (gui->%s),\n"
            "\t\t\tGTK_ADJUSTMENT(gui->%s));\n",
      { "name", "hadjustment", NULL },
      NULL,
      NULL},  
       
      
    { "GtkTextView", "vadjustment",
      "\tgtk_scrollable_set_vadjustment (GTK_SCROLLABLE (gui->%s),\n"
            "\t\t\tGTK_ADJUSTMENT(gui->%s));\n",
      { "name", "vadjustment", NULL },
      NULL,
      NULL},  
      
   { "GtkTextBuffer", "text",
      "\tgtk_text_buffer_set_text (GTK_TEXT_BUFFER (gui->%s), %s, -1);\n",
      { "name", "$text", NULL },
      NULL,
      NULL },    /*  text_buffer_text */
         
    { "GtkToggleButton", "active",
      "\tgtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (gui->%s), %s);\n",
      { "name", "active", NULL, NULL, NULL },
      NULL,
      NULL },  
      
   { "GtkToolButton", "is_important",
      "\tgtk_tool_item_set_is_important (GTK_TOOL_ITEM (gui->%s), %s);\n",
      { "name", "is_important", NULL },
      NULL,
      NULL },
      
   { "GtkToolButton", "icon_name",
      "\tgtk_tool_button_set_icon_name(GTK_TOOL_BUTTON (gui->%s), %s);\n",
     { "name", "$icon_name", NULL },
     NULL,
     NULL},
      
    { "GtkToolButton", "icon_widget",
      "\tgtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON (gui->%s),\n"
            "\t\t\tGTK_WIDGET(gui->%s));\n",
     { "name", "icon_widget", NULL },
     NULL,
     NULL},    
      
    { "GtkToolButton", "label_widget",
      "\tgtk_tool_button_set_label_widget(GTK_TOOL_BUTTON (gui->%s),\n"
            "\t\t\tGTK_WIDGET(gui->%s));\n",
     { "name", "label_widget", NULL },
     NULL,
     NULL},  
     
   { "GtkToolButton", "stock_id",
      "\tgtk_tool_button_set_icon_name(GTK_TOOL_BUTTON (gui->%s), %s);\n",
     { "name", "$stock_id", NULL },
     NULL,
     NULL},
      
   { "GtkToolItemGroup", "ellipsize",
       NULL,
      { NULL },
       NULL,
      label_ellipsize },
     
    { "GtkToolItemGroup", "label_widget",
      "\tgtk_tool_item_group_set_label_widget(GTK_TOOL_ITEM_GROUP (gui->%s),\n"
            "\t\t\tGTK_WIDGET(gui->%s));\n",
     { "name", "label_widget", NULL },
     NULL,
     NULL},  
      
    { "GtkToolPalette", "icon_size",
       NULL,
      { NULL },
       NULL,
      icon_size },
      
    { "GtkToolPalette", "toolbar_style",
       NULL,
      { NULL },
       NULL,
      toolbar_style },
      
    { "GtkToolPalette", "hadjustment",
      "\tgtk_scrollable_set_hadjustment (GTK_SCROLLABLE (gui->%s), GTK_ADJUSTMENT(gui->%s));\n",
      { "name", "hadjustment", NULL },
      NULL },
      
    { "GtkToolPalette", "vadjustment",
      "\tgtk_scrollable_set_vadjustment (GTK_SCROLLABLE (gui->%s), GTK_ADJUSTMENT(gui->%s));\n",
      { "name", "vadjustment", NULL },
      NULL },
      
    { "GtkToolPalette", "hscroll_policy",
      "\tgtk_scrollable_set_hscroll_policy (GTK_SCROLLABLE (gui->%s), GTK_SCROLL_NATURAL);\n",
      { "name", NULL },
      NULL },
      
    { "GtkToolPalette", "vscroll_policy",
      "\tgtk_scrollable_set_vscroll_policy (GTK_SCROLLABLE (gui->%s), GTK_SCROLL_NATURAL);\n",
      { "name", NULL },
      NULL },  
      
    { "GtkToggleToolButton", "label",
      "\tgtk_tool_button_set_label (GTK_TOOL_BUTTON (gui->%s), %s);\n",
      { "name", "$label", NULL },
      NULL,
      NULL },
      
    { "GtkToggleToolButton", "use_underline",
      "\tgtk_tool_button_set_use_underline (GTK_TOOL_BUTTON (gui->%s), %s);\n",
      { "name", "use_underline", NULL },
      NULL,
      NULL },
      
    { "GtkToggleToolButton", "is_important",
      "\tgtk_tool_item_set_is_important (GTK_TOOL_ITEM (gui->%s), %s);\n",
      { "name", "is_important", NULL },
      NULL,
      NULL },
      
    { "GtkToggleToolButton", "visible_horizontal",
      "\tgtk_tool_item_set_visible_horizontal (GTK_TOOL_ITEM (gui->%s), %s);\n",
      { "name", "visible_horizontal", NULL },
      NULL,
      NULL },  
      
    { "GtkToggleToolButton", "visible_vertical",
      "\tgtk_tool_item_set_visible_vertical (GTK_TOOL_ITEM (gui->%s), %s);\n",
      { "name", "visible_vertical", NULL },
      NULL,
      NULL }, 
      
    { "GtkToolbar", "toolbar_style",
      NULL,
      { NULL },
      NULL,
      toolbar_style },  

    { "GtkToolButton", "visible_horizontal",
      "\tgtk_tool_item_set_visible_horizontal (GTK_TOOL_ITEM (gui->%s), %s);\n",
      { "name", "visible_horizontal", NULL },
      NULL,
      NULL },  
      
    { "GtkToolButton", "visible_vertical",
      "\tgtk_tool_item_set_visible_vertical (GTK_TOOL_ITEM (gui->%s), %s);\n",
      { "name", "visible_vertical", NULL },
      NULL,
      NULL },   

    { "GtkTreeSelection", "mode",
      NULL,
      { NULL },
      NULL,
      tree_selection_mode }, 
      
    { "GtkTreeView", "expander_column",
      "\tgtk_tree_view_set_expander_column(GTK_TREE_VIEW(gui->%s),\n"
            "\t\t\tGTK_TREE_VIEW_COLUMN(gui->%s));\n",
      { "name", "expander_column", NULL },
      NULL,
      NULL },
      
    { "GtkTreeView", "model",
      "\tgtk_tree_view_set_model(GTK_TREE_VIEW(gui->%s),\n"
            "\t\t\tGTK_TREE_MODEL(gui->%s));\n",
      { "name", "model", NULL },
      NULL,
      NULL },
      
    { "GtkTreeView", "enable_grid_lines",
      NULL,
      { NULL },
      NULL,
      tree_grid_lines },         

    { "GtkTreeView", "hadjustment",
      "\tgtk_tree_view_%s.set_hadjustment (self.%s);\n",
      { "name", "hadjustment", NULL },
      NULL }, 
      
    { "GtkTreeView", "vadjustment",
      "\tgtk_tree_view_%s.set_vadjustment (self.%s);\n",
      { "name", "vadjustment", NULL },
      NULL }, 
      
    { "GtkWindow", "resize",
      "\tgtk_window_set_resizable (GTK_WINDOW (gui->%s), %s);\n",
      { "name", "resize", NULL },
      NULL,
      NULL },
      
    { "GtkTreeViewColumn", "resize",
      "\tgtk_tree_view_column_set_resizable (GTK_TREE_VIEW_COLUMN (gui->%s),\n"
            "\t\t\t%s);\n",
      { "name", "resize", NULL },
      NULL,
      NULL },  
      
    { "GtkTreeViewColumn", "alignment",
      NULL,
      { NULL },
      NULL,
      view_column_alignment},
      
    { "GtkTreeViewColumn", "sort_order",
      "\tgtk_tree_view_column_set_sort_order (GTK_TREE_VIEW_COLUMN (gui->%s),\n"
            "\t\t\tGTK_SORT_DESCENDING);\n",
      { "name", NULL },
      NULL,
      NULL },    
      
    { "GtkViewport", "shadow_type",
      NULL,
      { NULL },
      NULL,
      shadow_type }, 
      
    { "GtkVolumeButton", "adjustment",
      NULL,
      { NULL },
      NULL,
      volume_button_adjustment },
      
    { "GtkVolumeButton", "icons",
      NULL,
      { NULL },
      NULL,
      scale_button_icons },   
      
    { "GtkVolumeButton", "size",
      NULL,
      { NULL },
      NULL,
      volume_button_size },   

    { "GtkWidget", "tooltip",
      "\tgtk_widget_set_tooltip_next (GTK_WIDGET (gui->%s), %s);\n",
      { "name", "$tooltip", NULL, NULL, NULL },
      NULL,
      NULL },
      
    { "GtkWindow", "default_height",
      "\tg_object_set(G_OBJECT(gui->%s),\"default_height\", %s,NULL);\n",
      { "name", "default_height", NULL },
      NULL,
      NULL },
      
    { "GtkWindow", "default_width",
      "\tg_object_set(G_OBJECT(gui->%s),\"default_width\", %s,NULL);\n",
      { "name", "default_width", NULL },
      NULL,
      NULL },
      
   { "GtkWindow", "height_request",
      "\tg_object_set(G_OBJECT(gui->%s),\"height_request\", %s,NULL);\n",
      { "name", "height_request", NULL },
      NULL,
      NULL },
      
    { "GtkWindow", "width_request",
      "\tg_object_set(G_OBJECT(gui->%s),\"width_request\", %s,NULL);\n",
      { "name", "width_request", NULL },
      NULL,
      NULL }, 

    { "GtkWindow", "icon",
      NULL,
      { NULL },
      NULL,
      window_icon },   
      
    { NULL, NULL,
      NULL,
      { NULL },
      NULL,
      NULL }
      
  };

/* Table of properties handled the same for all widgets */
/* second parameter: True means use gtk_widget; False means use g_object */
/* third parameter: if not null means use prefix e.g. with prefix GTK_WINDOW, toplevel becomes GTK_WINDOW_TOPLEVEL  */
/*  if the third parameter is NULL then the value is boolean TRUE/FALSE */
/*  if the third parameter is "int", no prefix but the value must not be enclosed in quotation marks */
/*  if the third parameter is "char", no prefix but the value must be enclosed in quotation marks even if apparently numeric */
/*  if the third parameter is "widget" the value is a widget and must be set up as such in a parameter */
/* fourth parameter (alternative): the type name to use e.g. "GtkTreeView" in place of the widget's klass_name */
/*  This can be used either to handle enumerable properties of the widget e.g. 'justify' for GtkLabel when the widget is GtkLabel */
/*   or the property belongs to an ancestral widget class, which is given here.  */
static g2cCommonParam common_params[] =
  {
    {"can_focus", TRUE,  NULL, NULL},
    {"name",TRUE,"char",NULL},
    {"background",FALSE,"char",NULL},
    {"foreground",FALSE,"char",NULL},
    {"font",FALSE,"char",NULL},
    {"max_width_chars",FALSE,"int",NULL},
    {"width_chars",FALSE,"int",NULL},
//    {"wrap_mode",FALSE,"PANGO_WRAP",NULL},
    {"wrap_width",FALSE,"int",NULL},
    {"single_paragraph_mode", FALSE,NULL, NULL},
    {"family", FALSE, "char",NULL},
    {"variant",FALSE, "PANGO_VARIANT",NULL},
    {"weight",FALSE,"int",NULL},
    {"stretch",FALSE,"PANGO_STRETCH", NULL},
    {"strikethrough",FALSE,NULL,NULL},
    {"underline",FALSE,"PANGO_UNDERLINE",NULL},
    {"ellipsize",FALSE,"PANGO_ELLIPSIZE",NULL},
    {"enable_emoji_completion",FALSE,NULL,NULL},
    {"show_emoji_icon",FALSE,NULL,NULL},
    {"sizing",FALSE,"GTK_TREE_VIEW_COLUMN", "GtkTreeViewColumn"},
    {"margin_start", TRUE,  NULL, NULL},
    {"margin_end", TRUE,  NULL, NULL},  
    {"margin_top", TRUE,  NULL, NULL},
    {"margin_bottom", TRUE,  NULL, NULL},
    {"halign", TRUE, "GTK_ALIGN", NULL},
    {"valign", TRUE, "GTK_ALIGN", NULL},
    {"height_request", FALSE, NULL, NULL},
    {"width_request", FALSE, NULL, NULL},
    {"height", FALSE, NULL, NULL},
    {"has_entry", FALSE, NULL, NULL},
    {"hexpand", TRUE,  NULL, NULL},
    {"vexpand", TRUE,  NULL, NULL},
    {"sensitive", TRUE, NULL, NULL},
    {"has_focus", FALSE,  NULL, NULL},
    {"is_focus", FALSE,  NULL, NULL},
    {"inconsistent", FALSE, NULL, NULL},
    {"receives_default",TRUE,  NULL, NULL},
//    {"has_default",FALSE,  NULL, NULL},
    {"rect_anchor_dx", FALSE,  NULL, NULL},
    {"rect_anchor_dy", FALSE,  NULL, NULL},
    {"can_default",TRUE,  NULL, NULL}, 
    {"no_show_all", TRUE, NULL, NULL},
    {"opacity", TRUE,  NULL, NULL},
    {"tooltip_text", TRUE,  NULL, NULL},
    {"margin", FALSE, NULL, NULL},
    {"has_tooltip", TRUE,  NULL, NULL},
    {"focus_on_click",TRUE,  NULL, NULL},
    {"app_paintable",TRUE,  NULL, NULL},
    {"popup_fixed_width", FALSE, NULL, NULL},
    {"justify",TRUE, "GTK_JUSTIFY", "GtkLabel"},
    {"editable", FALSE, NULL, NULL},
    {"truncate_multiline", FALSE, NULL, NULL},
    {"caps_lock_warning", FALSE, NULL, NULL},
    {"primary_icon_stock", FALSE, NULL, NULL},
    {"primary_icon_tooltip_text", FALSE, NULL, NULL},      
    {"primary_icon_sensitive", FALSE, NULL, NULL}, 
    {"primary_icon_activatable", FALSE, NULL, NULL},
    {"primary_icon_name", FALSE, NULL, NULL},
    {"secondary_icon_stock", FALSE, NULL, NULL},
    {"secondary_icon_sensitive", FALSE, NULL, NULL}, 
    {"secondary_icon_activatable", FALSE, NULL, NULL},
    {"secondary_icon_name", FALSE, NULL, NULL},
    {"secondary_icon_tooltip_text", FALSE, NULL, NULL},
    {"populate_all", FALSE, NULL, NULL},
    {"image_position", TRUE, "GTK_POS", "GtkButton"},
    {"tab_pos", TRUE, "GTK_POS", "GtkNotebook"},
    {"xpad", FALSE, NULL, NULL},
    {"ypad", FALSE, NULL, NULL},
    {"double_buffered", FALSE, NULL,NULL},
    {"type_hint", FALSE, "GDK_WINDOW_TYPE_HINT", "GtkWindow"},
    {"gravity", FALSE, "GDK_GRAVITY", "GtkWindow"},
    {"position", FALSE, "GTK_WIN_POS", "GtkWindow"},
    {"tooltip_markup", TRUE, NULL, NULL},
    {"events", TRUE, "int", NULL},
    {"modal", TRUE, NULL, "GtkWindow"},
    {"destroy_with_parent", TRUE, NULL, "GtkWindow"},
    {"hide_titlebar_when_maximized", TRUE, NULL, "GtkWindow"},
    {"icon_name", TRUE, NULL, "GtkWindow"},
    {"skip_taskbar_hint", TRUE, NULL, "GtkWindow"},
    {"skip_pager_hint", TRUE, NULL, "GtkWindow"},
    {"urgency_hint", TRUE, NULL, "GtkWindow"},
    {"accept_focus", TRUE, NULL, "GtkWindow"},
    {"focus_on_map", TRUE, NULL, "GtkWindow"},
    {"decorated", TRUE, NULL, "GtkWindow"},
    {"deletable", TRUE, NULL, "GtkWindow"},
    {"has_resize_grip", TRUE, NULL, "GtkWindow"},
    {"accel_path", TRUE, NULL, "GtkMenuItem" },
    {"role", TRUE, "char", "GtkWindow" },
    {"startup_id", TRUE, "char", "GtkWindow" },
    {"attached_to", TRUE, "widget", "GtkWindow" },
    {"show_editor", FALSE, NULL, NULL},
    {"content_type", FALSE, NULL, NULL},
    {"left_padding", FALSE, NULL, NULL},
    {"justification", FALSE, "GTK_JUSTIFY", "GtkTextView" },
    {"header_relief", FALSE, "GTK_RELIEF", "GtkToolItemGroup" },
    {"orientation", FALSE, "GTK_ORIENTATION", "GtkOrientable" },
    {"use_fallback", FALSE,  NULL, NULL},
    {"use_header_bar", FALSE, NULL, NULL },
    {NULL, 0, NULL, NULL}
};

/* Signal list management
 * 
 * An interesting problem arises when you map more than one signal handler 
 * to the same handler.  e.g. both a menu item and a button use the
 * function on_file_open() to handle the "activated" and "clicked" events.
 * 
 * We can add the signal handler twice, like so:
 *    void on_file_open (GtkImageMenuItem *widget, gpointer user_data);
 *    void on_file_open (GtkButton *widget, gpointer user_data);
 * 
 * which is what we used to do.  But that doesn't work, since C doesn't like
 * function overloading.  So we can do this:
 *    void on_file_open (GtkWidget *widget, gpointer user_data);
 * 
 * and have this function map to both signals.  As long as the signal handler
 * prototypes are the same, this works.  If they aren't, then the programmer
 * needs to find a different naming scheme.
 * 
 * To help out, the functions below manage a list of signal handlers that
 * have already been added, so that we don't add them twice.  These functions
 * will be called from g2c_doc.c and g2c_widget.c.
 */
void 
add_to_signal_list (gchar *signal_name)
{
  signal_list = g_list_append (signal_list, signal_name);
}

void
clear_signal_list (void)
{
  g_list_free (signal_list);
  signal_list = NULL;
}

gboolean
is_in_signal_list (gchar *signal_name)
{
  GList *temp_list = NULL;
  temp_list = g_list_find_custom (signal_list, signal_name, g2c_string_list_compare_cb);

  if (temp_list == NULL) return 0;
  else return 1;
}


/* Special Handlers */
void about_authors ( g2cWidget *widget )
{
gchar * authors = NULL;
gchar * authorlist = NULL;

  g_assert( NULL != widget );
  authors = g2c_widget_get_property( widget, "authors" );
  authorlist = g_strdelimit( authors, "\n", ':' );
  fprintf( CURRENT_FILE,
          "\tgtk_about_dialog_set_authors (GTK_ABOUT_DIALOG(gui->%s), (const gchar **) g_strsplit(\"%s\", \":\", -1));\n",
          widget->name, authorlist);
 
}

void about_artists ( g2cWidget *widget )
{
gchar * artists = NULL;
gchar * artistlist = NULL;

  g_assert( NULL != widget );
  artists = g2c_widget_get_property( widget, "artists" );
  artistlist = g_strdelimit( artists, "\n", ':' );
  fprintf( CURRENT_FILE,
          "\tgtk_about_dialog_set_artists (GTK_ABOUT_DIALOG(gui->%s), (const gchar **) g_strsplit(\"%s\", \":\", -1));\n",
          widget->name, artistlist);
 
}

void about_documenters ( g2cWidget *widget )
{
gchar * documenters = NULL;
gchar * documenterlist = NULL;

  g_assert( NULL != widget );
  documenters = g2c_widget_get_property( widget, "documenters" );
  documenterlist = g_strdelimit( documenters, "\n", ':' );
  fprintf( CURRENT_FILE,
          "\tgtk_about_dialog_set_documenters (GTK_ABOUT_DIALOG(gui->%s), (const gchar **) g_strsplit(\"%s\", \":\", -1));\n",
          widget->name, documenterlist);	
}

void about_license_type ( g2cWidget *widget )
{
gchar *license_type = NULL;
gchar *license2 = NULL;
gchar *license3 = NULL;

    license_type = g2c_widget_get_property( widget, "license_type");
    license2 = g_strdelimit( license_type, "-", '_' );
    license3 = g_ascii_strup( license2, -1 );
    fprintf( CURRENT_FILE,
          "\tgtk_about_dialog_set_license_type (GTK_ABOUT_DIALOG(gui->%s), GTK_LICENSE_%s );\n",
           widget->name, license3);
    g_free( license3 );
}

void attach_action ( g2cWidget *widget )
{
gchar *action_name = NULL;
gchar *text = NULL;

    action_name = g2c_widget_get_property( widget, "action_name" );
    text = g2c_widget_get_property( widget, "text" );
    if (text == NULL)
        text = g2c_widget_get_property( widget, "label" );
    if (text != NULL) {
        fprintf( CURRENT_FILE,
                "\tgtk_actionable_set_detailed_action_name(GTK_ACTIONABLE(gui->%s), \"%s::%s\");\n",
                widget->name, action_name, text );
    } else {
        /*  no target (default state) can be set for the action  */
        fprintf( CURRENT_FILE,
                "\tgtk_actionable_set_detailed_action_name(GTK_ACTIONABLE(gui->%s), \"%s\");\n",
                widget->name, action_name );
    }
}

void background_rgb ( g2cWidget *widget )
{
gchar *rgb = NULL;
gchar *cell_rgb = NULL;

    g_assert( NULL != widget );
    rgb = g2c_widget_get_property( widget, "background_rgba" );
    if (rgb != NULL) {
    fprintf( CURRENT_FILE,
            "\tgdk_rgba_parse(&rgb_%s, \"%s\");\n",
            widget->name, rgb);
    fprintf( CURRENT_FILE,
            "\tg_object_set(G_OBJECT(gui->%s),\"background-rgba\", &rgb_%s, NULL);\n",
            widget->name, widget->name);
    }  else {
       rgb = g2c_widget_get_property( widget, "cell_background_rgba" );
       if (rgb != NULL ) {
           fprintf( CURRENT_FILE,
                   "\tgdk_rgba_parse(&rgb_%s, \"%s\");\n",
                   widget->name, rgb);
           fprintf( CURRENT_FILE,
                   "\tg_object_set(G_OBJECT(gui->%s),\"cell-background-rgba\", &rgb_%s, NULL);\n",
                   widget->name, widget->name);
       }
    }
}


void cell_background_rgb ( g2cWidget *widget )
{
gchar *rgb = NULL;
gchar *cell_rgb = NULL;

    g_assert( NULL != widget );
//    rgb = g2c_widget_get_property( widget, "background_rgba" );
//    if (rgb != NULL) {
//    fprintf( CURRENT_FILE,
//            "\tgdk_rgba_parse(&rgb_%s, \"%s\");\n",
//            widget->name, rgb);
//    fprintf( CURRENT_FILE,
//            "\tg_object_set(G_OBJECT(gui->%s),\"background-rgba\", &rgb_%s, NULL);\n",
//            widget->name, widget->name);
//    } else {
        rgb = g2c_widget_get_property( widget, "cell_background_rgba" );
        if (rgb != NULL ) {
            fprintf( CURRENT_FILE,
                    "\tgdk_rgba_parse(&rgb_%s, \"%s\");\n",
                    widget->name, rgb);
            fprintf( CURRENT_FILE,
                    "\tg_object_set(G_OBJECT(gui->%s),\"cell-background-rgba\", &rgb_%s, NULL);\n",
                    widget->name, widget->name);
        }
    //}
}

void font_size_scale ( g2cWidget *widget )
{
gchar *size;
gdouble fsize;

    g_assert( NULL != widget );
    size = g2c_widget_get_property( widget, "scale" );
    if (!isnumber(size)) {
        g_message("font size scale not numeric %s for %s id %s\n", size, widget->klass_name, widget->name);
        return;
    }
    fsize = g_ascii_strtod(size, NULL);
    fprintf( CURRENT_FILE,
            "\tg_object_set(G_OBJECT(gui->%s),\"scale\", %6.2f, NULL);\n",
            widget->name, fsize);
}

void font_size_points ( g2cWidget *widget )
{
gchar *size;
gdouble fsize;

    g_assert( NULL != widget );
    size = g2c_widget_get_property( widget, "size_points" );
    if (!isnumber(size)) {
        g_message("font size points not numeric %s for %s id %s\n", size, widget->klass_name, widget->name);
        return;
    }
    fsize = g_ascii_strtod(size, NULL);
    fprintf( CURRENT_FILE,
            "\tg_object_set(G_OBJECT(gui->%s),\"size_points\", %6.2f, NULL);\n",
            widget->name, fsize);
}

void view_column_alignment ( g2cWidget *widget )
{
gchar *size;
gdouble fsize;

    g_assert( NULL != widget );
    size = g2c_widget_get_property( widget, "alignment" );
    if (!isnumber(size)) {
        g_message("column alignment not numeric %s for %s id %s\n", size, widget->klass_name, widget->name);
        return;
    }
    fsize = g_ascii_strtod(size, NULL);
    fprintf( CURRENT_FILE,
            "\tg_object_set(G_OBJECT(gui->%s),\"alignment\", %6.2f, NULL);\n",
            widget->name, fsize);    
}

void volume_button_adjustment ( g2cWidget *widget )
{
gchar *adjustment = NULL;    
    g_assert( NULL != widget );
    adjustment = g2c_widget_get_property( widget, "adjustment" );
    fprintf( CURRENT_FILE,
            "\tgtk_scale_button_set_adjustment (GTK_SCALE_BUTTON(gui->%s), gui->%s);\n",
            widget->name, adjustment);
}

void range_lower_sensitivity( g2cWidget *widget )
{
gchar *sensitivity = NULL; 
gchar *sensitivity1 = NULL; 
    g_assert( NULL != widget );
    
    sensitivity = g2c_widget_get_property( widget, "lower_stepper_sensitivity");
    sensitivity1 = make_enumeral ("GTK_SENSITIVITY", sensitivity);
    fprintf( CURRENT_FILE,
         "\tgtk_range_set_lower_stepper_sensitivity(GTK_RANGE(gui->%s), %s);\n",
         widget->name, sensitivity1);
}

void range_upper_sensitivity( g2cWidget *widget )
{
gchar *sensitivity = NULL; 
gchar *sensitivity1 = NULL; 
    g_assert( NULL != widget );
  
    sensitivity = g2c_widget_get_property( widget, "upper_stepper_sensitivity");
    sensitivity1 = make_enumeral ("GTK_SENSITIVITY", sensitivity);
    fprintf( CURRENT_FILE,
         "\tgtk_range_set_upper_stepper_sensitivity(GTK_RANGE(gui->%s), %s);\n",
         widget->name, sensitivity1);
}

void scale_button_icons ( g2cWidget *widget )
{
gchar *icons = NULL; 
gchar *list_icons = NULL;
guint i = 0;

    g_assert( NULL != widget );
    icons = g2c_widget_get_property( widget, "icons" );   
    list_icons = g_strdelimit( icons, "\n", ':' );    
    fprintf( CURRENT_FILE,
            "\tgtk_scale_button_set_icons(GTK_SCALE_BUTTON(gui->%s), (const gchar **) g_strsplit(\"%s\", \":\", -1));\n",
            widget->name, list_icons);
    
}

void flowbox_selection_mode( g2cWidget *widget )
{
    gchar *mode = NULL;
    gchar *enum_mode = NULL;
    
    mode = g2c_widget_get_property( widget, "selection_mode" );
    enum_mode = make_enumeral("GTK_SELECTION", mode);
    fprintf( CURRENT_FILE,
        "\tgtk_flow_box_set_selection_mode(GTK_FLOW_BOX(gui->%s),  %s);\n",  
            widget->name,enum_mode);
    g_free( enum_mode );    
}

void listbox_selection_mode ( g2cWidget *widget )
{
    gchar *mode = NULL;
    gchar *enum_mode = NULL;
    
    mode = g2c_widget_get_property( widget, "selection_mode" );
    enum_mode = make_enumeral("GTK_SELECTION", mode);
    fprintf( CURRENT_FILE,
        "\tgtk_list_box_set_selection_mode(GTK_LIST_BOX(gui->%s),  %s);\n",  
            widget->name,enum_mode);
    g_free( enum_mode );
}

void iconview_selection_mode ( g2cWidget *widget )
{
    gchar *mode = NULL;
    gchar *enum_mode = NULL;
    
    mode = g2c_widget_get_property( widget, "selection_mode" );
    enum_mode = make_enumeral("GTK_SELECTION", mode);
    fprintf( CURRENT_FILE,
        "\tgtk_icon_view_set_selection_mode(GTK_ICON_VIEW(gui->%s),  %s);\n",  
            widget->name,enum_mode);
    g_free( enum_mode );
}

void volume_button_size ( g2cWidget *widget )
{
gchar *size = NULL; 
gchar *size_name = NULL;

    g_assert( NULL != widget );
    size = g2c_widget_get_property( widget, "size" ); 
    if (size == NULL) {
        size_name = g_strdup("GTK_ICON_SIZE_SMALL_TOOLBAR");
    } else {
        size_name = make_enumeral("GTK_ICON_SIZE", size);
    }
    fprintf( CURRENT_FILE,
            "\tg_object_set(G_OBJECT(gui->%s),\"size\", %s, NULL);\n",
            widget->name, size_name);
}

void foreground_rgb ( g2cWidget *widget )
{
gchar *rgb = NULL;

    g_assert( NULL != widget );
    rgb = g2c_widget_get_property( widget, "foreground_rgba" );
    if (NULL != rgb) {
        fprintf( CURRENT_FILE,
                "\tgdk_rgba_parse(&%s_rgb, \"%s\");\n",
                widget->name, rgb);
        fprintf( CURRENT_FILE,
                "\tg_object_set(G_OBJECT(gui->%s),\"foreground-rgba\", &%s_rgb, NULL);\n",
                widget->name, widget->name);
    }     
}

void strikethrough_rgb( g2cWidget *widget )
{
gchar *strgb = NULL;

    strgb = g2c_widget_get_property( widget, "strikethrough_rgba" );
    if (NULL != strgb) {
        fprintf( CURRENT_FILE,
                "\tgdk_rgba_parse(&%s_strgb, \"%s\");\n",
                widget->name, strgb);
        fprintf( CURRENT_FILE,
                "\tg_object_set(G_OBJECT(gui->%s),\"strikethrough-rgba\",\n"
                "\t\t\t&%s_strgb, NULL);\n",
                widget->name, widget->name);
    }
}

void underline_rgb( g2cWidget *widget )
{
gchar *ulrgb = NULL;

    ulrgb = g2c_widget_get_property( widget, "underline_rgba" );
    if (NULL != ulrgb) {
        fprintf( CURRENT_FILE,
                "\tgdk_rgba_parse(&%s_ulrgb, \"%s\");\n",
                widget->name, ulrgb);
        fprintf( CURRENT_FILE,
                "\tg_object_set(G_OBJECT(gui->%s),\"underline-rgba\",\n"
                "\t\t\t&%s_ulrgb, NULL);\n",
                widget->name, widget->name);
    }

}

void paragraph_background_rgb( g2cWidget *widget )
{
gchar *pbrgb = NULL;

    pbrgb = g2c_widget_get_property( widget, "paragraph_background_rgba" );
    if (NULL != pbrgb) {
        fprintf( CURRENT_FILE,
                "\tgdk_rgba_parse(&%s_pbrgb, \"%s\");\n",
                widget->name, pbrgb);
        fprintf( CURRENT_FILE,
                "\tg_object_set(G_OBJECT(gui->%s),\"paragraph-background-rgba\",\n"
                "\t\t\t&%s_pbrgb, NULL);\n",
                widget->name, widget->name);
    }
}

void baseline_position ( g2cWidget *widget )
{
gchar *position;
gchar *szposition = NULL;

   g_assert( NULL != widget );
   position = g2c_widget_get_property( widget, "baseline_position" );
   if (position == NULL ) {
	   szposition = g_strdup("GTK_BASELINE_POSITION_CENTER");
   } else {
	   szposition = make_enumeral("GTK_BASELINE_POSITION", position);
   }
   fprintf( CURRENT_FILE,
          "\tgtk_box_set_baseline_position (GTK_BOX(gui->%s), %s);\n",
          widget->name, szposition);
 
   g_free( szposition );
}

void bin_label_handler( g2cWidget *widget )
{
  gchar * action = NULL;
  gchar *accel_group = NULL;
  gchar *mask = NULL;

  g_assert( NULL != widget );

  if ( g_type_is_a( widget->klass, GTK_TYPE_BUTTON ) )
    {
      action = g_strdup( "clicked" );
    }
  else if ( g_type_is_a( widget->klass, GTK_TYPE_MENU_ITEM ) )
    {
      action = g_strdup( "activate_item" );
    }

  if ( ( NULL != widget->parent ) &&
       g_type_is_a( widget->parent->klass, GTK_TYPE_MENU ) )
    {
      accel_group = g_strdup_printf( "%s_accel_group", widget->parent->name );
      mask = g_strdup( "0" );
    }
  else
    {
      accel_group = g_strdup( "accel_group" );
      mask = g_strdup( "GDK_MOD1_MASK" );
    }

  /* Option menus don't have accelerators! */
  if ( ( NULL != widget->parent ) &&
       ( NULL != widget->parent->parent ) &&
       !g_type_is_a( widget->parent->parent->klass, GTK_TYPE_COMBO_BOX_TEXT ) )
    {
      if ( g2c_widget_get_property( widget, "stock_pixmap" ) == NULL )
        {
          gchar * str = g2c_widget_get_property( widget, "label" );

          str = g2c_stringify( str );

          fprintf( CURRENT_FILE,
                   "\tgtk_widget_add_accelerator (GTK_WIDGET (gui->%s), \"%s\", \n"
                   "\t                             gui->%s, %s_key, %s, 0);\n",
                   widget->name,
                   action,
                   accel_group,
                   widget->name,
                   mask );

          g_free( str );
        }
    }

  if ( NULL != action ) g_free( action );
  if ( NULL != accel_group ) g_free( accel_group );
  if ( NULL != mask ) g_free( mask );
}

void
calendar_set_display_options( g2cWidget *widget )
{
  gchar * option_names[ 5 ] = { "GTK_CALENDAR_SHOW_HEADING",
                                "GTK_CALENDAR_SHOW_DAY_NAMES",
                                "GTK_CALENDAR_NO_MONTH_CHANGE",
                                "GTK_CALENDAR_SHOW_WEEK_NUMBERS",
                                "GTK_CALENDAR_WEEK_START_MONDAY" };
  gchar **options = NULL;
  gchar *option_string = NULL;
  guint i = 0;

  g_assert( NULL != widget );

  options = g_new0( gchar*, 6 );

  if ( g2c_get_bool( g2c_widget_get_property( widget, "show_headings" ) ) )
    options[ i++ ] = g_strdup( option_names[ 0 ] );

  if ( g2c_get_bool( g2c_widget_get_property( widget, "show_day_names" ) ) )
    options[ i++ ] = g_strdup( option_names[ 1 ] );

  if ( g2c_get_bool( g2c_widget_get_property( widget, "no_month_change" ) ) )
    options[ i++ ] = g_strdup( option_names[ 2 ] );

  if ( g2c_get_bool( g2c_widget_get_property( widget, "show_week_numbers" ) ) )
    options[ i++ ] = g_strdup( option_names[ 3 ] );

  if ( g2c_get_bool( g2c_widget_get_property( widget, "week_start_monday" ) ) )
    options[ i++ ] = g_strdup( option_names[ 4 ] );

  if ( i > 0 )
    option_string = g_strjoinv( " |\n\t                              ", ( gchar** ) options );
  else
    option_string = g_strdup( "" );

  fprintf( CURRENT_FILE,
           "\tgtk_calendar_display_options (GTK_CALENDAR (gui->%s),\n"
           "\t                              %s);\n",
           widget->name,
           option_string );

  g_free( option_string );
  g_strfreev( options );
}

void 
colour_chooser_rgba ( g2cWidget *widget )
{
gchar *rgba = NULL;
gchar *alpha = NULL;

    g_assert( NULL != widget );
    rgba = g2c_widget_get_property( widget, "rgba" );
    alpha = g2c_widget_get_property( widget, "alpha" );
    
    fprintf( CURRENT_FILE, "\tGdkRGBA %s_colour;\n", widget->name);
    fprintf( CURRENT_FILE,
            "\tgdk_rgba_parse(&%s_colour, \"%s\");\n", widget->name, rgba);
    if (alpha != NULL) 
        fprintf( CURRENT_FILE, "\t%s_colour.alpha = %s / 65535;\n", widget->name, alpha);
    fprintf( CURRENT_FILE,
           "\tgtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER(gui->%s), &%s_colour);\n",
            widget->name, widget->name);
}

void scrolled_window_placement ( g2cWidget *widget )
{
gchar *placement = NULL;
gchar *placename = NULL;

    g_assert( NULL != widget );
    placement = g2c_widget_get_property( widget, "window_placement" ) ;
    g_assert( placement != NULL);
    placename = g_strdup_printf("%s_%s", "GTK_CORNER", 
            g_strdelimit(g_utf8_strup (placement, strlen(placement)),":-", '_' ) );
    fprintf( CURRENT_FILE,
         "\tgtk_scrolled_window_set_placement (GTK_SCROLLED_WINDOW(gui->%s), %s);\n",
           widget->name,
           placename);
}

gchar *
make_icon_size_enumeral(gchar *strsize) 
{
guint size;
gchar * size_names[ 7 ] = { "GTK_ICON_SIZE_INVALID", 
                            "GTK_ICON_SIZE_MENU",
                            "GTK_ICON_SIZE_SMALL_TOOLBAR",
                            "GTK_ICON_SIZE_LARGE_TOOLBAR",
                            "GTK_ICON_SIZE_BUTTON",
                            "GTK_ICON_SIZE_DND",
                            "GTK_ICON_SIZE_DIALOG"  };
    if (strsize == NULL) {
        return size_names[ 4 ];  // default is BUTTON
    }
    size = atoi(strsize);
    if (size > 6 )  {    
        return size_names[ 0 ];
    }
    return size_names[ size ];
}
void 
set_gtk_button_box_style( g2cWidget *widget )
{
gchar * style_names[ 6 ] = { "GTK_BUTTONBOX_SPREAD",
                             "GTK_BUTTONBOX_EDGE",
                             "GTK_BUTTONBOX_START",
                             "GTK_BUTTONBOX_END",
                             "GTK_BUTTONBOX_CENTER",
                             "GTK_BUTTONBOX_EXPAND"  };
gchar * style_keys[ 6 ]  = { "spread",
                             "edge",
                             "start",
                             "end",
                             "center",
                             "expand"  };
gchar *layout = NULL;
gchar *style = NULL;
guint i;
   g_assert( NULL != widget );
   //
   layout = g2c_widget_get_property( widget, "layout_style" ) ;
   g_assert( layout != NULL);
   for (i = 0; i < 6; i++) {
       if (strcmp(style_keys[i], layout) == 0) {
           style = strdup(style_names[i]);
           break;
       }
   }
   if (style == NULL) return;
   fprintf( CURRENT_FILE,
         "\tgtk_button_box_set_layout (gui->%s, %s);\n",
           widget->name,
           style);
}

void set_popover_position ( g2cWidget *widget )
{
gchar *position = NULL;
gchar *postype = NULL;
    position = g2c_widget_get_property( widget, "position" ) ;
    if (position == NULL)  return;
	postype = make_enumeral("GTK_POS", position);
    fprintf( CURRENT_FILE,
            "\tgtk_popover_set_position(GTK_POPOVER(gui->%s), %s);\n",
            widget->name, postype);
    g_free( postype );
}

void set_menu_button_direction ( g2cWidget *widget )
{
gchar *direction = NULL;
gchar *button_dir = NULL;
    direction = g2c_widget_get_property( widget, "direction" ) ;
    if (direction == NULL)  return;
    button_dir = make_enumeral("GTK_ARROW", direction);
    fprintf( CURRENT_FILE,
            "\tgtk_menu_button_set_direction(GTK_MENU_BUTTON(gui->%s), %s);\n",
            widget->name, button_dir);
    g_free( button_dir );
}

void text_tag_direction( g2cWidget *widget )
{
gchar *direction = NULL;
gchar *text_dir = NULL;
    direction = g2c_widget_get_property( widget, "direction" ) ;
    if (direction == NULL)  return;
    text_dir = make_enumeral("GTK_TEXT_DIR", direction);
    fprintf( CURRENT_FILE,
            "\tg_object_set(G_OBJECT(gui->%s), \"direction\", %s, NULL);\n",
            widget->name, text_dir);  
    g_free( text_dir );
}

void text_tag_justification( g2cWidget *widget )
{
gchar *justify = g2c_widget_get_property( widget, "justification" );
gchar *justenum = NULL;
    
    justenum = make_enumeral("GTK_JUSTIFY", justify);
    fprintf( CURRENT_FILE,
            "\tg_object_set(G_OBJECT(gui->%s), \"justification\", %s, NULL);\n",
            widget->name, justenum); 
    g_free( justenum );
}

void 
toolbar_style ( g2cWidget *widget )
{
gchar *value = NULL;
gchar *style = NULL;

   g_assert( NULL != widget );
   
   value = g2c_widget_get_property( widget, "toolbar_style" ) ;
   //style = g_strdup_printf("%s_%s", "GTK_TOOLBAR", g_strdelimit(g_utf8_strup (value, strlen(value)),":-", '_' ) );
   style = make_enumeral("GTK_TOOLBAR", value);
   if (widget->klass == GTK_TYPE_TOOLBAR) {
       fprintf( CURRENT_FILE,
          "\tgtk_toolbar_set_style (GTK_TOOLBAR(gui->%s), %s);\n",
            widget->name, style);
   } else if (widget->klass == GTK_TYPE_TOOL_PALETTE){
        fprintf( CURRENT_FILE,
              "\tgtk_tool_palette_set_style (GTK_TOOL_PALETTE(gui->%s), %s);\n",
                widget->name, style);
   } else {
       g_message("Unexpected toolbar_style for %s %s\n", widget->klass_name, widget->name);
   }
   
}

void 
text_buffer_text ( g2cWidget *widget )
{
  gchar *result = NULL;
  gchar *temp = NULL;
  gchar  **lines    = NULL;
  guint i = 0;
  gchar *text =  g2c_widget_get_property( widget, "text" );
  
   if (has_newline(text)) {
          /*  deal with multi-line strings */
         lines = g_strsplit( text, "\n", 0 ); 
         while( NULL != lines[i] )
          {             
             if (strlen(lines[i]) > 0) {
                 temp = g_strdup_printf("\"%s\\n\"", lines[i]);
                 fprintf( CURRENT_FILE,
                     "\tgtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER (gui->%s), %s, -1);\n",
                      widget->name, temp );               
             }             
             i++;
          }              
         g_strfreev( lines );         
    } else {
       fprintf( CURRENT_FILE,
         "\tgtk_text_buffer_set_text (GTK_TEXT_BUFFER (gui->%s), %s, -1);\n",
               widget->name, g2c_stringify(text));
    }
}

void text_view_wrap( g2cWidget *widget )
{
gchar *wrap_mode = NULL;
gchar *wrap_enum = NULL;
 
    wrap_mode = g2c_widget_get_property( widget, "wrap_mode" );
    wrap_enum = make_enumeral( "GTK_WRAP", wrap_mode );
    fprintf( CURRENT_FILE,
            "\tgtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(gui->%s), %s);\n",
             widget->name,
             wrap_enum);
    g_free( wrap_enum );
}

void infobar_message_type( g2cWidget *widget )
{
gchar *message_type = NULL;
gchar *message_enum = NULL;

    message_type = g2c_widget_get_property( widget, "message_type" );
    message_enum = make_enumeral("GTK_MESSAGE", message_type);
    fprintf( CURRENT_FILE,
            "\tgtk_info_bar_set_message_type(GTK_INFO_BAR(gui->%s), %s);\n",
            widget->name,
            message_enum);
    g_free( message_enum );
}

void input_hints( g2cWidget *widget )
{
gchar * hintlist = NULL;
gchar * func_name = NULL;
gchar * caps_name = NULL;

    hintlist = g2c_widget_get_property( widget, "input_hints");
	func_name = g2c_transform_name ( widget->klass_name, NT_FUNCTION ); 
	caps_name = g_utf8_strup (func_name, strlen(func_name)); 
    if (  ( strcmp( widget->klass_name, "GtkEntry"   ) == 0 )  ||
          ( strcmp( widget->klass_name, "GtkTextView" ) == 0 ) )  {
        fprintf( CURRENT_FILE,
               "\t%s_set_input_hints (%s (gui->%s), %s);\n",
			    func_name,
				caps_name,
                widget->name,			    
                hintlist );   
    } else {
        g_message("Unexpected input hints for widget %s\n", widget->name);
    }
}

void input_purpose( g2cWidget *widget )
{
gchar * purpose = NULL;
gchar * purpose_enum = NULL;
gchar * func_name = NULL;
gchar * caps_name = NULL;

    purpose = g2c_widget_get_property( widget, "input_purpose");
    func_name = g2c_transform_name ( widget->klass_name, NT_FUNCTION ); 
    caps_name = g_utf8_strup (func_name, strlen(func_name)); 
    purpose_enum = make_enumeral("GTK_INPUT_PURPOSE", purpose);
    if (  ( strcmp( widget->klass_name, "GtkEntry"   ) == 0 )  ||
          ( strcmp( widget->klass_name, "GtkTextView" ) == 0 ) )  {
        fprintf( CURRENT_FILE,
               "\t%s_set_input_purpose (%s (gui->%s), %s);\n",
		func_name,
		caps_name,
                widget->name,			    
                purpose_enum );   
    } else {
        g_message("Unexpected input purpose for widget %s\n", widget->name);
    }    
}

void
label_use_markup( g2cWidget *widget )
{
gchar * label = NULL;
//gchar * func_name = NULL;
//gchar * caps_name = NULL;
gboolean markup = FALSE;
gboolean underline = FALSE;

    g_assert( NULL != widget );
    markup = g2c_get_bool(g2c_widget_get_property( widget, "use_markup" ));
    g_assert( TRUE == markup );   
	//func_name = g2c_transform_name ( widget->klass_name, NT_FUNCTION ); 
	//caps_name = g_utf8_strup (func_name, strlen(func_name)); 	
    underline = g2c_get_bool(g2c_widget_get_property( widget, "use_underline" ));
    label = g2c_stringify( g2c_widget_get_property( widget, "label" ) );  
    if (underline == FALSE)  {  
        fprintf( CURRENT_FILE,
                   "\tgtk_label_set_markup (GTK_LABEL(gui->%s), %s);\n",
                   widget->name,
                   label );  
    } else {
        fprintf( CURRENT_FILE,
                   "\tgtk_label_set_markup_with_mnemonic (GTK_LABEL(gui->%s), %s);\n",			   				   
                   widget->name,
                   label ); 
        fprintf( CURRENT_FILE,
                   "\tgtk_label_set_use_underline (GTK_LABEL(gui->%s), TRUE);\n",				   
                   widget->name ); 
    }
    //  This function will set the “use-markup” property to True as a side effect.
    g_free( label );
}

void label_label_wrap ( g2cWidget *widget )
{
gchar *wrap_mode = NULL;
gchar *wrap_enum = NULL;
 
    wrap_mode = g2c_widget_get_property( widget, "wrap_mode" );
    wrap_enum = make_enumeral( "PANGO_WRAP", wrap_mode );
    fprintf( CURRENT_FILE,
            "\tgtk_label_set_line_wrap_mode(GTK_LABEL(gui->%s), %s);\n",
             widget->name,
             wrap_enum);
    g_free( wrap_enum );    
}

void 
notebook_packing( g2cWidget *widget, g2cWidget *box_widget )
{
gchar *str     = NULL;
gchar *formstr = NULL;

  g_assert( NULL != widget );
  
  if (widget->packing.tab.tab_fill == FALSE)
    fprintf( CURRENT_FILE,
               "\tgtk_container_child_set (GTK_CONTAINER(gui->%s), GTK_WIDGET(gui->%s),"
                "\"tab_fill\", %s, NULL);\n",
                widget->parent->name,
                widget->name,
                g2c_get_bool_b(widget->packing.tab.tab_fill) ); 
  
  if (widget->packing.tab.tab_expand ==  TRUE) 
    fprintf( CURRENT_FILE,
               "\tgtk_container_child_set (GTK_CONTAINER(gui->%s), GTK_WIDGET(gui->%s),"
                "\"tab_expand\", %s, NULL);\n",
                widget->parent->name,
                widget->name,
                g2c_get_bool_b(widget->packing.tab.tab_expand) ); 
  
  if (widget->packing.tab.reorderable == TRUE)
     fprintf( CURRENT_FILE,
               "\tgtk_container_child_set (GTK_CONTAINER(gui->%s), GTK_WIDGET(gui->%s),"
                "\"reorderable\", %s, NULL);\n",
                widget->parent->name,
                widget->name,
                g2c_get_bool_b(widget->packing.tab.reorderable) );  
  
  if (widget->packing.tab.detachable == TRUE)
    fprintf( CURRENT_FILE,
               "\tgtk_container_child_set (GTK_CONTAINER(gui->%s), GTK_WIDGET(gui->%s),"
                "\"detachable\", %s, NULL);\n",
                widget->parent->name,
                widget->name,
                g2c_get_bool_b(widget->packing.tab.detachable) );  
  
  if ( (box_widget != NULL) && 
       (widget->packing.tab.menu_label != NULL) ) {      
     fprintf( CURRENT_FILE,
             "\tgtk_notebook_set_menu_label_text (gui->%s,"
             "GTK_WIDGET (gui->%s),"
             "%s);\n",
             widget->parent->name,
             box_widget->name,
             g2c_stringify(widget->packing.tab.menu_label ) );  
  }
}

void 
menu_label( g2cWidget *widget )
{
gchar * label = NULL;
gchar * stock = NULL;
   g_assert( NULL != widget ); 
   label = g2c_widget_get_property( widget, "label");
   stock = g2c_widget_get_property( widget, "use_stock");
   if (stock != NULL) {
       fprintf( CURRENT_FILE,
               "\tgui->%s = (%s*) gtk_menu_item_new();\n",
               widget->name, widget->klass_name);
       return;
   }
   if (label == NULL) {
       fprintf( CURRENT_FILE,
               "\tgui->%s = (%s*) gtk_menu_item_new();\n",
               widget->name, widget->klass_name);
       return;
   }
   if (has_underscore(label) == FALSE)  {
       fprintf( CURRENT_FILE,
               "\tgui->%s = (%s*) gtk_menu_item_new_with_label(%s);\n",
               widget->name, widget->klass_name, 
               g2c_stringify(label) );
   } else {
       fprintf( CURRENT_FILE,
               "\tgui->%s = (%s*) gtk_menu_item_new_with_mnemonic(%s);\n",
               widget->name, widget->klass_name, 
               g2c_stringify(label) );
   }
}

void entry_markup ( g2cWidget *widget )
{
gchar *markup = NULL;

        g_assert( NULL != widget );
        markup = g2c_widget_get_property( widget, "primary_icon_tooltip_markup"); 
        g_assert ( NULL != markup );           
        fprintf( CURRENT_FILE,
                   "\tgtk_entry_set_icon_tooltip_markup(GTK_ENTRY(gui->%s),GTK_ENTRY_ICON_PRIMARY,%s);\n",
                   widget->name,g2c_stringify(g_strdelimit(markup,"\"",'\'')));
}

void entry_markup2 ( g2cWidget *widget )
{
gchar *markup = NULL;

        g_assert( NULL != widget );
        markup = g2c_widget_get_property( widget, "secondary_icon_tooltip_markup");                     
        g_assert ( NULL != markup );    
        fprintf( CURRENT_FILE,
                   "\tgtk_entry_set_icon_tooltip_markup(GTK_ENTRY(gui->%s),GTK_ENTRY_ICON_SECONDARY,%s);\n",
                   widget->name,g2c_stringify(g_strdelimit(markup,"\"",'\'')));
}

void common_events ( g2cWidget *widget )
{
gchar *events = NULL;
//gchar * func_name = NULL;
//gchar * caps_name = NULL;

        g_assert( NULL != widget );
        events = g2c_widget_get_property( widget, "events");
		//func_name = g2c_transform_name ( widget->klass_name, NT_FUNCTION ); 
		//caps_name = g_utf8_strup (func_name, strlen(func_name)); 
		fprintf( CURRENT_FILE,
				   "\tgtk_widget_set_events(GTK_WIDGET(gui->%s),%s);\n",				   
				   widget->name, events);
	
}

void common_tooltip_markup ( g2cWidget *widget )
{
gchar *markup = NULL;
        g_assert( NULL != widget );
        markup = g2c_widget_get_property( widget, "tooltip_markup");
        /* convert double quotes in markup to single quotes */
        if (strcmp(widget->klass_name,"GtkStatusIcon") == 0) {
            fprintf( CURRENT_FILE,
                       "\tgtk_status_icon_set_tooltip_markup(GTK_STATUS_ICON(gui->%s),%s);\n",
                       widget->name,g2c_stringify( g_strdelimit(markup,"\"",'\'') ));
        } else {        
            fprintf( CURRENT_FILE,
                       "\tgtk_widget_set_tooltip_markup(GTK_WIDGET(gui->%s),%s);\n",
                       widget->name,g2c_stringify( g_strdelimit(markup,"\"",'\'') ));
        }
}

void message_dialog_secondary_text ( g2cWidget *widget )
{
gchar *text = NULL;
gchar *markup = NULL;
        g_assert( NULL != widget );
        text = g2c_widget_get_property( widget, "secondary_text");
        markup = g2c_widget_get_property( widget, "secondary_use_markup" );
        if (markup == NULL) {
            fprintf( CURRENT_FILE,
            "\tgtk_message_dialog_format_secondary_text ( GTK_MESSAGE_DIALOG(gui->%s), %s);\n",
                    widget->name, g2c_stringify(text) );
        } else {
            fprintf( CURRENT_FILE,
            "\tgtk_message_dialog_format_secondary_markup ( GTK_MESSAGE_DIALOG(gui->%s), %s);\n",
                    widget->name, g2c_stringify(g_strdelimit(text,"\"",'\'')) );
        }
}

void 
button_label( g2cWidget *widget )
{
gchar * stock = NULL;
gchar * str = NULL;
gboolean underline = FALSE;

  g_assert( NULL != widget );
  
  stock = g2c_widget_get_property( widget, "use_stock");
  underline = g2c_get_bool(g2c_widget_get_property( widget, "use_underline" ));  
  if (stock != NULL) {
      if (g_ascii_strcasecmp(stock, "TRUE") == 0) {
          /*  Must have a null label for stock image to work properly */
          str = remove_prefix(g2c_widget_get_property( widget, "label" ));            
          fprintf( CURRENT_FILE,
             "\tgtk_button_set_label (GTK_BUTTON (gui->%s), %s);\n",
             widget->name, g2c_stringify(str ) );         
          g_free (str );
          return;
      }
  }  else { 
      fprintf( CURRENT_FILE,
           "\tgtk_button_set_label (GTK_BUTTON (gui->%s), \"%s\");\n",
           widget->name, g2c_widget_get_property( widget, "label" ) );
  }
   if (underline == TRUE) {
      fprintf( CURRENT_FILE,
         "\tgtk_button_set_use_underline(GTK_BUTTON (gui->%s), TRUE);\n",
            widget->name);  
   }
}

void 
button_relief ( g2cWidget *widget )
{
  gchar * str = NULL;
  gchar * relief = NULL;
  g_assert( NULL != widget ); 
  str = g2c_widget_get_property( widget, "relief" );
  if (str == NULL) return;
  relief = g_strdup_printf("GTK_RELIEF_%s", g_ascii_strup(str, strlen(str)));
  fprintf( CURRENT_FILE,
           "\tgtk_button_set_relief(GTK_BUTTON(gui->%s),%s );\n",
          widget->name, relief);
  g_free( relief );
}

void 
dialog_type_hint ( g2cWidget *widget )
{
  gchar * str = NULL;
  gchar * hint = NULL;
  g_assert( NULL != widget ); 
  str = g2c_widget_get_property( widget, "type_hint" );
  g_assert( NULL == widget->parent );
  if (str == NULL) return;
  hint = g_strdup_printf("GDK_WINDOW_TYPE_HINT_%s", g_ascii_strup(str, strlen(str)));
  fprintf( CURRENT_FILE,
           "\tgtk_window_set_type_hint(GTK_WINDOW(gui->%s),%s );\n",
          widget->name, hint);
  g_free( hint ); 
}

void dialog_transient( g2cWidget *widget )
{
gchar *transient = NULL;
gchar *type_name = NULL;
    g_assert( NULL != widget ); 
    transient = g2c_widget_get_property( widget, "transient_for" ); 
    type_name = g2c_transform_name( CURRENT_PROJECT->main_widget->name, NT_TYPENAME );
    if ( strcmp( CURRENT_PROJECT->main_widget->name, transient ) == 0 )
        fprintf( CURRENT_FILE,
                "\tgtk_window_set_transient_for (GTK_WINDOW(gui->%s), GTK_WINDOW(((%s *) owner)->gui->%s));\n",
                widget->name, type_name, transient);
    else {
        fprintf( CURRENT_FILE,
                "\tgtk_window_set_transient_for (GTK_WINDOW(gui->%s), GTK_WINDOW(((%s *) owner)->%sgui->%s));\n",
                widget->name, type_name, transient, transient);     
    }
    g_free(  type_name );
}

void file_chooser_filter( g2cWidget *widget )
{
gchar *filter = NULL;
gchar *type_name = NULL;
g2cWidget *top_widget = NULL;
gboolean sibling = FALSE;
    g_assert( NULL != widget ); 
    filter = g2c_widget_get_property( widget, "filter" ); 
    type_name = g2c_transform_name( CURRENT_PROJECT->main_widget->name, NT_TYPENAME );
    top_widget = g2c_widget_get_top_parent(widget);
    sibling = is_in_widget_list(top_widget->associates, filter);
    
    if ( (strcmp(widget->klass_name,"GtkRecentChooserDialog") == 0) ||
         (strcmp(widget->klass_name,"GtkRecentChooserWidget") == 0) )  {
        if (sibling == TRUE) {
            fprintf( CURRENT_FILE,
                    "\tgtk_recent_chooser_set_filter (GTK_RECENT_CHOOSER(gui->%s), GTK_RECENT_FILTER(gui->%s));\n",
                    widget->name, filter);
        } else {
            fprintf( CURRENT_FILE,
                    "\tgtk_recent_chooser_set_filter (GTK_RECENT_CHOOSER(gui->%s), GTK_RECENT_FILTER(((%s *) owner)->gui->%s));\n",
                    widget->name, type_name, filter);
        }
    } else if ( (strcmp(widget->klass_name,"GtkFileChooserDialog") == 0) ||
                (strcmp(widget->klass_name,"GtkFileChooserWidget") == 0) ||
                (strcmp(widget->klass_name,"GtkFileChooserButton") == 0) ) {  
        if (sibling == TRUE) {
            fprintf( CURRENT_FILE,
                    "\tgtk_file_chooser_set_filter (GTK_FILE_CHOOSER (gui->%s), GTK_FILE_FILTER(gui->%s));\n",            
                    widget->name, filter);
        } else {
            fprintf( CURRENT_FILE,
                    "\tgtk_file_chooser_set_filter (GTK_FILE_CHOOSER (gui->%s), GTK_FILE_FILTER(((%s *) owner)->gui->%s));\n",            
                    widget->name, type_name, filter);
        }
    } else {
        g_message("*** Invalid class for filter: %s\n", widget->name);
    }
    g_free(  type_name );    
}

void 
frame_label_xalign ( g2cWidget *widget )
{
gchar * xalign = NULL;
gchar * yalign = NULL;

  g_assert( NULL != widget ); 
  xalign = round_float( g2c_widget_get_property( widget, "label_xalign" ) );
  yalign = round_float( g2c_widget_get_property( widget, "label_yalign" ) );
  
  if (yalign == NULL) yalign = g_strdup("1.0");
  fprintf( CURRENT_FILE,
           "\tgtk_frame_set_label_align (GTK_FRAME(gui->%s), %s, %s);\n",
          widget->name, xalign, yalign);
    
}

void 
frame_label_yalign ( g2cWidget *widget )
{
gchar * xalign = NULL;
gchar * yalign = NULL;

  g_assert( NULL != widget ); 
  xalign = round_float( g2c_widget_get_property( widget, "label_xalign" ) );
  if (xalign != NULL) return;
  xalign = g_strdup("0.0");
  yalign = round_float( g2c_widget_get_property( widget, "label_yalign" ) );  
  
  fprintf( CURRENT_FILE,
           "\tgtk_frame_set_label_align (GTK_FRAME(gui->%s), %s, %s);\n",
          widget->name, xalign, yalign);
    
}

void
label_label_justify( g2cWidget *widget )
{
gchar * str = NULL;
gchar * just = NULL;

    g_assert( NULL != widget );
    
    str = g2c_widget_get_property( widget, "justify" );
    if (str == NULL) return;
    just = g_strdup_printf("GTK_JUSTIFY_%s", g_ascii_strup(str, strlen(str)));
    fprintf( CURRENT_FILE,
           "\tgtk_label_set_justify (GTK_LABEL(gui->%s), %s);\n",
           widget->name,  just);
    g_free( just );
}

void
label_label_align( g2cWidget *widget )
{
gchar * str = NULL;
gchar * just = NULL;

    g_assert( NULL != widget );
    
    str = g2c_widget_get_property( widget, "halign" );
    if (str == NULL) return;
    just = g_strdup_printf("GTK_ALIGN_%s", g_ascii_strup(str, strlen(str)));
    fprintf( CURRENT_FILE,
           "\tgtk_widget_set_halign (GTK_WIDGET(gui->%s), %s);\n",
           widget->name,  just);
    g_free( just );    
}

void 
label_label_ellipsize ( g2cWidget *widget )
{
gchar * str = NULL;
gchar * ellipsize = NULL;

    g_assert( NULL != widget );
    
    str = g2c_widget_get_property( widget, "ellipsize" );
    if (str == NULL) return;
	ellipsize = make_enumeral("PANGO_ELLIPSIZE", str);
    fprintf( CURRENT_FILE,
           "\tgtk_label_set_ellipsize (GTK_LABEL(gui->%s), %s);\n",
           widget->name,  ellipsize);
    g_free( ellipsize );     
}

void 
label_ellipsize ( g2cWidget *widget )
{
gchar * str = NULL;
gchar * ellipsize = NULL;
gchar *func_name = NULL;
gchar *caps_name = NULL;

    g_assert( NULL != widget );
    
    str = g2c_widget_get_property( widget, "ellipsize" );
    if (str == NULL) return;
    ellipsize = make_enumeral ("PANGO_ELLIPSIZE", str );    
    func_name = g2c_transform_name ( widget->klass_name, NT_FUNCTION );   /* e.g. gtk_button_box */
    caps_name = g_utf8_strup (func_name, strlen(func_name)); /* e.g. GTK_BUTTON_BOX  */
    fprintf( CURRENT_FILE,
           "\t%s_set_ellipsize (%s(gui->%s), %s);\n",
           func_name, caps_name, widget->name,  ellipsize);
    g_free( ellipsize ); 
	g_free( func_name );  
    g_free( caps_name );    
}

void grab_default ( g2cWidget *widget )
{   /*  makes widget the default widget  requires 'Can default' to be selected. */
gboolean has_default = FALSE;

    g_assert( NULL != widget );
    has_default = g2c_get_bool(g2c_widget_get_property( widget, "has_default" ));
    if ( has_default != TRUE ) return;
	fprintf( CURRENT_FILE,
		"\tgtk_widget_grab_default (GTK_WIDGET(gui->%s));\n",
			widget->name);   
}

void 
icon_size ( g2cWidget *widget )
{
gchar *str = NULL;
gchar *icon_size = NULL;
gchar *func_name = NULL;
gchar *caps_name = NULL;

    g_assert( NULL != widget );
    
    str = g2c_widget_get_property( widget, "icon_size" );
    if (str == NULL) return;    
    icon_size = icon_size_enum(str);    
    func_name = g2c_transform_name(widget->klass_name,NT_FUNCTION);
    caps_name = g_utf8_strup(func_name, strlen(func_name));
    fprintf( CURRENT_FILE,
           "\t%s_set_icon_size (%s(gui->%s), %s);\n",
           func_name, caps_name, widget->name,  icon_size);
    g_free( func_name );  
    g_free( caps_name );
    g_free( icon_size ); 
}


void 
layout_height ( g2cWidget *widget )
{
gchar *height = NULL;
gchar *width  = NULL;

    g_assert( NULL != widget );
    
    height = g2c_widget_get_property( widget, "height" );
    width  = g2c_widget_get_property( widget, "width" );
    g_assert( NULL != height );
    if (width == NULL) {
        fprintf( CURRENT_FILE,
           "\tgtk_layout_set_size (GTK_LAYOUT (gui->%s), 100, %s);\n",
                widget->name, height);
    } else {        
        fprintf( CURRENT_FILE,
            "\tgtk_layout_set_size (GTK_LAYOUT (gui->%s), %s, %s);\n",
                widget->name, width, height);
    }
    
}

void 
layout_width ( g2cWidget *widget )
{
gchar *height = NULL;
gchar *width  = NULL;

    g_assert( NULL != widget );
    
    height = g2c_widget_get_property( widget, "height" );
    if (height != NULL) return;  /* already dealt with in layout_height */
    width  = g2c_widget_get_property( widget, "width" );
    g_assert( NULL != width ); 
    fprintf( CURRENT_FILE,
        "\tgtk_layout_set_size (GTK_LAYOUT (gui->%s), %s, 100);\n",
                widget->name, width);
}

void
tree_selection_mode( g2cWidget *widget )
{
gchar * str = NULL;
gchar * mode = NULL;

    g_assert( NULL != widget );
    
    str = g2c_widget_get_property( widget, "mode" );
    if (str == NULL) return;
    mode = g_strdup_printf("GTK_SELECTION_%s", g_ascii_strup(str, strlen(str)));
    fprintf( CURRENT_FILE,
           "\tgtk_tree_selection_set_mode (GTK_TREE_SELECTION(gui->%s), %s);\n",
           widget->name,  mode);
    g_free( mode );        
}

void 
shadow_type( g2cWidget *widget )
{
gchar * str = NULL;
gchar * mode = NULL;
gchar * klass = NULL;
gchar * func_name = NULL;
gchar * caps_name = NULL;

    g_assert( NULL != widget );
    
    str = g2c_widget_get_property( widget, "shadow_type" );
    if (str == NULL) return;
    mode = make_enumeral ("GTK_SHADOW", str ); 
    if (strcmp(widget->klass_name, "GtkAspectFrame") == 0) {
        klass = g_strdup("GtkFrame");
    } else if (strcmp(widget->klass_name, "GtkPlacesSidebar") == 0) {
        klass = g_strdup("GtkScrolledWindow");
    } else {
        klass = g_strdup(widget->klass_name);
    }
    func_name = g2c_transform_name ( klass, NT_FUNCTION );   /* e.g. gtk_button_box */
    caps_name = g_utf8_strup (func_name, strlen(func_name)); /* e.g. GTK_BUTTON_BOX  */  
    
    fprintf( CURRENT_FILE,
           "\t%s_set_shadow_type (%s(gui->%s), %s);\n",
           func_name, caps_name, widget->name,  mode);
    g_free( mode );    
}

void scale_value_pos( g2cWidget *widget )
{
gchar * str = NULL;
gchar * mode = NULL;

    g_assert( NULL != widget );
    
    str = g2c_widget_get_property( widget, "value_pos" );
    if (str == NULL) return;
    mode = make_enumeral ("GTK_POS", str );
    fprintf( CURRENT_FILE,
           "\tgtk_scale_set_value_pos (GTK_SCALE (gui->%s), %s);\n",
           widget->name,  mode);
    g_free( mode );     
}

void recent_chooser_sort_type( g2cWidget *widget )
{
gchar * sort = NULL;
gchar * mode = NULL;

    g_assert( NULL != widget );
    
    sort = g2c_widget_get_property( widget, "sort_type" );
    if (sort == NULL) return;
    mode = make_enumeral ("GTK_RECENT_SORT", sort );
    fprintf( CURRENT_FILE,
           "\tgtk_recent_chooser_set_sort_type (GTK_RECENT_CHOOSER (gui->%s), %s);\n",
           widget->name,  mode);
    g_free( mode );     
}

void recent_manager_filename( g2cWidget *widget )
{
gchar *filename  = NULL;
gchar *filename2  = NULL;
gchar *filename3  = NULL;

    g_assert( NULL != widget );

    filename = g2c_widget_get_property( widget, "filename" );
    if (filename == NULL) return;
    filename2 = g_strdelimit(filename, "\\", '/');
    filename3 = g_strdelimit(filename2, "\n", ' ');
    fprintf( CURRENT_FILE,
           "\tgtk_recent_manager_add_item (GTK_RECENT_MANAGER (gui->%s), \"%s\");\n",
            widget->name, filename3);
}

void stack_transition( g2cWidget *widget )
{
gchar * str = NULL;
gchar * mode = NULL;

    g_assert( NULL != widget );
    
    str = g2c_widget_get_property( widget, "transition_type" );
    if (str == NULL) return;
    mode = make_enumeral ("GTK_STACK_TRANSITION_TYPE", str );
    fprintf( CURRENT_FILE,
           "\tgtk_stack_set_transition_type (GTK_STACK (gui->%s),\n"
            "\t\t\t%s);\n",
           widget->name,  mode);
    g_free( mode );     
}

void transition_type ( g2cWidget *widget )
{
gchar * str = NULL;
gchar * mode = NULL;

    g_assert( NULL != widget );
    
    str = g2c_widget_get_property( widget, "transition_type" );
    if (str == NULL) return;
    mode = make_enumeral ("GTK_REVEALER_TRANSITION_TYPE", str );
    fprintf( CURRENT_FILE,
           "\tgtk_revealer_set_transition_type (GTK_REVEALER (gui->%s), %s);\n",
           widget->name,  mode);
    g_free( mode ); 
}

void tree_grid_lines ( g2cWidget *widget )
{
gchar *grid_lines = NULL;
gchar *grid_mode = NULL;

    grid_lines = g2c_widget_get_property( widget, "enable_grid_lines" );
    if (grid_lines == NULL) return;
    grid_mode = make_enumeral ("GTK_TREE_VIEW_GRID_LINES", grid_lines );
    fprintf( CURRENT_FILE,
           "\tgtk_tree_view_set_grid_lines (GTK_TREE_VIEW (gui->%s), %s);\n",
           widget->name,  grid_mode);
    g_free( grid_mode );
}

void pack_renderer( g2cWidget *widget )
{
gchar * col_no = NULL;
g2cWidget *column_widget = NULL;

   g_assert( NULL != widget );
   col_no = g2c_widget_get_property( widget, "text" );
   if (col_no == NULL) return;
   column_widget = widget->parent;   
   if (strcmp(column_widget->klass_name, "GtkComboBox") == 0 )
   {
       fprintf( CURRENT_FILE,
           "\tgtk_cell_layout_pack_start(GTK_CELL_LAYOUT(gui->%s), GTK_CELL_RENDERER(gui->%s), TRUE);\n",
           column_widget->name,
           widget->name); 
       fprintf( CURRENT_FILE,
           "\tgtk_cell_layout_add_attribute(GTK_CELL_LAYOUT(gui->%s), GTK_CELL_RENDERER(gui->%s), \"text\", %s);\n",
           column_widget->name,
           widget->name,
           col_no);
       
   } else if (strcmp(column_widget->parent->klass_name, "GtkTreeView") == 0 ) {
   
       fprintf( CURRENT_FILE,
           "\tgtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(gui->%s), GTK_CELL_RENDERER(gui->%s), TRUE);\n",
           column_widget->name,
           widget->name); 
       fprintf( CURRENT_FILE,
           "\tgtk_tree_view_column_add_attribute(GTK_TREE_VIEW_COLUMN(gui->%s), GTK_CELL_RENDERER(gui->%s), \"text\", %s);\n",
           column_widget->name,
           widget->name,
           col_no);
   }
           
}

void popover_submenu( g2cWidget *widget )
{
gchar *submenu = g2c_widget_get_property( widget, "_submenu" );
gchar *popovermenu = widget->parent->name;
gchar *position = g2c_widget_get_property( widget, "_position" );

    fprintf( CURRENT_FILE,
           "\tg_value_init (&%s_submenu, G_TYPE_STRING);\n",
            widget->name);
    fprintf( CURRENT_FILE,
           "\tg_value_set_string(&%s_submenu, \"%s\");\n",
           widget->name, submenu); 
    fprintf( CURRENT_FILE,
           "\tgtk_container_child_set_property(GTK_CONTAINER (gui->%s),\n",
           popovermenu); 
    fprintf( CURRENT_FILE,
           "\t            GTK_WIDGET (gui->%s), \"submenu\", (const GValue *) &%s_submenu);\n",
           widget->name,widget->name); 
    if (position != NULL) {
        fprintf( CURRENT_FILE,
               "\tg_value_init (&%s_submenu_position, G_TYPE_UINT);\n",
                widget->name);
        fprintf( CURRENT_FILE,
               "\tg_value_set_uint(&%s_submenu_position, %s);\n",
               widget->name, position); 
        fprintf( CURRENT_FILE,
               "\tgtk_container_child_set_property(GTK_CONTAINER (gui->%s),\n",
               popovermenu); 
        fprintf( CURRENT_FILE,
               "\t            GTK_WIDGET (gui->%s), \"position\",\n"
               "\t            (const GValue *) &%s_submenu_position);\n",
               widget->name,widget->name); 
    }
}

void pack_combo_box_column( g2cWidget *widget )
{
gchar * col_no = NULL;
g2cWidget *column_widget = NULL;
g2cWidget *combo_box_widget = NULL;

   g_assert( NULL != widget );
   col_no = g2c_widget_get_property( widget, "text" );
   if (col_no == NULL) return;
   column_widget = widget->parent;
   combo_box_widget = column_widget->parent;
   /* gtk_cell_layout_column_pack_start(col, renderer, TRUE);
    * gtk_cell_layout_column_add_attribute(col, renderer, "text", text_value);   */
   fprintf( CURRENT_FILE,
           "\tgtk_cell_layout_pack_start(GTK_CELL_LAYOUT(gui->%s), GTK_CELL_RENDERER(gui->%s), TRUE);\n",
           column_widget->name,
           widget->name); 
   fprintf( CURRENT_FILE,
           "\tgtk_cell_layout_add_attribute(GTK_CELL_LAYOUT(gui->%s), GTK_CELL_RENDERER(gui->%s), \"text\", %s);\n",
           column_widget->name,
           widget->name,
           col_no);
           
}

void 
button_use_stock( g2cWidget *widget )
{
gchar * stock_label = NULL;
gchar * norm_label = NULL;

   g_assert( NULL != widget );
   /*  GtkWidget *image = gtk_image_new_from_icon_name("gtk-select-color" ,GTK_ICON_SIZE_BUTTON);
       gtk_button_set_image(GTK_BUTTON (gui->button), image); */
   stock_label = g2c_widget_get_property( widget, "label" );
   if (stock_label == NULL) {
       g_message("stock button name missing for %s\n", widget->name);
       return;
   }
   fprintf( CURRENT_FILE,
           "\tgui->%simage = gtk_image_new_from_stock(\"%s\" ,GTK_ICON_SIZE_BUTTON);\n",
           widget->name, stock_label);   /* need to compile with -Wno-deprecated-declarations  */
   fprintf( CURRENT_FILE,
           "\tgtk_button_set_image(GTK_BUTTON (gui->%s), GTK_WIDGET(gui->%simage));\n",
           widget->name, widget->name);
   norm_label = remove_prefix(stock_label);
   fprintf( CURRENT_FILE,
           "\tgtk_button_set_label(GTK_BUTTON (gui->%s), \"%s\");\n",
           widget->name, norm_label);
   g_free( norm_label );
}

void menu_anchor_hint( g2cWidget *widget )
{
gchar * anchor_names[ 9 ] = { "GDK_ANCHOR_FLIP_X",
                             "GDK_ANCHOR_FLIP_Y",
                             "GDK_ANCHOR_SLIDE_X",
                             "GDK_ANCHOR_SLIDE_Y",
                             "GDK_ANCHOR_RESIZE_X",
                             "GDK_ANCHOR_RESIZE_Y",
			     "GDK_ANCHOR_FLIP",
			     "GDK_ANCHOR_SLIDE",
			     "GDK_ANCHOR_RESIZE" };
guint anchor_vals[ 9 ]  =  { 1,
                             2,
                             4,
                             8,
                             16,
                             32,
                             3,
                             12,
                             48 };
gchar *hints = NULL;
gchar **hintset = NULL;
guint val = 0;
guint i = 0;
guint j = 0;

    hints = g2c_widget_get_property( widget, "anchor_hints" );
    hintset = g_strsplit( hints, "|", 0 ); 
    while( NULL != hintset [i] ) {
        for (j = 0; j < 9; j++) {
          if (strcmp(anchor_names[j], g_strstrip(hintset[i])) == 0) {
               val |= anchor_vals[j];           
          }
        } 
        i++;
    }
    fprintf( CURRENT_FILE, "\t/*  anchor_hints:  %s  */\n", hints);
    fprintf( CURRENT_FILE,
            "\tg_object_set(G_OBJECT(gui->%s),\"anchor-hints\", %d, NULL);\n",
            widget->name, val);
    g_strfreev( hintset );
}

void menu_type_hint( g2cWidget *widget )
{
gchar *hint = NULL;  
gchar *hint_name = NULL;   

    hint = g2c_widget_get_property( widget, "menu_type_hint" );
    hint_name = make_enumeral("GDK_WINDOW_TYPE_HINT", hint);
    fprintf( CURRENT_FILE,
            "\tg_object_set(G_OBJECT(gui->%s),\"menu-type-hint\", %s, NULL);\n",
            widget->name, hint_name);
    g_free( hint_name );
}

void menu_item_label( g2cWidget *widget )
{
gchar *label = NULL;
gchar *norm_label = NULL;

    g_assert( NULL != widget );
    label = g2c_widget_get_property( widget, "label" );
    norm_label = remove_prefix(label); 
    fprintf( CURRENT_FILE,
           "\tgtk_menu_item_set_label (GTK_MENU_ITEM(gui->%s), %s);\n",
            widget->name, g2c_stringify(norm_label));
    g_free( norm_label );
}

void menu_bar_direction( g2cWidget *widget )
{
gchar *direction = NULL;
gchar *direction_enum = NULL;

    g_assert( NULL != widget );
    direction = g2c_widget_get_property( widget, "pack_direction" );
    if (direction != NULL) {
        direction_enum = make_enumeral("GTK_PACK_DIRECTION", direction);
        fprintf( CURRENT_FILE,
               "\tgtk_menu_bar_set_pack_direction (GTK_MENU_BAR(gui->%s), %s);\n",
                widget->name, direction_enum);
        g_free( direction_enum );
    }
    direction = g2c_widget_get_property( widget, "child_pack_direction" );
    if (direction != NULL) {
        direction_enum = make_enumeral("GTK_PACK_DIRECTION", direction);
        fprintf( CURRENT_FILE,
               "\tgtk_menu_bar_set_child_pack_direction (GTK_MENU_BAR(gui->%s), %s);\n",
                widget->name, direction_enum);
        g_free( direction_enum );
    }
}

void 
menu_item_use_stock ( g2cWidget *widget )
{
gchar * stock_label = NULL;
gchar * norm_label = NULL;
gboolean use_stock = FALSE;
gboolean use_underline = FALSE;
gchar * image = NULL;
GList *run = NULL;
gchar *key = NULL;
g2cAccel *accel = NULL;
gchar *handler = NULL;

   g_assert( NULL != widget );
   stock_label = g2c_widget_get_property( widget, "label" );
   if (stock_label == NULL) return; 
   use_stock = g2c_get_bool(g2c_widget_get_property( widget, "use_stock" ));   
   use_underline = g2c_get_bool(g2c_widget_get_property( widget, "use_underline" ));    
   /*  https://developer.gnome.org/gtk3/stable/GtkImageMenuItem.html#gtk-image-menu-item-set-image  */
   fprintf( CURRENT_FILE,
           "\tgui->%sbox = (GtkBox*) gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 6);\n",
           widget->name);
   if ( use_stock == TRUE ) {
        fprintf( CURRENT_FILE,
                "\tgui->%simage = gtk_image_new_from_stock(\"%s\" ,GTK_ICON_SIZE_MENU);\n",
                widget->name, stock_label);    /* need to compile with -Wno-deprecated-declarations  */
        norm_label = remove_prefix(stock_label); 
        fprintf( CURRENT_FILE,
                "\tgui->%slabel = (GtkLabel*) gtk_accel_label_new (\"%s\");\n",
                widget->name, norm_label);
        fprintf( CURRENT_FILE,
               "\tgtk_container_add (GTK_CONTAINER (gui->%sbox), gui->%simage);\n",
               widget->name, widget->name);
   } else {   /*  use_stock is FALSE in which case there must be a GtkImage to use  */  
        fprintf( CURRENT_FILE,
              "\tgui->%slabel = (GtkLabel*) gtk_accel_label_new (\"%s\");\n",
              widget->name, stock_label);
		if ( use_underline == TRUE ) {
            fprintf( CURRENT_FILE,
                  "\tgtk_label_set_use_underline(GTK_LABEL(gui->%slabel),TRUE);\n",
                   widget->name );
        }	  
        image = g2c_widget_get_property( widget, "image" ); 
        fprintf( CURRENT_FILE,
             "\tgtk_container_add (GTK_CONTAINER (gui->%sbox), GTK_WIDGET(gui->%s));\n",
             widget->name, image);
   }   
    run = widget->accelerators;
    while (run != NULL) {
      accel = (g2cAccel *) run->data; 
      handler = find_signal_handler(widget, accel->signal);
      if (handler == NULL) continue;
      key = g_strdup_printf( "GDK_KEY_%s", accel->key);     
      fprintf( CURRENT_FILE,
           "\tgtk_widget_add_accelerator (GTK_WIDGET (gui->%s), \"%s\", gui->accel_group,\n"
           "\t                              %s, %s, GTK_ACCEL_VISIBLE);\n", 
              widget->name, accel->signal, key, accel->modifiers); 
      // fprintf( CURRENT_FILE,
           // "\tgtk_accel_label_set_accel_widget (GTK_ACCEL_LABEL (gui->%slabel), GTK_WIDGET (gui->%s));\n",
              // widget->name,  widget->name);
      g_free ( key );              
      run = run->next;
  } 
   fprintf( CURRENT_FILE,
           "\tgtk_box_pack_end (GTK_BOX (gui->%sbox), GTK_WIDGET (gui->%slabel), TRUE, TRUE, 0);\n",
            widget->name, widget->name);
   fprintf( CURRENT_FILE,
           "\tgtk_widget_show_all (GTK_WIDGET (gui->%sbox));\n",
           widget->name);
   fprintf( CURRENT_FILE,
           "\tgtk_container_add (GTK_CONTAINER (gui->%s), GTK_WIDGET (gui->%sbox));\n",
           widget->name, widget->name);

   g_free( norm_label );
}

void menu_button_popup( g2cWidget *widget )
{
gchar *popup = NULL;  

    g_assert( NULL != widget );
    popup = g2c_widget_get_property( widget, "popup" );  
    fprintf( CURRENT_FILE,
       "\tgtk_menu_button_set_popup (GTK_MENU_BUTTON(gui->%s), GTK_WIDGET(gui->%s));\n",
            widget->name, popup);
}


void window_icon ( g2cWidget *widget )
{
gchar * file_name = NULL;
gchar * file_name2 = NULL;
gchar * file_name3 = NULL;

    g_assert( NULL != widget );
    file_name = g2c_widget_get_property( widget, "icon" );  
    g_assert(NULL != file_name );
    file_name2 = g_strdelimit(file_name, "\\", '/');
    file_name3 = g_strdelimit(file_name, "\n", ' ');
    
    fprintf( CURRENT_FILE,
           "\t%s_pixbuf = gdk_pixbuf_new_from_file( \"%s\", &%s_error );\n",
           widget->name, file_name2, widget->name); 
    fprintf( CURRENT_FILE,"\tif (%s_pixbuf == NULL) {\n", widget->name);
    fprintf( CURRENT_FILE,"\t\tg_print(\"pixbuf error %%s \\n\", %s_error->message );\n ",
            widget->name);
    fprintf( CURRENT_FILE,"\t\treturn NULL;\n");
    fprintf( CURRENT_FILE,"\t}\n");
    fprintf( CURRENT_FILE,
           "\tgtk_window_set_icon(GTK_WINDOW(gui->%s), %s_pixbuf);\n", 
            widget->name, widget->name);
}

void entry_primary_pixbuf ( g2cWidget *widget )
{
gchar * file_name = NULL;
gchar * file_name2 = NULL;
    file_name = g2c_widget_get_property( widget, "primary_icon_pixbuf" );  
    g_assert(NULL != file_name );
    file_name2 = g_strdelimit(file_name, "\\", '/');
    fprintf( CURRENT_FILE,
           "\t%s_pixbuf = gdk_pixbuf_new_from_file( %s, &%s_error );\n",
           widget->name, g2c_stringify(file_name2), widget->name); 
    fprintf( CURRENT_FILE,"\tif (%s_pixbuf == NULL) {\n", widget->name);
    fprintf( CURRENT_FILE,"\t\tg_print(\"pixbuf error %%s \\n\", %s_error->message );\n ",
            widget->name);
    fprintf( CURRENT_FILE,"\t\treturn NULL;\n");
    fprintf( CURRENT_FILE,"\t}\n");
    fprintf( CURRENT_FILE,
           "\tgtk_entry_set_icon_from_pixbuf(GTK_ENTRY(gui->%s), GTK_ENTRY_ICON_PRIMARY, %s_pixbuf);\n", 
            widget->name, widget->name);
}

void entry_secondary_pixbuf ( g2cWidget *widget )
{
gchar * file_name = NULL;
gchar * file_name2 = NULL;
    file_name = g2c_widget_get_property( widget, "secondary_icon_pixbuf" );  
    g_assert(NULL != file_name );
    file_name2 = g_strdelimit(file_name, "\\", '/');
    fprintf( CURRENT_FILE,
           "\tpixbuf_%s = gdk_pixbuf_new_from_file( %s, &error_%s );\n",
           widget->name, g2c_stringify(file_name2), widget->name); 
    fprintf( CURRENT_FILE,"\tif (pixbuf_%s == NULL) {\n", widget->name);
    fprintf( CURRENT_FILE,"\t\tg_print(\"pixbuf error %%s \\n\", error_%s->message );\n ",
            widget->name);
    fprintf( CURRENT_FILE,"\t\treturn NULL;\n");
    fprintf( CURRENT_FILE,"\t}\n");
    fprintf( CURRENT_FILE,
           "\tgtk_entry_set_icon_from_pixbuf(GTK_ENTRY(gui->%s), GTK_ENTRY_ICON_SECONDARY, pixbuf_%s);\n", 
            widget->name, widget->name);    
}

//void image_from_pixbuf( g2cWidget *widget )
//{   /*  'pixbuf' is actually a file name, but has to be put in a pixbuf first  */
//gchar * file_name = NULL;
//gchar * file_name2 = NULL;
//gchar * file_name3 = NULL;
//
//    g_assert( NULL != widget );
//    file_name = g2c_widget_get_property( widget, "pixbuf" );
//    if (file_name == NULL) {
//       file_name = g2c_widget_get_property( widget, "resource" ); 
//    }
//    g_assert(NULL != file_name );
//    file_name2 = g_strdelimit(file_name, "\\", '/');
//    file_name3 = g_strdelimit(file_name2, "\n", ' ');    
//     
//    /*  image1_pixbuf and image1_error are set up by g2c_widget_create_temp_declaration_cb  */
//    //if (simple_name == NULL) {        
//       fprintf( CURRENT_FILE,
//           "\t%s_pixbuf = gdk_pixbuf_new_from_file( \"%s\", &%s_error );\n",
//           widget->name, file_name3, widget->name);
////    } else {
////        simple_name2 = g_string_new(simple_name);
////        g_string_erase(simple_name2, 0, 1);
////        fprintf( CURRENT_FILE,
////           "\t%s_pixbuf = gdk_pixbuf_new_from_file( %s, &%s_error );\n",
////           widget->name, g2c_stringify(g_strdup(simple_name2->str)), widget->name); 
////    }
//    fprintf( CURRENT_FILE,"\tif (%s_pixbuf == NULL) {\n", widget->name);
//    fprintf( CURRENT_FILE,"\t\tg_print(\"pixbuf error %%s \\n\", %s_error->message );\n ",
//            widget->name);
//    fprintf( CURRENT_FILE,"\t\treturn NULL;\n");
//    fprintf( CURRENT_FILE,"\t}\n");
//    fprintf( CURRENT_FILE,
//           "\tgtk_image_set_from_pixbuf(GTK_IMAGE(gui->%s), %s_pixbuf);\n", 
//            widget->name, widget->name);    
//}

//void image_from_resource( g2cWidget *widget )
//{
//gchar * file_name = NULL;
//gchar * simple_name = NULL;
//    g_assert( NULL != widget );
//    file_name = g2c_widget_get_property( widget, "resource" );
//    simple_name = strrchr(file_name, '/'); 
//    if (simple_name == NULL) {
//       fprintf( CURRENT_FILE,
//           "\tgtk_image_set_from_resource( GTK_IMAGE(gui->%s), %s );\n",
//           widget->name, g2c_stringify(file_name));
//    } else {
//       fprintf( CURRENT_FILE,
//            "\tgtk_image_set_from_resource( GTK_IMAGE(gui->%s), %s );\n",
//           widget->name, g2c_stringify(simple_name+1)); 
//    }
//}

void image_from_stock( g2cWidget *widget )
{
gchar * stock_name = NULL;
gchar * icon_size = NULL;

    g_assert( NULL != widget );
    stock_name = g2c_widget_get_property( widget, "stock" );
    if (stock_name == NULL) {
        stock_name = g2c_widget_get_property( widget, "icon_name" );
    }
    icon_size = g2c_widget_get_property( widget, "icon_size" );
    if (icon_size != NULL) {    
       fprintf( CURRENT_FILE,
           "\tgtk_image_set_from_icon_name(GTK_IMAGE(gui->%s), \"%s\", %s);\n", 
            widget->name, stock_name, icon_size); 
    } else {  // default is Button
       fprintf( CURRENT_FILE,
           "\tgtk_image_set_from_icon_name(GTK_IMAGE(gui->%s), \"%s\", GTK_ICON_SIZE_BUTTON);\n", 
            widget->name, stock_name );   
    }
}

/* Creation handlers */

void
create_custom_widget( g2cWidget *widget )
{
  gchar **params = NULL;
  gchar *param_string = NULL;
  gint i = 0;

  g_assert( NULL != widget );

  params = g_new0( gchar*, 5 );

  /* There are several attributes that determine the behaviour of the dock item */
  if ( g2c_widget_get_property( widget, "string1" ) != NULL )
    params[ i++ ] = g2c_stringify( g2c_widget_get_property( widget, "string1" ) );

  if ( g2c_widget_get_property( widget, "string2" ) != NULL )
    params[ i++ ] = g2c_stringify( g2c_widget_get_property( widget, "string2" ) );

  if ( g2c_widget_get_property( widget, "int1" ) != NULL )
    params[ i++ ] = g_strdup_printf( "%s", g2c_widget_get_property( widget, "int1" ) );

  if ( g2c_widget_get_property( widget, "int2" ) != NULL )
    params[ i++ ] = g_strdup_printf( "%s", g2c_widget_get_property( widget, "int2" ) );

  if ( i > 0 )
    param_string = g_strjoinv( ", ", params );
  else
    param_string = g_strdup( "" );

  fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkWidget*) %s (%s);\n",
           widget->name,
           g2c_widget_get_property( widget, "creation_function" ),
           param_string );

  g_strfreev( params );
  g_free( param_string );
}

void create_gtk_label( g2cWidget *widget )
{   /*  for GtkAccelLabel as well  */
gchar *label = NULL;
gboolean markup = FALSE;
gboolean underline = FALSE;
gchar * func_name = NULL;
gchar * caps_name = NULL;

    g_assert( NULL != widget );
    label = g2c_stringify( g2c_widget_get_property( widget, "label" ));   
	func_name = g2c_transform_name ( widget->klass_name, NT_FUNCTION ); 
	caps_name = g_utf8_strup (func_name, strlen(func_name)); 
    markup = g2c_get_bool(g2c_widget_get_property( widget, "use_markup" ));    
    if (markup == TRUE) {   /*  label cannot be None for Gtk.AccelLabel    */ 
        fprintf( CURRENT_FILE,
             "\tgui->%s = (%s*) %s_new (\"\");\n",  
                 widget->name, widget->klass_name, func_name);         
       return;   /*  markups set by label_use_markup  */
    }    
    if (label == NULL) {        
            fprintf( CURRENT_FILE,
                "\tgui->%s = (%s*) %s_new (\"\");\n",  
                   widget->name, widget->klass_name, func_name);         
    } else {   /* (label != NULL) */
        underline = g2c_get_bool(g2c_widget_get_property( widget, "use_underline" ));        
        if (underline == FALSE) {            
            fprintf( CURRENT_FILE,
                "\tgui->%s = (%s*) %s_new (%s);\n",  
                    widget->name, widget->klass_name, func_name, label);
        } else {
            fprintf( CURRENT_FILE,
                "\tgui->%s = (%s*) gtk_label_new_with_mnemonic (%s);\n",  
                    widget->name, widget->klass_name, label);
            fprintf( CURRENT_FILE,
                   "\tgtk_label_set_use_underline (GTK_LABEL(gui->%s), TRUE);\n",
                   widget->name ); 
        }        
    }
    g_free( func_name );
}

void create_gtk_alignment( g2cWidget *widget )
{
gchar *xalign = NULL;
gchar *yalign = NULL;
gchar *xscale = NULL;
gchar *yscale = NULL;

  xalign = g_strdup(g2c_widget_get_property( widget, "xalign" ));
  if (xalign == NULL) {
     xalign = g_strdup("0.50");  
  }
  yalign = g_strdup(g2c_widget_get_property( widget, "yalign" ));
  if (yalign == NULL) {
     yalign = g_strdup("0.50");  
  }
  xscale = g_strdup(g2c_widget_get_property( widget, "xscale" ));
  if (xscale == NULL) {
     xscale = g_strdup("1.00");  
  }
  yscale = g_strdup(g2c_widget_get_property( widget, "yscale" ));
  if (yscale == NULL) {
     yscale = g_strdup("1.00");  
  }
  fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkAlignment*) gtk_alignment_new (%s, %s, %s, %s);\n",
          widget->name, xalign, yalign, xscale, yscale);
  g_message("GtkAlignment is deprecated and may give compiler warnings.\n");
  g_free( xalign );
  g_free( yalign );
  g_free( xscale );
  g_free( yscale );
}

void
create_gtk_aspect_frame( g2cWidget *widget )
{
  gchar * label = NULL;
  gchar * obey_child = NULL;

  g_assert( NULL != widget );

  label = g2c_widget_get_property( widget, "label" );
  obey_child = g2c_widget_get_property( widget, "obey_child" );
  if (obey_child == NULL) obey_child = g_strdup("True");
  if ( NULL == label ) label = g_strdup( "NULL" );
  else label = g2c_stringify( label );

  fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkAspectFrame*) gtk_aspect_frame_new (%s, %s, %s, %s, %s);\n",
           widget->name,
           label,
           round_float( g2c_widget_get_property( widget, "xalign" ) ),
           round_float( g2c_widget_get_property( widget, "yalign" ) ),
           g2c_widget_get_property( widget, "ratio" ),
           g2c_get_bool_s( obey_child ) );

  g_free( label );
}

void
create_gtk_app_chooser_dialog ( g2cWidget *widget )
{
gchar * content = NULL; 
gchar *modal = NULL;
gchar *destroy = NULL;

 g_assert( NULL != widget );

   content = g2c_widget_get_property( widget, "content_type" );
   
   if (content != NULL) {
     fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkAppChooserDialog *) gtk_app_chooser_dialog_new_for_content_type (NULL, 0, \"%s\");\n",
           widget->name, content);
   } else {
     fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkAppChooserDialog *) gtk_app_chooser_dialog_new_for_content_type (NULL, 0,  \"\");\n",
           widget->name);  
   }
}

void
create_gtk_button( g2cWidget *widget )
{
  g_assert( NULL != widget );
  g2cWidget *parent = NULL;
  gchar *responseid = NULL;
  gchar *label = NULL;
  gboolean underline = FALSE;

  label = g2c_widget_get_property( widget, "label" );
  underline = g2c_get_bool(g2c_widget_get_property( widget, "use_underline" ));
  if ( ( NULL != widget->parent ) &&
       ( NULL != widget->child_name ) )
    {
      if ( strcmp( widget->child_name, "FileSel:cancel_button" ) == 0 )
        {
          fprintf( CURRENT_FILE,
                   "\tgui->%s = (GtkButton*) GTK_FILE_SELECTION (gui->%s)->cancel_button;\n",
                   widget->name, widget->parent->name );
        }
      else if ( strcmp( widget->child_name, "FileSel:ok_button" ) == 0 )
        {
          fprintf( CURRENT_FILE,
                   "\tgui->%s = (GtkButton*) GTK_FILE_SELECTION (gui->%s)->ok_button;\n",
                   widget->name, widget->parent->name );
        }
      else if ( strcmp( widget->child_name, "ColorSel:ok_button" ) == 0 )
        {
          fprintf( CURRENT_FILE,
                   "\tgui->%s = (GtkButton*) GTK_COLOR_SELECTION_DIALOG (gui->%s)->ok_button;\n",
                   widget->name, widget->parent->name );
        }
      else if ( strcmp( widget->child_name, "ColorSel:cancel_button" ) == 0 )
        {
          fprintf( CURRENT_FILE,
                   "\tgui->%s = (GtkButton*) GTK_COLOR_SELECTION_DIALOG (gui->%s)->cancel_button;\n",
                   widget->name, widget->parent->name );
        }
      else if ( strcmp( widget->child_name, "ColorSel:help_button" ) == 0 )
        {
          fprintf( CURRENT_FILE,
                   "\tgui->%s = (GtkButton*) GTK_COLOR_SELECTION_DIALOG (gui->%s)->help_button;\n",
                   widget->name, widget->parent->name );
        }
      else if ( strcmp( widget->child_name, "FontSel:ok_button" ) == 0 )
        {
          fprintf( CURRENT_FILE,
                   "\tgui->%s = (GtkButton*) GTK_FONT_SELECTION_DIALOG (gui->%s)->ok_button;\n",
                   widget->name, widget->parent->name );
        }
      else if ( strcmp( widget->child_name, "FontSel:cancel_button" ) == 0 )
        {
          fprintf( CURRENT_FILE,
                   "\tgui->%s = (GtkButton*) GTK_FONT_SELECTION_DIALOG (gui->%s)->cancel_button;\n",
                   widget->name, widget->parent->name );
        }
      else if ( strcmp( widget->child_name, "FontSel:apply_button" ) == 0 )
        {
          fprintf( CURRENT_FILE,
                   "\tgui->%s = (GtkButton*) GTK_FONT_SELECTION_DIALOG (gui->%s)->apply_button;\n",
                   widget->name, widget->parent->name );
        }
      else if ( strcmp( widget->child_name, "Toolbar:button" ) == 0 )
        {
          if (label == NULL) {
            fprintf( CURRENT_FILE,
                     "\tgui->%s = (GtkButton*) gtk_button_new_with_label (\"\");\n",
                     widget->name );
          } else {
			  fprintf( CURRENT_FILE,
						 "\tgui->%s = (GtkButton*) gtk_button_new_with_label (\"%s\");\n",
						 widget->name, label );
          }
        }
      else if ( strcmp( widget->child_name, "InputDialog:save_button" ) == 0 )
        {
          fprintf( CURRENT_FILE,
                   "\tgui->%s = (GtkButton*) gui->%s->save_button;\n",
                   widget->name,
                   widget->parent->name );
        }
      else if ( strcmp( widget->child_name, "InputDialog:close_button" ) == 0 )
        {
          fprintf( CURRENT_FILE,
                   "\tgui->%s = (GtkButton*) gui->%s->close_button;\n",
                   widget->name,
                   widget->parent->name );
        }
      else   
        {
          if (label == NULL) {
            fprintf ( CURRENT_FILE,
                      "\tgui->%s = (GtkButton*) gtk_button_new_with_label (\"\");\n",
                      widget->name );
          } else {
			  if (underline == FALSE)  {
                fprintf ( CURRENT_FILE,
                      "\tgui->%s = (GtkButton*) gtk_button_new_with_label (\"%s\");\n",
                      widget->name, label );
			  } else {
				  fprintf( CURRENT_FILE,
						 "\tgui->%s = (GtkButton*) gtk_button_new_with_mnemonic (\"%s\");\n",
						 widget->name, label );
				  fprintf ( CURRENT_FILE,
                   "\tgtk_button_set_use_underline (GTK_BUTTON(gui->%s), TRUE);\n",
                   widget->name ); 
			  }
          }
        }
    }
  else     /*  button has parent but no child_name   */
    {          
      if (widget->parent->internal == FALSE) {
          if (label == NULL) {
            fprintf ( CURRENT_FILE,
                      "\tgui->%s = (GtkButton*) gtk_button_new_with_label (\"\");\n",
                      widget->name );
          } else {
			  if (underline == FALSE)  {
				fprintf ( CURRENT_FILE,
						  "\tgui->%s = (GtkButton*) gtk_button_new_with_label (\"%s\");\n",
						  widget->name, remove_prefix(label) ); 
			  } else {
				 fprintf ( CURRENT_FILE,
						  "\tgui->%s = (GtkButton*) gtk_button_new_with_mnemonic (\"%s\");\n",
						  widget->name, remove_prefix(label) );  
				 fprintf ( CURRENT_FILE,
                   "\tgtk_button_set_use_underline (GTK_BUTTON(gui->%s), TRUE);\n",
                   widget->name ); 
			  }
          }
      } else {   /*  button has parent and parent is internal and ButtonBox   */
         parent =  widget->parent->parent;  /* parent of ButtonBox: GtkBox, also internal  */
         if (parent != NULL) {             
             if (parent->internal == TRUE) {   /*  internal GtkBox  */
                g_assert( strcmp(parent->klass_name, "GtkBox") == 0 );
                parent = parent->parent; 
                if (parent != NULL) {   /*  This should be a GtkDialog  */
                    g_assert( g_type_is_a(parent->klass, GTK_TYPE_DIALOG) );
                    responseid = g2c_widget_get_action_widget(parent, widget->name);
                    if (responseid == NULL)  responseid = g_strdup("0");
                    if (label == NULL) {
                        fprintf ( CURRENT_FILE,
                          "\n\tgui->%s = (GtkButton*) gtk_dialog_add_button (GTK_DIALOG(gui->%s), \"\", %s);\n",
                                widget->name,
                                parent->name,
                                responseid);
                    } else {
                        fprintf ( CURRENT_FILE,
                          "\n\tgui->%s = (GtkButton*) gtk_dialog_add_button (GTK_DIALOG(gui->%s), \"%s\", %s);\n",
                                widget->name,
                                parent->name,
                                label,
                                responseid);
                    }
                }
             } else {  /* parent of ButtonBox is GtkInfoBar  */
                g_assert( strcmp(parent->klass_name, "GtkInfoBar") == 0 );
                responseid = g2c_widget_get_action_widget(parent, widget->name);
                if (responseid == NULL)  responseid = g_strdup("0");
                if (label == NULL) {
                    fprintf ( CURRENT_FILE,
                      "\n\tgui->%s = (GtkButton*) gtk_info_bar_add_button (GTK_INFO_BAR(gui->%s), \"\", %s);\n",
                            widget->name,
                            parent->name,
                            responseid);
                } else {
                    fprintf ( CURRENT_FILE,
                      "\n\tgui->%s = (GtkButton*) gtk_info_bar_add_button (GTK_INFO_BAR(gui->%s), \"%s\", %s);\n",
                            widget->name,
                            parent->name,
                            label,
                            responseid);
                }
				fprintf ( CURRENT_FILE,
                          "\tgtk_widget_show(GTK_WIDGET(gui->%s));\n", widget->name);
             }
         }
      }
    }
}

void create_gtk_image( g2cWidget *widget )
{
gchar *pixbuf = NULL;
gchar *file_name1 = NULL;
gchar *file_name = NULL;
gchar *stock = NULL;
gchar *icon_name = NULL;
gchar *resource = NULL;
gchar *strsize = NULL;
gchar *nsize = NULL;
    pixbuf = g2c_widget_get_property( widget, "pixbuf" );
    stock = g2c_widget_get_property( widget, "stock");
    icon_name =  g2c_widget_get_property( widget, "icon_name");
    resource = g2c_widget_get_property( widget, "resource" );
    strsize = g2c_widget_get_property( widget, "icon_size");
    if (pixbuf != NULL) {
        file_name1 = g_strdelimit(pixbuf, "\\", '/');
        file_name = g_strdelimit(file_name1, "\n", ' ');
        fprintf ( CURRENT_FILE,
                "\tgui->%s = (GtkImage*) gtk_image_new_from_file(\n\t\"%s\");\n",
                widget->name, file_name);
        return;
    }
    if (stock != NULL) {        
        fprintf ( CURRENT_FILE,
                "\tgui->%s = (GtkImage*) gtk_image_new_from_pixbuf(NULL);\n",
                widget->name);
        /*  image set up in image_from_stock  */
        return;
    }
    if (icon_name != NULL) {
        nsize = make_icon_size_enumeral(strsize);
        fprintf ( CURRENT_FILE,
                "\tgui->%s = (GtkImage*) gtk_image_new_from_stock(\"%s\", %s);\n",
                widget->name, icon_name, nsize);    /* need to compile with -Wno-deprecated-declarations  */
        return;
    }
    if (resource != NULL) {
        /*  In GTK+ 3.0, resource files have been deprecated and replaced by CSS-like style sheets */
        file_name1 = g_strdelimit(resource, "\\", '/');
        file_name = g_strdelimit(file_name1, "\n", ' ');
        fprintf ( CURRENT_FILE,
                "\tgui->%s = (GtkImage*) gtk_image_new_from_resource\n\t (\"%s\");\n",
                widget->name, file_name);
        return;
    }
}

void create_gtk_lockbutton( g2cWidget *widget )
{
//gchar *action_id = NULL;

//    action_id = g_strdup("NULL");
//    fprintf( CURRENT_FILE,
//               "\tgui->%s = (GtkLockButton*) gtk_lock_button_new(\n", 
//               widget->name);
//    fprintf( CURRENT_FILE,
//               "\t\tpolkit_permission_new_sync(%s, NULL, NULL, NULL) );\n",
//            action_id);
//    g_free ( action_id );
    fprintf( CURRENT_FILE,"\t/***    LockButton not implemented by Glade   ***/\n");
}

void create_gtk_popover( g2cWidget *widget )
{
//gchar *relative_to = NULL;
//gchar *main_type = NULL;

    //relative_to = g2c_widget_get_property( widget, "relative_to" );
    //main_type = g2c_transform_name( MAIN_WINDOW, NT_TYPENAME );
    //if (relative_to != NULL) {
    //    fprintf( CURRENT_FILE,
    //           "\tgui->%s = (GtkPopover*) gtk_popover_new (GTK_WIDGET ( ((%s*)owner)->gui->%s ));\n",
     //          widget->name, main_type, relative_to);  
    //    fprintf( CURRENT_FILE,
    //            "\tgtk_menu_button_set_popover(GTK_MENU_BUTTON( ((%s*)owner)->gui->%s ), GTK_WIDGET(gui->%s) );\n",
    //            main_type, relative_to, widget->name);
    //} else {
        fprintf( CURRENT_FILE,
               "\tgui->%s = (GtkPopover*) gtk_popover_new (NULL);\n",
               widget->name);
    //    g_message("YOU NEED TO ENTER the widget (button) which is 'relative to' this popover %s\n", widget->name);
    //} 
}

void create_gtk_popovermenu( g2cWidget *widget )
{
//gchar *relative_to = NULL;
//gchar *main_type = NULL;
//
//    relative_to = g2c_widget_get_property( widget, "relative_to" );
//    main_type = g2c_transform_name( MAIN_WINDOW, NT_TYPENAME );
//    if (relative_to != NULL) {
        fprintf( CURRENT_FILE,
               "\tgui->%s = (GtkPopoverMenu*) gtk_popover_menu_new ();\n",
               widget->name );  
//        fprintf( CURRENT_FILE,
//                "\tgtk_popover_set_relative_to(GTK_POPOVER(gui->%s), GTK_WIDGET ( ((%s*)owner)->gui->%s ));\n",
//                widget->name, main_type, relative_to );
//        fprintf( CURRENT_FILE,
//                "\tgtk_menu_button_set_popover(GTK_MENU_BUTTON( ((%s*)owner)->gui->%s ), GTK_WIDGET(gui->%s) );\n",
//                main_type, relative_to, widget->name);
//    } else {
//        fprintf( CURRENT_FILE,
//               "\tgui->%s = (GtkPopover*) gtk_popover_menu_new (NULL);\n",
//               widget->name);
//        g_message("YOU NEED TO ENTER the widget (button) which is 'relative to' this popovermenu %s\n", widget->name);
//    } 
}


void create_gtk_cellrenderertoggle( g2cWidget *widget )
{
gchar *active = NULL;  
g2cWidget *column_widget = NULL;
gchar *activatable = NULL;
gchar * col_no;

    active = g2c_widget_get_property( widget, "active" );
    activatable = g2c_widget_get_property( widget, "activatable" ); 
    //if (active == NULL) active = "FALSE";  -- if active is FALSE it does not appear in the glade file
    //gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(gui->col3), GTK_CELL_RENDERER(gui->cellrenderertoggle1), TRUE);
    //gtk_tree_view_column_add_attribute(GTK_TREE_VIEW_COLUMN(gui->col3), GTK_CELL_RENDERER(gui->cellrenderertoggle1), "active", col_no);
    //gtk_cell_renderer_toggle_set_active(GTK_CELL_RENDERER_TOGGLE(gui->cellrenderertoggle1),TRUE );
    // see pack_renderer
    column_widget = widget->parent;      
    col_no = g2c_widget_get_property( column_widget, "sort_column_id");
    
    if (strcmp("0",col_no) == 0) {
        g_message("Is the model column no in the treecolumn sort column id really zero?\n");
    }
    fprintf( CURRENT_FILE,
               "\tgui->%s = (GtkCellRendererToggle*) gtk_cell_renderer_toggle_new ();\n",
               widget->name);
               
    fprintf( CURRENT_FILE,
           "\tgtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(gui->%s), GTK_CELL_RENDERER(gui->%s), TRUE);\n",
           column_widget->name,
           widget->name);
    //if ( (activatable != NULL) && (strcmp(activatable,"TRUE") == 0) )
    //{    
        fprintf( CURRENT_FILE,
               "\tgtk_cell_renderer_toggle_set_active(GTK_CELL_RENDERER_TOGGLE(gui->%s), %s);\n",
               widget->name,
               (active == NULL)? "FALSE": g_utf8_strup(active, strlen(active)));
        if (col_no != NULL) {
            fprintf( CURRENT_FILE,
               "\tgtk_tree_view_column_add_attribute(GTK_TREE_VIEW_COLUMN(gui->%s), GTK_CELL_RENDERER(gui->%s), \"active\", %s);\n",
               column_widget->name,
               widget->name,
               col_no);
        }

    //}
}

void 
create_gtk_combobox( g2cWidget *widget )
{
gchar *entry = NULL;
gchar *model = NULL;
gchar *fname = NULL;
  g_assert( NULL != widget );

  if ( NULL != widget->parent )  {
      fname = g2c_transform_name( widget->klass_name, NT_FUNCTION );
      entry = g2c_widget_get_property( widget, "has_entry" );
      model = g2c_widget_get_property( widget, "model" );
      if ((entry == NULL) && (model == NULL)) {
          fprintf( CURRENT_FILE,
               "\tgui->%s = (%s*) %s_new ();\n",
               widget->name, widget->klass_name, fname );
      } else if ((entry != NULL) && (model == NULL)) {
          fprintf( CURRENT_FILE,
               "\tgui->%s = (%s*) %s_new_with_entry ();\n",
                   widget->name, widget->klass_name, fname );
      } else if ((entry == NULL) && (model != NULL)) {
          fprintf( CURRENT_FILE,
               "\tgui->%s = (%s*) gtk_combo_box_new_with_model (GTK_TREE_MODEL(gui->%s));\n",
                   widget->name, widget->klass_name, model );
      } else if ((entry != NULL) && (model != NULL)) {
          fprintf( CURRENT_FILE,
               "\tgui->%s = (%s*) gtk_combo_box_new_with_model_and_entry (GTK_TREE_MODEL(gui->%s));\n",
                   widget->name, widget->klass_name, model );
      }
  }  
}

void
create_gtk_entry( g2cWidget *widget )
{
  g_assert( NULL != widget );

  if ( NULL != widget->parent )
    {
      if ( ( strcmp( widget->parent->klass_name, "GtkComboBox" ) == 0 ) ||
           ( strcmp( widget->parent->klass_name, "GtkComboBoxText" ) == 0 ) )
        {
          fprintf( CURRENT_FILE,
                   "\tgui->%s = (GtkEntry *) gtk_bin_get_child(GTK_BIN(gui->%s));\n\n",
                   widget->name,
                   widget->parent->name );
        }
    
    else   {
      fprintf( CURRENT_FILE,
               "\tgui->%s = (GtkEntry*) gtk_entry_new ();\n",
               widget->name );
    }
  }
}

void 
create_gtk_file_chooser ( g2cWidget *widget )
{
gchar *init_action = NULL;  
gchar *action = NULL;
gchar *title = NULL;
gchar *enumaction = NULL;

   g_assert( NULL != widget );
   
    init_action = g2c_widget_get_property( widget, "action" );
    if (init_action != NULL) 
        action = g_strdelimit( init_action, ":-", '_' );
    if (action == NULL) {
       enumaction = g_strdup( "GTK_FILE_CHOOSER_ACTION_OPEN" );
    } else {
       enumaction = make_enumeral ( "GTK_FILE_CHOOSER_ACTION", action );
    }    
    if (strcmp(widget->klass_name,"GtkFileChooserDialog") == 0) {
        if ( NULL != widget->parent ) return;
        title = g2c_widget_get_property( widget, "title" );
        if (title == NULL) {                           
            fprintf( CURRENT_FILE,
               "\tgui->%s = (GtkFileChooserDialog*) gtk_file_chooser_dialog_new (\"\", NULL, %s, NULL, NULL);\n",
               widget->name, enumaction );
        } else {
            fprintf( CURRENT_FILE,
               "\tgui->%s = (GtkFileChooserDialog*) gtk_file_chooser_dialog_new (\"%s\", NULL, %s, NULL, NULL);\n",
               widget->name, title, enumaction );
        }
         
     } else if (strcmp(widget->klass_name,"GtkFileChooserWidget") == 0) {
        fprintf( CURRENT_FILE,
             "\tgui->%s = (GtkFileChooserWidget*) gtk_file_chooser_widget_new (%s);\n",
             widget->name, enumaction );                                       
     }
    g_free ( enumaction );
     
}

void
create_gtk_frame( g2cWidget *widget )
{
    g2cWidget *Label = NULL;
    g2cWidget *child = NULL;
    gchar *label = NULL;
    GList *children = NULL;
    GList *run = NULL;
    
    g_assert( NULL != widget );
    children = widget->children;
    run = g_list_first(children);
    while (run != NULL) {
        child = (g2cWidget *) run->data; 
        if (strcmp(child->klass_name, "GtkLabel") == 0) {
            label = g2c_widget_get_property( child, "label" );
            break;
        }
        run = run->next;
    }
    if (label != NULL) {
        fprintf( CURRENT_FILE,
               "\tgui->%s =(GtkFrame*) gtk_frame_new (%s);\n",
                widget->name, g2c_stringify(label));
    } else {
        fprintf( CURRENT_FILE,
               "\tgui->%s =(GtkFrame*) gtk_frame_new (\"\");\n",
                widget->name);
    }
    
}

void 
create_gtk_file_chooser_button ( g2cWidget *widget )
{
gchar *init_action = NULL;
gchar *action = NULL;
gchar *enumaction = NULL;
gchar *title = NULL;

   g_assert( NULL != widget );
   
   if ( NULL != widget->parent )
   {
       init_action = g2c_widget_get_property( widget, "action" );
       if (action == NULL) {
          enumaction = g_strdup( "GTK_FILE_CHOOSER_ACTION_OPEN" );
       } else {
          enumaction = make_enumeral ("GTK_FILE_CHOOSER_ACTION", action);
       }
       title = g2c_widget_get_property( widget, "title" );
       if (title == NULL) {
          fprintf( CURRENT_FILE,
               "\tgui->%s = (GtkFileChooserButton*) gtk_file_chooser_button_new (\"\", %s);\n",
               widget->name, enumaction ); 
       } else {
          fprintf( CURRENT_FILE,
               "\tgui->%s = (GtkFileChooserButton*) gtk_file_chooser_button_new (\"%s\", %s);\n",
               widget->name, title, enumaction );
       }
       g_free ( enumaction );
   }
   
}

void 
create_gtk_liststore( g2cWidget *widget )
{  /*  for GtkListStore and GtkTreeStore  */
  g_assert( NULL != widget );
  GList *run = widget->columns;
  g2cColumn *column;
  gchar *type;
  guint ncols = 0;
  gboolean first = TRUE;
  GString *coltypes = g_string_new( "" );;
  
  while (run != NULL) {
      ncols++;
      if (first == FALSE) {
          g_string_append_c(coltypes, ',');
      }  
      column = (g2cColumn *) run->data;
      type = g2c_transform_name ((gchar *) column->col_type, NT_CAPITALISE);
      g_string_append(coltypes, type);
      g_free(type);
      first = FALSE;
      run = run->next;
  }
  if (strcmp(widget->klass_name, "GtkListStore") == 0 )  {
    fprintf( CURRENT_FILE,
             "\tgui->%s = (GtkListStore*) gtk_list_store_new(%d,%s );\n",
            widget->name, ncols, coltypes->str );
  } else if (strcmp(widget->klass_name, "GtkTreeStore") == 0 )  {
    fprintf( CURRENT_FILE,
             "\tgui->%s = (GtkTreeStore*) gtk_tree_store_new(%d,%s );\n",
            widget->name, ncols, coltypes->str );  
  }
  
  g_string_free( coltypes, TRUE );   
}

void create_gtk_message_dialog ( g2cWidget *widget  )
{
gchar *type = NULL;
gchar *buttons = NULL;
gchar *full_buttons = NULL;
gchar *full_type = NULL;
gchar *flags = "0";
gchar *message = NULL;
gchar *markup = NULL;
   g_assert( NULL != widget );
   type = g2c_widget_get_property( widget, "message_type" );
   buttons = g2c_widget_get_property( widget, "buttons" );
   message = g2c_widget_get_property( widget, "text" );
   markup = g2c_widget_get_property( widget, "use_markup" );
   if (buttons != NULL) {
       full_buttons = make_enumeral( "GTK_BUTTONS", buttons );
   } else {
       full_buttons = g_strdup( "GTK_BUTTONS_NONE" );
   }
   if (type != NULL) {
       full_type = make_enumeral( "GTK_MESSAGE", type );
   } else {
       full_type = g_strdup( "GTK_MESSAGE_INFO" );
   }
   if (markup == NULL) {
       fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkMessageDialog*) gtk_message_dialog_new(NULL, %s, %s, %s, %s );\n",
          widget->name, flags, full_type, full_buttons, g2c_stringify(message ));
   } else {
       fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkMessageDialog*) gtk_message_dialog_new_with_markup(NULL, %s, %s, %s, %s );\n",
          widget->name, flags, full_type, full_buttons, g2c_stringify(g_strdelimit(message,"\"",'\'') ) );
   }
   g_free ( full_type );
   g_free ( full_buttons );
}

void 
create_gtk_treeview( g2cWidget *widget )
{
  g_assert( NULL != widget );
  gchar *model = g2c_widget_get_property( widget, "model" );
  if (model == NULL) {
      fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkTreeView *) gtk_tree_view_new();\n", 
              widget->name);
  } else {
      fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkTreeView *) gtk_tree_view_new_with_model(GTK_TREE_MODEL(gui->%s));\n", 
              widget->name, model);
  }  
}

void 
create_gtk_treemodel_filter( g2cWidget *widget )
{
  g_assert( NULL != widget );
  gchar *model = g2c_widget_get_property( widget, "child_model" );
  if (model == NULL) {
      g_message("No model specified for GtkTreeModelFilter\n");
  } else {
      fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkTreeModelFilter *) gtk_tree_model_filter_new(GTK_TREE_MODEL(gui->%s),NULL);\n", 
              widget->name, model);
  }
}

void 
create_gtk_treemodel_sort( g2cWidget *widget )
{
  g_assert( NULL != widget );
  gchar *model = g2c_widget_get_property( widget, "model" );
  if (model == NULL) {
      g_message("No model specified for GtkTreeModelSort\n");      
  } else {
      fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkTreeModelSort *) gtk_tree_model_sort_new_with_model(GTK_TREE_MODEL(gui->%s));\n", 
              widget->name, model);
  }
}


g2cWidget *
find_liststore(g2cWidget *widget, gchar *model)
{
g2cWidget *associate = NULL;
GList *run;
run = g_list_first(widget->associates);
      while (run != NULL) {
         associate = (g2cWidget *) run->data;
         if ( (strcmp(associate->klass_name,"GtkListStore)") == 0 ) &&
              (strcmp(associate->name,model) == 0) ) {
             break;
         }
         run = g_list_next( run ); 
      }
      return associate;
}

void 
create_gtk_iconview( g2cWidget *widget )
{
g2cWidget *parent = NULL;
g2cWidget *associate = NULL;
GList *run;
g2cColumn *column;
//gchar *coltype = NULL;
gint colno;
gboolean bTextfound = FALSE;

  g_assert( NULL != widget );
  gchar *model = g2c_widget_get_property( widget, "model" );
  if (model == NULL) {
      fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkIconView *) gtk_icon_view_new();\n", 
              widget->name);
  } else {
      fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkIconView *) gtk_icon_view_new_with_model(GTK_TREE_MODEL(gui->%s));\n", 
              widget->name, model);
      // navigate around to find the widget of the iconview's liststore
      parent = g2c_widget_get_top_parent(widget);
      associate = find_liststore(parent, model);
      g_assert ( NULL != associate );
      run = g_list_first(associate->columns);
      /*   The column numbers are the column numbers of the ListStore.  */
      colno = 0;
      while (run != NULL) {
          //coltype = (gchar *) run->data;
          column = (g2cColumn *) run->data;
          if (strcmp(column->col_type, "GdkPixbuf") == 0 ) {
              fprintf( CURRENT_FILE,
                      "\tgtk_icon_view_set_pixbuf_column (GTK_ICON_VIEW(gui->%s), %d);\n",
                      widget->name, colno);
          }
          if ( (strcmp(column->col_type, "gchararray") == 0 ) && (bTextfound == FALSE) ) {
              fprintf( CURRENT_FILE,
                      "\tgtk_icon_view_set_text_column (GTK_ICON_VIEW(gui->%s), %d);\n",
                      widget->name, colno);
              bTextfound = TRUE;
          }
          colno++;
          run = g_list_next( run ); 
      }
  }
  
}

void
create_gtk_text_buffer( g2cWidget *widget )
{
gchar *tagtable =  NULL;

    g_assert( NULL != widget );
    tagtable = g2c_widget_get_property( widget, "tag_table" );
    if (NULL != tagtable) {
        fprintf( CURRENT_FILE, 
            "\tgui->%s = gtk_text_buffer_new (gui->%s);\n",
           widget->name, tagtable);     
    } else {
        fprintf( CURRENT_FILE, 
            "\tgui->%s = gtk_text_buffer_new (NULL);\n",
                widget->name);
    }
}

void 
create_gtk_tree_selection( g2cWidget *widget )
{
  g_assert( NULL != widget );
  
  fprintf( CURRENT_FILE, 
   "\tgui->%s = gtk_tree_view_get_selection (GTK_TREE_VIEW(gui->%s));\n",
          widget->name, widget->parent->name);
  fprintf( CURRENT_FILE, 
      "\tgtk_tree_selection_set_mode (gui->%s, GTK_SELECTION_SINGLE);\n",
       widget->name);
  fprintf( CURRENT_FILE,
      "\tg_object_set_data (G_OBJECT (gui->%s), \"owner\", owner);\n\n",
      widget->name );
}

void create_gtk_radio_button( g2cWidget *widget )
{
    g_assert( NULL != widget );
    gchar *label = g2c_widget_get_property( widget, "label" );
    gchar *norm_label = remove_prefix(label); 
    gchar *group = g2c_widget_get_property( widget, "group" );  
    if (group == NULL) {
        fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkRadioButton *) gtk_radio_button_new_with_label(NULL, %s);\n", 
              widget->name, g2c_stringify(norm_label) );
    } else {
        fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkRadioButton *) gtk_radio_button_new_with_label_from_widget(gui->%s, %s);\n", 
              widget->name, group, g2c_stringify(norm_label) );
    }  
   
}

void create_gtk_radio_tool_button ( g2cWidget *widget )
{
   g_assert( NULL != widget );
   gchar *group = g2c_widget_get_property( widget, "group" );  
   if (group == NULL) {
        fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkRadioToolButton *) gtk_radio_tool_button_new(NULL);\n", 
              widget->name);
    } else {
        fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkRadioToolButton *) gtk_radio_tool_button_new_from_widget(gui->%s);\n", 
              widget->name, group);
    }  
}

void 
create_gtk_radio_menu_item( g2cWidget *widget )
{
    g_assert( NULL != widget );
    gchar *label = g2c_widget_get_property( widget, "label" );
    gchar *group = g2c_widget_get_property( widget, "group" ); 
    if (label == NULL) {
        if (group == NULL) {
            fprintf( CURRENT_FILE,
               "\tgui->%s = (GtkRadioMenuItem *) gtk_radio_menu_item_new(NULL);\n", 
                  widget->name);
        } else {
            fprintf( CURRENT_FILE,
               "\tgui->%s = (GtkRadioMenuItem *) gtk_radio_menu_item_new_from_widget(gui->%s);\n", 
                  widget->name, group);
        }         
    } else {
        if (group == NULL) {
            if (has_underscore(label) == FALSE) {
              fprintf( CURRENT_FILE,
               "\tgui->%s = (GtkRadioMenuItem *) gtk_radio_menu_item_new_with_label(NULL, %s);\n", 
                  widget->name, g2c_stringify(label) );
            } else {
               fprintf( CURRENT_FILE,
               "\tgui->%s = (GtkRadioMenuItem *) gtk_radio_menu_item_new_with_mnemonic(NULL, %s);\n", 
                  widget->name, g2c_stringify(label) );  
            }
        } else {
            if (has_underscore(label) == FALSE) {
              fprintf( CURRENT_FILE,
               "\tgui->%s = (GtkRadioMenuItem *) gtk_radio_menu_item_new_with_label_from_widget(gui->%s, %s);\n", 
                  widget->name, group, g2c_stringify(label) );
            } else {
              fprintf( CURRENT_FILE,
               "\tgui->%s = (GtkRadioMenuItem *) gtk_radio_menu_item_new_with_mnemonic_from_widget(gui->%s, %s);\n", 
                  widget->name, group, g2c_stringify(label) );  
            }
        } 
    }
}

void create_gtk_recent_chooser_dialog ( g2cWidget *widget )
{
gchar *recent_manager = NULL;
gchar *func_name = NULL;
gchar *caps_name = NULL;

    g_assert( NULL != widget );
    recent_manager = g2c_widget_get_property( widget, "recent_manager" ); 
    func_name = g2c_transform_name ( widget->klass_name, NT_FUNCTION );   /* e.g. gtk_recent_chooser */
    caps_name = g_utf8_strup ( func_name, strlen(func_name) ); /* e.g. GTK_RECENT_CHOOSER  */
    if (strcmp(widget->klass_name, "GtkRecentChooserDialog") == 0 )  {
        if (recent_manager == NULL) {
            fprintf( CURRENT_FILE,
            "\tgui->%s = (%s *) %s_new (NULL, NULL, NULL, NULL, NULL);\n",
                    widget->name, widget->klass_name, func_name);
        } else {
            fprintf( CURRENT_FILE,
            "\tgui->%s = (%s *) %s_new_for_manager\n"
                    "\t\t\t(NULL, NULL, gui->%s, NULL, NULL);\n",
                    widget->name, widget->klass_name, func_name, recent_manager);
        }
    } else if (strcmp(widget->klass_name, "GtkRecentChooserWidget") == 0 )  {
        if (recent_manager == NULL) {
            fprintf( CURRENT_FILE,
            "\tgui->%s = (%s *) %s_new ();\n",
                    widget->name, widget->klass_name, func_name);
        } else {
            fprintf( CURRENT_FILE,
            "\tgui->%s = (%s *) %s_new_for_manager\n"
                    "\t\t\t(gui->%s);\n",
                    widget->name, widget->klass_name, func_name, recent_manager);
        }
    }
}

void create_gtk_link_button( g2cWidget *widget )
{
gchar *uri = NULL;
gchar *label = NULL;

    g_assert( NULL != widget );
    uri = g2c_widget_get_property( widget, "uri");
    label = proplist_lookup(widget,  "name");  /* because Glade doesn't have provision for a label */
    fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkLinkButton*) gtk_link_button_new (%s);\n",
           widget->name, g2c_stringify(uri));
    if (label != NULL) {
        fprintf( CURRENT_FILE,
           "\tgtk_button_set_label(GTK_BUTTON(gui->%s), %s );\n",
               widget->name, g2c_stringify(label)); 
    }
}

void create_gtk_scale_button( g2cWidget *widget )
{
gchar *size = NULL;
gchar *button_size = NULL;

    g_assert( NULL != widget );
    size = g2c_widget_get_property( widget, "size");
    if (size == NULL) {
        button_size = g_strdup("GTK_ICON_SIZE_SMALL_TOOLBAR");
    } else {
        button_size = make_enumeral("GTK_ICON_SIZE", size);
    }
    fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkScaleButton*) gtk_scale_button_new (%s,0,0,0,NULL);\n",
            widget->name, button_size);
}

void
create_gtk_spin_button( g2cWidget *widget )
{
gchar * climb_rate = NULL;
gchar * digits = NULL;
gdouble rsize;
  g_assert( NULL != widget );
// climb_rate should be double.  digits should be zero if absent.
  climb_rate = g2c_widget_get_property( widget, "climb_rate" );
  if (climb_rate != NULL) {
    digits = g2c_widget_get_property( widget, "digits" );  // after dec. point
    if (!isnumber(climb_rate)) {
          g_message("climb rate not numeric %s for %s id %s\n", climb_rate, widget->klass_name, widget->name);
          return;
      }
    rsize = g_ascii_strtod(climb_rate, NULL);
    fprintf( CURRENT_FILE,
             "\tgui->%s = (GtkSpinButton*) gtk_spin_button_new (\n"
             "\t          NULL, %6.2f, %s);\n",
             widget->name,
             rsize,
             (digits == NULL) ? "0" : digits
            );
  } else {
    fprintf( CURRENT_FILE,
             "\tgui->%s = (GtkSpinButton*) gtk_spin_button_new (\n"
             "\t          NULL, 0, 0);\n",
             widget->name             
            );  
  }
}

void create_gtk_model_button( g2cWidget *widget )
{
gchar *action = NULL;    
    fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkModelButton*) gtk_model_button_new();\n",
            widget->name);
    action = g2c_widget_get_property( widget, "action_name");
    if (action == NULL) {
        // There is no option in Glade to set the role for GtkModelButtons when there is no action
        fprintf( CURRENT_FILE,
              "\tg_object_set(G_OBJECT(gui->%s),\"role\", GTK_BUTTON_ROLE_CHECK, NULL);\n",
              widget->name);  
    }
}

void create_gtk_scrollbar( g2cWidget *widget )
{
gchar *orientation = NULL;
gchar *adjustment = NULL;
gchar *orientation1 = NULL;
 
    orientation = g2c_widget_get_property( widget,"orientation");
    adjustment  = g2c_widget_get_property( widget,"adjustment");
    if (orientation == NULL) {
        orientation1 = strdup("GTK_ORIENTATION_HORIZONTAL");
    } else {
        orientation1 = make_enumeral("GTK_ORIENTATION", orientation);
    }
    fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkScrollbar*) gtk_scrollbar_new (%s, GTK_ADJUSTMENT(gui->%s));\n",
             widget->name, orientation1, adjustment);  
    g_free( orientation1 );
}

void create_gtk_scale( g2cWidget *widget )
{
gchar *orientation = NULL;
gchar *adjustment = NULL;
gchar *orientation1 = NULL;
 
    orientation = g2c_widget_get_property( widget,"orientation");
    adjustment  = g2c_widget_get_property( widget,"adjustment");
    if (orientation == NULL) {
        orientation1 = strdup("GTK_ORIENTATION_HORIZONTAL");
    } else {
        orientation1 = make_enumeral("GTK_ORIENTATION", orientation);
    }
    fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkScale*) gtk_scale_new (%s, GTK_ADJUSTMENT(gui->%s));\n",
             widget->name, orientation1, adjustment);  
    g_free( orientation1 );    
}

void create_gtk_scrolled_window( g2cWidget *widget )
{
gchar *hpolicy = NULL;
gchar *vpolicy = NULL;
gchar *hadjustment = NULL;
gchar *vadjustment = NULL;
gchar *hpolicy_name = NULL;
gchar *vpolicy_name = NULL;
gchar *selfhadjustment = NULL;
gchar *selfvadjustment = NULL;

     g_assert( NULL != widget );
	 hadjustment = g2c_widget_get_property( widget, "hadjustment");
     vadjustment = g2c_widget_get_property( widget, "vadjustment");
     hpolicy = g2c_widget_get_property( widget, "hscrollbar_policy" ) ;
     vpolicy = g2c_widget_get_property( widget, "vscrollbar_policy" ) ;
	 if (hadjustment == NULL) {
         selfhadjustment = g_strdup( "NULL" );
     } else {
         selfhadjustment = g_strconcat( "gui->", hadjustment, NULL );
     }
     if (vadjustment == NULL) {
         selfvadjustment = g_strdup( "NULL" );
     } else {
         selfvadjustment = g_strconcat( "gui->", vadjustment, NULL );
     }
     fprintf( CURRENT_FILE,
           "\tgui->%s = (GtkScrolledWindow*) gtk_scrolled_window_new (%s, %s);\n",
             widget->name, 
             selfhadjustment, 
             selfvadjustment);     
     if (hpolicy != NULL) {
         hpolicy_name = g_strdup_printf("%s_%s", "GTK_POLICY", 
            g_utf8_strup (hpolicy, strlen(hpolicy)) );         
     }    
     if (vpolicy != NULL) {
         vpolicy_name = g_strdup_printf("%s_%s", "GTK_POLICY", 
            g_utf8_strup (vpolicy, strlen(vpolicy)) );         
     }  
     fprintf( CURRENT_FILE,
           "\tgtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(gui->%s),\n\t\t %s, %s);\n",
             widget->name, 
             (hpolicy_name == NULL) ? "GTK_POLICY_AUTOMATIC": hpolicy_name, 
             (vpolicy_name == NULL) ? "GTK_POLICY_AUTOMATIC": vpolicy_name);
			 
	 if ( hpolicy_name != NULL ) g_free( hpolicy_name );
     if ( vpolicy_name != NULL ) g_free( vpolicy_name );
	 g_free( selfhadjustment );
     g_free( selfvadjustment );
}

void create_gtk_paned ( g2cWidget *widget )
{   
gchar *orientation = NULL;
gchar *func_name = NULL;
gchar *position_set = NULL;
gchar *position_s = NULL;
     g_assert( NULL != widget );
     orientation =  g2c_widget_get_property( widget, "orientation" ) ;
     position_set =  g2c_widget_get_property( widget, "position_set" ) ;
     func_name = g2c_transform_name ( widget->klass_name, NT_FUNCTION );   /*  gtk_paned */
     if (orientation == NULL) {
         fprintf( CURRENT_FILE,
                   "\tgui->%s = (%s*) %s_new (GTK_ORIENTATION_HORIZONTAL);\n",
                   widget->name,
                   widget->klass_name,
                   func_name);
     } else {
         fprintf( CURRENT_FILE,
                   "\tgui->%s = (%s*) %s_new (%s);\n",
                   widget->name,
                   widget->klass_name,
                   func_name,                       
                   make_enumeral("GTK_ORIENTATION", orientation) );
     }
     if  (position_set == NULL) {
         fprintf( CURRENT_FILE,
                 "\tg_object_set(G_OBJECT(gui->%s),\"position_set\", FALSE, NULL);\n",
                 widget->name);
     } else {
         position_s = g2c_get_bool_s(position_set);
         fprintf( CURRENT_FILE,
                 "\tg_object_set(G_OBJECT(gui->%s),\"position_set\", %s, NULL);\n",
                 widget->name,
                 position_s);
         g_free( position_s );
     }
}

void create_gtk_separator ( g2cWidget *widget )
{   
gchar *orientation = NULL;
gchar *func_name = NULL;
     g_assert( NULL != widget );
     orientation =  g2c_widget_get_property( widget, "orientation" ) ;
     func_name = g2c_transform_name ( widget->klass_name, NT_FUNCTION );   /*  gtk_separator */
     if (orientation == NULL) {
         fprintf( CURRENT_FILE,
                   "\tgui->%s = (%s*) %s_new (GTK_ORIENTATION_HORIZONTAL);\n",
                   widget->name,
                   widget->klass_name,
                   func_name);
     } else {
         fprintf( CURRENT_FILE,
                   "\tgui->%s = (%s*) %s_new (%s);\n",
                   widget->name,
                   widget->klass_name,
                   func_name,                       
                   make_enumeral("GTK_ORIENTATION", orientation) );
     }
 
}

void create_gtk_sizegroup ( g2cWidget *widget )
{
gchar *group_mode = NULL;
gchar *mode_enum = NULL;
     g_assert( NULL != widget );
     group_mode =  g2c_widget_get_property( widget, "mode" ) ;     
     if (group_mode == NULL) {
         mode_enum = g_strdup("GTK_SIZE_GROUP_NONE");
     } else {
         mode_enum = make_enumeral("GTK_SIZE_GROUP", group_mode);
     }
     
     fprintf( CURRENT_FILE,
              "\tgui->%s = (GtkSizeGroup*) gtk_size_group_new (%s);\n",
              widget->name,                       
              mode_enum );
     g_free( mode_enum );
}

void
create_gtk_box( g2cWidget *widget )
{                                   /* for GtkBox and GtkButtonBox  */  
  gchar *orientation = NULL;
  gchar *orientation1 = NULL;
  gchar *spacing = NULL;  
  gchar *spacing1 = NULL;
  gchar *parent_name = NULL;

  g_assert( NULL != widget );

  if ( NULL != widget->child_name ) {
       g_message( "Could not handle %s\n", widget->child_name );
       g_assert_not_reached ();
       return;
  }
  if (widget->internal == FALSE) {          
      
    if (strcmp(widget->klass_name, "GtkBox") == 0) {
          
          orientation =  g2c_widget_get_property( widget, "orientation" ) ;
          spacing =  g2c_widget_get_property( widget, "spacing" ) ;

          if (orientation == NULL) {
              orientation1 = strdup("GTK_ORIENTATION_HORIZONTAL");
          } else {
               if (strcmp(orientation, "vertical") == 0) {
                   orientation1 = strdup("GTK_ORIENTATION_VERTICAL");
               } else {
                   orientation1 = strdup("GTK_ORIENTATION_HORIZONTAL");
               }
          }
          if (spacing == NULL) 
              spacing = strdup("0");

          fprintf( CURRENT_FILE,
                   "\tgui->%s = (%s*) gtk_box_new (%s,%s);\n",
                   widget->name,
                   widget->klass_name,                       
                   orientation1,
                   spacing );
          
          
      } else if (strcmp(widget->klass_name, "GtkButtonBox") == 0) {
          orientation =  g2c_widget_get_property( widget, "orientation" ) ;
          if (orientation == NULL) {
              orientation1 = strdup("GTK_ORIENTATION_HORIZONTAL");
          } else {
               if (strcmp(orientation, "vertical") == 0) {
                   orientation1 = strdup("GTK_ORIENTATION_VERTICAL");
               } else {
                   orientation1 = strdup("GTK_ORIENTATION_HORIZONTAL");
               }
          }
          fprintf( CURRENT_FILE,
                   "\tgui->%s = (%s*) gtk_button_box_new (%s);\n",
                   widget->name,
                   widget->klass_name,                       
                   orientation1 );
        }
       
    } else {   // This is a box internal to a GtkDialog or GtkAssistant or GtkInfoBar
      if (strcmp(widget->klass_name, "GtkBox") == 0) {
          if ( (strcmp(widget->parent->klass_name, "GtkDialog") == 0) ||
               (strcmp(widget->parent->klass_name, "GtkAboutDialog") == 0) ||
               (strcmp(widget->parent->klass_name, "GtkAppChooserDialog") == 0) ||
               (strcmp(widget->parent->klass_name, "GtkColorChooserDialog") == 0) ||
               (strcmp(widget->parent->klass_name, "GtkFileChooserDialog") == 0)  ||
               (strcmp(widget->parent->klass_name, "GtkFontChooserDialog") == 0)  ||
               (strcmp(widget->parent->klass_name, "GtkRecentChooserDialog") == 0)  ||
               (strcmp(widget->parent->klass_name, "GtkMessageDialog") == 0) ) {

            parent_name = g_strdup(widget->parent->name);
            fprintf( CURRENT_FILE,
                   "\tgui->%s = (%s*) gtk_dialog_get_content_area (GTK_DIALOG(gui->%s));\n\n",
                   widget->name,
                   widget->klass_name,
                   parent_name );
          } else if (strcmp(widget->parent->klass_name, "GtkInfoBar") == 0) {
            parent_name = g_strdup(widget->parent->name);
            fprintf( CURRENT_FILE,
                   "\tgui->%s = (%s*) gtk_info_bar_get_content_area  (GTK_INFO_BAR(gui->%s));\n\n",
                   widget->name,
                   widget->klass_name,
                   parent_name );  
          } else {
             g_assert( strcmp(widget->parent->klass_name, "GtkAssistant") == 0 );
             parent_name = g_strdup(widget->parent->name);
             fprintf( CURRENT_FILE,
                   "\tgui->%s = (%s*) g_object_get_data (G_OBJECT(gui->%s), \"action_area\");\n\n",                     
                   widget->name,
                   widget->klass_name,
                   parent_name ); 
          }
          
      } else if (strcmp(widget->klass_name, "GtkButtonBox") == 0) {
          
          if (strcmp(widget->parent->klass_name, "GtkInfoBar") == 0) {
              parent_name = g_strdup(widget->parent->name);
              fprintf( CURRENT_FILE,
                     "\tgui->%s = (%s*) gtk_info_bar_get_action_area (GTK_INFO_BAR(gui->%s));\n",
                     widget->name,
                     widget->klass_name,
                     parent_name );
          } else {  /* for GtkDialog there is an internal GtkBox and inside that a GtkButtonBox   */
          /*  Access to the ButtonBox is discouraged. Buttons are added using gtk_dialog_add_button. */
          /*  gtk_dialog_get_action_area is deprecated. */
//          parent_name = g_strdup(widget->parent->parent->name);
//          fprintf( CURRENT_FILE,
//                   "\tgui->%s = (%s*) gtk_dialog_get_action_area (GTK_DIALOG(gui->%s));\n\n",
//                   widget->name,
//                   widget->klass_name,
//                   parent_name );
          }

      }      
    } 
  

  if ( NULL != orientation ) g_free ( orientation );
  if ( NULL != spacing ) g_free ( spacing );
  if ( NULL != orientation1 ) g_free ( orientation1 );
  if ( NULL != spacing1 ) g_free ( spacing1 );
}

void create_gtk_window( g2cWidget *widget )
{
gchar *type = NULL;
gchar *full_type = NULL;

    g_assert( NULL != widget );
    type = g2c_widget_get_property( widget, "type" ) ;
    if (type == NULL) {
        fprintf( CURRENT_FILE,
                   "\tgui->%s = (GtkWindow*) gtk_window_new (GTK_WINDOW_TOPLEVEL);\n",
                widget->name);
    } else {
        full_type =  g_strdelimit(g_utf8_strup (type, strlen(type)),":-", '_' );  
        fprintf( CURRENT_FILE,
                   "\tgui->%s = (GtkWindow*) gtk_window_new (GTK_WINDOW_%s);\n",
                    widget->name, full_type);
    }
    
}

/* Helpers */

static gint
compare_strings( gconstpointer data,
                 gconstpointer user_data )
{
  if ( ( NULL == data ) || ( NULL == user_data ) )
    return 1;
  else
    return strcmp( ( gchar * ) data, ( gchar * ) user_data );
}

static void
g2c_widget_free_children_cb( gpointer data,
                  gpointer user_data )
{
g2cWidget *widget = (g2cWidget *) data;
  //g_print("g2c_widget_free_children_cb %s\n", widget->name);
  g2c_widget_destroy( widget );
}

static void
free_action_widgets( gpointer data,
                     gpointer user_data )
{
g2cActionWidget *action = (g2cActionWidget *) data;
    if( NULL != action->button_name)  g_free( action->button_name );
    if( NULL != action->responseid)   g_free( action->responseid );
    g_free( action );
}

static void
free_accelerators( gpointer data,
                   gpointer user_data )
{
  g2c_accel_destroy( ( g2cAccel * ) data );
}

static void
free_attributes( gpointer data,
                 gpointer user_data )
{
g2cAttribute *attrib = (g2cAttribute *) data;
    if ( NULL != attrib->key )    g_free( attrib->key );
    if ( NULL != attrib->value )  g_free( attrib->value );
    g_free( attrib );
}

static void
free_columns( gpointer data,
              gpointer user_data )
{
g2cColumn *column = (g2cColumn *) data;
    if( NULL != column->col_name )  g_free( column->col_name );
    if( NULL != column->col_type )  g_free( column->col_type );
    g_free( column );
}

static void
free_coldata( gpointer data,
              gpointer user_data )
{
g2cColdata * coldata = (g2cColdata *) data;
    if( NULL != coldata->col_value)   g_free(coldata->col_value);
    g_free( coldata );
}

void
free_comboboxtext_items( gpointer data,
                         gpointer user_data )
{
g2cItemData * itemdata = (g2cItemData *) data;
    if( NULL != itemdata->text)  g_free( itemdata->text );
    g_free( itemdata );
}

static void
free_packing (g2cPacking packing)
{
    if (NULL != packing.tab.menu_label ) g_free( packing.tab.menu_label ); 
    if (NULL != packing.stack.icon_name ) g_free( packing.stack.icon_name );
    if (NULL != packing.stack.name ) g_free( packing.stack.name );
    if (NULL != packing.stack.title ) g_free( packing.stack.title );
}

static void
free_signals( gpointer data,
              gpointer user_data )
{
  g2c_signal_destroy( ( g2cSignal * ) data );
}

static void
free_tables( gpointer data,
             gpointer user_data )
{
GList *row = (GList *) data;

   g_list_foreach( row,
                   free_coldata,
                   NULL );

   g_list_free( row ); 
}

static void
free_regster( gpointer data,
             gpointer user_data )
{
g2cRegister *reg = (g2cRegister *) data;
    if( NULL != reg->name )  g_free( reg->name );
    g_free( reg );
}

/* Class Functions */

g2cWidget *
g2c_widget_new( gchar *class_name )
{
  /* Create a new widget struct */
  g2cWidget * widget = g_new0( g2cWidget, 1 );

  allocs = allocs + 1;

  /* Create a new GList for properties etc - no-ops really */
  widget->properties = NULL; 

  widget->associates = NULL;
  widget->children = NULL;
  widget->signals = NULL;
  widget->parent = NULL;
  widget->accelerators = NULL;
  widget->accel_widgets = NULL;
  widget->popups = NULL;
  widget->comboboxtext_items = NULL;
  widget->patterns = NULL;
  widget->mime_types = NULL;
  widget->attributes = NULL;
  widget->columns = NULL;
  widget->table = NULL;
  widget->css_classes = NULL;
  widget->action_widgets = NULL;
  widget->internal = FALSE;
  widget->child_name = NULL;
  widget->packing.box.expand = FALSE;
  widget->packing.box.fill = FALSE;
  widget->packing.box.padding = 0;
  widget->packing.box.pack_type = PACK_START;
  widget->packing.grid.height = 0;
  widget->packing.grid.width = 0;
  widget->packing.grid.left_attach = 0;
  widget->packing.grid.top_attach  = 0;
  widget->packing.tab.detachable = FALSE;
  widget->packing.tab.menu_label = NULL;
  widget->packing.tab.reorderable = FALSE;
  widget->packing.tab.tab_expand = FALSE;
  widget->packing.tab.tab_fill = TRUE;
  widget->packing.layout.x = 0;
  widget->packing.layout.y = 0;
  widget->packing_type = BOX_PACKING;
  widget->packing.stack.icon_name = NULL;
  widget->packing.stack.name = NULL;
  widget->packing.stack.needs_attention = FALSE;
  widget->packing.stack.position = 0;
  widget->packing.stack.title = NULL;
  widget->sizegroup = NULL;
  widget->regster = NULL;
  widget->requires = NULL;
  
  widget->klass_name =  class_name ;
  widget->name = NULL;

  widget->klass = g_type_from_name( widget->klass_name );

  if ( G_TYPE_INVALID != widget->klass )   /*  g_type_from_name found the klass  */
    {
      if ( strcmp( widget->klass_name, "GtkBox" ) == 0 ) {  widget->klass = GTK_TYPE_BOX; 
      } else if (strcmp( widget->klass_name, "GtkDialog" ) == 0) {  widget->klass = GTK_TYPE_DIALOG;
      } else if (strcmp( widget->klass_name, "GtkButton" ) == 0) {  widget->klass = GTK_TYPE_BUTTON;
      } else if (strcmp( widget->klass_name, "GtkAssistant" ) == 0) {  widget->klass = GTK_TYPE_ASSISTANT;
      } else if (strcmp( widget->klass_name, "GtkMenuButton" ) == 0) {  widget->klass = GTK_TYPE_MENU_BUTTON;
      } else if (strcmp( widget->klass_name, "GtkCheckButton" ) == 0) { widget->klass = GTK_TYPE_CHECK_BUTTON;
      } else if (strcmp( widget->klass_name, "GtkToggleButton" ) == 0) { widget->klass = GTK_TYPE_TOGGLE_BUTTON;
      } else if (strcmp( widget->klass_name, "GtkRadioButton" ) == 0) { widget->klass = GTK_TYPE_RADIO_BUTTON;
      } else if (strcmp( widget->klass_name, "GtkFileChooserButton" ) == 0) {  widget->klass = GTK_TYPE_FILE_CHOOSER_BUTTON;
      } else if (strcmp( widget->klass_name, "GtkFileChooserDialog" ) == 0) {  widget->klass = GTK_TYPE_FILE_CHOOSER_DIALOG;
      } else if (strcmp( widget->klass_name, "GtkAppChooserDialog" ) == 0) {  widget->klass = GTK_TYPE_APP_CHOOSER_DIALOG;
      } else if (strcmp( widget->klass_name, "GtkAppChooserButton" ) == 0) {  widget->klass = GTK_TYPE_APP_CHOOSER_BUTTON;
      } else if (strcmp( widget->klass_name, "GtkFileFilter" ) == 0) {  widget->klass = GTK_TYPE_FILE_FILTER;
      } else if (strcmp( widget->klass_name, "GtkRecentFilter" ) == 0) {  widget->klass = GTK_TYPE_RECENT_FILTER;
      } else if (strcmp( widget->klass_name, "GtkButtonBox" ) == 0) { widget->klass = GTK_TYPE_BUTTON_BOX;
      } else if (strcmp( widget->klass_name, "GtkScrolledWindow" ) == 0) { widget->klass = GTK_TYPE_SCROLLED_WINDOW;
      } else if (strcmp( widget->klass_name, "GtkFrame" ) == 0) {  widget->klass = GTK_TYPE_FRAME;
      } else if (strcmp( widget->klass_name, "GtkComboBox" ) == 0 ) { widget->klass = GTK_TYPE_COMBO_BOX;
      } else if (strcmp( widget->klass_name, "GtkComboBoxText" ) == 0 ) { widget->klass = GTK_TYPE_COMBO_BOX_TEXT;
      } else if (strcmp( widget->klass_name, "GtkEntry" ) == 0) {  widget->klass = GTK_TYPE_ENTRY;
      } else if (strcmp( widget->klass_name, "GtkImage" ) == 0) {  widget->klass = GTK_TYPE_IMAGE;
      } else if (strcmp( widget->klass_name, "GtkLabel" ) == 0) {  widget->klass = GTK_TYPE_LABEL;
      } else if (strcmp( widget->klass_name, "GtkAccelLabel" ) == 0) {  widget->klass = GTK_TYPE_ACCEL_LABEL;
      } else if (strcmp( widget->klass_name, "GtkLayout" ) == 0) {  widget->klass = GTK_TYPE_LAYOUT;
      } else if (strcmp( widget->klass_name, "GtkListBoxRow" ) == 0) {  widget->klass = GTK_TYPE_LIST_BOX_ROW;
      } else if (strcmp( widget->klass_name, "GtkMenu" ) == 0) {  widget->klass = GTK_TYPE_MENU;
      } else if (strcmp( widget->klass_name, "GtkPaned" ) == 0) {  widget->klass = GTK_TYPE_PANED;
      } else if (strcmp( widget->klass_name, "GtkPopover" ) == 0) {  widget->klass = GTK_TYPE_POPOVER;
      } else if (strcmp( widget->klass_name, "GtkToolbar" ) == 0) {  widget->klass = GTK_TYPE_TOOLBAR;
      } else if (strcmp( widget->klass_name, "GtkInfoBar" ) == 0) {  widget->klass = GTK_TYPE_INFO_BAR;
      } else if (strcmp( widget->klass_name, "GtkHeaderBar" ) == 0) {  widget->klass = GTK_TYPE_HEADER_BAR;
      } else if (strcmp( widget->klass_name, "GtkToolButton" ) == 0) {  widget->klass = GTK_TYPE_TOOL_BUTTON;
      } else if (strcmp( widget->klass_name, "GtkToolItemGroup" ) == 0) {  widget->klass = GTK_TYPE_TOOL_ITEM_GROUP;
      } else if (strcmp( widget->klass_name, "GtkMenuToolButton" ) == 0) {  widget->klass = GTK_TYPE_MENU_TOOL_BUTTON;
      } else if (strcmp( widget->klass_name, "GtkRadioToolButton" ) == 0) {  widget->klass = GTK_TYPE_RADIO_TOOL_BUTTON;
      } else if (strcmp( widget->klass_name, "GtkTreeView" ) == 0) {  widget->klass = GTK_TYPE_TREE_VIEW;
      } else if (strcmp( widget->klass_name, "GtkTreeSelection" ) == 0) {  widget->klass = GTK_TYPE_TREE_SELECTION;
      } else if (strcmp( widget->klass_name, "GtkTreeViewColumn" ) == 0) {  widget->klass = GTK_TYPE_TREE_VIEW_COLUMN;
      } else if (strcmp( widget->klass_name, "GtkTreeModelSort" ) == 0) {  widget->klass = GTK_TYPE_TREE_MODEL_SORT;
      } else if (strcmp( widget->klass_name, "GtkTreeModelFilter" ) == 0) {  widget->klass = GTK_TYPE_TREE_MODEL_FILTER;
      } else if (strcmp( widget->klass_name, "GtkCheckMenuItem" ) == 0) {  widget->klass = GTK_TYPE_CHECK_MENU_ITEM;
      } else if (strcmp( widget->klass_name, "GtkRadioMenuItem" ) == 0) {  widget->klass = GTK_TYPE_RADIO_MENU_ITEM;
      } else if (strcmp( widget->klass_name, "GtkModelButton" ) == 0 ) { widget->klass = GTK_TYPE_MODEL_BUTTON;
      } else if (strcmp( widget->klass_name, "GtkScaleButton" ) == 0 ) { widget->klass = GTK_TYPE_SCALE_BUTTON;
      } else if (strcmp( widget->klass_name, "GtkFixed" ) == 0) {  widget->klass = GTK_TYPE_FIXED;
      } else if (strcmp( widget->klass_name, "GtkGrid" ) == 0) {  widget->klass = GTK_TYPE_GRID;
      } else if (strcmp( widget->klass_name, "GtkSeparator" ) == 0) {  widget->klass = GTK_TYPE_SEPARATOR;
      } else if (strcmp( widget->klass_name, "GtkStack" ) == 0) {  widget->klass = GTK_TYPE_STACK;
      } else if (strcmp( widget->klass_name, "GtkStackSwitcher" ) == 0) {  widget->klass = GTK_TYPE_STACK_SWITCHER;  
      } else if (strcmp( widget->klass_name, "GtkStackSidebar" ) == 0) {  widget->klass = GTK_TYPE_STACK_SIDEBAR;  
      } else if (strcmp( widget->klass_name, "GtkScale" ) == 0) {  widget->klass = GTK_TYPE_SCALE;
      } else if (strcmp( widget->klass_name, "GtkActionBar" ) == 0) {  widget->klass = GTK_TYPE_ACTION_BAR;
      } else if (strcmp( widget->klass_name, "GtkSearchBar" ) == 0) {  widget->klass = GTK_TYPE_SEARCH_BAR;
      } else if (strcmp( widget->klass_name, "GtkTextBuffer" ) == 0) {  widget->klass = GTK_TYPE_TEXT_BUFFER;
      } else if (strcmp( widget->klass_name, "GtkTextView" ) == 0) {  widget->klass = GTK_TYPE_TEXT_VIEW;
      } else if (strcmp( widget->klass_name, "GtkFlowBoxChild" ) == 0) {  widget->klass = GTK_TYPE_FLOW_BOX_CHILD;
      } else if (strcmp( widget->klass_name, "GtkViewport" ) == 0) {  widget->klass = GTK_TYPE_VIEWPORT;
      } else if (strcmp( widget->klass_name, "GtkAccelGroup" ) == 0) {  widget->klass = GTK_TYPE_ACCEL_GROUP;
      } else if (strcmp( widget->klass_name, "GtkRecentManager" ) == 0) {  widget->klass = GTK_TYPE_RECENT_MANAGER;
      } else if (strcmp( widget->klass_name, "GtkTextTag" ) == 0) {  widget->klass = GTK_TYPE_TEXT_TAG;
      } else if (strcmp( widget->klass_name, "GtkTextTagTable" ) == 0) {  widget->klass = GTK_TYPE_TEXT_TAG_TABLE;
      } else if (strcmp( widget->klass_name, "GtkSizeGroup" ) == 0) {  widget->klass = GTK_TYPE_SIZE_GROUP;
      } else if (strcmp( widget->klass_name, "GtkWindowGroup" ) == 0) {  widget->klass = GTK_TYPE_WINDOW_GROUP;
//      } else if (strcmp( widget->klass_name, "GtkIconFactory" ) == 0) {  widget->klass = GTK_TYPE_ICON_FACTORY;
//      } else if (strcmp( widget->klass_name, "GtkStatusIcon" ) == 0) {  widget->klass = GTK_TYPE_STATUS_ICON;
      } else  if ( NULL == g_type_class_peek( widget->klass ) )
                 g_message( "Invalid type: %s\n", widget->klass_name );
 }
  else   /*  g_type_from_name did not find the klass  */
    {
      if ( strcmp( widget->klass_name, "GtkMenuBar" ) == 0 ) widget->klass = GTK_TYPE_MENU_SHELL;
      else if ( strcmp( widget->klass_name, "GtkBox" ) == 0 ) widget->klass = GTK_TYPE_BOX;
      else if ( strcmp( widget->klass_name, "GtkButton" ) == 0 ) widget->klass = GTK_TYPE_BUTTON;
      else if ( strcmp( widget->klass_name, "GtkAccelGroup" ) == 0 ) widget->klass = GTK_TYPE_ACCEL_GROUP;
      else if ( strcmp( widget->klass_name, "GtkAccelLabel" ) == 0 ) widget->klass = GTK_TYPE_ACCEL_LABEL;      
      else if ( strcmp( widget->klass_name, "GtkAdjustment" ) == 0 ) widget->klass = G_TYPE_OBJECT;
      else if ( strcmp( widget->klass_name, "GtkAlignment" ) == 0 ) widget->klass = G_TYPE_OBJECT;
      else if ( strcmp( widget->klass_name, "GtkComboBox" ) == 0 ) widget->klass = GTK_TYPE_COMBO_BOX;
      else if ( strcmp( widget->klass_name, "GtkComboBoxText" ) == 0 ) widget->klass = GTK_TYPE_COMBO_BOX_TEXT;
      else if ( strcmp( widget->klass_name, "GtkProgressBar" ) == 0 ) widget->klass = GTK_TYPE_PROGRESS_BAR;
      else if ( strcmp( widget->klass_name, "GtkPaned" ) == 0 ) widget->klass = GTK_TYPE_PANED;      
      else if ( strcmp( widget->klass_name, "GtkButtonBox" ) == 0 ) widget->klass = GTK_TYPE_BUTTON_BOX;
      else if ( strcmp( widget->klass_name, "GtkStatusbar" ) == 0 ) widget->klass = GTK_TYPE_BOX;
      else if ( strcmp( widget->klass_name, "GtkTreeView" ) == 0 ) widget->klass = GTK_TYPE_TREE_VIEW;
      else if ( strcmp( widget->klass_name, "GtkTreeViewColumn" ) == 0 ) widget->klass = GTK_TYPE_TREE_VIEW_COLUMN;
      else if ( strcmp( widget->klass_name, "GtkTreeSelection" ) == 0 ) widget->klass = GTK_TYPE_TREE_SELECTION;
      else if ( strcmp( widget->klass_name, "GtkTreeModelSort" ) == 0) widget->klass = GTK_TYPE_TREE_MODEL_SORT;
      else if ( strcmp( widget->klass_name, "GtkTreeModelFilter" ) == 0) widget->klass = GTK_TYPE_TREE_MODEL_FILTER;
      else if ( strcmp( widget->klass_name, "GtkListStore" ) == 0 ) widget->klass = G_TYPE_OBJECT;
      else if ( strcmp( widget->klass_name, "GtkTreeStore" ) == 0 ) widget->klass = G_TYPE_OBJECT;
      else if ( strcmp( widget->klass_name, "GtkCellRendererText" ) == 0 ) widget->klass = GTK_TYPE_WIDGET;
      else if ( strcmp( widget->klass_name, "GtkCellRendererSpin" ) == 0 ) widget->klass = GTK_TYPE_WIDGET;
      else if ( strcmp( widget->klass_name, "GtkCellRendererToggle" ) == 0 ) widget->klass = GTK_TYPE_WIDGET;
      else if ( strcmp( widget->klass_name, "GtkCellRendererCombo" ) == 0 ) widget->klass = GTK_TYPE_WIDGET;
      else if ( strcmp( widget->klass_name, "GtkCellRendererAccel" ) == 0 ) widget->klass = GTK_TYPE_WIDGET;
      else if ( strcmp( widget->klass_name, "GtkCellRendererPixbuf" ) == 0 ) widget->klass = GTK_TYPE_WIDGET;
      else if ( strcmp( widget->klass_name, "GtkGrid" ) == 0 ) widget->klass = GTK_TYPE_GRID;
      else if ( strcmp( widget->klass_name, "Custom" ) == 0 ) widget->klass = GTK_TYPE_WIDGET;
      else if ( strcmp( widget->klass_name, "GtkWindow" ) == 0 ) widget->klass = GTK_TYPE_WINDOW;
      else if ( strcmp( widget->klass_name, "GtkApplicationWindow" ) == 0 ) widget->klass = GTK_TYPE_APPLICATION_WINDOW;
      else if ( strcmp( widget->klass_name, "GtkOffscreenWindow" ) == 0 ) widget->klass = GTK_TYPE_OFFSCREEN_WINDOW;
      else if ( strcmp( widget->klass_name, "GtkDialog" ) == 0 ) widget->klass = GTK_TYPE_DIALOG;
      else if ( strcmp( widget->klass_name, "GtkAssistant" ) == 0 ) widget->klass = GTK_TYPE_ASSISTANT;
      else if ( strcmp( widget->klass_name, "GtkAboutDialog" ) == 0 ) widget->klass = GTK_TYPE_ABOUT_DIALOG;
      else if ( strcmp( widget->klass_name, "GtkMessageDialog" ) == 0 ) widget->klass = GTK_TYPE_MESSAGE_DIALOG;
      else if ( strcmp( widget->klass_name, "GtkColorChooserDialog" ) == 0 ) widget->klass = GTK_TYPE_DIALOG;
      else if ( strcmp( widget->klass_name, "GtkFontChooserDialog" ) == 0 ) widget->klass = GTK_TYPE_FONT_CHOOSER_DIALOG;
      else if ( strcmp( widget->klass_name, "GtkRecentChooserDialog" ) == 0 ) widget->klass = GTK_TYPE_RECENT_CHOOSER_DIALOG;
      else if ( strcmp( widget->klass_name, "GtkFileChooserWidget" ) == 0 ) widget->klass = GTK_TYPE_FILE_CHOOSER_DIALOG;
      else if ( strcmp( widget->klass_name, "GtkColorChooserWidget" ) == 0 ) widget->klass = GTK_TYPE_DIALOG;
      else if ( strcmp( widget->klass_name, "GtkFontChooserWidget" ) == 0 ) widget->klass = GTK_TYPE_FONT_CHOOSER_DIALOG;
      else if ( strcmp( widget->klass_name, "GtkRecentChooserWidget" ) == 0 ) widget->klass = GTK_TYPE_RECENT_CHOOSER_DIALOG;
      else if ( strcmp( widget->klass_name, "GtkFileChooserDialog" ) == 0 ) widget->klass = GTK_TYPE_FILE_CHOOSER_DIALOG;
      else if ( strcmp( widget->klass_name, "GtkAppChooserDialog" ) == 0 ) widget->klass = GTK_TYPE_APP_CHOOSER_DIALOG;
      else if ( strcmp( widget->klass_name, "GtkAppChooserButton" ) == 0 ) widget->klass = GTK_TYPE_APP_CHOOSER_BUTTON;
      else if ( strcmp( widget->klass_name, "GtkFileChooserButton" ) == 0 ) widget->klass = GTK_TYPE_FILE_CHOOSER_BUTTON;
      else if ( strcmp( widget->klass_name, "GtkScrolledWindow" ) == 0 ) widget->klass = GTK_TYPE_SCROLLED_WINDOW;
      else if ( strcmp( widget->klass_name, "GtkViewport" ) == 0 ) widget->klass = GTK_TYPE_VIEWPORT;
      else if ( strcmp( widget->klass_name, "GtkFileFilter" ) == 0 ) widget->klass = GTK_TYPE_FILE_FILTER;
      else if ( strcmp( widget->klass_name, "GtkRecentFilter" ) == 0 ) widget->klass = GTK_TYPE_RECENT_FILTER;
      else if ( strcmp( widget->klass_name, "GtkRecentManager" ) == 0 ) widget->klass = GTK_TYPE_RECENT_MANAGER;  
      else if ( strcmp( widget->klass_name, "GtkFrame" ) == 0 ) widget->klass = GTK_TYPE_FRAME;
      else if ( strcmp( widget->klass_name, "GtkAspectFrame" ) == 0 ) widget->klass = GTK_TYPE_ASPECT_FRAME;
      else if ( strcmp( widget->klass_name, "GtkDrawingArea" ) == 0 ) widget->klass = GTK_TYPE_DRAWING_AREA;
      else if ( strcmp( widget->klass_name, "GtkEntry" ) == 0 ) widget->klass = GTK_TYPE_ENTRY;
      else if ( strcmp( widget->klass_name, "GtkSearchEntry" ) == 0 ) widget->klass = GTK_TYPE_SEARCH_ENTRY;
      else if ( strcmp( widget->klass_name, "GtkFixed" ) == 0 ) widget->klass = GTK_TYPE_FIXED;
      else if ( strcmp( widget->klass_name, "GtkLabel" ) == 0 ) widget->klass = GTK_TYPE_LABEL;
      else if ( strcmp( widget->klass_name, "GtkLayout" ) == 0 ) widget->klass = GTK_TYPE_LAYOUT;
      else if ( strcmp( widget->klass_name, "GtkListBox" ) == 0 ) widget->klass = GTK_TYPE_LIST_BOX;
      else if ( strcmp( widget->klass_name, "GtkListBoxRow" ) == 0 ) widget->klass = GTK_TYPE_LIST_BOX_ROW;
      else if ( strcmp( widget->klass_name, "GtkCheckButton" ) == 0 ) widget->klass = GTK_TYPE_CHECK_BUTTON;
      else if ( strcmp( widget->klass_name, "GtkMenuButton" ) == 0 ) widget->klass = GTK_TYPE_MENU_BUTTON;
      else if ( strcmp( widget->klass_name, "GtkPopover" ) == 0 ) widget->klass = GTK_TYPE_POPOVER;
      else if ( strcmp( widget->klass_name, "GtkPopoverMenu" ) == 0 ) widget->klass = GTK_TYPE_POPOVER_MENU;
      else if ( strcmp( widget->klass_name, "GtkModelButton" ) == 0 ) widget->klass = GTK_TYPE_MODEL_BUTTON;
      else if ( strcmp( widget->klass_name, "GtkImageMenuItem" ) == 0 ) widget->klass = GTK_TYPE_MENU_ITEM;
      else if ( strcmp( widget->klass_name, "GtkImage" ) == 0 ) widget->klass = GTK_TYPE_IMAGE;
      else if ( strcmp( widget->klass_name, "GtkCheckMenuItem" ) == 0 ) widget->klass = GTK_TYPE_CHECK_MENU_ITEM;
      else if ( strcmp( widget->klass_name, "GtkRadioMenuItem" ) == 0 ) widget->klass = GTK_TYPE_RADIO_MENU_ITEM;
      else if ( strcmp( widget->klass_name, "GtkSeparatorMenuItem" ) == 0 ) widget->klass = GTK_TYPE_SEPARATOR_MENU_ITEM;
      else if ( strcmp( widget->klass_name, "GtkRadioButton" ) == 0 ) widget->klass = GTK_TYPE_RADIO_BUTTON;
      else if ( strcmp( widget->klass_name, "GtkFontButton" ) == 0 ) widget->klass = GTK_TYPE_FONT_BUTTON;
      else if ( strcmp( widget->klass_name, "GtkColorButton" ) == 0 ) widget->klass = GTK_TYPE_COLOR_BUTTON;
      else if ( strcmp( widget->klass_name, "GtkSeparator" ) == 0 ) widget->klass = GTK_TYPE_SEPARATOR;
      else if ( strcmp( widget->klass_name, "GtkToolbar" ) == 0 ) widget->klass = GTK_TYPE_TOOLBAR;
      else if ( strcmp( widget->klass_name, "GtkToolButton" ) == 0 ) widget->klass = GTK_TYPE_TOOL_BUTTON;
      else if ( strcmp( widget->klass_name, "GtkSpinButton" ) == 0 ) widget->klass = GTK_TYPE_SPIN_BUTTON;
      else if ( strcmp( widget->klass_name, "GtkToggleToolButton" ) == 0 ) widget->klass = GTK_TYPE_TOGGLE_TOOL_BUTTON;
      else if ( strcmp( widget->klass_name, "GtkMenuToolButton" ) == 0 ) widget->klass = GTK_TYPE_MENU_TOOL_BUTTON;
      else if ( strcmp( widget->klass_name, "GtkRadioToolButton" ) == 0 ) widget->klass = GTK_TYPE_RADIO_TOOL_BUTTON;
      else if ( strcmp( widget->klass_name, "GtkSeparatorToolItem" ) == 0 ) widget->klass = GTK_TYPE_SEPARATOR_TOOL_ITEM;
      else if ( strcmp( widget->klass_name, "GtkToolPalette" ) == 0 ) widget->klass = GTK_TYPE_TOOL_PALETTE;
      else if ( strcmp( widget->klass_name, "GtkToolItem" ) == 0 ) widget->klass = GTK_TYPE_TOOL_ITEM;
      else if ( strcmp( widget->klass_name, "GtkToolItemGroup" ) == 0 ) widget->klass = GTK_TYPE_TOOL_ITEM_GROUP;
      else if ( strcmp( widget->klass_name, "GtkTextView" ) == 0 ) widget->klass = GTK_TYPE_TEXT_VIEW;
      else if ( strcmp( widget->klass_name, "GtkTextBuffer" ) == 0 ) widget->klass = GTK_TYPE_TEXT_BUFFER;
      else if ( strcmp( widget->klass_name, "GtkEntryBuffer" ) == 0 ) widget->klass = GTK_TYPE_ENTRY_BUFFER;
      else if ( strcmp( widget->klass_name, "GtkOverlay" ) == 0 ) widget->klass = GTK_TYPE_OVERLAY;
      else if ( strcmp( widget->klass_name, "GtkRevealer" ) == 0 ) widget->klass = GTK_TYPE_REVEALER;
      else if ( strcmp( widget->klass_name, "GtkSwitch" ) == 0 ) widget->klass = GTK_TYPE_SWITCH;
      else if ( strcmp( widget->klass_name, "GtkSpinner" ) == 0 ) widget->klass = GTK_TYPE_SPINNER;
      else if ( strcmp( widget->klass_name, "GtkTextTagTable" ) == 0)  widget->klass = GTK_TYPE_TEXT_TAG_TABLE;
      else if ( strcmp( widget->klass_name, "GtkTextTag" ) == 0)  widget->klass = GTK_TYPE_TEXT_TAG;
      else if ( strcmp( widget->klass_name, "GtkEntryCompletion" ) == 0 ) widget->klass = G_TYPE_OBJECT;
      else if ( strcmp( widget->klass_name, "GtkLinkButton" ) == 0 )  widget->klass = GTK_TYPE_LINK_BUTTON;
      else if ( strcmp( widget->klass_name, "GtkVolumeButton" ) == 0 )  widget->klass = GTK_TYPE_VOLUME_BUTTON;
      else if ( strcmp( widget->klass_name, "GtkFixed" ) == 0 ) widget->klass = GTK_TYPE_FIXED;
      else if ( strcmp( widget->klass_name, "GtkSeparator" ) == 0 ) widget->klass = GTK_TYPE_SEPARATOR;
      else if ( strcmp( widget->klass_name, "GtkStack" ) == 0 ) widget->klass = GTK_TYPE_STACK;
      else if ( strcmp( widget->klass_name, "GtkStackSwitcher" ) == 0 ) widget->klass = GTK_TYPE_STACK_SWITCHER;
      else if ( strcmp( widget->klass_name, "GtkStackSidebar" ) == 0 ) widget->klass = GTK_TYPE_STACK_SIDEBAR;
      else if ( strcmp( widget->klass_name, "GtkPlacesSidebar" ) == 0 ) widget->klass = GTK_TYPE_PLACES_SIDEBAR;
      else if ( strcmp( widget->klass_name, "GtkHeaderBar" ) == 0)   widget->klass = GTK_TYPE_HEADER_BAR;
      else if ( strcmp( widget->klass_name, "GtkScrollbar" ) == 0)   widget->klass = GTK_TYPE_SCROLLBAR;
      else if ( strcmp( widget->klass_name, "GtkScale" ) == 0)   widget->klass = GTK_TYPE_SCALE;
      else if ( strcmp( widget->klass_name, "GtkActionBar" ) == 0)   widget->klass = GTK_TYPE_ACTION_BAR;
      else if ( strcmp( widget->klass_name, "GtkSearchBar" ) == 0)   widget->klass = GTK_TYPE_SEARCH_BAR;
      else if ( strcmp( widget->klass_name, "GtkInfoBar" ) == 0)   widget->klass = GTK_TYPE_INFO_BAR;
      else if ( strcmp( widget->klass_name, "GtkLevelBar" ) == 0 ) widget->klass = GTK_TYPE_LEVEL_BAR;
      else if ( strcmp( widget->klass_name, "GtkCalendar" ) == 0 ) widget->klass = GTK_TYPE_CALENDAR;
      else if ( strcmp( widget->klass_name, "GtkIconView" ) == 0 ) widget->klass = GTK_TYPE_ICON_VIEW;
      else if ( strcmp( widget->klass_name, "GtkFlowBox" ) == 0 ) widget->klass = GTK_TYPE_FLOW_BOX;
      else if ( strcmp( widget->klass_name, "GtkFlowBoxChild" ) == 0 ) widget->klass = GTK_TYPE_FLOW_BOX_CHILD;
      else if ( strcmp( widget->klass_name, "GtkSizeGroup" ) == 0)     widget->klass = GTK_TYPE_SIZE_GROUP;
      else if ( strcmp( widget->klass_name, "GtkWindowGroup" ) == 0)   widget->klass = GTK_TYPE_WINDOW_GROUP;
      else if ( strcmp( widget->klass_name, "GtkStatusIcon" ) == 0 ) widget->klass = GTK_TYPE_STATUS_ICON;
      else
        {
          g_message( "Unhandled class, %s, set to GtkWidget\n", widget->klass_name );
          widget->klass = GTK_TYPE_WIDGET;
        }
    }

  return widget;
}

void
g2c_widget_destroy( g2cWidget *widget )
{
g2cProplist *proplist = NULL;
gboolean    propmore = TRUE;
gchar *key = NULL;
gchar *value = NULL;
GList *run;
gchar *text = NULL;

  //g_print("g2c_widget_destroy %s\n", widget->name);
  allocs = allocs - 1;

  proplist = proplist_start(widget);
  propmore = proplist_readnext(&proplist, &key, &value);
  while (propmore == TRUE) {      
      propmore = proplist_readnext(&proplist, &key, &value);      
  }
  
  proplist_end(proplist);
  
  proplist_destroy(widget);
  
  /* Free the sub-widgets */
  if ( widget->children )
    {
      if (strcmp(widget->klass_name, "GtkAccelGroup") != 0) {
         g_list_foreach( widget->children,
                      g2c_widget_free_children_cb,
                      NULL );
      }
    //g_list_free( widget->children );
    }
  
  if ( widget->signals )
    {
      g_list_foreach( widget->signals,
                      free_signals,
                      NULL );

      g_list_free( widget->signals );
    }

  if ( widget->accelerators )
    {
      g_list_foreach( widget->accelerators,
                      free_accelerators,
                      NULL );

      g_list_free( widget->accelerators );
    }
  
  if ( widget->columns )
    {
      g_list_foreach( widget->columns,
                      free_columns,
                      NULL );

      g_list_free( widget->columns );
    }
  
  if ( widget->table )
    {
      g_list_foreach( widget->table,
                      free_tables,
                      NULL );

      g_list_free( widget->table );
    }
  
  if ( widget->css_classes )
    {
       run = g_list_first(widget->css_classes);
       while (run != NULL) {
            text = (gchar *) run->data;
            g_free( text );
            run = g_list_next( run ); 
       }
       g_list_free( widget->css_classes );
    }
  
  if ( widget->comboboxtext_items )
  {
      g_list_foreach( widget->comboboxtext_items,
                      free_comboboxtext_items,
                      NULL );

      g_list_free( widget->comboboxtext_items );
  }
  
  if ( widget->action_widgets )
    {
      g_list_foreach( widget->action_widgets,
                      free_action_widgets,
                      NULL );

      g_list_free( widget->action_widgets );
    }
  
  if ( widget->patterns )
    {
       run = g_list_first(widget->patterns);
       while (run != NULL) {
            text = (gchar *) run->data;
            g_free( text );
            run = g_list_next( run ); 
       }
       g_list_free( widget->patterns );
    }
  
  if ( widget->mime_types )
    {
       run = g_list_first(widget->mime_types);
       while (run != NULL) {
            text = (gchar *) run->data;
            g_free( text );
            run = g_list_next( run ); 
       }
       g_list_free( widget->mime_types );
    }
  
  if ( widget->attributes )
    {
      g_list_foreach( widget->attributes,
                      free_attributes,
                      NULL );

      g_list_free( widget->attributes );
    }
  
  if ( widget->sizegroup )
    {
       run = g_list_first(widget->sizegroup);
       while (run != NULL) {
            text = (gchar *) run->data;
            g_free( text );
            run = g_list_next( run ); 
       }
       g_list_free( widget->sizegroup );
    }
  
  if ( widget->regster )
    {
      g_list_foreach( widget->regster,
                      free_regster,
                      NULL );

      g_list_free( widget->regster );
    }
  if ( widget->requires )
  {
    g_list_free_full(widget->requires, free_requires);
  }

  if (NULL != widget->name)       g_free (widget->name);
  if (NULL != widget->child_name) g_free (widget->child_name);
  if (NULL != widget->klass_name) g_free (widget->klass_name);
  
  free_packing( widget->packing );

  g_free( widget );
}

g2cWidget *
g2c_widget_get_top_parent( g2cWidget *widget )
{
  g2cWidget * result = NULL;
  result = widget;

  while ( NULL != result->parent )
    {
      result = result->parent;
    }

  return result;
}

void
g2c_widget_set_order( g2cWidget *widget, gint order )
{
  widget->order = order;
}

void
g2c_widget_set_property( g2cWidget *widget,
                         const gchar *name,
                         const gchar *value )
{
//  if ( strcmp( name, "name" ) == 0 )
//    {
//      if (NULL != widget->name) 
//	g_free (widget->name);
//      
//      /* We don't want any "-" in the name, so convert to "_" */
//      //widget->name = g_strdup( value );
//      //widget->name = g_strdelimit( widget->name, ":-", '_' );
//      proplist_add(widget, name, value);
//    }
//  else 
      if ( strcmp( name, "class" ) == 0 )
    {
      if (NULL != widget->klass_name) 
	g_free (widget->klass_name);
      
      widget->klass_name = g_strdup( value );
    }
/*
  else if ( strcmp( name, "child_name" ) == 0 )
    {
      if (NULL != widget->child_name) 
	g_free (widget->child_name);
      
      widget->child_name = g_strdup( value );
    }
*/
  else
    {
      //g_message("g2c_widget_set_property called for %s %s %s\n", widget->name, name, value);
      /* Add to the list of managed properties */
      
      proplist_add(widget, name, value);
    
    }
}

gchar *
g2c_widget_get_property( g2cWidget *widget,
                         const gchar *name )
{
  if ( NULL == name ) return NULL;
  if ( strcmp( name, "name" ) == 0 ) return widget->name;
  
  else if ( strcmp( name, "class" ) == 0 ) return widget->klass_name;
  
  else return proplist_lookup(widget, name) ;
}

void
g2c_widget_add_subwidget( g2cWidget *widget, g2cWidget *subwidget )
{
  subwidget->parent = widget;

  if ( g_type_is_a( widget->klass, GTK_TYPE_NOTEBOOK ) &&
       g_type_is_a( subwidget->klass, GTK_TYPE_LABEL ) )
    {
      /* Special treatment for notebook tab labels.
       * The last widget (usually box) appended will be the widget
       * that is added to the notebook.  This label widget
       * is the tab's label for the aforementioned widget.
       * In the XML file the label follows the widgets constituting 
       * the page. Prepending brings it to the front so that it can 
       * be created before it is referenced.
       */
      g2c_widget_set_property((g2cWidget*) g_list_last (widget->children)->data,
                               "_tab_label",
                               subwidget->name);

      widget->children = g_list_prepend( widget->children, subwidget );
    }
  else
    widget->children = g_list_append( widget->children, subwidget );
}

void
g2c_widget_add_action_widget( g2cWidget *widget,
                         const gchar *button_name,
                         const gchar *response )
{
g2cActionWidget * action_widget = g_new0( g2cActionWidget, 1 );

  action_widget->button_name = g_strdup(button_name);
  action_widget->responseid = g_strdup(response);
  
  //g_message("add action widget: %s response: %s\n", button_name, response);
  widget->action_widgets = g_list_append( widget->action_widgets, action_widget ); 

}

gchar*
g2c_widget_get_action_widget(g2cWidget *widget,
                            const gchar *button_name )
{
GList *run = NULL;
g2cActionWidget * action_widget = NULL;

      run = g_list_first( widget->action_widgets );
      while ( NULL != run )   {
	action_widget = (g2cActionWidget *) run->data;
	if (strcmp(action_widget->button_name, button_name) == 0) {
	   return (action_widget->responseid);
         }
         run = g_list_next( run );
      }
    return NULL;
    
}

void
g2c_widget_add_signal( g2cWidget *widget, g2cSignal *signal )
{
  widget->signals = g_list_append( widget->signals, signal );
}

void
g2c_widget_add_accel( g2cWidget *widget,
                      g2cAccel *accel )
{
  widget->accelerators = g_list_append( widget->accelerators, accel );
}

void
g2c_widget_add_focus_target( g2cWidget *widget,
                             const gchar *focus_target )
{
  g2cAccel * accel = NULL;
  g2cWidget *parent = NULL;
  gchar *key = NULL;

  g_assert( widget != NULL );
  g_assert( focus_target != NULL );

  key = g_strconcat( focus_target, "_", widget->name, "_key", NULL );

  accel = g2c_accel_new();
  g2c_accel_set_modifiers( accel, "GDK_MOD1_MASK" );
  g2c_accel_set_key( accel, key );

  /* We don't set the signal, since it depends on the type of the focus target widget */
  g2c_accel_set_focus_target( accel, focus_target );

  /* We add this accelerator to the top-level widget.  We do this to simplify processing
   * later on.  If a focus_target is present in an accelerator, then we do special processing.  
   * See g2c_doc.c::output_widget_files.
   */
  parent = g2c_widget_get_top_parent( widget );

  g2c_widget_add_accel( parent, accel );

  if ( NULL != key ) g_free( key );
}

void
g2c_widget_create_signal_connect_cb( gpointer data,
                                     gpointer user_data )
{
  /* data      = signal
   * user_data = widget
   *
   * Each signal connected to the widget will produce a line of code
   * in the source file.  For now this function produces generic
   * calls to connect the signal, so the arguments will be arg1, arg2, etc.
   *
   * Future versions will have lookup tables to get the exact arg names.
   * For now, though, this is a quick and easy way to handle all possible
   * signals.
   */

  g2cSignal * signal = ( g2cSignal * ) data;
  g2cWidget *widget = ( g2cWidget * ) user_data;

  /* Should look like this:
   *   g_signal_connect( G_OBJECT( gui->widget_name ), "signal-name",
   *                       GTK_SIGNAL_FUNC( handler ),
   *                       NULL );
   */
  fprintf( CURRENT_FILE, "\tg_signal_connect%s%s%s (G_OBJECT (gui->%s), \"%s\",\n",
           ( signal->after == TRUE ) ? "_after" : "",
           ( signal->object != NULL ) ? "_object" : "",
           ( signal->swapped == TRUE ) ? "_swapped" : "",
           widget->name,
           signal->name );

  fprintf( CURRENT_FILE, "\t                    G_CALLBACK (%s),\n",
           signal->handler );

  /* If signal->object is present, use it,
   * else you signal->data, else it's NULL */
  if ( NULL != signal->object ) {
    fprintf( CURRENT_FILE, "\t                    G_OBJECT (gui->%s),\n", signal->object );
    fprintf( CURRENT_FILE, "\t                    G_CONNECT_AFTER);\n\n");
  } else if ( NULL != signal->data )
    fprintf( CURRENT_FILE, "\t                    (gpointer) %s);\n\n", signal->data );
  else
    fprintf( CURRENT_FILE, "\t                    %s);\n\n", "NULL" );
}

void
g2c_widget_create_signal_prototype_cb( gpointer data,
                                       gpointer user_data )
{
  /* data      = signal
   * user_data = widget
   *
   * Each signal connected to the widget will produce a line of code
   * in the source file.  For now this function produces generic
   * calls to connect the signal, so the arguments will be arg1, arg2, etc.
   *
   * Future versions will have lookup tables to get the exact arg names.
   * For now, though, this is a quick and easy way to handle all possible
   * signals.
   * 
   * Since the user may connect several widget signals to one handler,
   * we need to make sure that there are no duplicates in the .c/.h files.
   * We DO need to connect all of the handlers, though!
   */

  g2cSignal * signal = ( g2cSignal * ) data;
  g2cWidget *widget = ( g2cWidget * ) user_data;

  GSignalQuery signal_query;
  GType signal_type = 0;
  guint signal_id = 0;
  guint i = 0;
  guint arg_name_index = 0;
  gboolean has_extra_args = FALSE;
  GType arg_name_type;
  gchar *event = NULL;
  //guint key = 0;
  //GdkModifierType modifier = 0;
  gchar *keystr = NULL; 
  gchar *modifierstr = NULL;
  
  if (strcmp(signal->handler, "gtk_main_quit") == 0 ) {
      return;
  }

  /* Make sure we haven't already added this function */
  if (is_in_signal_list (signal->handler))
    return;
  else
    add_to_signal_list (signal->handler);
  
  if (signal->swapped == TRUE) return;

  g_type_class_ref( widget->klass );   /* stops "unable to lookup signal" error  */
  signal_type = widget->klass;
  extract_signal(&event, &keystr, &modifierstr, signal->name);
  signal_id = g_signal_lookup( event, signal_type );
  if (signal_id > 0)
     g_signal_query( signal_id, &signal_query );

  while ( NULL != signal_param_names[ arg_name_index ][ 0 ] )
    {
      arg_name_type = g_type_from_name( signal_param_names[ arg_name_index ][ 0 ] );

      if ( ( strcmp( widget->klass_name, signal_param_names[ arg_name_index ][ 0 ] ) == 0 ) &&   // g_type_is_a
           ( strcmp( event, signal_param_names[ arg_name_index ][ 1 ] ) == 0 ) )
        {
          has_extra_args = TRUE;
          break;
        }
      arg_name_index++;
    }
  if ( signal_id == 0 )
    {      
      //g_message("signal lookup fails in prototype for event %s\n", signal->name);
      signal_query.n_params = 0;
      if (has_extra_args == FALSE) {
          arg_name_index = 0;
          while ( NULL != signal_param_names[ arg_name_index ][ 0 ] )
            {
              arg_name_type = g_type_from_name( signal_param_names[ arg_name_index ][ 0 ] );
              
//              if ( ( strcmp( "GtkWidget", signal_param_names[ arg_name_index ][ 0 ] ) == 0 ) &&   // g_type_is_a
//                   ( strcmp( event, signal_param_names[ arg_name_index ][ 1 ] ) == 0 ) )
              if ( ( strcmp( widget->klass_name, signal_param_names[ arg_name_index ][ 0 ] ) == 0 ) &&   // g_type_is_a doesn't work                
                   ( strcmp( event, signal_param_names[ arg_name_index ][ 1 ] ) == 0 ) )    
                {
                  has_extra_args = TRUE;
                  break;
                }
              arg_name_index++;
            }
      }
      fprintf( CURRENT_FILE, "void\n");
        
      fprintf (CURRENT_FILE, "%s (%s* widget,\n",
	   signal->handler,  widget->klass_name);
      /* Print each of the args for the signal */
      i = 2;
      if (has_extra_args == TRUE) {
          while (signal_param_names[ arg_name_index ][ i ] != NULL) {
            fprintf( CURRENT_FILE, "\t%-25s arg%d,\n",                      
                       signal_param_names[ arg_name_index ][ i ],   /* takes the param type from g2c_signals.h  */
                    i);
            i++;    
          }
      }
      fprintf( CURRENT_FILE, "\t%-25s user_data);\n\n", "gpointer" );
      
    } else {

  /* Should look like this:
   *   return_code 
   *   handler( WidgetType *widget_name,
   *            ArgType arg1,
   *            ArgType argN,
   *            gpointer user_data );
   */
  fprintf( CURRENT_FILE, "%s%s\n",
           g_type_name( signal_query.return_type ),
           G_TYPE_FUNDAMENTAL( signal_query.return_type ) == G_TYPE_OBJECT ? "*" : "" );

  //fprintf (CURRENT_FILE, "%s (GtkWidget* widget,\n",
  //	   signal->handler);

  
  fprintf( CURRENT_FILE, "%s (%s* %s,\n",
           signal->handler,
           widget->klass_name,
	   //GTK_FUNDAMENTAL_TYPE( widget->klass ) == GTK_TYPE_OBJECT ? "*" : "", 
           widget->name );
  

  /* Print each of the args for the signal */
  for ( i = 0; i < signal_query.n_params; i++ )
    {
      if ( TRUE == has_extra_args )
        {
          fprintf( CURRENT_FILE, "\t%-25s %s,\n",
                  signal_param_names[ arg_name_index ][ i + 2 ],
                  g_type_name( signal_query.param_types[ i ] ) 
                  );
        }
      else
        {
          /* <tab>argtype argN, */
          fprintf( CURRENT_FILE, "\t%-25s *arg%d,\n",
                   g_type_name( signal_query.param_types[ i ] ), i );
        }
    }
  fprintf( CURRENT_FILE, "\t%-25s user_data);\n\n", "gpointer" );
  
    }
  g_free( keystr );
  g_free( modifierstr );
}

void 
g2c_widget_create_closure_connect(g2cSignal * signal, g2cWidget *accel_widget)
{  

  gchar *event = NULL;
  //guint accel_key = 0;
  //GdkModifierType accel_mods = 0;
  gchar *accel_key_str = NULL;
  gchar *accel_mods_str = NULL;
  g2cRegister *reg = NULL;
  g2cWidget  *main_widget = CURRENT_PROJECT->main_widget;
  g2cWidget  *object = NULL;
  guint signal_id = 0;  

	extract_signal(&event, &accel_key_str, &accel_mods_str, signal->name);

	fprintf (CURRENT_FILE, 
	"\tgtk_accel_group_connect (gui->%s, %s, %s,\n"                         
                         "\t\t\tGTK_ACCEL_VISIBLE,\n"
                         "\t\t\tg_cclosure_new(G_CALLBACK(%s), NULL, NULL));\n\n",
		accel_widget->name, accel_key_str, accel_mods_str, signal->handler);
        if (signal->object != NULL) {
            // find widget klass for signal object
            reg = find_widget_by_name(main_widget->regster, signal->object);
            object = reg->widget;
            // try a few events. Any other likely possibilities?
            signal_id = g_signal_lookup("activate", object->klass);
            if (signal_id != 0) { 
                g_free( event );
                event = g_strdup("activate");
            } else {
                signal_id = g_signal_lookup("clicked", object->klass);
                if (signal_id != 0) { 
                    g_free( event );
                    event = g_strdup("clicked");
                } else {
                    signal_id = g_signal_lookup("toggled", object->klass);
                    if (signal_id != 0) { 
                        g_free( event );
                        event = g_strdup("toggled");
                    }
                }
            }
            fprintf (CURRENT_FILE, 
            "\tgtk_widget_add_accelerator (GTK_WIDGET(gui->%s), \"%s\", gui->%s,\n"
                             "\t\t\t%s, %s,\n"   // GdkModifierType
                             "\t\t\tGTK_ACCEL_VISIBLE);\n\n",
            //signal->object, "activate", accel_widget->name, accel_key_str, accel_mods_str);
             signal->object, event, accel_widget->name, accel_key_str, accel_mods_str);
        } else {
            g_message("For Accelerator Group %s, in the Signals tab, the keystroke %s has no 'user data' (widget id). Using %s.\n", 
                    accel_widget->name, signal->name, MAIN_WINDOW );
            fprintf (CURRENT_FILE, 
            "\tgtk_widget_add_accelerator (GTK_WIDGET(gui->%s), \"%s\", gui->%s,\n"
                             "\t\t\t%s, %s,\n"   // GdkModifierType
                             "\t\t\tGTK_ACCEL_VISIBLE);\n\n",
                    MAIN_WINDOW, "activate_default", accel_widget->name, accel_key_str, accel_mods_str);
        }

/* For accel_group property of a widget - ignore, put with accel group signal.  */
  g_free( event );
  g_free( accel_key_str );
  g_free( accel_mods_str );
}

void
g2c_widget_create_closure_prototype( g2cSignal * signal,
                                     g2cWidget * widget )
{
  /*    
   * 
   * Since the user may connect several widget signals to one handler,
   * we need to make sure that there are no duplicates in the .c/.h files.
   * We DO need to connect all of the handlers, though!
   */
  gchar *event = NULL;
  //guint key = 0;
  //GdkModifierType modifier = 0;
  gchar *keystr = NULL; 
  gchar *modifierstr = NULL;

  /* Make sure we haven't already added this function */
  if (is_in_signal_list (signal->handler))
    return;
  else
    add_to_signal_list (signal->handler);

  //signal_type = widget->klass;
  extract_signal(&event, &keystr, &modifierstr, signal->name);
  fprintf( CURRENT_FILE, "gboolean\n");
        
  fprintf (CURRENT_FILE, "%s (GtkAccelGroup * accel_group,\n",
	   signal->handler);

  fprintf (CURRENT_FILE, "\t%-25s *acceleratable,\n", "GObject");

  fprintf (CURRENT_FILE, "\t%-25s keyval,\n", "guint");
     
  fprintf (CURRENT_FILE, "\t%-25s modifier);\n", "GdkModifierType");                                     
    
  g_free( keystr );
  g_free( modifierstr );
}

void
g2c_widget_create_closure_handler( g2cSignal * signal,
                                   g2cWidget * widget )
{
  /*    
   * 
   * Since the user may connect several widget signals to one handler,
   * we need to make sure that there are no duplicates in the .c/.h files.
   * We DO need to connect all of the handlers, though!
   */
  gchar *event = NULL;
  //guint key = 0;
  //GdkModifierType modifier = 0;
  g2cWidget *window = NULL;
  gchar *window_class = NULL;
  gchar *keystr = NULL; 
  gchar *modifierstr = NULL;

  /* Make sure we haven't already added this function */
  if (is_in_signal_list (signal->handler))
    return;
  else
    add_to_signal_list (signal->handler);

  extract_signal(&event, &keystr, &modifierstr, signal->name);
  
  window = g2c_widget_get_top_parent( widget );
  window_class = g2c_transform_name( window->name, NT_TYPENAME );
  
  fprintf( CURRENT_FILE, "gboolean\n");
        
  fprintf (CURRENT_FILE, "%s (GtkAccelGroup * accel_group,\n",
	   signal->handler);

  fprintf (CURRENT_FILE, "\t%-25s *acceleratable,\n", "GObject");

  fprintf (CURRENT_FILE, "\t%-25s keyval,\n", "guint");
     
  fprintf (CURRENT_FILE, "\t%-25s modifier)\n", "GdkModifierType");  

  fprintf( CURRENT_FILE,
           "{\n"
           "\t/* %s *prog = (%s*) g_object_get_data (G_OBJECT (acceleratable), \"owner\"); */\n"
           "\n"         
          "\treturn TRUE;\n"
           "}\n\n",           
           window_class,  /* Window1 */
           //window->name,  /* window1 */
           window_class   /* Window1 */           
         );                                   
  g_free( keystr );
  g_free( modifierstr );                      
}

void
g2c_widget_create_signal_handler_cb( g2cDoc *doc, g2cSignal * signal,
                                     g2cWidget *widget)
{
  /* 
   * Each signal connected to the widget will produce a line of code
   * in the source file.  For now this function produces generic
   * calls to connect the signal, so the arguments will be arg1, arg2, etc.
   *
   * Future versions will have lookup tables to get the exact arg names.
   * For now, though, this is a quick and easy way to handle all possible
   * signals.
   *
   * Note that we only output the function if it has not been written yet!
   * Check the parser to see if this function is already implemented.
   *
   */
  
  g2cWidget *window = NULL;
  gchar *window_class = NULL;

  GSignalQuery signal_query;
  GType signal_type = 0;
  guint signal_id = 0;
  gchar *event = NULL;
  gchar *keystr = NULL; 
  gchar *modifierstr = NULL;
  guint i = 0;
  guint arg_name_index = 0;
  gboolean has_extra_args = FALSE;
  GType arg_name_type;

  guint file_len = 0;
  guint cur_pos = 0;
  gchar *end_text = NULL;
  
  if (strcmp(signal->handler, "gtk_main_quit") == 0 ) {
      return;
  }

  /* Make sure we haven't already added this function */
  if (is_in_signal_list (signal->handler))
    return;
  else
    add_to_signal_list (signal->handler);
  
  if (signal->swapped == TRUE) return;
  
  //window = g2c_widget_get_top_parent( widget );
  window = doc->project->main_widget;
  window_class = g2c_transform_name( window->name, NT_TYPENAME );
  
  extract_signal(&event, &keystr, &modifierstr, signal->name);

  if ( NULL != CURRENT_SOURCE_PARSER )
    {
      if ( g2c_file_parser_item_exists( CURRENT_SOURCE_PARSER, signal->handler ) ) {          
        goto finish;
      } else {
        g_print("  Handler '%s' is new. Included in generated file.\n", signal->handler); 
      }
    }

  arg_name_index = 0;
  while ( NULL != signal_param_names[ arg_name_index ][ 0 ] )
    {
      arg_name_type = g_type_from_name( signal_param_names[ arg_name_index ][ 0 ] );

        if ( //( g_type_is_a( widget->klass, arg_name_type ) ) &&
               ( strcmp( widget->klass_name, signal_param_names[ arg_name_index ][ 0 ] ) == 0 ) &&
           ( strcmp( signal->name, signal_param_names[ arg_name_index ][ 1 ] ) == 0 ) )
        {
          has_extra_args = TRUE;
          break;
        }
      arg_name_index++;
    }

  g_type_class_ref( widget->klass );   /* stops "unable to lookup signal" error  */
  signal_type = widget->klass;
  signal_id = g_signal_lookup( signal->name, signal_type );
  if (signal_id > 0) 
    g_signal_query( signal_id, &signal_query );
  
  //g_assert( 0 != signal_query.signal_id );

  /* Should look like this:
   *   return_code 
   *   handler( WidgetType* widget_name,
   *            ArgType arg1,
   *            ArgType argN,
   *            gpointer user_data )
   *   {
   *     Window2 *window2 = (Window2*) g_object_get_data( G_OBJECT( interrupt_button ), "owner" ); 
   *   }
   */ 
  
  if ( signal_id == 0 )
    {
      //g_message("signal lookup fails in handler for event %s\n", signal->name);
      signal_query.n_params = 0;
 
      if (has_extra_args == FALSE) {
          arg_name_index = 0;
          while ( NULL != signal_param_names[ arg_name_index ][ 0 ] )
            {
              arg_name_type = g_type_from_name( signal_param_names[ arg_name_index ][ 0 ] );
              
              
              if ( ( strcmp( widget->klass_name, signal_param_names[ arg_name_index ][ 0 ] ) == 0 ) &&                         
                   ( strcmp( event, signal_param_names[ arg_name_index ][ 1 ] ) == 0 ) )    
                {
                  has_extra_args = TRUE;
                  g_message("Found extra args for handler of: class: %s, event: %s\n", widget->klass_name, signal->name ); 
                  break;
                }
              arg_name_index++;
            }
      }
      fprintf( CURRENT_FILE, "void\n");
        
      fprintf (CURRENT_FILE, "%s (%s* %s,\n",
	      signal->handler, 
              widget->klass_name, 
              widget->name);
      /* Print each of the args for the signal */
      i = 2;
      if (has_extra_args == TRUE) {
          while (signal_param_names[ arg_name_index ][ i ] != NULL) {
            fprintf( CURRENT_FILE, "\t%-25s arg%d,\n",                       
                       signal_param_names[ arg_name_index ][ i ],
                    i);
            i++;    
          }
      }
      
 }  else {      /*  lookup succeeded  */
  fprintf( CURRENT_FILE, "%s%s\n",
           g_type_name( signal_query.return_type ),
           G_TYPE_FUNDAMENTAL( signal_query.return_type ) == G_TYPE_OBJECT ? "*" : "" );

  fprintf( CURRENT_FILE, "%s (%s* %s,\n",           
           signal->handler,
           widget->klass_name,
           widget->name);
  

  /*
  fprintf( CURRENT_FILE, "%s (%s %s%s,\n",
           signal->handler,
           widget->klass_name,
           G_TYPE_FUNDAMENTAL( widget->klass ) == GTK_TYPE_OBJECT ? "*" : "",
           widget->name );
  */

  /* Print each of the args for the signal */
  for ( i = 0; i < signal_query.n_params; i++ )
    {
      if ( TRUE == has_extra_args )   
        {   /* found in g2c_signals.h   */
          fprintf( CURRENT_FILE, "\t%-25s %s,\n",                   
                   signal_param_names[ arg_name_index ][ i + 2 ],   /*  take the param type from g2c_signals.h  */
                   g_type_name( signal_query.param_types[ i ] )
                  );
        }
      else
        {
          /* <tab>argtype argN, */    
          /* if not found take the param type from the signal query */
            fprintf( CURRENT_FILE, "\t%-25s *arg%d,\n",
                     g_type_name( signal_query.param_types[ i ] ), i );         
        }
    }
 }
  fprintf( CURRENT_FILE, "\t%-25s user_data)\n\n", "gpointer" );
  fprintf( CURRENT_FILE,
           "{\n"
           "\t/* %s *%s = (%s*) g_object_get_data (G_OBJECT (%s), \"owner\"); */\n"
           "\n" ,
           window_class,  /* Top Window */
           "prog",  /* top-level instance  */
           window_class,  /* Top Window */
           widget->name   /* first argument - the object of the signal  */
         );
  if (signal_id > 0) {
    if ( strcmp(g_type_name( signal_query.return_type ), "gboolean") == 0 ) {
        end_text = g_strdup("\treturn FALSE;\n"
                           "}\n\n");
    } else {
        end_text = g_strdup("\treturn;\n"
                          "}\n\n");
    }
  } else {
      end_text = g_strdup("\treturn;\n"
                          "}\n\n");
  }
  
  /* Copy the end text back to the end of the file */
  if ( NULL != end_text )
    {
      fprintf( CURRENT_FILE, (char *) end_text, NULL );
    }

finish:

  if ( NULL != window_class ) g_free( window_class );
  if ( NULL != end_text ) g_free( end_text );
}

void
g2c_widget_create_struct_cb( gpointer data,
                             gpointer user_data )
{
  /* data      = gchar     *name
   * user_data = g2cWidget *widget
   *
   * Print out the type and name of this widget
   * <tab> type name;
   *
   */

  /*  gchar      *name   = (gchar *) data; */
  g2cWidget * widget = ( g2cWidget * ) user_data;

  fprintf( CURRENT_FILE,
           "\t%s %s%s;\n",
           widget->klass_name,
           "*",
           widget->name );
}

void
g2c_widget_create_temp_declaration_cb( gpointer data,
                                       gpointer user_data )
{
  /* data      = g2cWidget  *widget
   * user_data = unused
   *
   * Print out temporary variables 
   * <tab> guint focus_key_name = 0;
   *
   */
    
  g2cWidget *widget = ( g2cWidget * ) data;
  gboolean pixbuf = FALSE;
  
  g_assert( NULL != widget );
  
  /*  GtkCombo is deprecated and should not be used in newly-written code.  */
  
  if ( ( ( strcmp( widget->klass_name, "GtkWindow" ) == 0 ) ||
          ( strcmp( widget->klass_name, "GtkDialog" ) == 0 ) ||
          ( strcmp( widget->klass_name, "GtkAboutDialog" ) == 0 ) ||
          ( strcmp( widget->klass_name, "GtkAppChooserDialog" ) == 0 ) ||
          ( strcmp( widget->klass_name, "GtkFileChooserDialog" ) == 0 ) ||
          ( strcmp( widget->klass_name, "GtkFontChooserDialog" ) == 0 ) ||
          ( strcmp( widget->klass_name, "GtkColorChooserDialog" ) == 0 ) ||
          ( strcmp( widget->klass_name, "GtkMessageDialog" ) == 0 ) ||
          ( strcmp( widget->klass_name, "GtkRecentChooserDialog" ) == 0 ) )&& 
       ( g2c_widget_get_property( widget, "icon") != NULL ) )
  {
      pixbuf = TRUE;
  }
//  if ( ( strcmp( widget->klass_name, "GtkImage" ) == 0 ) && 
//          ((g2c_widget_get_property( widget, "pixbuf") != NULL ) ||   /*  ignored  */
//           (g2c_widget_get_property( widget, "resource") != NULL )) ) /*  ignored  */
//  {
//      pixbuf = TRUE;
//  }
  if ( ( ( strcmp( widget->klass_name, "GtkEntry" ) == 0 ) ||
         ( strcmp( widget->klass_name, "GtkSearchEntry" ) == 0 ) ||
         ( strcmp( widget->klass_name, "GtkSpinButton" ) == 0 ) ) &&
       ( g2c_widget_get_property( widget, "primary_icon_pixbuf") != NULL ) )
  {
      pixbuf = TRUE;
  }
  if (pixbuf == TRUE ) 
  {
      fprintf( CURRENT_FILE,
               "GdkPixbuf *%s_pixbuf = NULL;\n",
               widget->name );
      fprintf( CURRENT_FILE,
               "GError *%s_error = NULL;\n",
               widget->name );
  }
  if ( ( ( strcmp( widget->klass_name, "GtkEntry" ) == 0 ) ||
         ( strcmp( widget->klass_name, "GtkSearchEntry" ) == 0 )  ||
         ( strcmp( widget->klass_name, "GtkSpinButton" ) == 0 ) ) && 
       ( g2c_widget_get_property( widget, "secondary_icon_pixbuf") != NULL ) )
  {
      fprintf( CURRENT_FILE,
               "GdkPixbuf *pixbuf_%s = NULL;\n",
               widget->name );
      fprintf( CURRENT_FILE,
               "GError *error_%s = NULL;\n",
               widget->name );    
  }
  if (( strcmp( widget->klass_name, "GtkCellRendererText" ) == 0 ) ||
      ( strcmp( widget->klass_name, "GtkCellRendererSpin" ) == 0 ) ||
      ( strcmp( widget->klass_name, "GtkCellRendererCombo" ) == 0 ) ||
      ( strcmp( widget->klass_name, "GtkCellRendererAccel" ) == 0 ) ||
      ( strcmp( widget->klass_name, "GtkCellRendererToggle" ) == 0 ) ||
      ( strcmp( widget->klass_name, "GtkCellRendererPixbuf" ) == 0 ) ||
      ( strcmp( widget->klass_name, "GtkTextTag" ) == 0 ) )    
  { 
        if ((g2c_widget_get_property( widget, "background_rgba") != NULL ) || 
            (g2c_widget_get_property( widget, "cell_background_rgba") != NULL ) )
        {
          fprintf( CURRENT_FILE,
                     "GdkRGBA rgb_%s;\n",
                     widget->name );
        }
        if (g2c_widget_get_property( widget, "foreground_rgba") != NULL ) 
        {
          fprintf( CURRENT_FILE,
                     "GdkRGBA %s_rgb;\n",
                     widget->name );
        }
        if (g2c_widget_get_property( widget, "strikethrough_rgba") != NULL ) 
        {
          fprintf( CURRENT_FILE,
                     "GdkRGBA %s_strgb;\n",
                     widget->name );
        }
        if (g2c_widget_get_property( widget, "underline_rgba") != NULL ) 
        {
          fprintf( CURRENT_FILE,
                     "GdkRGBA %s_ulrgb;\n",
                     widget->name );
        }
        if (g2c_widget_get_property( widget, "paragraph_background_rgba") != NULL ) 
        {
          fprintf( CURRENT_FILE,
                     "GdkRGBA %s_pbrgb;\n",
                     widget->name );
        }
  }
  if (widget->attributes != NULL) {
  GList *run =  g_list_first(widget->attributes);
  g2cAttribute *attrib = NULL;
      fprintf( CURRENT_FILE,
                  "PangoAttrList *%s_attrlist = pango_attr_list_new();\n", widget->name);
  }
  if ( (widget->parent != NULL) && (strcmp( widget->parent->klass_name,"GtkStack" ) == 0 ) ) {
      if (widget->packing.stack.icon_name != NULL) {
          fprintf( CURRENT_FILE,
                  "GValue %s_icon_name = G_VALUE_INIT;\n",
                  widget->name);
      }
      if (widget->packing.stack.needs_attention != FALSE) {
          fprintf( CURRENT_FILE,
                  "GValue %s_needs_attention = G_VALUE_INIT;\n",
                  widget->name);
      }
      if (widget->packing.stack.position != 0) {
          fprintf( CURRENT_FILE,
                  "GValue %s_position = G_VALUE_INIT;\n",
                  widget->name);
      }
  }
  if ( ( widget->parent != NULL ) && 
       ( strcmp( widget->parent->klass_name,"GtkPopoverMenu" ) == 0 ) ) {
      if ( g2c_widget_get_property( widget, "_submenu" ) != NULL ) {
        fprintf( CURRENT_FILE,
                  "GValue %s_submenu = G_VALUE_INIT;\n",
                  widget->name);
      }
      if ( g2c_widget_get_property( widget, "_position" ) != NULL ) {
        fprintf( CURRENT_FILE,
                  "GValue %s_submenu_position = G_VALUE_INIT;\n",
                  widget->name);
      }
  }
  if (widget->css_classes != NULL) {
      GList *css_class =  g_list_first(widget->css_classes);
      gint i = 0;
      while (css_class != NULL) {
         i++;
         fprintf( CURRENT_FILE,
               "GtkCssProvider *%s_provider_%02d = gtk_css_provider_new ();\n",
               widget->name, i );
         css_class = css_class->next;
      }
  }

}

void
g2c_widget_create_accel_declaration_cb( gpointer data,
                                        gpointer user_data )
{
  /* data      = g2cWidget  *widget
   * user_data = unused
   *
   * Print out the variables to hold the accelerator keys
   * <tab> guint focus_key_name = 0;
   *
   */

  g2cWidget * widget = ( g2cWidget * ) data;

  g_assert( NULL != widget );

  /* Handle button/label accelerators */

  if ( NULL != widget->parent )
    {
      if ( NULL != widget->parent->parent )
        {
          if ( g_type_is_a( widget->parent->parent->klass, GTK_TYPE_COMBO_BOX_TEXT ) ) return ;
        }
    }

  if ( g_type_is_a( widget->klass, GTK_TYPE_BUTTON ) &&
       !g_type_is_a( widget->klass, GTK_TYPE_COMBO_BOX_TEXT ) )
    {
      fprintf( CURRENT_FILE,
               "\tguint %s_key = 0;\n",
               widget->name );
    }
  else if ( g_type_is_a( widget->klass, GTK_TYPE_MENU_ITEM ) )
    {
      if ( NULL != g2c_widget_get_property( widget, "label" ) )
        {
          fprintf( CURRENT_FILE,
                   "\tguint %s_key = 0;\n",
                   widget->name );
        }
    }
  else if ( g_type_is_a( widget->klass, GTK_TYPE_LABEL ) &&
            ( NULL != widget->child_name ) )
    {
      fprintf( CURRENT_FILE,
               "\tguint %s_key = 0;\n",
               widget->name );
    }
}

void
g2c_widget_create_focus_accel_declaration_cb( gpointer data,
    gpointer user_data )
{
  /* data      = g2cAccel  *accel
   * user_data = g2cWidget *widget
   *
   * Print out the variables to hold the accelerator keys
   * <tab> guint focus_key_name;
   *
   */

  g2cAccel * accel = ( g2cAccel * ) data;
  g2cWidget *widget = ( g2cWidget * ) user_data;

  g_assert( NULL != accel );
  g_assert( NULL != widget );


  /* Handle focus targets */
  if ( NULL != accel->focus_target )
    {
      fprintf( CURRENT_FILE,
               "\tguint %s = 0;\n",
               accel->key );
    }
}

void
g2c_widget_create_accel_cb( gpointer data,
                            gpointer user_data )
{
  /* data      = g2cAccel  *accel
   * user_data = g2cWidget *widget
   *
   * Print out the accelerators for this widget
   * <tab> gtk_widget_add_accelerator (close_button, "released", accel_group,
   *                          GDK_b, GDK_CONTROL_MASK | GDK_SHIFT_MASK,
   *                          GTK_ACCEL_VISIBLE);
   *
   */

  g2cAccel * accel = ( g2cAccel * ) data;
  g2cWidget *widget = ( g2cWidget * ) user_data;
  g2cWidget *target_widget = NULL;
  gchar *accel_group = NULL;
  gchar *key = NULL;
  GList *signal_run  = NULL;
  gchar *handler = NULL;
  g2cSignal *signal2 = NULL;
  gchar *accel_group_name = NULL;
  gchar *modifiers = NULL;

  g_assert( NULL != accel );
  g_assert( NULL != widget );

    /* Is this a focus_target accelerator? */
  if ( NULL != accel->focus_target )
    {
      /* Get the corresponding widget */
      target_widget = g2c_widget_find_by_name( g2c_widget_get_top_parent( widget ),
                      accel->focus_target );

      g2c_accel_set_signal( accel, "grab_focus" );
    }

  /* Accelerators for GtkImageMenuItem are handled by menu_item_use_stock */
  if ( strcmp( widget->klass_name, "GtkImageMenuItem" ) == 0 )
    {
      return;
/*
      accel_group_name = g2c_widget_get_property( widget, "accel_group" );
      if (accel_group_name != NULL) {
         accel_group = g_strdup_printf( "gui->%s", accel_group_name);
      } else {
         accel_group = g_strdup_printf( "gui->%s_accel_group", widget->parent->name );
      }
*/
    }
  else
    {
      accel_group = g_strdup( "gui->accel_group" );
    }
  
  handler = find_signal_handler(widget, accel->signal);
  
  if (handler == NULL ) {
      g_message( "An accelerator %s is set in the Common tab for %s, with event %s, but there's no handler.\n", accel->key,  widget->name, accel->signal );
      g_message( "  If you create an accelerator for a widget there must be a handler for the signal to accelerate\n");
      return;
  }
  /*  /usr/include/gtk-3.0/gdk/gdkkeysyms.h   */
  key = g_strdup_printf( "GDK_KEY_%s", accel->key);
  
/*
  fprintf (CURRENT_FILE, 
	"\tgtk_accel_group_connect (%s, %s, %s,\n"                         
                         "\t\t\tGTK_ACCEL_VISIBLE,\n"
                         "\t\t\tg_cclosure_new(G_CALLBACK(%s), NULL, NULL));\n\n",
		accel_group, key, accel->modifiers, handler);
*/
  
  if (strlen(accel->modifiers) == 0) {
      modifiers = g_strdup("0");
  } else {
      modifiers = g_strdup(accel->modifiers);
  }
  fprintf( CURRENT_FILE,
           "\tgtk_widget_add_accelerator (GTK_WIDGET (gui->%s), \"%s\", %s,\n"
           "\t\t%s, %s,\n"
           "\t\t%s);\n\n",
           ( NULL != accel->focus_target ) ? accel->focus_target : widget->name,
           accel->signal,
           accel_group,
           key,
           modifiers,
           "GTK_ACCEL_VISIBLE" );
  g_free( modifiers );

  if ( NULL != accel_group ) g_free( accel_group );
  g_free ( key );
}

void
g2c_widget_create_arg_cb( gchar *name,
                          gchar *value,
                          g2cWidget * widget )
{
  /* key       = name
   * data      = value
   * user_data = widget
   */

  //g2cWidget * widget = ( g2cWidget * ) user_data;
  //gchar *name = (gchar *) key;
  //gchar *value = ( gchar * ) data;
  gchar *func_prefix = NULL;
  gchar *type_name = NULL;
  gchar *type_name_temp = NULL;
  gchar *temp_value = NULL;
  gchar *remap_name = NULL;
  gchar *msg = NULL;
  GtkArgInfo *arg_info = NULL;
  gboolean flag;
  
  //g_message("g2c_widget_create_arg_cb called for %s %s %s\n", widget->klass_name, name, value);
  
  if (strcmp(name, "visible") == 0)   {
      if (g2c_get_bool(value) == TRUE) {
         fprintf( CURRENT_FILE,
               "\tgtk_widget_show (GTK_WIDGET (gui->%s));\n", widget->name); 
      }
      return;
  }
      
  /* Should we worry about this property? */
  if ( g2c_widget_ignore_param( widget, name ) == TRUE ) return ;
  
  /* Is this type remapped? */
  remap_name = g2c_widget_remap_param( widget, name ); 

  /* Is there a special handler for this property? */
  if ( g2c_widget_special_handler( widget, remap_name ) == TRUE ) return ;
  
  /*  Handle common property independent of widget class  */
  if ( g2c_widget_common_param ( widget, remap_name, name) == TRUE ) return;  
  
  func_prefix = g2c_transform_name(widget->klass_name, NT_FUNCTION);
  type_name_temp = g2c_transform_name(widget->klass_name, NT_FUNCTION);
  type_name = g_utf8_strup(type_name_temp, strlen(type_name_temp));
  temp_value = g2c_format_argument(widget->klass_name, name, value);  
   
  fprintf(CURRENT_FILE, "\t%s_set_%s(%s(gui->%s),%s );\n", 
          func_prefix, remap_name, type_name, widget->name, temp_value);
      
  g_free( func_prefix );
  g_free( type_name );
  g_free( type_name_temp );
  g_free( temp_value );
  
}

gchar *
g2c_widget_create_string( g2cWidget *widget )
{
  /* The create string for each widget may be a little different.
   * Under most circumstances, it is simply <widget_class>_new().
   * We keep a list of alternative functions, so check there first.
   * If not listed in the alternative functions list, just return the
   * standard <widget_class>_new().
   */

  int i = 0;
  int j = 0;
  int k = 0;
  gchar *result = NULL;
  gchar *str = NULL;
  gchar *temp_param = NULL;
  gchar *params[ MAX_CREATE_PARAMS ];
  gchar *param_str = NULL;
  gchar *func_str = NULL;
  gchar *trans_name = g2c_transform_name( widget->klass_name, NT_FUNCTION );

  for ( k = 0; k < MAX_CREATE_PARAMS; k++ )
    params[ k ] = NULL;

  /* Look up in table */
  while ( NULL != create_functions[ i ].widget_class )
    {
      if ( strcmp( widget->klass_name, create_functions[ i ].widget_class ) == 0 )
        {
          /* Is there a special function for this class? */
          if ( NULL != create_functions[ i ].handler )
            {
              ( *( create_functions[ i ].handler ) ) ( widget );

              g_free ( trans_name );

              return NULL;
            }

          /* Get the parameters values */
          while ( NULL != create_functions[ i ].parameters[ j ] )
            {
              g_assert( j <= MAX_CREATE_PARAMS );

              temp_param = g_strdup( g2c_widget_get_property( widget,
                                     create_functions[ i ].parameters[ j ] ) );

              /* If this is a string value, quote it */
              params[ j ] = g2c_format_argument( widget->klass_name,
                                                 create_functions[ i ].parameters[ j ],
                                                 temp_param );

              g_free( temp_param );

              j++;
            }
          params[ j ] = NULL;

          /* Can't think of a better way.  Suggestions wilkommen. */
          func_str = g_strdup_printf( create_functions[ i ].create_function,
                                      params[ 0 ],
                                      params[ 1 ],
                                      params[ 2 ],
                                      params[ 3 ],
                                      params[ 4 ],
                                      params[ 5 ],
                                      params[ 6 ],
                                      params[ 7 ],
                                      params[ 8 ],
                                      params[ 9 ]
                                    );

          str = g_strdup_printf( "\tgui->%s = (%s*) %s;\n",
                                 widget->name,
                                 widget->klass_name,
                                 func_str );

          g_free( func_str );
          g_free( param_str );

          for ( i = 0; i < MAX_CREATE_PARAMS; i++ )
            if ( NULL != params[ i ] )
              g_free( params[ i ] );

          g_free ( trans_name );

          return str;
        }

      i++;
    }

  /* Return the standard create function */
  result = g_strdup_printf( "\tgui->%s = (%s*) %s_new ();\n",
                            widget->name,
                            widget->klass_name,
                            trans_name );
  g_free ( trans_name );

  return result;
}

g2cWidget *
g2c_widget_find_by_name( g2cWidget *widget, const gchar *widget_name )
{
  GList * child = NULL;
  g2cWidget *target = NULL;

  g_assert( widget != NULL );
  g_assert( widget_name != NULL );

  if ( strcmp( widget->name, widget_name ) == 0 )
    return widget;

  child = g_list_first( widget->children );

  while ( NULL != child )
    {
      target = g2c_widget_find_by_name( ( g2cWidget * ) child->data, widget_name );
      if ( NULL != target ) break;

      child = g_list_next( child );
    }

  return target;
}

g2cWidget *
g2c_widget_find_by_type_name( g2cWidget *widget, const gchar *type_name )
{
  GList * child = NULL;
  g2cWidget *target = NULL;

  g_assert( widget != NULL );
  g_assert( type_name != NULL );

  if ( strcmp( widget->klass_name, type_name ) == 0 )
    return widget;

  child = g_list_first( widget->children );

  while ( NULL != child )
    {
      target = g2c_widget_find_by_type_name( ( g2cWidget * ) child->data, type_name );
      if ( NULL != target ) break;

      child = g_list_next( child );
    }

  return target;
}

g2cWidget *
g2c_widget_find_by_type( g2cWidget *widget, GType type )
{
  /* Finds the first child widget of the given type */
  GList * child = NULL;
  g2cWidget *target = NULL;

  g_assert( widget != NULL );

  if ( g_type_is_a( widget->klass, type ) )
    return widget;

  child = g_list_first( widget->children );

  while ( NULL != child )
    {
      target = g2c_widget_find_by_type( ( g2cWidget * ) child->data, type );
      if ( NULL != target ) break;

      child = g_list_next( child );
    }

  return target;
}


void
g2c_widget_output_after_children_cb( gpointer key,
                                     gpointer data,
                                     gpointer user_data )
{
  gchar * param = ( gchar * ) key;
  gchar *value = ( gchar * ) data;
  g2cWidget *widget = ( g2cWidget * ) user_data;

  int i = 0;
  int j = 0;
  gchar *params[ MAX_CREATE_PARAMS ];
  GType param_type;

  g_assert( NULL != param );

  // g_assert( NULL != value );
  if ( NULL == value )
    {
      g_message( "NULL value for %s in %s\n", param, widget->name );
      value = "";
    }

  g_assert( NULL != widget );

  /* If this parameter is in the list of parameters in after_params,
   * then either output a formatted statement or call a handler function
   */

/*
  while ( NULL != after_params[ i ].param )
    {
      param_type = g_type_from_name( after_params[ i ].type );
      if ( g_type_is_a( widget->klass, param_type ) ||
           strcmp( widget->klass_name, after_params[ i ].type ) == 0 )
        {
          if ( strcmp( after_params[ i ].param, param ) == 0 )
            {
              /* Does this handler have a special function to call? 
              if ( NULL != after_params[ i ].handler )
                {
                  ( *( after_params[ i ].handler ) ) ( widget );

                  return ;  /* It was handled! 
                }

              /* Use the format function 
              for ( j = 0; j < MAX_CREATE_PARAMS; j++ )
                params[ j ] = g2c_get_bool_s( g2c_widget_get_property( widget,
                                              after_params[ i ].params[ j ] ) );

              /* Can't think of a better way.  Suggestions wilkommen. 
              fprintf( CURRENT_FILE,
                       after_params[ i ].format,
                       params[ 0 ],
                       params[ 1 ],
                       params[ 2 ],
                       params[ 3 ],
                       params[ 4 ]
                     );

              for ( j = 0; j < MAX_CREATE_PARAMS; j++ )
                g_free( params[ j ] );
            }
        }
      i++;
    }
*/
}

gboolean
g2c_widget_common_param( g2cWidget *widget,
                            gchar *keyword,
                            gchar *old_keyword)
{
int i = 0;
gchar *value   = NULL;
gchar *print_value = NULL;
gchar *func_name = NULL;
gchar *caps_name = NULL;
gchar *name = NULL;

while ( NULL != common_params[ i ].property )
    {      
      if ( strcmp( keyword, common_params[ i ].property ) == 0 )
        {
          
          value = g2c_widget_get_property( widget, old_keyword);
          if (common_params[ i ].prefix != NULL) {
              if (strcmp(common_params[ i ].prefix,"int") == 0) {
                 print_value = g_strdup(value);  /* i.e. no quotation marks  */ 
              } else if (strcmp(common_params[ i ].prefix,"char") == 0) {
                 print_value = g2c_stringify( value );   /* i.e. force quotation marks  */ 
              } else if (strcmp(common_params[ i ].prefix,"widget") == 0) {
                 print_value = g_strdup_printf("GTK_WIDGET(gui->%s)", value);
              } else {
                 print_value = g_strdup_printf("%s_%s", common_params[ i ].prefix, g_strdelimit(g_utf8_strup (value, strlen(value)),":-", '_' ) );
              } 
          } else {
              print_value = g2c_format_argument(widget->klass_name, keyword, value); 
          }
          if (common_params[ i ].alternative != NULL) {   /* alternative should be the type name e.g. GtkButtonBox */
              func_name = g2c_transform_name ( common_params[ i ].alternative, NT_FUNCTION );   /* e.g. gtk_button_box */
              caps_name = g_utf8_strup (func_name, strlen(func_name)); /* e.g. GTK_BUTTON_BOX  */
              fprintf( CURRENT_FILE, "\t%s_set_%s ( %s (gui->%s), %s);\n",
                          func_name, keyword, caps_name, widget->name, print_value);
          } else {                                     
              if (common_params[ i ].use == TRUE ) {  /* can use gtk_widget call  */                   
                  
                  fprintf( CURRENT_FILE, "\tgtk_widget_set_%s ( GTK_WIDGET (gui->%s), %s);\n",
                          keyword, widget->name, print_value ); 
                  
              } else {           /*  must use g_object_set call   */
                  fprintf( CURRENT_FILE, "\tg_object_set(G_OBJECT(gui->%s),%s, %s, NULL);\n",
                          widget->name, g2c_stringify(keyword), print_value);
              }
          }
          g_free(print_value);          
          return TRUE;
          
        }
      i++;
    }
return FALSE;
}

gboolean
g2c_widget_ignore_param( g2cWidget *widget,
                         gchar *param )
{
  int i = 0;
  GType param_type;

  while ( NULL != ignore_params[ i ].type )
    {
      param_type = g_type_from_name( ignore_params[ i ].type );
      if ( g_type_is_a( widget->klass, param_type ) ||  
           strcmp( widget->klass_name, ignore_params[ i ].type ) == 0 )
        {
          if ( strcmp( ignore_params[ i ].param, param ) == 0 )
            return TRUE;
        }
      i++;
    }

  i = 0;

  while ( NULL != after_params[ i ].type )
    {      
      if ( strcmp( param, after_params[ i ].type ) == 0 )
        {          
            return TRUE;
        }
      i++;
    }

  return FALSE;
}

gchar *
g2c_widget_remap_param( g2cWidget *widget,
                        gchar *param )
{
  int i = 0;
  GType param_type;

  while ( NULL != remap_params[ i ].type )
    {
      param_type = g_type_from_name( remap_params[ i ].type );
      if ( (strcmp( widget->klass_name, remap_params[ i ].type ) == 0)  )
        {
          if ( strcmp( remap_params[ i ].old_param, param ) == 0 ) {
             //  g_message("      successful remap from %s to %s\n", param, remap_params[ i ].new_param );
            return g_strdup( remap_params[ i ].new_param );
          }
        }
      else if ( strcmp("common", remap_params[ i ].type ) == 0 )
        {
          if ( strcmp( remap_params[ i ].old_param, param ) == 0 ) {
            //    g_message("      successful remap from %s to %s\n", param, remap_params[ i ].new_param );
            return g_strdup( remap_params[ i ].new_param );
          }
        }
      i++;
    }

  return g_strdup( param );
}

gboolean
g2c_widget_special_handler( g2cWidget *widget,
                            gchar *keyword )
{
  int i = 0;
  int j = 0;
  gchar *params[ MAX_CREATE_PARAMS ];
  GType param_type;

  while ( NULL != special_handlers[ i ].keyword )
    {
      param_type = g_type_from_name( special_handlers[ i ].type );

      if ( g_type_is_a( widget->klass, param_type ) ||
           ( strcmp( widget->klass_name, special_handlers[ i ].type ) == 0 ) ||
           (  strcmp ( "Common", special_handlers[ i ].type ) == 0 ) )
        {
          if ( strcmp( special_handlers[ i ].keyword, keyword ) == 0 )
            {
              /* Does this handler have a special function to call? */
              if ( NULL != special_handlers[ i ].handler )
                {
                  ( *( special_handlers[ i ].handler ) ) ( widget );

                  return TRUE;  /* It was handled! */
                }
              /* Does this handler have a conditional use? */
              if ( NULL != special_handlers[ i ].conditional )
                {
                  if ( !g2c_get_bool( g2c_widget_get_property( widget,
                                      special_handlers[ i ].conditional ) ) )
                    return TRUE;  /* It was handled! */
                }

              for ( j = 0; j < MAX_CREATE_PARAMS; j++ )
                params[ j ] = NULL;

              for ( j = 0; j < MAX_CREATE_PARAMS; j++ )
                {
                  /* Handle null fields */
                  if ( NULL == special_handlers[ i ].params[ j ] )
                    {
                      params[ j ] = NULL;
                    }
                  /* Handle string values */
                  else if ( strncmp( special_handlers[ i ].params[ j ], "$", 1 ) == 0 )
                    {
                      params[ j ] = g2c_stringify( g2c_widget_get_property( widget,
                                                   special_handlers[ i ].params[ j ] + 1 ) );
                    }
                  /* Handle NULL values */
                  else if ( NULL == g2c_widget_get_property( widget, special_handlers[ i ].params[ j ] ) )
                    {
                      params[ j ] = NULL;
                    }
                  /* Handle boolean values */
                  else
                    {
                      params[ j ] = g2c_get_bool_s( g2c_widget_get_property( widget,
                                                    special_handlers[ i ].params[ j ] ) );
                    }
                }

              /* Can't think of a better way.  Suggestions wilkommen.   varags? */
              fprintf( CURRENT_FILE,
                       special_handlers[ i ].format,
                       params[ 0 ],
                       params[ 1 ],
                       params[ 2 ],
                       params[ 3 ],
                       params[ 4 ],
                       params[ 5 ],
                       params[ 6 ],
                       params[ 7 ],
                       params[ 8 ],
                       params[ 9 ]
                     );

              for ( j = 0; j < MAX_CREATE_PARAMS; j++ )
                if ( params[ j ] != NULL ) g_free( params[ j ] );

              return TRUE;
            }
        }
      i++;
    }

  return FALSE;
}

guint
position_after_last_brace( FILE *file )
{
  /* Find the last brace in the file */
  long pos = 0;
  int rc = 0;
  guint len = 0;

  rc = fseek( file, pos, SEEK_END );
  g_assert( rc == 0 );

  len = ftell( file );

  while ( TRUE )
    {
      pos--;

      rc = fseek( file, pos, SEEK_END );
      if ( rc != 0 )
        {
          if ( 0 != ftell( file ) )
            {
              /* No functions found.  Odd.  Place at end of file */
              fseek( file, 0, SEEK_END );

              return 0;
            }
          else
            {
              g_message( "fseek returned %d when pos=%ld\n", rc, pos );
              g_assert_not_reached();
            }
        }

      /* Test the current character to see if it is a }.
       * If so, then we just read past it, so the file location
       * is right after the brace
       */
      rc = fgetc( file );
      if ( rc == '}' ) break;
    }

  return len;
}

void push_to_stack( g2cWidget *widget, FILE *file )
{
/*  widget could be any container but its parent must be GtkStack  */
gchar *name = NULL;
gchar *title = NULL;

    g_assert (widget->parent->klass == GTK_TYPE_STACK );
    if (widget->packing.stack.name == NULL) {
        g_message("Name missing from stack component %s\n", widget->name);
        return;
    }
    if (widget->packing.stack.title == NULL) 
    {
        fprintf( file,
                "\tgtk_stack_add_named (GTK_STACK (gui->%s),\n"
                "\t\tGTK_WIDGET (gui->%s),\n"
                "\t\t%s);\n",
                widget->parent->name,   /* stack */
                widget->name,           /*  box  */
                g2c_stringify(widget->packing.stack.name) );
    } else {
        fprintf( file,
                "\tgtk_stack_add_titled (GTK_STACK (gui->%s),\n"
                "\t\tGTK_WIDGET (gui->%s),\n"
                "\t\t%s, %s);\n",
                widget->parent->name,   /* stack */
                widget->name,           /*  box  */
                g2c_stringify(widget->packing.stack.name), 
                g2c_stringify(widget->packing.stack.title)  );
    }
    if (widget->packing.stack.icon_name != NULL) {
        fprintf( file,
                "\tg_value_init (&%s_icon_name, G_TYPE_STRING);\n",
                widget->name);
        fprintf( file,
                "\tg_value_set_string(&%s_icon_name, %s);\n",
                widget->name, 
                g2c_stringify(widget->packing.stack.icon_name) ); 
        fprintf( file,
                "\tgtk_container_child_set_property(GTK_CONTAINER(gui->%s),\n"
                "\t\t\t\tGTK_WIDGET(gui->%s), \"icon-name\", &%s_icon_name);\n",
                widget->parent->name, 
                widget->name, 
                widget->name );
    }
    if (widget->packing.stack.needs_attention == TRUE) {
        fprintf( file,
                "\tg_value_init (&%s_needs_attention, G_TYPE_BOOLEAN);\n",
                widget->name);
        fprintf( file,
                "\tg_value_set_boolean(&%s_needs_attention, %s);\n",
                widget->name, 
                g2c_get_bool_b(widget->packing.stack.needs_attention) ); 
        fprintf( file,
                "\tgtk_container_child_set_property(GTK_CONTAINER(gui->%s),\n"
                "\t\t\tGTK_WIDGET(gui->%s), \"needs-attention\", &%s_needs_attention);\n",
                widget->parent->name, 
                widget->name, 
                widget->name);
    }
    if (widget->packing.stack.position != 0) {
        fprintf( file,
                "\tg_value_init (&%s_position, G_TYPE_UINT);\n",
                widget->name);
        fprintf( file,
                "\tg_value_set_uint(&%s_position, %d);\n",
                widget->name, 
                widget->packing.stack.position ); 
        fprintf( file,
                "\tgtk_container_child_set_property(GTK_CONTAINER(gui->%s),\n"
                "\t\t\tGTK_WIDGET(gui->%s), \"position\", &%s_position);\n",
                widget->parent->name, 
                widget->name,  
                widget->name);
    }
}

gchar *
find_signal_handler(g2cWidget *widget,
                    gchar *signal_name)
{   /* get handler from signal for the widget */
GList *signal_run  = NULL;
gchar *handler = NULL;
g2cSignal *signal = NULL;
//gchar *signal = NULL;

  signal_run = widget->signals;
  while (signal_run != NULL) {
     signal = (g2cSignal *) signal_run->data; 
     if (strcmp(signal->name, signal_name) ==  0) {
            handler = g_strdup(signal->handler);
            break;
     }               
     signal_run = signal_run->next;
  } 
  return handler;
}
        





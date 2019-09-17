#ifndef SIGNALS_H
#define SIGNALS_H

// Arguments of signal handlers
// 1st entry is the class name
// 2nd entry is the event (signal) name
// 3rd and following entries are the additional arguments in between the first and the last.
// The last always seems to be: "gpointer    user_data)"  and is added automatically.

gchar *signal_param_names[][10] =
  {
    { "GtkCellRendererToggle", "toggled", "gchar *"},
    { "GtkCellRendererCombo","changed","gchar *","GtkTreeIter *"},
    { "GtkCellRendererText","edited","gchar *","gchar *"},
    { "GtkCellRendererSpin","edited","gchar *","gchar *"},
    { "GtkCellRenderer","editing_started","GtkCellEditable *","gchar *"},
    { "GtkCellRendererText","editing_started","GtkCellEditable *","gchar *"},
    { "GtkCellRenderer","editing_started","GtkCellEditable *","gchar *"},
    { "GtkCellRendererAccel","accel_edited","gchar*","gint","GdkModifierType","guint"},
    { "GtkCellRendererAccel","accel_cleared","gchar*"},
    { "GtkTreeView","row_activated","GtkTreePath*","GtkTreeViewColumn*"},
    { "GtkTreeView","row_collapsed","GtkTreeIter*","GtkTreePath*"},
    { "GtkTreeView","row_expanded","GtkTreeIter*","GtkTreePath*"},
    { "GtkTreeModel","row_changed","GtkTreePath*","GtkTreeIter*"},
    { "GtkTreeModel","row_deleted","GtkTreePath*"},
    { "GtkTreeModel","row_inserted","GtkTreePath*","GtkTreeIter*"},
    { "GtkTreeModel","has_child_toggled","GtkTreePath*","GtkTreeIter*"},
    { "GtkModelButton","clicked"},
    { "GtkEntry","delete_from_cursor","GtkDeleteType","gint"},
    { "GtkEntry","insert_at_cursor","gchar*"},
    { "GtkDialog","response","gint"},
    { "GtkDrawingArea", "draw", "cairo_t*" },
    { "GtkInfoBar", "response", "gint"},
    { "GtkWindow","set-focus","GtkWidget*"},
    { "GtkContainer", "add", "GtkWidget*" },
    { "GtkContainer", "remove", "GtkWidget*" },
    { "GtkContainer", "set_focus_child", "GtkWidget*" },
    { "GtkEditable", "insert_text", "gchar*", "int", "gpointer" },
    { "GtkEditable", "delete_text", "gint", "gint" },
    { "GtkMenuShell", "move_current", "GtkMenuDirectionType" },
    { "GtkMenuShell", "activate_current", "gboolean" },
    { "GtkMenuShell", "move_selected", "gint" },
    { "GtkNotebook", "switch_page", "GtkWidget*", "guint" },
    { "GtkNotebook", "select_page", "gboolean"},
    { "GtkStatusBar", "text_pushed", "guint", "gchar*" },
    { "GtkStatusBar", "text_popped", "guint", "gchar*" },
    { "GtkToolbar", "orientation_changed", "GtkOrientation" },
    { "GtkLabel", "populate_popup", "GtkMenu*" },
    { "GtkListBox", "row_activated", "GtkListBoxRow*" },
    { "GtkToolbar", "style_changed", "GtkToolBarStyle" },
    { "GtkWidget", "button_press_event", "GdkEventButton*"}, 
    { "GtkWidget", "scroll_event", "GdkEventScroll*"}, 
    { "GtkWidget", "size_allocate", "gint", "gint", "gint" },
    { "GtkWidget", "state_flags_changed", "GtkStateFlags" },
    { "GtkWidget", "enter_notify_event", "GdkEvent*" },
    { "GtkWidget", "leave_notify_event", "GdkEvent*" },
    { "GtkWidget", "configure_event", "GdkEvent*" },
    { "GtkWidget", "focus_in_event", "GdkEvent*" },
    { "GtkWidget", "focus_out_event", "GdkEvent*" },
    { "GtkWidget", "map_event", "GdkEvent*" },
    { "GtkWidget", "unmap_event", "GdkEvent*" },
    { "GtkWidget", "property_notify_event", "GdkEvent*" },
    { "GtkWidget", "selection_clear_event", "GdkEvent*" },
    { "GtkWidget", "selection_request_event", "GdkEvent*" },
    { "GtkWidget", "selection_notify_event", "GdkEvent*" },
    { "GtkWidget", "selection_received", "GtkSelectionData*", "guint" },
    { "GtkWidget", "selection_get", "GtkSelectionData*", "guint", "guint" },
    { "GtkWidget", "proximity_in_event", "GdkEvent*" },
    { "GtkWidget", "proximity_out_event", "GdkEvent*" },
    { "GtkWidget", "drag_leave", "GdkDragContext*", "guint" },
    { "GtkWidget", "drag_begin", "GdkDragContext*" },
    { "GtkWidget", "drag_end", "GdkDragContext*" },
    { "GtkWidget", "drag_data_delete", "GdkDragContext*" },
    { "GtkWidget", "drag_motion", "GdkDragContext*", "gint", "guint", "guint" },
    { "GtkWidget", "drag_drop", "GdkDragContext*", "gint", "gint", "guint" },
    { "GtkWidget", "drag_data_get", "GdkDragContext*", "GtkSelectionData*", "guint", "guint" },
    { "GtkWidget", "drag_data_received", "GdkDragContext*", "gint", "gint", "GtkSelectionData*", "guint", "guint" },
    { "GtkWidget", "query_tooltip", "gint", "gint", "Gboolean", "GtkTooltip" },
    { "GtkWidget", "window_state_event", "GdkEvent*" },
    { NULL }
  };

#endif


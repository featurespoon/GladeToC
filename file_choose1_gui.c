#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <glib.h>

/*                Generated from D:/Gtk3/glade/g2c-gui.glade                 */

#include "file_choose1_gui.h"
#include "top_window.h"

FileChoose1Gui *file_choose1_gui_create (gpointer owner)
{
FileChoose1Gui *gui = g_new0 (FileChoose1Gui, 1);

	gui->accel_group = gtk_accel_group_new ();
	g_object_set_data (G_OBJECT (gui->accel_group), "owner", owner);

	/* Widget construction */
	/* Widgets at level 0 */
	/* Widgets at level 1 */
	gui->file_choose1 = (GtkFileChooserDialog*) gtk_file_chooser_dialog_new ("Select a Glade file", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, NULL, NULL);
	gtk_widget_set_can_focus ( GTK_WIDGET (gui->file_choose1), FALSE);
	gtk_window_set_modal ( GTK_WINDOW (gui->file_choose1), TRUE);
	gtk_window_set_type_hint(GTK_WINDOW(gui->file_choose1),GDK_WINDOW_TYPE_HINT_DIALOG );
	gtk_window_set_skip_taskbar_hint ( GTK_WINDOW (gui->file_choose1), TRUE);
	gtk_window_set_transient_for (GTK_WINDOW(gui->file_choose1), GTK_WINDOW(((TopWindow *) owner)->gui->top_window));
	gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (gui->file_choose1), TRUE);
	gtk_file_chooser_set_filter (GTK_FILE_CHOOSER (gui->file_choose1), GTK_FILE_FILTER(((TopWindow *) owner)->gui->filefilter1));
	gtk_file_chooser_set_preview_widget_active (GTK_FILE_CHOOSER (gui->file_choose1), FALSE);
	gtk_file_chooser_set_show_hidden (GTK_FILE_CHOOSER (gui->file_choose1), FALSE);
	gtk_file_chooser_set_use_preview_label (GTK_FILE_CHOOSER (gui->file_choose1), FALSE);
	g_object_set_data (G_OBJECT (gui->file_choose1), "owner", owner);

	/* Widgets at level 2 */
	gui->file_box1 = (GtkBox*) gtk_dialog_get_content_area (GTK_DIALOG(gui->file_choose1));

	/* Widgets at level 3 */
	/* Widgets at level 4 */

	gui->choose1 = (GtkButton*) gtk_dialog_add_button (GTK_DIALOG(gui->file_choose1), "Open", 5);
	gtk_widget_show (GTK_WIDGET (gui->choose1));
	g_object_set_data (G_OBJECT (gui->choose1), "owner", owner);


	gui->cancel = (GtkButton*) gtk_dialog_add_button (GTK_DIALOG(gui->file_choose1), "Cancel", 3);
	gtk_widget_show (GTK_WIDGET (gui->cancel));
	g_object_set_data (G_OBJECT (gui->cancel), "owner", owner);


	/* Accelerators */

	gtk_window_add_accel_group (GTK_WINDOW(gui->file_choose1), gui->accel_group);


	/* Signal connections */
	g_signal_connect (G_OBJECT (gui->choose1), "clicked",
	                    G_CALLBACK (choose1_click),
	                    NULL);

	return gui;
}

void file_choose1_gui_destroy (FileChoose1Gui *gui)
{
	gtk_widget_destroy (GTK_WIDGET (gui->file_choose1));
	g_free (gui);
	return;
}


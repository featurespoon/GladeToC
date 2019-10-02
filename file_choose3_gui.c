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

#include "file_choose3_gui.h"
#include "top_window.h"

FileChoose3Gui *file_choose3_gui_create (gpointer owner)
{
FileChoose3Gui *gui = g_new0 (FileChoose3Gui, 1);

	gui->accel_group = gtk_accel_group_new ();
	g_object_set_data (G_OBJECT (gui->accel_group), "owner", owner);

	/* Widget construction */
	/* Widgets at level 0 */
	/* Widgets at level 1 */
	gui->file_choose3 = (GtkFileChooserDialog*) gtk_file_chooser_dialog_new ("Select Windows Resource File", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, NULL, NULL);
	gtk_widget_set_can_focus ( GTK_WIDGET (gui->file_choose3), FALSE);
	gtk_window_set_type_hint(GTK_WINDOW(gui->file_choose3),GDK_WINDOW_TYPE_HINT_DIALOG );
	gtk_window_set_transient_for (GTK_WINDOW(gui->file_choose3), GTK_WINDOW(((TopWindow *) owner)->gui->top_window));
	gtk_file_chooser_set_filter (GTK_FILE_CHOOSER (gui->file_choose3), GTK_FILE_FILTER(((TopWindow *) owner)->gui->filefilter2));
	g_object_set_data (G_OBJECT (gui->file_choose3), "owner", owner);

	/* Widgets at level 2 */
	gui->file_box3 = (GtkBox*) gtk_dialog_get_content_area (GTK_DIALOG(gui->file_choose3));

	/* Widgets at level 3 */
	/* Widgets at level 4 */

	gui->choose3 = (GtkButton*) gtk_dialog_add_button (GTK_DIALOG(gui->file_choose3), "Open", 9);
	gtk_widget_show (GTK_WIDGET (gui->choose3));
	g_object_set_data (G_OBJECT (gui->choose3), "owner", owner);


	gui->cancel3 = (GtkButton*) gtk_dialog_add_button (GTK_DIALOG(gui->file_choose3), "Cancel", 0);
	gtk_widget_show (GTK_WIDGET (gui->cancel3));
	g_object_set_data (G_OBJECT (gui->cancel3), "owner", owner);


	/* Accelerators */

	gtk_window_add_accel_group (GTK_WINDOW(gui->file_choose3), gui->accel_group);


	/* Signal connections */
	g_signal_connect (G_OBJECT (gui->choose3), "clicked",
	                    G_CALLBACK (choose3_clicked),
	                    NULL);

	return gui;
}

void file_choose3_gui_destroy (FileChoose3Gui *gui)
{
	gtk_widget_destroy (GTK_WIDGET (gui->file_choose3));
	g_free (gui);
	return;
}


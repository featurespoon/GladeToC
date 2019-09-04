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

/*                Generated from C:/Gtk3/glade/g2c-gui.glade                 */

#include "file_choose3_gui.h"
#include "top_window.h"

FileChoose3Gui *file_choose3_gui_create (gpointer owner)
{
FileChoose3Gui *gui = g_new0 (FileChoose3Gui, 1);

	gui->accel_group = gtk_accel_group_new ();
	g_object_set_data (G_OBJECT (gui->accel_group), "owner", owner);

	gui->filefilter2 = (GtkFileFilter*) gtk_file_filter_new ();
	gtk_file_filter_add_pattern (GTK_FILE_FILTER(gui->filefilter2), "*.rc");
	g_object_set_data (G_OBJECT (gui->filefilter2), "owner", owner);



	/* Widget construction */
	gui->file_choose3 = (GtkFileChooserDialog*) gtk_file_chooser_dialog_new ("Select Windows Resource File", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, NULL, NULL);
	gtk_widget_set_can_focus ( GTK_WIDGET (gui->file_choose3), FALSE);
	gtk_window_set_type_hint(GTK_WINDOW(gui->file_choose3),GDK_WINDOW_TYPE_HINT_DIALOG );
	gtk_file_chooser_set_filter (GTK_FILE_CHOOSER (gui->file_choose3), GTK_FILE_FILTER(gui->filefilter2));
	g_object_set_data (G_OBJECT (gui->file_choose3), "owner", owner);

	gui->file_box3 = (GtkBox*) gtk_dialog_get_content_area (GTK_DIALOG(gui->file_choose3));

	gui->choose3 = (GtkButton*) gtk_dialog_add_button (GTK_DIALOG(gui->file_choose3), "", 9);
	gtk_button_set_label (GTK_BUTTON (gui->choose3), "Open");
	gtk_widget_show (GTK_WIDGET (gui->choose3));
	g_object_set_data (G_OBJECT (gui->choose3), "owner", owner);

	gui->cancel3 = (GtkButton*) gtk_dialog_add_button (GTK_DIALOG(gui->file_choose3), "", 0);
	gtk_button_set_label (GTK_BUTTON (gui->cancel3), "Cancel");
	gtk_widget_show (GTK_WIDGET (gui->cancel3));
	g_object_set_data (G_OBJECT (gui->cancel3), "owner", owner);


	/* Accelerators */

	gtk_window_add_accel_group (GTK_WINDOW(gui->file_choose3), gui->accel_group);


	/* Signal connections */
	g_signal_connect (G_OBJECT (gui->choose3), "clicked",
	                    G_CALLBACK (choose3_clicked),
	                    NULL);


	/* Population of Stores */

	return gui;
}

void file_choose3_gui_destroy (FileChoose3Gui *gui)
{
	gtk_widget_destroy (GTK_WIDGET (gui->file_choose3));
	g_free (gui);
	return;
}


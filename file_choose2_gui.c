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

#include "file_choose2_gui.h"
#include "top_window.h"

FileChoose2Gui *file_choose2_gui_create (gpointer owner)
{
FileChoose2Gui *gui = g_new0 (FileChoose2Gui, 1);

	gui->accel_group = gtk_accel_group_new ();
	g_object_set_data (G_OBJECT (gui->accel_group), "owner", owner);



	/* Widget construction */
	gui->file_choose2 = (GtkFileChooserDialog*) gtk_file_chooser_dialog_new ("Select a directory to hold the generated code", NULL, GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, NULL, NULL);
	gtk_widget_set_can_focus ( GTK_WIDGET (gui->file_choose2), FALSE);
	gtk_window_set_modal ( GTK_WINDOW (gui->file_choose2), TRUE);
	gtk_window_set_type_hint(GTK_WINDOW(gui->file_choose2),GDK_WINDOW_TYPE_HINT_DIALOG );
	gtk_file_chooser_set_preview_widget_active (GTK_FILE_CHOOSER (gui->file_choose2), FALSE);
	gtk_file_chooser_set_use_preview_label (GTK_FILE_CHOOSER (gui->file_choose2), FALSE);
	g_object_set_data (G_OBJECT (gui->file_choose2), "owner", owner);

	gui->file_box2 = (GtkBox*) gtk_dialog_get_content_area (GTK_DIALOG(gui->file_choose2));

	gui->choose2 = (GtkButton*) gtk_dialog_add_button (GTK_DIALOG(gui->file_choose2), "", 5);
	gtk_button_set_label (GTK_BUTTON (gui->choose2), "Select");
	gtk_widget_show (GTK_WIDGET (gui->choose2));
	g_object_set_data (G_OBJECT (gui->choose2), "owner", owner);

	gui->cancel2 = (GtkButton*) gtk_dialog_add_button (GTK_DIALOG(gui->file_choose2), "", 3);
	gtk_button_set_label (GTK_BUTTON (gui->cancel2), "Cancel");
	gtk_widget_show (GTK_WIDGET (gui->cancel2));
	g_object_set_data (G_OBJECT (gui->cancel2), "owner", owner);


	/* Accelerators */

	gtk_window_add_accel_group (GTK_WINDOW(gui->file_choose2), gui->accel_group);


	/* Signal connections */
	g_signal_connect (G_OBJECT (gui->choose2), "clicked",
	                    G_CALLBACK (choose2_click),
	                    NULL);

	return gui;
}

void file_choose2_gui_destroy (FileChoose2Gui *gui)
{
	gtk_widget_destroy (GTK_WIDGET (gui->file_choose2));
	g_free (gui);
	return;
}


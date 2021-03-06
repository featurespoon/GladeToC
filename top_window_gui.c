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

#include "top_window_gui.h"

TopWindowGui *top_window_gui_create (gpointer owner)
{
TopWindowGui *gui = g_new0 (TopWindowGui, 1);

	gui->accel_group = gtk_accel_group_new ();
	g_object_set_data (G_OBJECT (gui->accel_group), "owner", owner);

	/* Widget construction */
	/* Widgets at level 0 */
	gui->filefilter1 = (GtkFileFilter*) gtk_file_filter_new ();
	gtk_file_filter_add_pattern (GTK_FILE_FILTER(gui->filefilter1), "*.glade");
	g_object_set_data (G_OBJECT (gui->filefilter1), "owner", owner);

	gui->filefilter2 = (GtkFileFilter*) gtk_file_filter_new ();
	gtk_file_filter_add_pattern (GTK_FILE_FILTER(gui->filefilter2), "*.rc");
	g_object_set_data (G_OBJECT (gui->filefilter2), "owner", owner);

	gui->textbuffer1 = (GtkTextBuffer*) gtk_text_buffer_new (NULL);
	g_object_set_data (G_OBJECT (gui->textbuffer1), "owner", owner);

	/* Widgets at level 1 */
	gui->top_window = (GtkWindow*) gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_can_focus ( GTK_WIDGET (gui->top_window), FALSE);
	gtk_window_set_title(GTK_WINDOW(gui->top_window),"glade to C program" );
	g_object_set(G_OBJECT(gui->top_window),"default_width", 540,NULL);
	g_object_set(G_OBJECT(gui->top_window),"default_height", 250,NULL);
	g_object_set_data (G_OBJECT (gui->top_window), "owner", owner);

	/* Widgets at level 2 */
	gui->box1 = (GtkBox*) gtk_box_new (GTK_ORIENTATION_VERTICAL,0);
	gtk_container_add (GTK_CONTAINER (gui->top_window),
	                   GTK_WIDGET (gui->box1));
	gtk_widget_show (GTK_WIDGET (gui->box1));
	gtk_widget_set_halign ( GTK_WIDGET (gui->box1), GTK_ALIGN_END);
	gtk_widget_set_margin_start ( GTK_WIDGET (gui->box1), 10);
	gtk_widget_set_margin_end ( GTK_WIDGET (gui->box1), 10);
	gtk_widget_set_margin_top ( GTK_WIDGET (gui->box1), 10);
	gtk_widget_set_margin_bottom ( GTK_WIDGET (gui->box1), 10);
	g_object_set_data (G_OBJECT (gui->box1), "owner", owner);

	/* Widgets at level 3 */
	gui->glade_file_box1 = (GtkBox*) gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
	gtk_box_pack_start (GTK_BOX (gui->box1), 
	                    GTK_WIDGET (gui->glade_file_box1), FALSE, FALSE, 0);
	gtk_widget_show (GTK_WIDGET (gui->glade_file_box1));
	g_object_set_data (G_OBJECT (gui->glade_file_box1), "owner", owner);

	gui->gen_folder_box2 = (GtkBox*) gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
	gtk_box_pack_start (GTK_BOX (gui->box1), 
	                    GTK_WIDGET (gui->gen_folder_box2), FALSE, FALSE, 0);
	gtk_widget_show (GTK_WIDGET (gui->gen_folder_box2));
	g_object_set_data (G_OBJECT (gui->gen_folder_box2), "owner", owner);

	gui->program_box5 = (GtkBox*) gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
	gtk_box_pack_start (GTK_BOX (gui->box1), 
	                    GTK_WIDGET (gui->program_box5), FALSE, FALSE, 10);
	gtk_widget_show (GTK_WIDGET (gui->program_box5));
	g_object_set_data (G_OBJECT (gui->program_box5), "owner", owner);
#ifdef WIN32
	gui->resource_box6 = (GtkBox*) gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
	gtk_box_pack_start (GTK_BOX (gui->box1), 
	                    GTK_WIDGET (gui->resource_box6), FALSE, FALSE, 0);
	gtk_widget_show (GTK_WIDGET (gui->resource_box6));
	g_object_set_data (G_OBJECT (gui->resource_box6), "owner", owner);
#endif
	gui->generate_box7 = (GtkBox*) gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
	gtk_box_pack_start (GTK_BOX (gui->box1), 
	                    GTK_WIDGET (gui->generate_box7), FALSE, FALSE, 0);
	gtk_widget_show (GTK_WIDGET (gui->generate_box7));
	gtk_box_set_homogeneous(GTK_BOX (gui->generate_box7), TRUE);
	g_object_set_data (G_OBJECT (gui->generate_box7), "owner", owner);

	gui->textview_box9 = (GtkBox*) gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
	gtk_box_pack_start (GTK_BOX (gui->box1), 
	                    GTK_WIDGET (gui->textview_box9), FALSE, FALSE, 0);
	gtk_widget_show (GTK_WIDGET (gui->textview_box9));
	gtk_box_set_homogeneous(GTK_BOX (gui->textview_box9), TRUE);
	g_object_set_data (G_OBJECT (gui->textview_box9), "owner", owner);

	gui->dismiss_box11 = (GtkBox*) gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
	gtk_box_pack_start (GTK_BOX (gui->box1), 
	                    GTK_WIDGET (gui->dismiss_box11), FALSE, FALSE, 0);
	gtk_widget_show (GTK_WIDGET (gui->dismiss_box11));
	gtk_box_set_homogeneous(GTK_BOX (gui->dismiss_box11), TRUE);
	g_object_set_data (G_OBJECT (gui->dismiss_box11), "owner", owner);

	/* Widgets at level 4 */
	gui->glade_file = (GtkEntry*) gtk_entry_new ();
	gtk_box_pack_start (GTK_BOX (gui->glade_file_box1), 
	                    GTK_WIDGET (gui->glade_file), FALSE, TRUE, 10);
	gtk_widget_show (GTK_WIDGET (gui->glade_file));
	gtk_widget_set_halign ( GTK_WIDGET (gui->glade_file), GTK_ALIGN_START);
	gtk_widget_set_margin_start ( GTK_WIDGET (gui->glade_file), 10);
	gtk_widget_set_margin_top ( GTK_WIDGET (gui->glade_file), 20);
	gtk_widget_set_margin_bottom ( GTK_WIDGET (gui->glade_file), 20);
	g_object_set(G_OBJECT(gui->glade_file),"width_chars", 40, NULL);
	g_object_set(G_OBJECT(gui->glade_file),"max_width_chars", 50, NULL);
	g_object_set(G_OBJECT(gui->glade_file),"caps_lock_warning", FALSE, NULL);
	g_object_set_data (G_OBJECT (gui->glade_file), "owner", owner);

	gui->glade_button = (GtkButton*) gtk_button_new_with_label ("Glade File");
	gtk_box_pack_start (GTK_BOX (gui->glade_file_box1), 
	                    GTK_WIDGET (gui->glade_button), FALSE, TRUE, 10);
	gtk_widget_show (GTK_WIDGET (gui->glade_button));
	gtk_widget_set_tooltip_text ( GTK_WIDGET (gui->glade_button), "Select a file which defines a Graphical User Interface produced by Glade");
	gtk_widget_set_halign ( GTK_WIDGET (gui->glade_button), GTK_ALIGN_END);
	gtk_widget_set_margin_top ( GTK_WIDGET (gui->glade_button), 20);
	gtk_widget_set_margin_bottom ( GTK_WIDGET (gui->glade_button), 20);
	g_object_set_data (G_OBJECT (gui->glade_button), "owner", owner);

	gui->folder = (GtkEntry*) gtk_entry_new ();
	gtk_box_pack_start (GTK_BOX (gui->gen_folder_box2), 
	                    GTK_WIDGET (gui->folder), FALSE, TRUE, 10);
	gtk_widget_show (GTK_WIDGET (gui->folder));
	gtk_widget_set_halign ( GTK_WIDGET (gui->folder), GTK_ALIGN_START);
	gtk_widget_set_margin_start ( GTK_WIDGET (gui->folder), 10);
	gtk_widget_set_margin_bottom ( GTK_WIDGET (gui->folder), 20);
	g_object_set(G_OBJECT(gui->folder),"width_chars", 40, NULL);
	g_object_set(G_OBJECT(gui->folder),"max_width_chars", 50, NULL);
	g_object_set(G_OBJECT(gui->folder),"caps_lock_warning", FALSE, NULL);
	g_object_set(G_OBJECT(gui->folder),"primary_icon_activatable", FALSE, NULL);
	g_object_set(G_OBJECT(gui->folder),"secondary_icon_activatable", FALSE, NULL);
	g_object_set(G_OBJECT(gui->folder),"primary_icon_sensitive", FALSE, NULL);
	g_object_set(G_OBJECT(gui->folder),"secondary_icon_sensitive", FALSE, NULL);
	g_object_set_data (G_OBJECT (gui->folder), "owner", owner);

	gui->folder_button = (GtkButton*) gtk_button_new_with_label ("C Folder");
	gtk_box_pack_start (GTK_BOX (gui->gen_folder_box2), 
	                    GTK_WIDGET (gui->folder_button), FALSE, TRUE, 10);
	gtk_widget_show (GTK_WIDGET (gui->folder_button));
	gtk_widget_set_tooltip_text ( GTK_WIDGET (gui->folder_button), "Select a folder to hold the generated C files");
	gtk_widget_set_halign ( GTK_WIDGET (gui->folder_button), GTK_ALIGN_END);
	gtk_widget_set_margin_start ( GTK_WIDGET (gui->folder_button), 10);
	gtk_widget_set_margin_bottom ( GTK_WIDGET (gui->folder_button), 20);
	g_object_set_data (G_OBJECT (gui->folder_button), "owner", owner);

	gui->program = (GtkEntry*) gtk_entry_new ();
	gtk_box_pack_start (GTK_BOX (gui->program_box5), 
	                    GTK_WIDGET (gui->program), FALSE, FALSE, 10);
	gtk_widget_show (GTK_WIDGET (gui->program));
	gtk_widget_set_halign ( GTK_WIDGET (gui->program), GTK_ALIGN_END);
	gtk_widget_set_margin_start ( GTK_WIDGET (gui->program), 10);
	gtk_widget_set_margin_bottom ( GTK_WIDGET (gui->program), 20);
	g_object_set(G_OBJECT(gui->program),"width_chars", 36, NULL);
	g_object_set(G_OBJECT(gui->program),"max_width_chars", 50, NULL);
	g_object_set_data (G_OBJECT (gui->program), "owner", owner);

	gui->label1 = (GtkLabel*) gtk_label_new ("");
	gtk_box_pack_start (GTK_BOX (gui->program_box5), 
	                    GTK_WIDGET (gui->label1), FALSE, FALSE, 10);
	gtk_widget_show (GTK_WIDGET (gui->label1));
	gtk_widget_set_tooltip_text ( GTK_WIDGET (gui->label1), "The name of the program to be compiled from the generated code.");
	gtk_widget_set_halign ( GTK_WIDGET (gui->label1), GTK_ALIGN_START);
	gtk_widget_set_margin_start ( GTK_WIDGET (gui->label1), 10);
	gtk_widget_set_margin_bottom ( GTK_WIDGET (gui->label1), 20);
	gtk_label_set_text (GTK_LABEL (gui->label1), "Program Name");
	g_object_set_data (G_OBJECT (gui->label1), "owner", owner);
#ifdef WIN32
	gui->resource = (GtkEntry*) gtk_entry_new ();
	gtk_box_pack_start (GTK_BOX (gui->resource_box6), 
	                    GTK_WIDGET (gui->resource), FALSE, FALSE, 10);
	gtk_widget_show (GTK_WIDGET (gui->resource));
	gtk_widget_set_halign ( GTK_WIDGET (gui->resource), GTK_ALIGN_START);
	gtk_widget_set_margin_start ( GTK_WIDGET (gui->resource), 10);
	gtk_widget_set_margin_end ( GTK_WIDGET (gui->resource), 10);
	gtk_widget_set_margin_bottom ( GTK_WIDGET (gui->resource), 20);
	g_object_set(G_OBJECT(gui->resource),"width_chars", 30, NULL);
	g_object_set(G_OBJECT(gui->resource),"max_width_chars", 50, NULL);
	g_object_set_data (G_OBJECT (gui->resource), "owner", owner);

	gui->resource_button = (GtkButton*) gtk_button_new_with_label ("Windows Resource File (.rc)");
	gtk_box_pack_start (GTK_BOX (gui->resource_box6), 
	                    GTK_WIDGET (gui->resource_button), FALSE, FALSE, 10);
	gtk_widget_show (GTK_WIDGET (gui->resource_button));
	gtk_widget_set_tooltip_text ( GTK_WIDGET (gui->resource_button), "Use a resource file to set an icon for the program");
	gtk_widget_set_halign ( GTK_WIDGET (gui->resource_button), GTK_ALIGN_END);
	gtk_widget_set_margin_bottom ( GTK_WIDGET (gui->resource_button), 20);
	g_object_set_data (G_OBJECT (gui->resource_button), "owner", owner);
#endif
	gui->generate_button = (GtkButton*) gtk_button_new_with_label ("Generate");
	gtk_box_pack_start (GTK_BOX (gui->generate_box7), 
	                    GTK_WIDGET (gui->generate_button), FALSE, FALSE, 30);
	g_object_set(G_OBJECT(gui->generate_button),"width_request", 60,NULL);
	gtk_widget_show (GTK_WIDGET (gui->generate_button));
	gtk_widget_set_halign ( GTK_WIDGET (gui->generate_button), GTK_ALIGN_CENTER);
	gtk_widget_set_margin_bottom ( GTK_WIDGET (gui->generate_button), 10);
	g_object_set_data (G_OBJECT (gui->generate_button), "owner", owner);

	gui->scrolled1 = (GtkScrolledWindow*) gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(gui->scrolled1),
		 GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start (GTK_BOX (gui->textview_box9), 
	                    GTK_WIDGET (gui->scrolled1), FALSE, FALSE, 10);
	gtk_widget_show (GTK_WIDGET (gui->scrolled1));
	gtk_widget_set_halign ( GTK_WIDGET (gui->scrolled1), GTK_ALIGN_CENTER);
	gtk_widget_set_margin_start ( GTK_WIDGET (gui->scrolled1), 10);
	gtk_widget_set_margin_end ( GTK_WIDGET (gui->scrolled1), 10);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW(gui->scrolled1), GTK_SHADOW_IN);
	gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(gui->scrolled1),450 );
	gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(gui->scrolled1),200 );
	g_object_set_data (G_OBJECT (gui->scrolled1), "owner", owner);

	gui->dismiss_button = (GtkButton*) gtk_button_new_with_label ("Dismiss");
	gtk_box_pack_start (GTK_BOX (gui->dismiss_box11), 
	                    GTK_WIDGET (gui->dismiss_button), FALSE, FALSE, 30);
	gtk_widget_show (GTK_WIDGET (gui->dismiss_button));
	gtk_widget_set_halign ( GTK_WIDGET (gui->dismiss_button), GTK_ALIGN_CENTER);
	gtk_widget_set_margin_start ( GTK_WIDGET (gui->dismiss_button), 30);
	gtk_widget_set_margin_end ( GTK_WIDGET (gui->dismiss_button), 30);
	gtk_widget_set_margin_top ( GTK_WIDGET (gui->dismiss_button), 20);
	gtk_widget_set_margin_bottom ( GTK_WIDGET (gui->dismiss_button), 20);
	g_object_set_data (G_OBJECT (gui->dismiss_button), "owner", owner);

	/* Widgets at level 5 */
	gui->textview1 = (GtkTextView*) gtk_text_view_new ();
	gtk_container_add (GTK_CONTAINER (gui->scrolled1),
	                   GTK_WIDGET (gui->textview1));
	gtk_widget_show (GTK_WIDGET (gui->textview1));
	gtk_widget_set_can_focus ( GTK_WIDGET (gui->textview1), TRUE);
	g_object_set(G_OBJECT(gui->textview1),"editable", FALSE, NULL);
	gtk_text_view_set_left_margin(GTK_TEXT_VIEW(gui->textview1),10 );
	gtk_text_view_set_right_margin(GTK_TEXT_VIEW(gui->textview1),10 );
	gtk_text_view_set_top_margin(GTK_TEXT_VIEW(gui->textview1),10 );
	gtk_text_view_set_bottom_margin(GTK_TEXT_VIEW(gui->textview1),10 );
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(gui->textview1),FALSE );
	gtk_text_view_set_buffer (GTK_TEXT_VIEW (gui->textview1), GTK_TEXT_BUFFER(gui->textbuffer1));
	gtk_text_view_set_accepts_tab(GTK_TEXT_VIEW(gui->textview1),FALSE );
	g_object_set_data (G_OBJECT (gui->textview1), "owner", owner);

	gtk_widget_show (GTK_WIDGET (gui->top_window));


	/* Accelerators */

	gtk_window_add_accel_group (GTK_WINDOW(gui->top_window), gui->accel_group);


	/* Signal connections */
	g_signal_connect_swapped (G_OBJECT (gui->top_window), "destroy",
		G_CALLBACK (gtk_main_quit), NULL);

	g_signal_connect (G_OBJECT (gui->glade_button), "clicked",
	                    G_CALLBACK (glade_click),
	                    NULL);

	g_signal_connect (G_OBJECT (gui->folder_button), "clicked",
	                    G_CALLBACK (folder_click),
	                    NULL);
#ifdef WIN32
	g_signal_connect (G_OBJECT (gui->resource_button), "clicked",
	                    G_CALLBACK (resource_click),
	                    NULL);
#endif
	g_signal_connect (G_OBJECT (gui->generate_button), "clicked",
	                    G_CALLBACK (generate_click),
	                    NULL);

	g_signal_connect (G_OBJECT (gui->dismiss_button), "clicked",
	                    G_CALLBACK (dismiss_click),
	                    NULL);


	/* Population of Stores */

	initialise_top_window (gui);

	return gui;
}

void top_window_gui_destroy (TopWindowGui *gui)
{
	gtk_widget_destroy (GTK_WIDGET (gui->top_window));
	g_free (gui);
	return;
}


#ifndef top_window_gui_h
#define top_window_gui_h

#include <gtk/gtk.h>

typedef struct tag_TopWindowGui
{
	GtkAccelGroup        *accel_group;
	GtkWindow            *top_window;
	GtkBox               *box1;
	GtkBox               *glade_file_box1;
	GtkEntry             *glade_file;
	GtkButton            *glade_button;
	GtkBox               *gen_folder_box2;
	GtkEntry             *folder;
	GtkButton            *folder_button;
	GtkBox               *program_box5;
	GtkEntry             *program;
	GtkLabel             *label1;
	GtkBox               *resource_box6;
	GtkEntry             *resource;
	GtkButton            *resource_button;
	GtkBox               *generate_box7;
	GtkButton            *generate_button;
	GtkBox               *textview_box9;
	GtkScrolledWindow    *scrolled1;
	GtkTextView          *textview1;
	GtkBox               *dismiss_box11;
	GtkButton            *dismiss_button;
	GtkFileFilter        *filefilter1;
	GtkFileFilter        *filefilter2;
	GtkTextBuffer        *textbuffer1;
} TopWindowGui;

TopWindowGui *top_window_gui_create (gpointer owner);

void top_window_gui_destroy (TopWindowGui *top_window);

void
glade_click (GtkButton* glade_button,
	gpointer                  user_data);

void
folder_click (GtkButton* folder_button,
	gpointer                  user_data);

void
resource_click (GtkButton* resource_button,
	gpointer                  user_data);

void
generate_click (GtkButton* generate_button,
	gpointer                  user_data);

void
dismiss_click (GtkButton* dismiss_button,
	gpointer                  user_data);

void initialise_top_window (TopWindowGui *top_window);

#endif

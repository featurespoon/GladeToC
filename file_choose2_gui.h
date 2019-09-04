#ifndef file_choose2_gui_h
#define file_choose2_gui_h

#include <gtk/gtk.h>

typedef struct tag_FileChoose2Gui
{
	GtkAccelGroup        *accel_group;
	GtkFileChooserDialog *file_choose2;
	GtkBox               *file_box2;
	GtkButtonBox         *file_buttons2;
	GtkButton            *choose2;
	GtkButton            *cancel2;
} FileChoose2Gui;

FileChoose2Gui *file_choose2_gui_create (gpointer owner);

void file_choose2_gui_destroy (FileChoose2Gui *file_choose2);

void
choose2_click (GtkButton* choose2,
	gpointer                  user_data);

#endif

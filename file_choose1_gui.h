#ifndef file_choose1_gui_h
#define file_choose1_gui_h

#include <gtk/gtk.h>

typedef struct tag_FileChoose1Gui
{
	GtkAccelGroup        *accel_group;
	GtkFileChooserDialog *file_choose1;
	GtkBox               *file_box1;
	GtkButtonBox         *file_buttons1;
	GtkButton            *choose1;
	GtkButton            *cancel;
	GtkFileFilter        *filefilter1;
} FileChoose1Gui;

FileChoose1Gui *file_choose1_gui_create (gpointer owner);

void file_choose1_gui_destroy (FileChoose1Gui *file_choose1);

void
choose1_click (GtkButton* choose1,
	gpointer                  user_data);

#endif

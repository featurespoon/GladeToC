#ifndef file_choose3_gui_h
#define file_choose3_gui_h

#include <gtk/gtk.h>

typedef struct tag_FileChoose3Gui
{
	GtkAccelGroup        *accel_group;
	GtkFileChooserDialog *file_choose3;
	GtkBox               *file_box3;
	GtkButtonBox         *file_buttons3;
	GtkButton            *choose3;
	GtkButton            *cancel3;
	GtkFileFilter        *filefilter2;
} FileChoose3Gui;

FileChoose3Gui *file_choose3_gui_create (gpointer owner);

void file_choose3_gui_destroy (FileChoose3Gui *file_choose3);

void
choose3_clicked (GtkButton* choose3,
	gpointer                  user_data);

#endif

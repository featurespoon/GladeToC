#ifndef top_window_h
#define top_window_h

#include <gtk/gtk.h>
#include "top_window_gui.h"
#include "file_choose2_gui.h"
#include "file_choose1_gui.h"
#include "file_choose3_gui.h"

typedef struct tag_TopWindow
{
	TopWindowGui *gui;
	FileChoose2Gui *file_choose2gui;
	FileChoose1Gui *file_choose1gui;
	FileChoose3Gui *file_choose3gui;
} TopWindow;

void top_window_terminate (TopWindow *top_window);

#endif

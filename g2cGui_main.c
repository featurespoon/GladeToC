/*                Generated from C:/Gtk3/glade/g2c-gui.glade                 */

#include <gtk/gtk.h>
#include "top_window.h"
#include "top_window_gui.h"

int
main (int argc, char *argv[])
{
TopWindow *top_window = NULL;

#ifdef ENABLE_NLS
  bindtextdomain (PACKAGE, PACKAGE_LOCALE_DIR);
  textdomain (PACKAGE);
#endif

  gtk_init (&argc, &argv);

  top_window = g_new0 (TopWindow, 1);
  top_window->gui = top_window_gui_create ((gpointer) top_window);
  if (top_window->gui == NULL) return 0;
  top_window->file_choose2gui = file_choose2_gui_create ((gpointer) top_window);
  if (top_window->file_choose2gui == NULL) return 0;
  top_window->file_choose1gui = file_choose1_gui_create ((gpointer) top_window);
  if (top_window->file_choose1gui == NULL) return 0;
  top_window->file_choose3gui = file_choose3_gui_create ((gpointer) top_window);
  if (top_window->file_choose3gui == NULL) return 0;

  gtk_main ();
  return 0;
}

void top_window_terminate (TopWindow *top_window)
{
  file_choose2_gui_destroy (top_window->file_choose2gui);
  file_choose1_gui_destroy (top_window->file_choose1gui);
  file_choose3_gui_destroy (top_window->file_choose3gui);
  top_window_gui_destroy (top_window->gui);
  g_free (top_window);
  gtk_main_quit();
}

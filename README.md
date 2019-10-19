# g2c-3
Glade to C conversion

The goal of this project is to take XML files produced by using Glade, a user interface designer for GTK+ and GNOME, and generate C code which can be compiled and run with all unnecessary effort removed. You then have a program which does not have an XML file hanging around its neck. It uses the latest version of Glade 3.22.1 and targets gtk-3.0. It is based on a much older attempt g2c which targetted gtk-2.0. This version we would maintain is much more complete, although still not, at present, entirely comprehensive in supporting all the widgets which can be used in Glade.

Glade is available in Linux distributions and also on Windows with Msys64 and Mingw64. When built, this program will run on Linux and Windows.

Widget coverage is currently as follows:

Top Levels

GtkWindow, GtkOffscreenWindow, GtkDialog, GtkAboutDialog, GtkFileChooserDialog, GtkColorChooserDialog, GtkFontChooserDialog,
GtkMessageDialog, GtkAssistant.

Containers

GtkBox, GtkGrid, GtkNotebook, GtkFrame, GtkAspectFrame, GtkListBox, GtkOverlay, GtkMenuBar, GtkToolbar, GtkToolPalette, GtkPaned, GtkButtonBox, GtkLayout, GtkFixed, GtkEventBox, GtkExpander, GtkViewport, GtkScrolledWindow, GtkAlignment, GtkRevealer, GtkSearchBar, GtkHeaderBar, GtkStack, GtkPopupMenu, GtkPopover, GtkPopoverMenu, GtkActionBar, GtkFlowBox

Controls

GtkButton, GtkEntry, GtkSearchEntry, GtkSpinButton, GtkToggleButton, GtkCheckButton, GtkRadioButton, GtkMenuButton, GtkSwitch, GtkModelButton, GtkStackSwitcher, GtkStackSidebar, GtkComboBox, GtkComboBoxText, GtkFileChooserButton, GtkColorButton, GtkFontButton, GtkLinkButton, GtkScaleButton, GtkVolumeButton, GtkAppChooserButton, GtkScale, GtkScrollbar

Display

GtkLabel, GtkAccelLabel, GtkImage, GtkTextView, GtkTreeView (both Lists and Trees), GtkProgressBar, GtkSpinner, GtkMenu, GtkDrawingArea, GtkInfoBar, GtkCalendar, GtkLevelBar, GtkIconView, GtkSeparator

Miscellaneous

GtkListStore, GtkTreeStore, GtkEntryBuffer, GtkTextBuffer, GtkAccelGroup, GtkAdjustment, GtkEntryCompletion, GtkFileFilter, GtkPlacesSidebar

Coverage of the properties in Glade's Common tab (common to most widgets) is complete.



The project can be built using cmake.  This produces both a command line version and a Gui version of g2c.

For the command line version the arguments are as follows:

Usage: ../g2c.exe [-p name] -g gladefile -d dir [-r resource] [-h]
              -p      - Project (program) name.        
             -g      - file produced by GLADE.        
             -d      - directory into which generated files are placed.        
             -r      - Resource file.        
             -h      - Help. This message.
        
The resource file is only meaningful for the Windows version.  Its main purpose is to provide an icon for the generated program.

Not surprisingly, the GUI version requires the input of the same information, but the program name is automatically derived from the directory name, although it can be changed.

G2c produces a number of C files and headers plus a CMakeLists.txt file to drive cmake to produce a makefile to compile and link these files. The control.c file produced has skeleton handlers for all signal handlers and liststores defined in Glade. If liststore contents are defined in Glade then the code to populate the liststore is automatically produced. The program should link and run without errors.  Naturally it is then up to the developer to fill in the handler stubs with application code.


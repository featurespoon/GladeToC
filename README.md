# g2c-3
Glade to C conversion

The goal of this project is to take XML files produced by using Glade, a user interface designer for GTK+ and GNOME, and generate C code which can be compiled and run with all unnecessary effort removed. You then have a program which does not have an XML file hanging around its neck. It uses the latest version of Glade 3.22.1 and targets gtk-3.0. It is based on a much older attempt g2c which targetted gtk-2.0. This version we would maintain is much more complete, although still not, at present, entirely comprehensive in supporting all the widgets which can be used in Glade.

Glade is available in Linux distributions and also on Windows with Msys64 and Mingw64. When built, this program will run on Linux and Windows.

Widget coverage is currently as follows:
Top Levels
GtkWindow, GtkOffscreenWindow, GtkDialog, GtkAboutDialog, GtkFileChooserDialog, GtkColorChooserDialog, GtkFontChooserDialog,
GtkMessageDialog, GtkAssistant.

Containers
GtkBox, GtkGrid, GtkNotebook, GtkFrame, GtkAspectFrame, GtkListBox, GtkOverlay, GtkMenuBar, GtkToolbar, GtkToolPalette, GtkPaned, GtkButtonBox, GtkLayout, GtkFixed, GtkEventBox, GtkExpander, GtkViewport, GtkScrolledWindow, GtkAlignment, GtkRevealer, GtkSearchBar, GtkHeaderBar, GtkStack, GtkPopupMenu, GtkPopover, GtkActionBar

Controls
GtkButton, GtkEntry, GtkSearchEntry, GtkSpinButton, GtkToggleButton, GtkCheckButton, GtkRadioButton, GtkMenuButton, GtkSwitch, GtkModelButton, GtkStackSwitcher, GtkComboBox, GtkComboBoxText, GtkFileChooserButton, GtkColorButton, GtkFontButton, GtkLinkButton, GtkScaleButton, GtkVolumeButton, GtkAppChooserButton, GtkScale, GtkScrollbar

Display
GtkLabel, GtkAccelLabel, GtkImage, GtkTextView, GtkTreeView (both Lists and Trees), GtkProgressBar, GtkSpinner, GtkMenu, GtkDrawingArea, GtkInfoBar

Miscellaneous
GtkListStore, GtkTreeStore, GtkTextBuffer, GtkAccelGroup, GtkAdjustment, GtkEntryCompletion, GtkFileFilter


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

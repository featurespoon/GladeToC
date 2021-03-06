Notes on Generated Files

A number of C source files and headers are generated by GladeToC.  Their names are derived from the IDs 
given to the top-level widgets (a window and dialogs). So for example, if the first widget is a GtkWindow
with ID 'window1' and the program name is 'program1' then files with the following names are produced:
	program1_main.c
	window1.h
	window1.c
	window1_gui.c
	window1_gui.h
	control.c
	CMakeLists.txt
CMakeLists.txt, a file used to drive cmake, facilitating compilation and linking, is optional. If there are any dialogs, two more files are produced for each dialog in the Glade file.  So for GtkDialog with ID 'dialog1' we get:
	dialog1_gui.c
	dialog1_gui.h
CMakeLists.txt lists the files to be compiled. You will	notice that window1.c is absent. This because on the first generation run (and it is assumed that changes in Glade will require regeneration) window1.c is copied to control.c.  If control.c already exists it is not overwritten. This is because it contains the signal handlers which need to be completed by the programmer, and this code must plainly be preserved. On regeneration window1.c will not contain signal handlers already in control.c, only any new ones.  A message to that effect, naming the new handlers, will appear. Any new signal handlers will have to be copied to control.c. 

File window1_gui.h, dialog1_gui.h define data structures which hold references to every widget within these top-level widgets.  File window1.h defines the 'master' data structure which refers to these data structures. Every widget is given a reference to this structure under the property 'owner'. This way, all widgets are accessible to signal handlers. 

control.c may also contain populaters of liststores.  Any data set up in Glade for liststores will be used to generate code to populate the liststore, although on many occasions code to do that will have to be supplied by the programmer. In order to support a Model-View-Control (MVC) paradigm, this population code may be transferred to a new file, model.c. If this is done, it will be included in CMakeLists.txt. 

To run cmake on Windows put
cmake -DWIN32=yes .
In any case to compile the generated code with debug information, add the option -DSOURCE_DEBUG=yes

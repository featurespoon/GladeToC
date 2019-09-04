# g2c-3
Glade to C conversion

The goal of this project is to take XML files produced by using Glade, a user interface designer for GTK+ and GNOME, and generate C code which can be compiled and run with all unnecessary effort removed. You then have a program which does not have an XML file hanging around its neck. It uses the latest version of Glade 3.22.1 and targets gtk-3.0. It is based on a much older attempt g2c which targetted gtk-2.0. This version we would maintain is much more complete, although still not, at present, entirely comprehensive in supporting all the widgets which can be used in Glade.

Glade is available in Linux distributions and also on Windows with Msys64 and Mingw64. This program will run on Linux and Windows.

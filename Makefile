# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake.exe

# The command to remove a file.
RM = /usr/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /d/Gtk3/github/g2c-3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /d/Gtk3/github/g2c-3

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake.exe -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake.exe -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /d/Gtk3/github/g2c-3/CMakeFiles /d/Gtk3/github/g2c-3/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /d/Gtk3/github/g2c-3/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named g2cGui

# Build rule for target.
g2cGui: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 g2cGui
.PHONY : g2cGui

# fast build rule for target.
g2cGui/fast:
	$(MAKE) -f CMakeFiles/g2cGui.dir/build.make CMakeFiles/g2cGui.dir/build
.PHONY : g2cGui/fast

#=============================================================================
# Target rules for targets named lib2

# Build rule for target.
lib2: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 lib2
.PHONY : lib2

# fast build rule for target.
lib2/fast:
	$(MAKE) -f CMakeFiles/lib2.dir/build.make CMakeFiles/lib2.dir/build
.PHONY : lib2/fast

#=============================================================================
# Target rules for targets named lib1

# Build rule for target.
lib1: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 lib1
.PHONY : lib1

# fast build rule for target.
lib1/fast:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/build
.PHONY : lib1/fast

#=============================================================================
# Target rules for targets named g2c

# Build rule for target.
g2c: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 g2c
.PHONY : g2c

# fast build rule for target.
g2c/fast:
	$(MAKE) -f CMakeFiles/g2c.dir/build.make CMakeFiles/g2c.dir/build
.PHONY : g2c/fast

control.obj: control.c.obj

.PHONY : control.obj

# target to build an object file
control.c.obj:
	$(MAKE) -f CMakeFiles/lib2.dir/build.make CMakeFiles/lib2.dir/control.c.obj
.PHONY : control.c.obj

control.i: control.c.i

.PHONY : control.i

# target to preprocess a source file
control.c.i:
	$(MAKE) -f CMakeFiles/lib2.dir/build.make CMakeFiles/lib2.dir/control.c.i
.PHONY : control.c.i

control.s: control.c.s

.PHONY : control.s

# target to generate assembly for a file
control.c.s:
	$(MAKE) -f CMakeFiles/lib2.dir/build.make CMakeFiles/lib2.dir/control.c.s
.PHONY : control.c.s

file_choose1_gui.obj: file_choose1_gui.c.obj

.PHONY : file_choose1_gui.obj

# target to build an object file
file_choose1_gui.c.obj:
	$(MAKE) -f CMakeFiles/lib2.dir/build.make CMakeFiles/lib2.dir/file_choose1_gui.c.obj
.PHONY : file_choose1_gui.c.obj

file_choose1_gui.i: file_choose1_gui.c.i

.PHONY : file_choose1_gui.i

# target to preprocess a source file
file_choose1_gui.c.i:
	$(MAKE) -f CMakeFiles/lib2.dir/build.make CMakeFiles/lib2.dir/file_choose1_gui.c.i
.PHONY : file_choose1_gui.c.i

file_choose1_gui.s: file_choose1_gui.c.s

.PHONY : file_choose1_gui.s

# target to generate assembly for a file
file_choose1_gui.c.s:
	$(MAKE) -f CMakeFiles/lib2.dir/build.make CMakeFiles/lib2.dir/file_choose1_gui.c.s
.PHONY : file_choose1_gui.c.s

file_choose2_gui.obj: file_choose2_gui.c.obj

.PHONY : file_choose2_gui.obj

# target to build an object file
file_choose2_gui.c.obj:
	$(MAKE) -f CMakeFiles/lib2.dir/build.make CMakeFiles/lib2.dir/file_choose2_gui.c.obj
.PHONY : file_choose2_gui.c.obj

file_choose2_gui.i: file_choose2_gui.c.i

.PHONY : file_choose2_gui.i

# target to preprocess a source file
file_choose2_gui.c.i:
	$(MAKE) -f CMakeFiles/lib2.dir/build.make CMakeFiles/lib2.dir/file_choose2_gui.c.i
.PHONY : file_choose2_gui.c.i

file_choose2_gui.s: file_choose2_gui.c.s

.PHONY : file_choose2_gui.s

# target to generate assembly for a file
file_choose2_gui.c.s:
	$(MAKE) -f CMakeFiles/lib2.dir/build.make CMakeFiles/lib2.dir/file_choose2_gui.c.s
.PHONY : file_choose2_gui.c.s

file_choose3_gui.obj: file_choose3_gui.c.obj

.PHONY : file_choose3_gui.obj

# target to build an object file
file_choose3_gui.c.obj:
	$(MAKE) -f CMakeFiles/lib2.dir/build.make CMakeFiles/lib2.dir/file_choose3_gui.c.obj
.PHONY : file_choose3_gui.c.obj

file_choose3_gui.i: file_choose3_gui.c.i

.PHONY : file_choose3_gui.i

# target to preprocess a source file
file_choose3_gui.c.i:
	$(MAKE) -f CMakeFiles/lib2.dir/build.make CMakeFiles/lib2.dir/file_choose3_gui.c.i
.PHONY : file_choose3_gui.c.i

file_choose3_gui.s: file_choose3_gui.c.s

.PHONY : file_choose3_gui.s

# target to generate assembly for a file
file_choose3_gui.c.s:
	$(MAKE) -f CMakeFiles/lib2.dir/build.make CMakeFiles/lib2.dir/file_choose3_gui.c.s
.PHONY : file_choose3_gui.c.s

g2c.obj: g2c.c.obj

.PHONY : g2c.obj

# target to build an object file
g2c.c.obj:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c.c.obj
.PHONY : g2c.c.obj

g2c.i: g2c.c.i

.PHONY : g2c.i

# target to preprocess a source file
g2c.c.i:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c.c.i
.PHONY : g2c.c.i

g2c.s: g2c.c.s

.PHONY : g2c.s

# target to generate assembly for a file
g2c.c.s:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c.c.s
.PHONY : g2c.c.s

g2cGui_main.obj: g2cGui_main.c.obj

.PHONY : g2cGui_main.obj

# target to build an object file
g2cGui_main.c.obj:
	$(MAKE) -f CMakeFiles/lib2.dir/build.make CMakeFiles/lib2.dir/g2cGui_main.c.obj
.PHONY : g2cGui_main.c.obj

g2cGui_main.i: g2cGui_main.c.i

.PHONY : g2cGui_main.i

# target to preprocess a source file
g2cGui_main.c.i:
	$(MAKE) -f CMakeFiles/lib2.dir/build.make CMakeFiles/lib2.dir/g2cGui_main.c.i
.PHONY : g2cGui_main.c.i

g2cGui_main.s: g2cGui_main.c.s

.PHONY : g2cGui_main.s

# target to generate assembly for a file
g2cGui_main.c.s:
	$(MAKE) -f CMakeFiles/lib2.dir/build.make CMakeFiles/lib2.dir/g2cGui_main.c.s
.PHONY : g2cGui_main.c.s

g2c_accel.obj: g2c_accel.c.obj

.PHONY : g2c_accel.obj

# target to build an object file
g2c_accel.c.obj:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_accel.c.obj
.PHONY : g2c_accel.c.obj

g2c_accel.i: g2c_accel.c.i

.PHONY : g2c_accel.i

# target to preprocess a source file
g2c_accel.c.i:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_accel.c.i
.PHONY : g2c_accel.c.i

g2c_accel.s: g2c_accel.c.s

.PHONY : g2c_accel.s

# target to generate assembly for a file
g2c_accel.c.s:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_accel.c.s
.PHONY : g2c_accel.c.s

g2c_doc.obj: g2c_doc.c.obj

.PHONY : g2c_doc.obj

# target to build an object file
g2c_doc.c.obj:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_doc.c.obj
.PHONY : g2c_doc.c.obj

g2c_doc.i: g2c_doc.c.i

.PHONY : g2c_doc.i

# target to preprocess a source file
g2c_doc.c.i:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_doc.c.i
.PHONY : g2c_doc.c.i

g2c_doc.s: g2c_doc.c.s

.PHONY : g2c_doc.s

# target to generate assembly for a file
g2c_doc.c.s:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_doc.c.s
.PHONY : g2c_doc.c.s

g2c_file_parser.obj: g2c_file_parser.c.obj

.PHONY : g2c_file_parser.obj

# target to build an object file
g2c_file_parser.c.obj:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_file_parser.c.obj
.PHONY : g2c_file_parser.c.obj

g2c_file_parser.i: g2c_file_parser.c.i

.PHONY : g2c_file_parser.i

# target to preprocess a source file
g2c_file_parser.c.i:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_file_parser.c.i
.PHONY : g2c_file_parser.c.i

g2c_file_parser.s: g2c_file_parser.c.s

.PHONY : g2c_file_parser.s

# target to generate assembly for a file
g2c_file_parser.c.s:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_file_parser.c.s
.PHONY : g2c_file_parser.c.s

g2c_helpers.obj: g2c_helpers.c.obj

.PHONY : g2c_helpers.obj

# target to build an object file
g2c_helpers.c.obj:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_helpers.c.obj
.PHONY : g2c_helpers.c.obj

g2c_helpers.i: g2c_helpers.c.i

.PHONY : g2c_helpers.i

# target to preprocess a source file
g2c_helpers.c.i:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_helpers.c.i
.PHONY : g2c_helpers.c.i

g2c_helpers.s: g2c_helpers.c.s

.PHONY : g2c_helpers.s

# target to generate assembly for a file
g2c_helpers.c.s:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_helpers.c.s
.PHONY : g2c_helpers.c.s

g2c_main.obj: g2c_main.c.obj

.PHONY : g2c_main.obj

# target to build an object file
g2c_main.c.obj:
	$(MAKE) -f CMakeFiles/g2c.dir/build.make CMakeFiles/g2c.dir/g2c_main.c.obj
.PHONY : g2c_main.c.obj

g2c_main.i: g2c_main.c.i

.PHONY : g2c_main.i

# target to preprocess a source file
g2c_main.c.i:
	$(MAKE) -f CMakeFiles/g2c.dir/build.make CMakeFiles/g2c.dir/g2c_main.c.i
.PHONY : g2c_main.c.i

g2c_main.s: g2c_main.c.s

.PHONY : g2c_main.s

# target to generate assembly for a file
g2c_main.c.s:
	$(MAKE) -f CMakeFiles/g2c.dir/build.make CMakeFiles/g2c.dir/g2c_main.c.s
.PHONY : g2c_main.c.s

g2c_message.obj: g2c_message.c.obj

.PHONY : g2c_message.obj

# target to build an object file
g2c_message.c.obj:
	$(MAKE) -f CMakeFiles/g2c.dir/build.make CMakeFiles/g2c.dir/g2c_message.c.obj
.PHONY : g2c_message.c.obj

g2c_message.i: g2c_message.c.i

.PHONY : g2c_message.i

# target to preprocess a source file
g2c_message.c.i:
	$(MAKE) -f CMakeFiles/g2c.dir/build.make CMakeFiles/g2c.dir/g2c_message.c.i
.PHONY : g2c_message.c.i

g2c_message.s: g2c_message.c.s

.PHONY : g2c_message.s

# target to generate assembly for a file
g2c_message.c.s:
	$(MAKE) -f CMakeFiles/g2c.dir/build.make CMakeFiles/g2c.dir/g2c_message.c.s
.PHONY : g2c_message.c.s

g2c_message_gui.obj: g2c_message_gui.c.obj

.PHONY : g2c_message_gui.obj

# target to build an object file
g2c_message_gui.c.obj:
	$(MAKE) -f CMakeFiles/g2cGui.dir/build.make CMakeFiles/g2cGui.dir/g2c_message_gui.c.obj
.PHONY : g2c_message_gui.c.obj

g2c_message_gui.i: g2c_message_gui.c.i

.PHONY : g2c_message_gui.i

# target to preprocess a source file
g2c_message_gui.c.i:
	$(MAKE) -f CMakeFiles/g2cGui.dir/build.make CMakeFiles/g2cGui.dir/g2c_message_gui.c.i
.PHONY : g2c_message_gui.c.i

g2c_message_gui.s: g2c_message_gui.c.s

.PHONY : g2c_message_gui.s

# target to generate assembly for a file
g2c_message_gui.c.s:
	$(MAKE) -f CMakeFiles/g2cGui.dir/build.make CMakeFiles/g2cGui.dir/g2c_message_gui.c.s
.PHONY : g2c_message_gui.c.s

g2c_project.obj: g2c_project.c.obj

.PHONY : g2c_project.obj

# target to build an object file
g2c_project.c.obj:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_project.c.obj
.PHONY : g2c_project.c.obj

g2c_project.i: g2c_project.c.i

.PHONY : g2c_project.i

# target to preprocess a source file
g2c_project.c.i:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_project.c.i
.PHONY : g2c_project.c.i

g2c_project.s: g2c_project.c.s

.PHONY : g2c_project.s

# target to generate assembly for a file
g2c_project.c.s:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_project.c.s
.PHONY : g2c_project.c.s

g2c_signal.obj: g2c_signal.c.obj

.PHONY : g2c_signal.obj

# target to build an object file
g2c_signal.c.obj:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_signal.c.obj
.PHONY : g2c_signal.c.obj

g2c_signal.i: g2c_signal.c.i

.PHONY : g2c_signal.i

# target to preprocess a source file
g2c_signal.c.i:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_signal.c.i
.PHONY : g2c_signal.c.i

g2c_signal.s: g2c_signal.c.s

.PHONY : g2c_signal.s

# target to generate assembly for a file
g2c_signal.c.s:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_signal.c.s
.PHONY : g2c_signal.c.s

g2c_widget.obj: g2c_widget.c.obj

.PHONY : g2c_widget.obj

# target to build an object file
g2c_widget.c.obj:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_widget.c.obj
.PHONY : g2c_widget.c.obj

g2c_widget.i: g2c_widget.c.i

.PHONY : g2c_widget.i

# target to preprocess a source file
g2c_widget.c.i:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_widget.c.i
.PHONY : g2c_widget.c.i

g2c_widget.s: g2c_widget.c.s

.PHONY : g2c_widget.s

# target to generate assembly for a file
g2c_widget.c.s:
	$(MAKE) -f CMakeFiles/lib1.dir/build.make CMakeFiles/lib1.dir/g2c_widget.c.s
.PHONY : g2c_widget.c.s

top_window_gui.obj: top_window_gui.c.obj

.PHONY : top_window_gui.obj

# target to build an object file
top_window_gui.c.obj:
	$(MAKE) -f CMakeFiles/lib2.dir/build.make CMakeFiles/lib2.dir/top_window_gui.c.obj
.PHONY : top_window_gui.c.obj

top_window_gui.i: top_window_gui.c.i

.PHONY : top_window_gui.i

# target to preprocess a source file
top_window_gui.c.i:
	$(MAKE) -f CMakeFiles/lib2.dir/build.make CMakeFiles/lib2.dir/top_window_gui.c.i
.PHONY : top_window_gui.c.i

top_window_gui.s: top_window_gui.c.s

.PHONY : top_window_gui.s

# target to generate assembly for a file
top_window_gui.c.s:
	$(MAKE) -f CMakeFiles/lib2.dir/build.make CMakeFiles/lib2.dir/top_window_gui.c.s
.PHONY : top_window_gui.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... g2cGui"
	@echo "... edit_cache"
	@echo "... lib2"
	@echo "... lib1"
	@echo "... g2c"
	@echo "... control.obj"
	@echo "... control.i"
	@echo "... control.s"
	@echo "... file_choose1_gui.obj"
	@echo "... file_choose1_gui.i"
	@echo "... file_choose1_gui.s"
	@echo "... file_choose2_gui.obj"
	@echo "... file_choose2_gui.i"
	@echo "... file_choose2_gui.s"
	@echo "... file_choose3_gui.obj"
	@echo "... file_choose3_gui.i"
	@echo "... file_choose3_gui.s"
	@echo "... g2c.obj"
	@echo "... g2c.i"
	@echo "... g2c.s"
	@echo "... g2cGui_main.obj"
	@echo "... g2cGui_main.i"
	@echo "... g2cGui_main.s"
	@echo "... g2c_accel.obj"
	@echo "... g2c_accel.i"
	@echo "... g2c_accel.s"
	@echo "... g2c_doc.obj"
	@echo "... g2c_doc.i"
	@echo "... g2c_doc.s"
	@echo "... g2c_file_parser.obj"
	@echo "... g2c_file_parser.i"
	@echo "... g2c_file_parser.s"
	@echo "... g2c_helpers.obj"
	@echo "... g2c_helpers.i"
	@echo "... g2c_helpers.s"
	@echo "... g2c_main.obj"
	@echo "... g2c_main.i"
	@echo "... g2c_main.s"
	@echo "... g2c_message.obj"
	@echo "... g2c_message.i"
	@echo "... g2c_message.s"
	@echo "... g2c_message_gui.obj"
	@echo "... g2c_message_gui.i"
	@echo "... g2c_message_gui.s"
	@echo "... g2c_project.obj"
	@echo "... g2c_project.i"
	@echo "... g2c_project.s"
	@echo "... g2c_signal.obj"
	@echo "... g2c_signal.i"
	@echo "... g2c_signal.s"
	@echo "... g2c_widget.obj"
	@echo "... g2c_widget.i"
	@echo "... g2c_widget.s"
	@echo "... top_window_gui.obj"
	@echo "... top_window_gui.i"
	@echo "... top_window_gui.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system


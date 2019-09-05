cmake_minimum_required (VERSION 2.8.4)
cmake_policy(SET CMP0015 NEW)
cmake_policy(SET CMP0081 OLD)
project (g2cGui C)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(XML REQUIRED libxml-2.0)
set(INC_DIRS "${GTK3_INCLUDE_DIRS}")
string(REPLACE "C:" "../../.." INC_DIRS "${INC_DIRS}")
set (XML_DIRS "${XML_INCLUDE_DIRS}")
string(REPLACE "C:" "../../.." XML_DIRS "${XML_DIRS}")
include_directories( ${INC_DIRS} ${XML_DIRS})
set(LIB_DIRS "${GTK3_LIBRARY_DIRS}")
string(REPLACE "C:" "../.." LIB_DIRS "${LIB_DIRS}")
set(XML_LIB_DIRS "${XML_LIBRARY_DIRS}")
string(REPLACE "C:" "../.." XML_LIB_DIRS "${XML_LIB_DIRS}")
link_directories(${LIB_DIRS} ${XML_LIB_DIRS})
link_libraries(${GTK3_LIBRARIES} ${XML_LIBRARIES})
add_definitions(${GTK3_CFLAGS_OTHER})
set(OPTIONS "-Wall -Wno-unused-variable -Wno-unused-but-set-variable -Wno-comment -Wno-unused-function -Wno-unused-value -Wno-pointer-sign -g")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${OPTIONS}")
set(EXE_OPTIONS "-mwindows")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EXE_OPTIONS}")
add_definitions( -DWIN32 )
SET(CORE g2c.c
         g2c_accel.c
		 g2c_doc.c
		 g2c_file_parser.c
		 g2c_helpers.c
		 g2c_project.c
		 g2c_signal.c
		 g2c_widget.c
		 )
add_library(lib1 OBJECT ${CORE} )
add_executable( g2c 
		g2c_main.c
		g2c_message.c
		$<TARGET_OBJECTS:lib1> )
SET(GUI g2cGui_main.c
			top_window_gui.c
			file_choose1_gui.c
			file_choose2_gui.c
			file_choose3_gui.c
			control.c
			)
add_library(lib2 OBJECT ${GUI} )
set (CMAKE_RC_COMPILER "/c/msys64/mingw64/bin/windres.exe")
set (RC_SOURCE g2c.rc)
set (RC_OBJ ${RC_SOURCE}.obj)
add_custom_command(OUTPUT ${RC_OBJ} PRE_LINK 
		COMMAND ${CMAKE_RC_COMPILER} ARGS -o${RC_OBJ} -i${RC_SOURCE} -O coff
		DEPENDS lib2
		)
add_executable( g2cGui 
		g2c_message_gui.c
		${RC_OBJ}
		$<TARGET_OBJECTS:lib2>
		$<TARGET_OBJECTS:lib1>)

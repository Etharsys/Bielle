# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/maxime/Documents/Synthèse 2/GLImac-Template"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/maxime/Documents/Synthèse 2/GLImac-Template/build"

# Include any dependencies generated for this target.
include TP2/CMakeFiles/TP2_exo3_triangle_grey.dir/depend.make

# Include the progress variables for this target.
include TP2/CMakeFiles/TP2_exo3_triangle_grey.dir/progress.make

# Include the compile flags for this target's objects.
include TP2/CMakeFiles/TP2_exo3_triangle_grey.dir/flags.make

TP2/CMakeFiles/TP2_exo3_triangle_grey.dir/exo3_triangle_grey.cpp.o: TP2/CMakeFiles/TP2_exo3_triangle_grey.dir/flags.make
TP2/CMakeFiles/TP2_exo3_triangle_grey.dir/exo3_triangle_grey.cpp.o: ../TP2/exo3_triangle_grey.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/maxime/Documents/Synthèse 2/GLImac-Template/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object TP2/CMakeFiles/TP2_exo3_triangle_grey.dir/exo3_triangle_grey.cpp.o"
	cd "/home/maxime/Documents/Synthèse 2/GLImac-Template/build/TP2" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TP2_exo3_triangle_grey.dir/exo3_triangle_grey.cpp.o -c "/home/maxime/Documents/Synthèse 2/GLImac-Template/TP2/exo3_triangle_grey.cpp"

TP2/CMakeFiles/TP2_exo3_triangle_grey.dir/exo3_triangle_grey.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP2_exo3_triangle_grey.dir/exo3_triangle_grey.cpp.i"
	cd "/home/maxime/Documents/Synthèse 2/GLImac-Template/build/TP2" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/maxime/Documents/Synthèse 2/GLImac-Template/TP2/exo3_triangle_grey.cpp" > CMakeFiles/TP2_exo3_triangle_grey.dir/exo3_triangle_grey.cpp.i

TP2/CMakeFiles/TP2_exo3_triangle_grey.dir/exo3_triangle_grey.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP2_exo3_triangle_grey.dir/exo3_triangle_grey.cpp.s"
	cd "/home/maxime/Documents/Synthèse 2/GLImac-Template/build/TP2" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/maxime/Documents/Synthèse 2/GLImac-Template/TP2/exo3_triangle_grey.cpp" -o CMakeFiles/TP2_exo3_triangle_grey.dir/exo3_triangle_grey.cpp.s

# Object files for target TP2_exo3_triangle_grey
TP2_exo3_triangle_grey_OBJECTS = \
"CMakeFiles/TP2_exo3_triangle_grey.dir/exo3_triangle_grey.cpp.o"

# External object files for target TP2_exo3_triangle_grey
TP2_exo3_triangle_grey_EXTERNAL_OBJECTS =

TP2/TP2_exo3_triangle_grey: TP2/CMakeFiles/TP2_exo3_triangle_grey.dir/exo3_triangle_grey.cpp.o
TP2/TP2_exo3_triangle_grey: TP2/CMakeFiles/TP2_exo3_triangle_grey.dir/build.make
TP2/TP2_exo3_triangle_grey: glimac/libglimac.a
TP2/TP2_exo3_triangle_grey: /usr/lib/x86_64-linux-gnu/libSDLmain.a
TP2/TP2_exo3_triangle_grey: /usr/lib/x86_64-linux-gnu/libSDL.so
TP2/TP2_exo3_triangle_grey: /usr/lib/x86_64-linux-gnu/libGL.so.1
TP2/TP2_exo3_triangle_grey: /usr/lib/x86_64-linux-gnu/libGLEW.so
TP2/TP2_exo3_triangle_grey: TP2/CMakeFiles/TP2_exo3_triangle_grey.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/maxime/Documents/Synthèse 2/GLImac-Template/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TP2_exo3_triangle_grey"
	cd "/home/maxime/Documents/Synthèse 2/GLImac-Template/build/TP2" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP2_exo3_triangle_grey.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
TP2/CMakeFiles/TP2_exo3_triangle_grey.dir/build: TP2/TP2_exo3_triangle_grey

.PHONY : TP2/CMakeFiles/TP2_exo3_triangle_grey.dir/build

TP2/CMakeFiles/TP2_exo3_triangle_grey.dir/clean:
	cd "/home/maxime/Documents/Synthèse 2/GLImac-Template/build/TP2" && $(CMAKE_COMMAND) -P CMakeFiles/TP2_exo3_triangle_grey.dir/cmake_clean.cmake
.PHONY : TP2/CMakeFiles/TP2_exo3_triangle_grey.dir/clean

TP2/CMakeFiles/TP2_exo3_triangle_grey.dir/depend:
	cd "/home/maxime/Documents/Synthèse 2/GLImac-Template/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/maxime/Documents/Synthèse 2/GLImac-Template" "/home/maxime/Documents/Synthèse 2/GLImac-Template/TP2" "/home/maxime/Documents/Synthèse 2/GLImac-Template/build" "/home/maxime/Documents/Synthèse 2/GLImac-Template/build/TP2" "/home/maxime/Documents/Synthèse 2/GLImac-Template/build/TP2/CMakeFiles/TP2_exo3_triangle_grey.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : TP2/CMakeFiles/TP2_exo3_triangle_grey.dir/depend


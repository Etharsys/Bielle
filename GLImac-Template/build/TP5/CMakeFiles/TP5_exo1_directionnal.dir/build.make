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
CMAKE_SOURCE_DIR = /home/maxime/Documents/Synthèse2/GLImac-Template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maxime/Documents/Synthèse2/GLImac-Template/build

# Include any dependencies generated for this target.
include TP5/CMakeFiles/TP5_exo1_directionnal.dir/depend.make

# Include the progress variables for this target.
include TP5/CMakeFiles/TP5_exo1_directionnal.dir/progress.make

# Include the compile flags for this target's objects.
include TP5/CMakeFiles/TP5_exo1_directionnal.dir/flags.make

TP5/CMakeFiles/TP5_exo1_directionnal.dir/exo1_directionnal.cpp.o: TP5/CMakeFiles/TP5_exo1_directionnal.dir/flags.make
TP5/CMakeFiles/TP5_exo1_directionnal.dir/exo1_directionnal.cpp.o: ../TP5/exo1_directionnal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maxime/Documents/Synthèse2/GLImac-Template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object TP5/CMakeFiles/TP5_exo1_directionnal.dir/exo1_directionnal.cpp.o"
	cd /home/maxime/Documents/Synthèse2/GLImac-Template/build/TP5 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TP5_exo1_directionnal.dir/exo1_directionnal.cpp.o -c /home/maxime/Documents/Synthèse2/GLImac-Template/TP5/exo1_directionnal.cpp

TP5/CMakeFiles/TP5_exo1_directionnal.dir/exo1_directionnal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP5_exo1_directionnal.dir/exo1_directionnal.cpp.i"
	cd /home/maxime/Documents/Synthèse2/GLImac-Template/build/TP5 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maxime/Documents/Synthèse2/GLImac-Template/TP5/exo1_directionnal.cpp > CMakeFiles/TP5_exo1_directionnal.dir/exo1_directionnal.cpp.i

TP5/CMakeFiles/TP5_exo1_directionnal.dir/exo1_directionnal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP5_exo1_directionnal.dir/exo1_directionnal.cpp.s"
	cd /home/maxime/Documents/Synthèse2/GLImac-Template/build/TP5 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maxime/Documents/Synthèse2/GLImac-Template/TP5/exo1_directionnal.cpp -o CMakeFiles/TP5_exo1_directionnal.dir/exo1_directionnal.cpp.s

# Object files for target TP5_exo1_directionnal
TP5_exo1_directionnal_OBJECTS = \
"CMakeFiles/TP5_exo1_directionnal.dir/exo1_directionnal.cpp.o"

# External object files for target TP5_exo1_directionnal
TP5_exo1_directionnal_EXTERNAL_OBJECTS =

TP5/TP5_exo1_directionnal: TP5/CMakeFiles/TP5_exo1_directionnal.dir/exo1_directionnal.cpp.o
TP5/TP5_exo1_directionnal: TP5/CMakeFiles/TP5_exo1_directionnal.dir/build.make
TP5/TP5_exo1_directionnal: glimac/libglimac.a
TP5/TP5_exo1_directionnal: /usr/lib/x86_64-linux-gnu/libSDLmain.a
TP5/TP5_exo1_directionnal: /usr/lib/x86_64-linux-gnu/libSDL.so
TP5/TP5_exo1_directionnal: /usr/lib/x86_64-linux-gnu/libGL.so.1
TP5/TP5_exo1_directionnal: /usr/lib/x86_64-linux-gnu/libGLEW.so
TP5/TP5_exo1_directionnal: TP5/CMakeFiles/TP5_exo1_directionnal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/maxime/Documents/Synthèse2/GLImac-Template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TP5_exo1_directionnal"
	cd /home/maxime/Documents/Synthèse2/GLImac-Template/build/TP5 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP5_exo1_directionnal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
TP5/CMakeFiles/TP5_exo1_directionnal.dir/build: TP5/TP5_exo1_directionnal

.PHONY : TP5/CMakeFiles/TP5_exo1_directionnal.dir/build

TP5/CMakeFiles/TP5_exo1_directionnal.dir/clean:
	cd /home/maxime/Documents/Synthèse2/GLImac-Template/build/TP5 && $(CMAKE_COMMAND) -P CMakeFiles/TP5_exo1_directionnal.dir/cmake_clean.cmake
.PHONY : TP5/CMakeFiles/TP5_exo1_directionnal.dir/clean

TP5/CMakeFiles/TP5_exo1_directionnal.dir/depend:
	cd /home/maxime/Documents/Synthèse2/GLImac-Template/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maxime/Documents/Synthèse2/GLImac-Template /home/maxime/Documents/Synthèse2/GLImac-Template/TP5 /home/maxime/Documents/Synthèse2/GLImac-Template/build /home/maxime/Documents/Synthèse2/GLImac-Template/build/TP5 /home/maxime/Documents/Synthèse2/GLImac-Template/build/TP5/CMakeFiles/TP5_exo1_directionnal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : TP5/CMakeFiles/TP5_exo1_directionnal.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/walter/MEGAsync/Vision/textura

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/walter/MEGAsync/Vision/textura/build

# Include any dependencies generated for this target.
include CMakeFiles/sum_diff.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sum_diff.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sum_diff.dir/flags.make

CMakeFiles/sum_diff.dir/sum_diff.cpp.o: CMakeFiles/sum_diff.dir/flags.make
CMakeFiles/sum_diff.dir/sum_diff.cpp.o: ../sum_diff.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/walter/MEGAsync/Vision/textura/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sum_diff.dir/sum_diff.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sum_diff.dir/sum_diff.cpp.o -c /home/walter/MEGAsync/Vision/textura/sum_diff.cpp

CMakeFiles/sum_diff.dir/sum_diff.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sum_diff.dir/sum_diff.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/walter/MEGAsync/Vision/textura/sum_diff.cpp > CMakeFiles/sum_diff.dir/sum_diff.cpp.i

CMakeFiles/sum_diff.dir/sum_diff.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sum_diff.dir/sum_diff.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/walter/MEGAsync/Vision/textura/sum_diff.cpp -o CMakeFiles/sum_diff.dir/sum_diff.cpp.s

CMakeFiles/sum_diff.dir/sum_diff.cpp.o.requires:

.PHONY : CMakeFiles/sum_diff.dir/sum_diff.cpp.o.requires

CMakeFiles/sum_diff.dir/sum_diff.cpp.o.provides: CMakeFiles/sum_diff.dir/sum_diff.cpp.o.requires
	$(MAKE) -f CMakeFiles/sum_diff.dir/build.make CMakeFiles/sum_diff.dir/sum_diff.cpp.o.provides.build
.PHONY : CMakeFiles/sum_diff.dir/sum_diff.cpp.o.provides

CMakeFiles/sum_diff.dir/sum_diff.cpp.o.provides.build: CMakeFiles/sum_diff.dir/sum_diff.cpp.o


# Object files for target sum_diff
sum_diff_OBJECTS = \
"CMakeFiles/sum_diff.dir/sum_diff.cpp.o"

# External object files for target sum_diff
sum_diff_EXTERNAL_OBJECTS =

sum_diff: CMakeFiles/sum_diff.dir/sum_diff.cpp.o
sum_diff: CMakeFiles/sum_diff.dir/build.make
sum_diff: /usr/local/lib/libopencv_shape.so.3.2.0
sum_diff: /usr/local/lib/libopencv_stitching.so.3.2.0
sum_diff: /usr/local/lib/libopencv_superres.so.3.2.0
sum_diff: /usr/local/lib/libopencv_videostab.so.3.2.0
sum_diff: /usr/local/lib/libopencv_viz.so.3.2.0
sum_diff: /usr/local/lib/libopencv_objdetect.so.3.2.0
sum_diff: /usr/local/lib/libopencv_calib3d.so.3.2.0
sum_diff: /usr/local/lib/libopencv_features2d.so.3.2.0
sum_diff: /usr/local/lib/libopencv_flann.so.3.2.0
sum_diff: /usr/local/lib/libopencv_highgui.so.3.2.0
sum_diff: /usr/local/lib/libopencv_ml.so.3.2.0
sum_diff: /usr/local/lib/libopencv_photo.so.3.2.0
sum_diff: /usr/local/lib/libopencv_video.so.3.2.0
sum_diff: /usr/local/lib/libopencv_videoio.so.3.2.0
sum_diff: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
sum_diff: /usr/local/lib/libopencv_imgproc.so.3.2.0
sum_diff: /usr/local/lib/libopencv_core.so.3.2.0
sum_diff: CMakeFiles/sum_diff.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/walter/MEGAsync/Vision/textura/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sum_diff"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sum_diff.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sum_diff.dir/build: sum_diff

.PHONY : CMakeFiles/sum_diff.dir/build

CMakeFiles/sum_diff.dir/requires: CMakeFiles/sum_diff.dir/sum_diff.cpp.o.requires

.PHONY : CMakeFiles/sum_diff.dir/requires

CMakeFiles/sum_diff.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sum_diff.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sum_diff.dir/clean

CMakeFiles/sum_diff.dir/depend:
	cd /home/walter/MEGAsync/Vision/textura/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/walter/MEGAsync/Vision/textura /home/walter/MEGAsync/Vision/textura /home/walter/MEGAsync/Vision/textura/build /home/walter/MEGAsync/Vision/textura/build /home/walter/MEGAsync/Vision/textura/build/CMakeFiles/sum_diff.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sum_diff.dir/depend


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
CMAKE_SOURCE_DIR = /home/walter/Vision/Practica_2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/walter/Vision/Practica_2/build

# Include any dependencies generated for this target.
include CMakeFiles/vision.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/vision.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/vision.dir/flags.make

CMakeFiles/vision.dir/vision.cpp.o: CMakeFiles/vision.dir/flags.make
CMakeFiles/vision.dir/vision.cpp.o: ../vision.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/walter/Vision/Practica_2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/vision.dir/vision.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vision.dir/vision.cpp.o -c /home/walter/Vision/Practica_2/vision.cpp

CMakeFiles/vision.dir/vision.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vision.dir/vision.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/walter/Vision/Practica_2/vision.cpp > CMakeFiles/vision.dir/vision.cpp.i

CMakeFiles/vision.dir/vision.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vision.dir/vision.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/walter/Vision/Practica_2/vision.cpp -o CMakeFiles/vision.dir/vision.cpp.s

CMakeFiles/vision.dir/vision.cpp.o.requires:

.PHONY : CMakeFiles/vision.dir/vision.cpp.o.requires

CMakeFiles/vision.dir/vision.cpp.o.provides: CMakeFiles/vision.dir/vision.cpp.o.requires
	$(MAKE) -f CMakeFiles/vision.dir/build.make CMakeFiles/vision.dir/vision.cpp.o.provides.build
.PHONY : CMakeFiles/vision.dir/vision.cpp.o.provides

CMakeFiles/vision.dir/vision.cpp.o.provides.build: CMakeFiles/vision.dir/vision.cpp.o


# Object files for target vision
vision_OBJECTS = \
"CMakeFiles/vision.dir/vision.cpp.o"

# External object files for target vision
vision_EXTERNAL_OBJECTS =

vision: CMakeFiles/vision.dir/vision.cpp.o
vision: CMakeFiles/vision.dir/build.make
vision: /usr/local/lib/libopencv_shape.so.3.2.0
vision: /usr/local/lib/libopencv_stitching.so.3.2.0
vision: /usr/local/lib/libopencv_superres.so.3.2.0
vision: /usr/local/lib/libopencv_videostab.so.3.2.0
vision: /usr/local/lib/libopencv_viz.so.3.2.0
vision: /usr/local/lib/libopencv_objdetect.so.3.2.0
vision: /usr/local/lib/libopencv_calib3d.so.3.2.0
vision: /usr/local/lib/libopencv_features2d.so.3.2.0
vision: /usr/local/lib/libopencv_flann.so.3.2.0
vision: /usr/local/lib/libopencv_highgui.so.3.2.0
vision: /usr/local/lib/libopencv_ml.so.3.2.0
vision: /usr/local/lib/libopencv_photo.so.3.2.0
vision: /usr/local/lib/libopencv_video.so.3.2.0
vision: /usr/local/lib/libopencv_videoio.so.3.2.0
vision: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
vision: /usr/local/lib/libopencv_imgproc.so.3.2.0
vision: /usr/local/lib/libopencv_core.so.3.2.0
vision: CMakeFiles/vision.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/walter/Vision/Practica_2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable vision"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vision.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/vision.dir/build: vision

.PHONY : CMakeFiles/vision.dir/build

CMakeFiles/vision.dir/requires: CMakeFiles/vision.dir/vision.cpp.o.requires

.PHONY : CMakeFiles/vision.dir/requires

CMakeFiles/vision.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vision.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vision.dir/clean

CMakeFiles/vision.dir/depend:
	cd /home/walter/Vision/Practica_2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/walter/Vision/Practica_2 /home/walter/Vision/Practica_2 /home/walter/Vision/Practica_2/build /home/walter/Vision/Practica_2/build /home/walter/Vision/Practica_2/build/CMakeFiles/vision.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/vision.dir/depend

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
CMAKE_SOURCE_DIR = /home/walter/MEGAsync/computerVision/5_Otsu_method

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/walter/MEGAsync/computerVision/5_Otsu_method/build

# Include any dependencies generated for this target.
include CMakeFiles/otsu.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/otsu.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/otsu.dir/flags.make

CMakeFiles/otsu.dir/otsu.cpp.o: CMakeFiles/otsu.dir/flags.make
CMakeFiles/otsu.dir/otsu.cpp.o: ../otsu.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/walter/MEGAsync/computerVision/5_Otsu_method/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/otsu.dir/otsu.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/otsu.dir/otsu.cpp.o -c /home/walter/MEGAsync/computerVision/5_Otsu_method/otsu.cpp

CMakeFiles/otsu.dir/otsu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/otsu.dir/otsu.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/walter/MEGAsync/computerVision/5_Otsu_method/otsu.cpp > CMakeFiles/otsu.dir/otsu.cpp.i

CMakeFiles/otsu.dir/otsu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/otsu.dir/otsu.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/walter/MEGAsync/computerVision/5_Otsu_method/otsu.cpp -o CMakeFiles/otsu.dir/otsu.cpp.s

CMakeFiles/otsu.dir/otsu.cpp.o.requires:

.PHONY : CMakeFiles/otsu.dir/otsu.cpp.o.requires

CMakeFiles/otsu.dir/otsu.cpp.o.provides: CMakeFiles/otsu.dir/otsu.cpp.o.requires
	$(MAKE) -f CMakeFiles/otsu.dir/build.make CMakeFiles/otsu.dir/otsu.cpp.o.provides.build
.PHONY : CMakeFiles/otsu.dir/otsu.cpp.o.provides

CMakeFiles/otsu.dir/otsu.cpp.o.provides.build: CMakeFiles/otsu.dir/otsu.cpp.o


# Object files for target otsu
otsu_OBJECTS = \
"CMakeFiles/otsu.dir/otsu.cpp.o"

# External object files for target otsu
otsu_EXTERNAL_OBJECTS =

otsu: CMakeFiles/otsu.dir/otsu.cpp.o
otsu: CMakeFiles/otsu.dir/build.make
otsu: /usr/local/lib/libopencv_shape.so.3.2.0
otsu: /usr/local/lib/libopencv_stitching.so.3.2.0
otsu: /usr/local/lib/libopencv_superres.so.3.2.0
otsu: /usr/local/lib/libopencv_videostab.so.3.2.0
otsu: /usr/local/lib/libopencv_viz.so.3.2.0
otsu: /usr/local/lib/libopencv_objdetect.so.3.2.0
otsu: /usr/local/lib/libopencv_calib3d.so.3.2.0
otsu: /usr/local/lib/libopencv_features2d.so.3.2.0
otsu: /usr/local/lib/libopencv_flann.so.3.2.0
otsu: /usr/local/lib/libopencv_highgui.so.3.2.0
otsu: /usr/local/lib/libopencv_ml.so.3.2.0
otsu: /usr/local/lib/libopencv_photo.so.3.2.0
otsu: /usr/local/lib/libopencv_video.so.3.2.0
otsu: /usr/local/lib/libopencv_videoio.so.3.2.0
otsu: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
otsu: /usr/local/lib/libopencv_imgproc.so.3.2.0
otsu: /usr/local/lib/libopencv_core.so.3.2.0
otsu: CMakeFiles/otsu.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/walter/MEGAsync/computerVision/5_Otsu_method/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable otsu"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/otsu.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/otsu.dir/build: otsu

.PHONY : CMakeFiles/otsu.dir/build

CMakeFiles/otsu.dir/requires: CMakeFiles/otsu.dir/otsu.cpp.o.requires

.PHONY : CMakeFiles/otsu.dir/requires

CMakeFiles/otsu.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/otsu.dir/cmake_clean.cmake
.PHONY : CMakeFiles/otsu.dir/clean

CMakeFiles/otsu.dir/depend:
	cd /home/walter/MEGAsync/computerVision/5_Otsu_method/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/walter/MEGAsync/computerVision/5_Otsu_method /home/walter/MEGAsync/computerVision/5_Otsu_method /home/walter/MEGAsync/computerVision/5_Otsu_method/build /home/walter/MEGAsync/computerVision/5_Otsu_method/build /home/walter/MEGAsync/computerVision/5_Otsu_method/build/CMakeFiles/otsu.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/otsu.dir/depend


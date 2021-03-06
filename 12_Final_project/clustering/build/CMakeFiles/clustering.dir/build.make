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
CMAKE_SOURCE_DIR = /home/walter/MEGAsync/Vision/project/clustering

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/walter/MEGAsync/Vision/project/clustering/build

# Include any dependencies generated for this target.
include CMakeFiles/clustering.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/clustering.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/clustering.dir/flags.make

CMakeFiles/clustering.dir/clustering.cpp.o: CMakeFiles/clustering.dir/flags.make
CMakeFiles/clustering.dir/clustering.cpp.o: ../clustering.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/walter/MEGAsync/Vision/project/clustering/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/clustering.dir/clustering.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clustering.dir/clustering.cpp.o -c /home/walter/MEGAsync/Vision/project/clustering/clustering.cpp

CMakeFiles/clustering.dir/clustering.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clustering.dir/clustering.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/walter/MEGAsync/Vision/project/clustering/clustering.cpp > CMakeFiles/clustering.dir/clustering.cpp.i

CMakeFiles/clustering.dir/clustering.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clustering.dir/clustering.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/walter/MEGAsync/Vision/project/clustering/clustering.cpp -o CMakeFiles/clustering.dir/clustering.cpp.s

CMakeFiles/clustering.dir/clustering.cpp.o.requires:

.PHONY : CMakeFiles/clustering.dir/clustering.cpp.o.requires

CMakeFiles/clustering.dir/clustering.cpp.o.provides: CMakeFiles/clustering.dir/clustering.cpp.o.requires
	$(MAKE) -f CMakeFiles/clustering.dir/build.make CMakeFiles/clustering.dir/clustering.cpp.o.provides.build
.PHONY : CMakeFiles/clustering.dir/clustering.cpp.o.provides

CMakeFiles/clustering.dir/clustering.cpp.o.provides.build: CMakeFiles/clustering.dir/clustering.cpp.o


# Object files for target clustering
clustering_OBJECTS = \
"CMakeFiles/clustering.dir/clustering.cpp.o"

# External object files for target clustering
clustering_EXTERNAL_OBJECTS =

clustering: CMakeFiles/clustering.dir/clustering.cpp.o
clustering: CMakeFiles/clustering.dir/build.make
clustering: /usr/local/lib/libopencv_shape.so.3.2.0
clustering: /usr/local/lib/libopencv_stitching.so.3.2.0
clustering: /usr/local/lib/libopencv_superres.so.3.2.0
clustering: /usr/local/lib/libopencv_videostab.so.3.2.0
clustering: /usr/local/lib/libopencv_viz.so.3.2.0
clustering: /usr/local/lib/libopencv_objdetect.so.3.2.0
clustering: /usr/local/lib/libopencv_calib3d.so.3.2.0
clustering: /usr/local/lib/libopencv_features2d.so.3.2.0
clustering: /usr/local/lib/libopencv_flann.so.3.2.0
clustering: /usr/local/lib/libopencv_highgui.so.3.2.0
clustering: /usr/local/lib/libopencv_ml.so.3.2.0
clustering: /usr/local/lib/libopencv_photo.so.3.2.0
clustering: /usr/local/lib/libopencv_video.so.3.2.0
clustering: /usr/local/lib/libopencv_videoio.so.3.2.0
clustering: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
clustering: /usr/local/lib/libopencv_imgproc.so.3.2.0
clustering: /usr/local/lib/libopencv_core.so.3.2.0
clustering: CMakeFiles/clustering.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/walter/MEGAsync/Vision/project/clustering/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable clustering"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/clustering.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/clustering.dir/build: clustering

.PHONY : CMakeFiles/clustering.dir/build

CMakeFiles/clustering.dir/requires: CMakeFiles/clustering.dir/clustering.cpp.o.requires

.PHONY : CMakeFiles/clustering.dir/requires

CMakeFiles/clustering.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/clustering.dir/cmake_clean.cmake
.PHONY : CMakeFiles/clustering.dir/clean

CMakeFiles/clustering.dir/depend:
	cd /home/walter/MEGAsync/Vision/project/clustering/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/walter/MEGAsync/Vision/project/clustering /home/walter/MEGAsync/Vision/project/clustering /home/walter/MEGAsync/Vision/project/clustering/build /home/walter/MEGAsync/Vision/project/clustering/build /home/walter/MEGAsync/Vision/project/clustering/build/CMakeFiles/clustering.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/clustering.dir/depend


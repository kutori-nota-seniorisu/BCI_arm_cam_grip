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
CMAKE_SOURCE_DIR = /home/sd/BCI_arm_cam_grip/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sd/BCI_arm_cam_grip/build

# Include any dependencies generated for this target.
include online_analysis/CMakeFiles/rnetstreamingreceiver.dir/depend.make

# Include the progress variables for this target.
include online_analysis/CMakeFiles/rnetstreamingreceiver.dir/progress.make

# Include the compile flags for this target's objects.
include online_analysis/CMakeFiles/rnetstreamingreceiver.dir/flags.make

online_analysis/CMakeFiles/rnetstreamingreceiver.dir/src/rnetstreamingreceiver.cpp.o: online_analysis/CMakeFiles/rnetstreamingreceiver.dir/flags.make
online_analysis/CMakeFiles/rnetstreamingreceiver.dir/src/rnetstreamingreceiver.cpp.o: /home/sd/BCI_arm_cam_grip/src/online_analysis/src/rnetstreamingreceiver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sd/BCI_arm_cam_grip/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object online_analysis/CMakeFiles/rnetstreamingreceiver.dir/src/rnetstreamingreceiver.cpp.o"
	cd /home/sd/BCI_arm_cam_grip/build/online_analysis && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rnetstreamingreceiver.dir/src/rnetstreamingreceiver.cpp.o -c /home/sd/BCI_arm_cam_grip/src/online_analysis/src/rnetstreamingreceiver.cpp

online_analysis/CMakeFiles/rnetstreamingreceiver.dir/src/rnetstreamingreceiver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rnetstreamingreceiver.dir/src/rnetstreamingreceiver.cpp.i"
	cd /home/sd/BCI_arm_cam_grip/build/online_analysis && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sd/BCI_arm_cam_grip/src/online_analysis/src/rnetstreamingreceiver.cpp > CMakeFiles/rnetstreamingreceiver.dir/src/rnetstreamingreceiver.cpp.i

online_analysis/CMakeFiles/rnetstreamingreceiver.dir/src/rnetstreamingreceiver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rnetstreamingreceiver.dir/src/rnetstreamingreceiver.cpp.s"
	cd /home/sd/BCI_arm_cam_grip/build/online_analysis && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sd/BCI_arm_cam_grip/src/online_analysis/src/rnetstreamingreceiver.cpp -o CMakeFiles/rnetstreamingreceiver.dir/src/rnetstreamingreceiver.cpp.s

# Object files for target rnetstreamingreceiver
rnetstreamingreceiver_OBJECTS = \
"CMakeFiles/rnetstreamingreceiver.dir/src/rnetstreamingreceiver.cpp.o"

# External object files for target rnetstreamingreceiver
rnetstreamingreceiver_EXTERNAL_OBJECTS =

/home/sd/BCI_arm_cam_grip/devel/lib/librnetstreamingreceiver.so: online_analysis/CMakeFiles/rnetstreamingreceiver.dir/src/rnetstreamingreceiver.cpp.o
/home/sd/BCI_arm_cam_grip/devel/lib/librnetstreamingreceiver.so: online_analysis/CMakeFiles/rnetstreamingreceiver.dir/build.make
/home/sd/BCI_arm_cam_grip/devel/lib/librnetstreamingreceiver.so: online_analysis/CMakeFiles/rnetstreamingreceiver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sd/BCI_arm_cam_grip/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library /home/sd/BCI_arm_cam_grip/devel/lib/librnetstreamingreceiver.so"
	cd /home/sd/BCI_arm_cam_grip/build/online_analysis && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rnetstreamingreceiver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
online_analysis/CMakeFiles/rnetstreamingreceiver.dir/build: /home/sd/BCI_arm_cam_grip/devel/lib/librnetstreamingreceiver.so

.PHONY : online_analysis/CMakeFiles/rnetstreamingreceiver.dir/build

online_analysis/CMakeFiles/rnetstreamingreceiver.dir/clean:
	cd /home/sd/BCI_arm_cam_grip/build/online_analysis && $(CMAKE_COMMAND) -P CMakeFiles/rnetstreamingreceiver.dir/cmake_clean.cmake
.PHONY : online_analysis/CMakeFiles/rnetstreamingreceiver.dir/clean

online_analysis/CMakeFiles/rnetstreamingreceiver.dir/depend:
	cd /home/sd/BCI_arm_cam_grip/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sd/BCI_arm_cam_grip/src /home/sd/BCI_arm_cam_grip/src/online_analysis /home/sd/BCI_arm_cam_grip/build /home/sd/BCI_arm_cam_grip/build/online_analysis /home/sd/BCI_arm_cam_grip/build/online_analysis/CMakeFiles/rnetstreamingreceiver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : online_analysis/CMakeFiles/rnetstreamingreceiver.dir/depend


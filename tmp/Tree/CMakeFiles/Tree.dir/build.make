# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/cmake/1413/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1413/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mikhail/TA/lab2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mikhail/TA/lab2/tmp

# Include any dependencies generated for this target.
include Tree/CMakeFiles/Tree.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Tree/CMakeFiles/Tree.dir/compiler_depend.make

# Include the progress variables for this target.
include Tree/CMakeFiles/Tree.dir/progress.make

# Include the compile flags for this target's objects.
include Tree/CMakeFiles/Tree.dir/flags.make

Tree/CMakeFiles/Tree.dir/STree.cpp.o: Tree/CMakeFiles/Tree.dir/flags.make
Tree/CMakeFiles/Tree.dir/STree.cpp.o: /home/mikhail/TA/lab2/Tree/STree.cpp
Tree/CMakeFiles/Tree.dir/STree.cpp.o: Tree/CMakeFiles/Tree.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/mikhail/TA/lab2/tmp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Tree/CMakeFiles/Tree.dir/STree.cpp.o"
	cd /home/mikhail/TA/lab2/tmp/Tree && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Tree/CMakeFiles/Tree.dir/STree.cpp.o -MF CMakeFiles/Tree.dir/STree.cpp.o.d -o CMakeFiles/Tree.dir/STree.cpp.o -c /home/mikhail/TA/lab2/Tree/STree.cpp

Tree/CMakeFiles/Tree.dir/STree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Tree.dir/STree.cpp.i"
	cd /home/mikhail/TA/lab2/tmp/Tree && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mikhail/TA/lab2/Tree/STree.cpp > CMakeFiles/Tree.dir/STree.cpp.i

Tree/CMakeFiles/Tree.dir/STree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Tree.dir/STree.cpp.s"
	cd /home/mikhail/TA/lab2/tmp/Tree && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mikhail/TA/lab2/Tree/STree.cpp -o CMakeFiles/Tree.dir/STree.cpp.s

# Object files for target Tree
Tree_OBJECTS = \
"CMakeFiles/Tree.dir/STree.cpp.o"

# External object files for target Tree
Tree_EXTERNAL_OBJECTS =

Tree/libTree.a: Tree/CMakeFiles/Tree.dir/STree.cpp.o
Tree/libTree.a: Tree/CMakeFiles/Tree.dir/build.make
Tree/libTree.a: Tree/CMakeFiles/Tree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/mikhail/TA/lab2/tmp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libTree.a"
	cd /home/mikhail/TA/lab2/tmp/Tree && $(CMAKE_COMMAND) -P CMakeFiles/Tree.dir/cmake_clean_target.cmake
	cd /home/mikhail/TA/lab2/tmp/Tree && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Tree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Tree/CMakeFiles/Tree.dir/build: Tree/libTree.a
.PHONY : Tree/CMakeFiles/Tree.dir/build

Tree/CMakeFiles/Tree.dir/clean:
	cd /home/mikhail/TA/lab2/tmp/Tree && $(CMAKE_COMMAND) -P CMakeFiles/Tree.dir/cmake_clean.cmake
.PHONY : Tree/CMakeFiles/Tree.dir/clean

Tree/CMakeFiles/Tree.dir/depend:
	cd /home/mikhail/TA/lab2/tmp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mikhail/TA/lab2 /home/mikhail/TA/lab2/Tree /home/mikhail/TA/lab2/tmp /home/mikhail/TA/lab2/tmp/Tree /home/mikhail/TA/lab2/tmp/Tree/CMakeFiles/Tree.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : Tree/CMakeFiles/Tree.dir/depend


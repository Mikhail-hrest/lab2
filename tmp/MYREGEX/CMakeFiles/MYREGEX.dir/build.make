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
include MYREGEX/CMakeFiles/MYREGEX.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include MYREGEX/CMakeFiles/MYREGEX.dir/compiler_depend.make

# Include the progress variables for this target.
include MYREGEX/CMakeFiles/MYREGEX.dir/progress.make

# Include the compile flags for this target's objects.
include MYREGEX/CMakeFiles/MYREGEX.dir/flags.make

MYREGEX/CMakeFiles/MYREGEX.dir/MYREGEX.cpp.o: MYREGEX/CMakeFiles/MYREGEX.dir/flags.make
MYREGEX/CMakeFiles/MYREGEX.dir/MYREGEX.cpp.o: /home/mikhail/TA/lab2/MYREGEX/MYREGEX.cpp
MYREGEX/CMakeFiles/MYREGEX.dir/MYREGEX.cpp.o: MYREGEX/CMakeFiles/MYREGEX.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/mikhail/TA/lab2/tmp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object MYREGEX/CMakeFiles/MYREGEX.dir/MYREGEX.cpp.o"
	cd /home/mikhail/TA/lab2/tmp/MYREGEX && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT MYREGEX/CMakeFiles/MYREGEX.dir/MYREGEX.cpp.o -MF CMakeFiles/MYREGEX.dir/MYREGEX.cpp.o.d -o CMakeFiles/MYREGEX.dir/MYREGEX.cpp.o -c /home/mikhail/TA/lab2/MYREGEX/MYREGEX.cpp

MYREGEX/CMakeFiles/MYREGEX.dir/MYREGEX.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MYREGEX.dir/MYREGEX.cpp.i"
	cd /home/mikhail/TA/lab2/tmp/MYREGEX && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mikhail/TA/lab2/MYREGEX/MYREGEX.cpp > CMakeFiles/MYREGEX.dir/MYREGEX.cpp.i

MYREGEX/CMakeFiles/MYREGEX.dir/MYREGEX.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MYREGEX.dir/MYREGEX.cpp.s"
	cd /home/mikhail/TA/lab2/tmp/MYREGEX && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mikhail/TA/lab2/MYREGEX/MYREGEX.cpp -o CMakeFiles/MYREGEX.dir/MYREGEX.cpp.s

# Object files for target MYREGEX
MYREGEX_OBJECTS = \
"CMakeFiles/MYREGEX.dir/MYREGEX.cpp.o"

# External object files for target MYREGEX
MYREGEX_EXTERNAL_OBJECTS =

MYREGEX/libMYREGEX.a: MYREGEX/CMakeFiles/MYREGEX.dir/MYREGEX.cpp.o
MYREGEX/libMYREGEX.a: MYREGEX/CMakeFiles/MYREGEX.dir/build.make
MYREGEX/libMYREGEX.a: MYREGEX/CMakeFiles/MYREGEX.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/mikhail/TA/lab2/tmp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libMYREGEX.a"
	cd /home/mikhail/TA/lab2/tmp/MYREGEX && $(CMAKE_COMMAND) -P CMakeFiles/MYREGEX.dir/cmake_clean_target.cmake
	cd /home/mikhail/TA/lab2/tmp/MYREGEX && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MYREGEX.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
MYREGEX/CMakeFiles/MYREGEX.dir/build: MYREGEX/libMYREGEX.a
.PHONY : MYREGEX/CMakeFiles/MYREGEX.dir/build

MYREGEX/CMakeFiles/MYREGEX.dir/clean:
	cd /home/mikhail/TA/lab2/tmp/MYREGEX && $(CMAKE_COMMAND) -P CMakeFiles/MYREGEX.dir/cmake_clean.cmake
.PHONY : MYREGEX/CMakeFiles/MYREGEX.dir/clean

MYREGEX/CMakeFiles/MYREGEX.dir/depend:
	cd /home/mikhail/TA/lab2/tmp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mikhail/TA/lab2 /home/mikhail/TA/lab2/MYREGEX /home/mikhail/TA/lab2/tmp /home/mikhail/TA/lab2/tmp/MYREGEX /home/mikhail/TA/lab2/tmp/MYREGEX/CMakeFiles/MYREGEX.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : MYREGEX/CMakeFiles/MYREGEX.dir/depend


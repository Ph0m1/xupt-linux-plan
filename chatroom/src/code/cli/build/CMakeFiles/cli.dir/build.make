# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ph0m/plan/chatroom/src/code/cli/back

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ph0m/plan/chatroom/src/code/cli/build

# Include any dependencies generated for this target.
include CMakeFiles/cli.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cli.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cli.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cli.dir/flags.make

CMakeFiles/cli.dir/menu.cpp.o: CMakeFiles/cli.dir/flags.make
CMakeFiles/cli.dir/menu.cpp.o: /home/ph0m/plan/chatroom/src/code/cli/back/menu.cpp
CMakeFiles/cli.dir/menu.cpp.o: CMakeFiles/cli.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ph0m/plan/chatroom/src/code/cli/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cli.dir/menu.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cli.dir/menu.cpp.o -MF CMakeFiles/cli.dir/menu.cpp.o.d -o CMakeFiles/cli.dir/menu.cpp.o -c /home/ph0m/plan/chatroom/src/code/cli/back/menu.cpp

CMakeFiles/cli.dir/menu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cli.dir/menu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ph0m/plan/chatroom/src/code/cli/back/menu.cpp > CMakeFiles/cli.dir/menu.cpp.i

CMakeFiles/cli.dir/menu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cli.dir/menu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ph0m/plan/chatroom/src/code/cli/back/menu.cpp -o CMakeFiles/cli.dir/menu.cpp.s

# Object files for target cli
cli_OBJECTS = \
"CMakeFiles/cli.dir/menu.cpp.o"

# External object files for target cli
cli_EXTERNAL_OBJECTS =

cli: CMakeFiles/cli.dir/menu.cpp.o
cli: CMakeFiles/cli.dir/build.make
cli: /usr/lib/libQt5Widgets.so.5.15.13
cli: /usr/lib/libQt5Gui.so.5.15.13
cli: /usr/lib/libQt5Core.so.5.15.13
cli: CMakeFiles/cli.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ph0m/plan/chatroom/src/code/cli/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cli"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cli.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cli.dir/build: cli
.PHONY : CMakeFiles/cli.dir/build

CMakeFiles/cli.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cli.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cli.dir/clean

CMakeFiles/cli.dir/depend:
	cd /home/ph0m/plan/chatroom/src/code/cli/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ph0m/plan/chatroom/src/code/cli/back /home/ph0m/plan/chatroom/src/code/cli/back /home/ph0m/plan/chatroom/src/code/cli/build /home/ph0m/plan/chatroom/src/code/cli/build /home/ph0m/plan/chatroom/src/code/cli/build/CMakeFiles/cli.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/cli.dir/depend


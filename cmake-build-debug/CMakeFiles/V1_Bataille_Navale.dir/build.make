# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /usr/local/lib/python3.10/dist-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /usr/local/lib/python3.10/dist-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/c/Users/Raphaël DA SILVA/Desktop/V1 Bataille Navale"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/Raphaël DA SILVA/Desktop/V1 Bataille Navale/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/V1_Bataille_Navale.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/V1_Bataille_Navale.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/V1_Bataille_Navale.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/V1_Bataille_Navale.dir/flags.make

CMakeFiles/V1_Bataille_Navale.dir/main.c.o: CMakeFiles/V1_Bataille_Navale.dir/flags.make
CMakeFiles/V1_Bataille_Navale.dir/main.c.o: /mnt/c/Users/Raphaël\ DA\ SILVA/Desktop/V1\ Bataille\ Navale/main.c
CMakeFiles/V1_Bataille_Navale.dir/main.c.o: CMakeFiles/V1_Bataille_Navale.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Raphaël DA SILVA/Desktop/V1 Bataille Navale/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/V1_Bataille_Navale.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/V1_Bataille_Navale.dir/main.c.o -MF CMakeFiles/V1_Bataille_Navale.dir/main.c.o.d -o CMakeFiles/V1_Bataille_Navale.dir/main.c.o -c "/mnt/c/Users/Raphaël DA SILVA/Desktop/V1 Bataille Navale/main.c"

CMakeFiles/V1_Bataille_Navale.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/V1_Bataille_Navale.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/c/Users/Raphaël DA SILVA/Desktop/V1 Bataille Navale/main.c" > CMakeFiles/V1_Bataille_Navale.dir/main.c.i

CMakeFiles/V1_Bataille_Navale.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/V1_Bataille_Navale.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/c/Users/Raphaël DA SILVA/Desktop/V1 Bataille Navale/main.c" -o CMakeFiles/V1_Bataille_Navale.dir/main.c.s

# Object files for target V1_Bataille_Navale
V1_Bataille_Navale_OBJECTS = \
"CMakeFiles/V1_Bataille_Navale.dir/main.c.o"

# External object files for target V1_Bataille_Navale
V1_Bataille_Navale_EXTERNAL_OBJECTS =

V1_Bataille_Navale: CMakeFiles/V1_Bataille_Navale.dir/main.c.o
V1_Bataille_Navale: CMakeFiles/V1_Bataille_Navale.dir/build.make
V1_Bataille_Navale: CMakeFiles/V1_Bataille_Navale.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/Raphaël DA SILVA/Desktop/V1 Bataille Navale/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable V1_Bataille_Navale"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/V1_Bataille_Navale.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/V1_Bataille_Navale.dir/build: V1_Bataille_Navale
.PHONY : CMakeFiles/V1_Bataille_Navale.dir/build

CMakeFiles/V1_Bataille_Navale.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/V1_Bataille_Navale.dir/cmake_clean.cmake
.PHONY : CMakeFiles/V1_Bataille_Navale.dir/clean

CMakeFiles/V1_Bataille_Navale.dir/depend:
	cd "/mnt/c/Users/Raphaël DA SILVA/Desktop/V1 Bataille Navale/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/Raphaël DA SILVA/Desktop/V1 Bataille Navale" "/mnt/c/Users/Raphaël DA SILVA/Desktop/V1 Bataille Navale" "/mnt/c/Users/Raphaël DA SILVA/Desktop/V1 Bataille Navale/cmake-build-debug" "/mnt/c/Users/Raphaël DA SILVA/Desktop/V1 Bataille Navale/cmake-build-debug" "/mnt/c/Users/Raphaël DA SILVA/Desktop/V1 Bataille Navale/cmake-build-debug/CMakeFiles/V1_Bataille_Navale.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/V1_Bataille_Navale.dir/depend

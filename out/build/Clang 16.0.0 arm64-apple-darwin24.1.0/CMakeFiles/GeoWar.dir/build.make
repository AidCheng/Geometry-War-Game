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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.0/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/aiden/Developer/COMP4300/Geo-Wars

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/aiden/Developer/COMP4300/Geo-Wars/out/build/Clang 16.0.0 arm64-apple-darwin24.1.0"

# Include any dependencies generated for this target.
include CMakeFiles/GeoWar.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/GeoWar.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/GeoWar.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GeoWar.dir/flags.make

CMakeFiles/GeoWar.dir/main.cpp.o: CMakeFiles/GeoWar.dir/flags.make
CMakeFiles/GeoWar.dir/main.cpp.o: /Users/aiden/Developer/COMP4300/Geo-Wars/main.cpp
CMakeFiles/GeoWar.dir/main.cpp.o: CMakeFiles/GeoWar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/aiden/Developer/COMP4300/Geo-Wars/out/build/Clang 16.0.0 arm64-apple-darwin24.1.0/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GeoWar.dir/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GeoWar.dir/main.cpp.o -MF CMakeFiles/GeoWar.dir/main.cpp.o.d -o CMakeFiles/GeoWar.dir/main.cpp.o -c /Users/aiden/Developer/COMP4300/Geo-Wars/main.cpp

CMakeFiles/GeoWar.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GeoWar.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/aiden/Developer/COMP4300/Geo-Wars/main.cpp > CMakeFiles/GeoWar.dir/main.cpp.i

CMakeFiles/GeoWar.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GeoWar.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/aiden/Developer/COMP4300/Geo-Wars/main.cpp -o CMakeFiles/GeoWar.dir/main.cpp.s

# Object files for target GeoWar
GeoWar_OBJECTS = \
"CMakeFiles/GeoWar.dir/main.cpp.o"

# External object files for target GeoWar
GeoWar_EXTERNAL_OBJECTS =

GeoWar: CMakeFiles/GeoWar.dir/main.cpp.o
GeoWar: CMakeFiles/GeoWar.dir/build.make
GeoWar: CMakeFiles/GeoWar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/aiden/Developer/COMP4300/Geo-Wars/out/build/Clang 16.0.0 arm64-apple-darwin24.1.0/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable GeoWar"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GeoWar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GeoWar.dir/build: GeoWar
.PHONY : CMakeFiles/GeoWar.dir/build

CMakeFiles/GeoWar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GeoWar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GeoWar.dir/clean

CMakeFiles/GeoWar.dir/depend:
	cd "/Users/aiden/Developer/COMP4300/Geo-Wars/out/build/Clang 16.0.0 arm64-apple-darwin24.1.0" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/aiden/Developer/COMP4300/Geo-Wars /Users/aiden/Developer/COMP4300/Geo-Wars "/Users/aiden/Developer/COMP4300/Geo-Wars/out/build/Clang 16.0.0 arm64-apple-darwin24.1.0" "/Users/aiden/Developer/COMP4300/Geo-Wars/out/build/Clang 16.0.0 arm64-apple-darwin24.1.0" "/Users/aiden/Developer/COMP4300/Geo-Wars/out/build/Clang 16.0.0 arm64-apple-darwin24.1.0/CMakeFiles/GeoWar.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/GeoWar.dir/depend


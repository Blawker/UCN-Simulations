# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/Thomas_Guilbaud/Documents/Stage 2A - UCN - 2020/UCN-Simulations/code"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/Thomas_Guilbaud/Documents/Stage 2A - UCN - 2020/UCN-Simulations/code"

# Include any dependencies generated for this target.
include CMakeFiles/conversion.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/conversion.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/conversion.dir/flags.make

CMakeFiles/conversion.dir/src/conversion.cxx.o: CMakeFiles/conversion.dir/flags.make
CMakeFiles/conversion.dir/src/conversion.cxx.o: src/conversion.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/Thomas_Guilbaud/Documents/Stage 2A - UCN - 2020/UCN-Simulations/code/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/conversion.dir/src/conversion.cxx.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conversion.dir/src/conversion.cxx.o -c "/Users/Thomas_Guilbaud/Documents/Stage 2A - UCN - 2020/UCN-Simulations/code/src/conversion.cxx"

CMakeFiles/conversion.dir/src/conversion.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conversion.dir/src/conversion.cxx.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/Thomas_Guilbaud/Documents/Stage 2A - UCN - 2020/UCN-Simulations/code/src/conversion.cxx" > CMakeFiles/conversion.dir/src/conversion.cxx.i

CMakeFiles/conversion.dir/src/conversion.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conversion.dir/src/conversion.cxx.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/Thomas_Guilbaud/Documents/Stage 2A - UCN - 2020/UCN-Simulations/code/src/conversion.cxx" -o CMakeFiles/conversion.dir/src/conversion.cxx.s

# Object files for target conversion
conversion_OBJECTS = \
"CMakeFiles/conversion.dir/src/conversion.cxx.o"

# External object files for target conversion
conversion_EXTERNAL_OBJECTS =

bin/Release/conversion: CMakeFiles/conversion.dir/src/conversion.cxx.o
bin/Release/conversion: CMakeFiles/conversion.dir/build.make
bin/Release/conversion: CMakeFiles/conversion.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/Thomas_Guilbaud/Documents/Stage 2A - UCN - 2020/UCN-Simulations/code/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/Release/conversion"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/conversion.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/conversion.dir/build: bin/Release/conversion

.PHONY : CMakeFiles/conversion.dir/build

CMakeFiles/conversion.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/conversion.dir/cmake_clean.cmake
.PHONY : CMakeFiles/conversion.dir/clean

CMakeFiles/conversion.dir/depend:
	cd "/Users/Thomas_Guilbaud/Documents/Stage 2A - UCN - 2020/UCN-Simulations/code" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/Thomas_Guilbaud/Documents/Stage 2A - UCN - 2020/UCN-Simulations/code" "/Users/Thomas_Guilbaud/Documents/Stage 2A - UCN - 2020/UCN-Simulations/code" "/Users/Thomas_Guilbaud/Documents/Stage 2A - UCN - 2020/UCN-Simulations/code" "/Users/Thomas_Guilbaud/Documents/Stage 2A - UCN - 2020/UCN-Simulations/code" "/Users/Thomas_Guilbaud/Documents/Stage 2A - UCN - 2020/UCN-Simulations/code/CMakeFiles/conversion.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/conversion.dir/depend


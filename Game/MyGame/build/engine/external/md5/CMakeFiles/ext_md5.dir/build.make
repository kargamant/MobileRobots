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
CMAKE_SOURCE_DIR = /home/kargamant/Game/MyGame

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kargamant/Game/MyGame/build

# Include any dependencies generated for this target.
include engine/external/md5/CMakeFiles/ext_md5.dir/depend.make

# Include the progress variables for this target.
include engine/external/md5/CMakeFiles/ext_md5.dir/progress.make

# Include the compile flags for this target's objects.
include engine/external/md5/CMakeFiles/ext_md5.dir/flags.make

engine/external/md5/CMakeFiles/ext_md5.dir/md5.c.o: engine/external/md5/CMakeFiles/ext_md5.dir/flags.make
engine/external/md5/CMakeFiles/ext_md5.dir/md5.c.o: ../cocos2d/external/md5/md5.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kargamant/Game/MyGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object engine/external/md5/CMakeFiles/ext_md5.dir/md5.c.o"
	cd /home/kargamant/Game/MyGame/build/engine/external/md5 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ext_md5.dir/md5.c.o   -c /home/kargamant/Game/MyGame/cocos2d/external/md5/md5.c

engine/external/md5/CMakeFiles/ext_md5.dir/md5.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ext_md5.dir/md5.c.i"
	cd /home/kargamant/Game/MyGame/build/engine/external/md5 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kargamant/Game/MyGame/cocos2d/external/md5/md5.c > CMakeFiles/ext_md5.dir/md5.c.i

engine/external/md5/CMakeFiles/ext_md5.dir/md5.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ext_md5.dir/md5.c.s"
	cd /home/kargamant/Game/MyGame/build/engine/external/md5 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kargamant/Game/MyGame/cocos2d/external/md5/md5.c -o CMakeFiles/ext_md5.dir/md5.c.s

# Object files for target ext_md5
ext_md5_OBJECTS = \
"CMakeFiles/ext_md5.dir/md5.c.o"

# External object files for target ext_md5
ext_md5_EXTERNAL_OBJECTS =

lib/libext_md5.a: engine/external/md5/CMakeFiles/ext_md5.dir/md5.c.o
lib/libext_md5.a: engine/external/md5/CMakeFiles/ext_md5.dir/build.make
lib/libext_md5.a: engine/external/md5/CMakeFiles/ext_md5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kargamant/Game/MyGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library ../../../lib/libext_md5.a"
	cd /home/kargamant/Game/MyGame/build/engine/external/md5 && $(CMAKE_COMMAND) -P CMakeFiles/ext_md5.dir/cmake_clean_target.cmake
	cd /home/kargamant/Game/MyGame/build/engine/external/md5 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ext_md5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
engine/external/md5/CMakeFiles/ext_md5.dir/build: lib/libext_md5.a

.PHONY : engine/external/md5/CMakeFiles/ext_md5.dir/build

engine/external/md5/CMakeFiles/ext_md5.dir/clean:
	cd /home/kargamant/Game/MyGame/build/engine/external/md5 && $(CMAKE_COMMAND) -P CMakeFiles/ext_md5.dir/cmake_clean.cmake
.PHONY : engine/external/md5/CMakeFiles/ext_md5.dir/clean

engine/external/md5/CMakeFiles/ext_md5.dir/depend:
	cd /home/kargamant/Game/MyGame/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kargamant/Game/MyGame /home/kargamant/Game/MyGame/cocos2d/external/md5 /home/kargamant/Game/MyGame/build /home/kargamant/Game/MyGame/build/engine/external/md5 /home/kargamant/Game/MyGame/build/engine/external/md5/CMakeFiles/ext_md5.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : engine/external/md5/CMakeFiles/ext_md5.dir/depend


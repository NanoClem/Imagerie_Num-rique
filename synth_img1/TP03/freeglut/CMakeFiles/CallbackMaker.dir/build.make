# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.7

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\Users\Anthony\Downloads\cmake-3.7.2-win64-x64\cmake-3.7.2-win64-x64\bin\cmake.exe

# The command to remove a file.
RM = D:\Users\Anthony\Downloads\cmake-3.7.2-win64-x64\cmake-3.7.2-win64-x64\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Users\Anthony\Downloads\freeglut-3.0.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Users\Anthony\Downloads\freeglut

# Include any dependencies generated for this target.
include CMakeFiles/CallbackMaker.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CallbackMaker.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CallbackMaker.dir/flags.make

CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.obj: CMakeFiles/CallbackMaker.dir/flags.make
CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.obj: CMakeFiles/CallbackMaker.dir/includes_C.rsp
CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.obj: D:/Users/Anthony/Downloads/freeglut-3.0.0/progs/demos/CallbackMaker/CallbackMaker.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Users\Anthony\Downloads\freeglut\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.obj"
	D:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\CallbackMaker.dir\progs\demos\CallbackMaker\CallbackMaker.c.obj   -c D:\Users\Anthony\Downloads\freeglut-3.0.0\progs\demos\CallbackMaker\CallbackMaker.c

CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.i"
	D:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Users\Anthony\Downloads\freeglut-3.0.0\progs\demos\CallbackMaker\CallbackMaker.c > CMakeFiles\CallbackMaker.dir\progs\demos\CallbackMaker\CallbackMaker.c.i

CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.s"
	D:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Users\Anthony\Downloads\freeglut-3.0.0\progs\demos\CallbackMaker\CallbackMaker.c -o CMakeFiles\CallbackMaker.dir\progs\demos\CallbackMaker\CallbackMaker.c.s

CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.obj.requires:

.PHONY : CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.obj.requires

CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.obj.provides: CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.obj.requires
	$(MAKE) -f CMakeFiles\CallbackMaker.dir\build.make CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.obj.provides.build
.PHONY : CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.obj.provides

CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.obj.provides.build: CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.obj


# Object files for target CallbackMaker
CallbackMaker_OBJECTS = \
"CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.obj"

# External object files for target CallbackMaker
CallbackMaker_EXTERNAL_OBJECTS =

bin/CallbackMaker.exe: CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.obj
bin/CallbackMaker.exe: CMakeFiles/CallbackMaker.dir/build.make
bin/CallbackMaker.exe: lib/libfreeglut.dll.a
bin/CallbackMaker.exe: CMakeFiles/CallbackMaker.dir/linklibs.rsp
bin/CallbackMaker.exe: CMakeFiles/CallbackMaker.dir/objects1.rsp
bin/CallbackMaker.exe: CMakeFiles/CallbackMaker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Users\Anthony\Downloads\freeglut\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin\CallbackMaker.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\CallbackMaker.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CallbackMaker.dir/build: bin/CallbackMaker.exe

.PHONY : CMakeFiles/CallbackMaker.dir/build

CMakeFiles/CallbackMaker.dir/requires: CMakeFiles/CallbackMaker.dir/progs/demos/CallbackMaker/CallbackMaker.c.obj.requires

.PHONY : CMakeFiles/CallbackMaker.dir/requires

CMakeFiles/CallbackMaker.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\CallbackMaker.dir\cmake_clean.cmake
.PHONY : CMakeFiles/CallbackMaker.dir/clean

CMakeFiles/CallbackMaker.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Users\Anthony\Downloads\freeglut-3.0.0 D:\Users\Anthony\Downloads\freeglut-3.0.0 D:\Users\Anthony\Downloads\freeglut D:\Users\Anthony\Downloads\freeglut D:\Users\Anthony\Downloads\freeglut\CMakeFiles\CallbackMaker.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CallbackMaker.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /nix/store/5sygy4bz205fn9hwwlvasi510c2k3l5b-cmake-3.22.3/bin/cmake

# The command to remove a file.
RM = /nix/store/5sygy4bz205fn9hwwlvasi510c2k3l5b-cmake-3.22.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku

# Include any dependencies generated for this target.
include CMakeFiles/OcrExe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/OcrExe.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/OcrExe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OcrExe.dir/flags.make

CMakeFiles/OcrExe.dir/src/functions/test.c.o: CMakeFiles/OcrExe.dir/flags.make
CMakeFiles/OcrExe.dir/src/functions/test.c.o: src/functions/test.c
CMakeFiles/OcrExe.dir/src/functions/test.c.o: CMakeFiles/OcrExe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/OcrExe.dir/src/functions/test.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/OcrExe.dir/src/functions/test.c.o -MF CMakeFiles/OcrExe.dir/src/functions/test.c.o.d -o CMakeFiles/OcrExe.dir/src/functions/test.c.o -c /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/src/functions/test.c

CMakeFiles/OcrExe.dir/src/functions/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OcrExe.dir/src/functions/test.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/src/functions/test.c > CMakeFiles/OcrExe.dir/src/functions/test.c.i

CMakeFiles/OcrExe.dir/src/functions/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OcrExe.dir/src/functions/test.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/src/functions/test.c -o CMakeFiles/OcrExe.dir/src/functions/test.c.s

CMakeFiles/OcrExe.dir/src/main.c.o: CMakeFiles/OcrExe.dir/flags.make
CMakeFiles/OcrExe.dir/src/main.c.o: src/main.c
CMakeFiles/OcrExe.dir/src/main.c.o: CMakeFiles/OcrExe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/OcrExe.dir/src/main.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/OcrExe.dir/src/main.c.o -MF CMakeFiles/OcrExe.dir/src/main.c.o.d -o CMakeFiles/OcrExe.dir/src/main.c.o -c /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/src/main.c

CMakeFiles/OcrExe.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OcrExe.dir/src/main.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/src/main.c > CMakeFiles/OcrExe.dir/src/main.c.i

CMakeFiles/OcrExe.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OcrExe.dir/src/main.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/src/main.c -o CMakeFiles/OcrExe.dir/src/main.c.s

CMakeFiles/OcrExe.dir/src/solver/read_file.c.o: CMakeFiles/OcrExe.dir/flags.make
CMakeFiles/OcrExe.dir/src/solver/read_file.c.o: src/solver/read_file.c
CMakeFiles/OcrExe.dir/src/solver/read_file.c.o: CMakeFiles/OcrExe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/OcrExe.dir/src/solver/read_file.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/OcrExe.dir/src/solver/read_file.c.o -MF CMakeFiles/OcrExe.dir/src/solver/read_file.c.o.d -o CMakeFiles/OcrExe.dir/src/solver/read_file.c.o -c /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/src/solver/read_file.c

CMakeFiles/OcrExe.dir/src/solver/read_file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OcrExe.dir/src/solver/read_file.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/src/solver/read_file.c > CMakeFiles/OcrExe.dir/src/solver/read_file.c.i

CMakeFiles/OcrExe.dir/src/solver/read_file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OcrExe.dir/src/solver/read_file.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/src/solver/read_file.c -o CMakeFiles/OcrExe.dir/src/solver/read_file.c.s

CMakeFiles/OcrExe.dir/src/solver/solver.c.o: CMakeFiles/OcrExe.dir/flags.make
CMakeFiles/OcrExe.dir/src/solver/solver.c.o: src/solver/solver.c
CMakeFiles/OcrExe.dir/src/solver/solver.c.o: CMakeFiles/OcrExe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/OcrExe.dir/src/solver/solver.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/OcrExe.dir/src/solver/solver.c.o -MF CMakeFiles/OcrExe.dir/src/solver/solver.c.o.d -o CMakeFiles/OcrExe.dir/src/solver/solver.c.o -c /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/src/solver/solver.c

CMakeFiles/OcrExe.dir/src/solver/solver.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OcrExe.dir/src/solver/solver.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/src/solver/solver.c > CMakeFiles/OcrExe.dir/src/solver/solver.c.i

CMakeFiles/OcrExe.dir/src/solver/solver.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OcrExe.dir/src/solver/solver.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/src/solver/solver.c -o CMakeFiles/OcrExe.dir/src/solver/solver.c.s

CMakeFiles/OcrExe.dir/src/solver/sudoku.c.o: CMakeFiles/OcrExe.dir/flags.make
CMakeFiles/OcrExe.dir/src/solver/sudoku.c.o: src/solver/sudoku.c
CMakeFiles/OcrExe.dir/src/solver/sudoku.c.o: CMakeFiles/OcrExe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/OcrExe.dir/src/solver/sudoku.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/OcrExe.dir/src/solver/sudoku.c.o -MF CMakeFiles/OcrExe.dir/src/solver/sudoku.c.o.d -o CMakeFiles/OcrExe.dir/src/solver/sudoku.c.o -c /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/src/solver/sudoku.c

CMakeFiles/OcrExe.dir/src/solver/sudoku.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OcrExe.dir/src/solver/sudoku.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/src/solver/sudoku.c > CMakeFiles/OcrExe.dir/src/solver/sudoku.c.i

CMakeFiles/OcrExe.dir/src/solver/sudoku.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OcrExe.dir/src/solver/sudoku.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/src/solver/sudoku.c -o CMakeFiles/OcrExe.dir/src/solver/sudoku.c.s

# Object files for target OcrExe
OcrExe_OBJECTS = \
"CMakeFiles/OcrExe.dir/src/functions/test.c.o" \
"CMakeFiles/OcrExe.dir/src/main.c.o" \
"CMakeFiles/OcrExe.dir/src/solver/read_file.c.o" \
"CMakeFiles/OcrExe.dir/src/solver/solver.c.o" \
"CMakeFiles/OcrExe.dir/src/solver/sudoku.c.o"

# External object files for target OcrExe
OcrExe_EXTERNAL_OBJECTS =

OcrExe: CMakeFiles/OcrExe.dir/src/functions/test.c.o
OcrExe: CMakeFiles/OcrExe.dir/src/main.c.o
OcrExe: CMakeFiles/OcrExe.dir/src/solver/read_file.c.o
OcrExe: CMakeFiles/OcrExe.dir/src/solver/solver.c.o
OcrExe: CMakeFiles/OcrExe.dir/src/solver/sudoku.c.o
OcrExe: CMakeFiles/OcrExe.dir/build.make
OcrExe: CMakeFiles/OcrExe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable OcrExe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OcrExe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OcrExe.dir/build: OcrExe
.PHONY : CMakeFiles/OcrExe.dir/build

CMakeFiles/OcrExe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OcrExe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OcrExe.dir/clean

CMakeFiles/OcrExe.dir/depend:
	cd /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku /home/tom.brossard/afs/SPE/Projects/OCR-Sudoku/CMakeFiles/OcrExe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OcrExe.dir/depend


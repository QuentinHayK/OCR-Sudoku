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
CMAKE_SOURCE_DIR = /home/tom.brossard/afs/SPE/OCR-Sudoku

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tom.brossard/afs/SPE/OCR-Sudoku

# Include any dependencies generated for this target.
include CMakeFiles/Ocr.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Ocr.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Ocr.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Ocr.dir/flags.make

CMakeFiles/Ocr.dir/src/functions/test.c.o: CMakeFiles/Ocr.dir/flags.make
CMakeFiles/Ocr.dir/src/functions/test.c.o: src/functions/test.c
CMakeFiles/Ocr.dir/src/functions/test.c.o: CMakeFiles/Ocr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tom.brossard/afs/SPE/OCR-Sudoku/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Ocr.dir/src/functions/test.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Ocr.dir/src/functions/test.c.o -MF CMakeFiles/Ocr.dir/src/functions/test.c.o.d -o CMakeFiles/Ocr.dir/src/functions/test.c.o -c /home/tom.brossard/afs/SPE/OCR-Sudoku/src/functions/test.c

CMakeFiles/Ocr.dir/src/functions/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Ocr.dir/src/functions/test.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom.brossard/afs/SPE/OCR-Sudoku/src/functions/test.c > CMakeFiles/Ocr.dir/src/functions/test.c.i

CMakeFiles/Ocr.dir/src/functions/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Ocr.dir/src/functions/test.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom.brossard/afs/SPE/OCR-Sudoku/src/functions/test.c -o CMakeFiles/Ocr.dir/src/functions/test.c.s

CMakeFiles/Ocr.dir/src/gui.c.o: CMakeFiles/Ocr.dir/flags.make
CMakeFiles/Ocr.dir/src/gui.c.o: src/gui.c
CMakeFiles/Ocr.dir/src/gui.c.o: CMakeFiles/Ocr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tom.brossard/afs/SPE/OCR-Sudoku/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Ocr.dir/src/gui.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Ocr.dir/src/gui.c.o -MF CMakeFiles/Ocr.dir/src/gui.c.o.d -o CMakeFiles/Ocr.dir/src/gui.c.o -c /home/tom.brossard/afs/SPE/OCR-Sudoku/src/gui.c

CMakeFiles/Ocr.dir/src/gui.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Ocr.dir/src/gui.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom.brossard/afs/SPE/OCR-Sudoku/src/gui.c > CMakeFiles/Ocr.dir/src/gui.c.i

CMakeFiles/Ocr.dir/src/gui.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Ocr.dir/src/gui.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom.brossard/afs/SPE/OCR-Sudoku/src/gui.c -o CMakeFiles/Ocr.dir/src/gui.c.s

CMakeFiles/Ocr.dir/src/main.c.o: CMakeFiles/Ocr.dir/flags.make
CMakeFiles/Ocr.dir/src/main.c.o: src/main.c
CMakeFiles/Ocr.dir/src/main.c.o: CMakeFiles/Ocr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tom.brossard/afs/SPE/OCR-Sudoku/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Ocr.dir/src/main.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Ocr.dir/src/main.c.o -MF CMakeFiles/Ocr.dir/src/main.c.o.d -o CMakeFiles/Ocr.dir/src/main.c.o -c /home/tom.brossard/afs/SPE/OCR-Sudoku/src/main.c

CMakeFiles/Ocr.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Ocr.dir/src/main.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom.brossard/afs/SPE/OCR-Sudoku/src/main.c > CMakeFiles/Ocr.dir/src/main.c.i

CMakeFiles/Ocr.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Ocr.dir/src/main.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom.brossard/afs/SPE/OCR-Sudoku/src/main.c -o CMakeFiles/Ocr.dir/src/main.c.s

CMakeFiles/Ocr.dir/src/neural_network/functions.c.o: CMakeFiles/Ocr.dir/flags.make
CMakeFiles/Ocr.dir/src/neural_network/functions.c.o: src/neural_network/functions.c
CMakeFiles/Ocr.dir/src/neural_network/functions.c.o: CMakeFiles/Ocr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tom.brossard/afs/SPE/OCR-Sudoku/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Ocr.dir/src/neural_network/functions.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Ocr.dir/src/neural_network/functions.c.o -MF CMakeFiles/Ocr.dir/src/neural_network/functions.c.o.d -o CMakeFiles/Ocr.dir/src/neural_network/functions.c.o -c /home/tom.brossard/afs/SPE/OCR-Sudoku/src/neural_network/functions.c

CMakeFiles/Ocr.dir/src/neural_network/functions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Ocr.dir/src/neural_network/functions.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom.brossard/afs/SPE/OCR-Sudoku/src/neural_network/functions.c > CMakeFiles/Ocr.dir/src/neural_network/functions.c.i

CMakeFiles/Ocr.dir/src/neural_network/functions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Ocr.dir/src/neural_network/functions.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom.brossard/afs/SPE/OCR-Sudoku/src/neural_network/functions.c -o CMakeFiles/Ocr.dir/src/neural_network/functions.c.s

CMakeFiles/Ocr.dir/src/neural_network/matrix.c.o: CMakeFiles/Ocr.dir/flags.make
CMakeFiles/Ocr.dir/src/neural_network/matrix.c.o: src/neural_network/matrix.c
CMakeFiles/Ocr.dir/src/neural_network/matrix.c.o: CMakeFiles/Ocr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tom.brossard/afs/SPE/OCR-Sudoku/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Ocr.dir/src/neural_network/matrix.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Ocr.dir/src/neural_network/matrix.c.o -MF CMakeFiles/Ocr.dir/src/neural_network/matrix.c.o.d -o CMakeFiles/Ocr.dir/src/neural_network/matrix.c.o -c /home/tom.brossard/afs/SPE/OCR-Sudoku/src/neural_network/matrix.c

CMakeFiles/Ocr.dir/src/neural_network/matrix.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Ocr.dir/src/neural_network/matrix.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom.brossard/afs/SPE/OCR-Sudoku/src/neural_network/matrix.c > CMakeFiles/Ocr.dir/src/neural_network/matrix.c.i

CMakeFiles/Ocr.dir/src/neural_network/matrix.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Ocr.dir/src/neural_network/matrix.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom.brossard/afs/SPE/OCR-Sudoku/src/neural_network/matrix.c -o CMakeFiles/Ocr.dir/src/neural_network/matrix.c.s

CMakeFiles/Ocr.dir/src/neural_network/neural_network.c.o: CMakeFiles/Ocr.dir/flags.make
CMakeFiles/Ocr.dir/src/neural_network/neural_network.c.o: src/neural_network/neural_network.c
CMakeFiles/Ocr.dir/src/neural_network/neural_network.c.o: CMakeFiles/Ocr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tom.brossard/afs/SPE/OCR-Sudoku/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/Ocr.dir/src/neural_network/neural_network.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Ocr.dir/src/neural_network/neural_network.c.o -MF CMakeFiles/Ocr.dir/src/neural_network/neural_network.c.o.d -o CMakeFiles/Ocr.dir/src/neural_network/neural_network.c.o -c /home/tom.brossard/afs/SPE/OCR-Sudoku/src/neural_network/neural_network.c

CMakeFiles/Ocr.dir/src/neural_network/neural_network.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Ocr.dir/src/neural_network/neural_network.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom.brossard/afs/SPE/OCR-Sudoku/src/neural_network/neural_network.c > CMakeFiles/Ocr.dir/src/neural_network/neural_network.c.i

CMakeFiles/Ocr.dir/src/neural_network/neural_network.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Ocr.dir/src/neural_network/neural_network.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom.brossard/afs/SPE/OCR-Sudoku/src/neural_network/neural_network.c -o CMakeFiles/Ocr.dir/src/neural_network/neural_network.c.s

CMakeFiles/Ocr.dir/src/neural_network/user_inputs_functions.c.o: CMakeFiles/Ocr.dir/flags.make
CMakeFiles/Ocr.dir/src/neural_network/user_inputs_functions.c.o: src/neural_network/user_inputs_functions.c
CMakeFiles/Ocr.dir/src/neural_network/user_inputs_functions.c.o: CMakeFiles/Ocr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tom.brossard/afs/SPE/OCR-Sudoku/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/Ocr.dir/src/neural_network/user_inputs_functions.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Ocr.dir/src/neural_network/user_inputs_functions.c.o -MF CMakeFiles/Ocr.dir/src/neural_network/user_inputs_functions.c.o.d -o CMakeFiles/Ocr.dir/src/neural_network/user_inputs_functions.c.o -c /home/tom.brossard/afs/SPE/OCR-Sudoku/src/neural_network/user_inputs_functions.c

CMakeFiles/Ocr.dir/src/neural_network/user_inputs_functions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Ocr.dir/src/neural_network/user_inputs_functions.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom.brossard/afs/SPE/OCR-Sudoku/src/neural_network/user_inputs_functions.c > CMakeFiles/Ocr.dir/src/neural_network/user_inputs_functions.c.i

CMakeFiles/Ocr.dir/src/neural_network/user_inputs_functions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Ocr.dir/src/neural_network/user_inputs_functions.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom.brossard/afs/SPE/OCR-Sudoku/src/neural_network/user_inputs_functions.c -o CMakeFiles/Ocr.dir/src/neural_network/user_inputs_functions.c.s

CMakeFiles/Ocr.dir/src/solver/read_file.c.o: CMakeFiles/Ocr.dir/flags.make
CMakeFiles/Ocr.dir/src/solver/read_file.c.o: src/solver/read_file.c
CMakeFiles/Ocr.dir/src/solver/read_file.c.o: CMakeFiles/Ocr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tom.brossard/afs/SPE/OCR-Sudoku/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/Ocr.dir/src/solver/read_file.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Ocr.dir/src/solver/read_file.c.o -MF CMakeFiles/Ocr.dir/src/solver/read_file.c.o.d -o CMakeFiles/Ocr.dir/src/solver/read_file.c.o -c /home/tom.brossard/afs/SPE/OCR-Sudoku/src/solver/read_file.c

CMakeFiles/Ocr.dir/src/solver/read_file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Ocr.dir/src/solver/read_file.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom.brossard/afs/SPE/OCR-Sudoku/src/solver/read_file.c > CMakeFiles/Ocr.dir/src/solver/read_file.c.i

CMakeFiles/Ocr.dir/src/solver/read_file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Ocr.dir/src/solver/read_file.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom.brossard/afs/SPE/OCR-Sudoku/src/solver/read_file.c -o CMakeFiles/Ocr.dir/src/solver/read_file.c.s

CMakeFiles/Ocr.dir/src/solver/solver.c.o: CMakeFiles/Ocr.dir/flags.make
CMakeFiles/Ocr.dir/src/solver/solver.c.o: src/solver/solver.c
CMakeFiles/Ocr.dir/src/solver/solver.c.o: CMakeFiles/Ocr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tom.brossard/afs/SPE/OCR-Sudoku/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/Ocr.dir/src/solver/solver.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Ocr.dir/src/solver/solver.c.o -MF CMakeFiles/Ocr.dir/src/solver/solver.c.o.d -o CMakeFiles/Ocr.dir/src/solver/solver.c.o -c /home/tom.brossard/afs/SPE/OCR-Sudoku/src/solver/solver.c

CMakeFiles/Ocr.dir/src/solver/solver.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Ocr.dir/src/solver/solver.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom.brossard/afs/SPE/OCR-Sudoku/src/solver/solver.c > CMakeFiles/Ocr.dir/src/solver/solver.c.i

CMakeFiles/Ocr.dir/src/solver/solver.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Ocr.dir/src/solver/solver.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom.brossard/afs/SPE/OCR-Sudoku/src/solver/solver.c -o CMakeFiles/Ocr.dir/src/solver/solver.c.s

CMakeFiles/Ocr.dir/src/solver/sudoku.c.o: CMakeFiles/Ocr.dir/flags.make
CMakeFiles/Ocr.dir/src/solver/sudoku.c.o: src/solver/sudoku.c
CMakeFiles/Ocr.dir/src/solver/sudoku.c.o: CMakeFiles/Ocr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tom.brossard/afs/SPE/OCR-Sudoku/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/Ocr.dir/src/solver/sudoku.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Ocr.dir/src/solver/sudoku.c.o -MF CMakeFiles/Ocr.dir/src/solver/sudoku.c.o.d -o CMakeFiles/Ocr.dir/src/solver/sudoku.c.o -c /home/tom.brossard/afs/SPE/OCR-Sudoku/src/solver/sudoku.c

CMakeFiles/Ocr.dir/src/solver/sudoku.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Ocr.dir/src/solver/sudoku.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom.brossard/afs/SPE/OCR-Sudoku/src/solver/sudoku.c > CMakeFiles/Ocr.dir/src/solver/sudoku.c.i

CMakeFiles/Ocr.dir/src/solver/sudoku.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Ocr.dir/src/solver/sudoku.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom.brossard/afs/SPE/OCR-Sudoku/src/solver/sudoku.c -o CMakeFiles/Ocr.dir/src/solver/sudoku.c.s

# Object files for target Ocr
Ocr_OBJECTS = \
"CMakeFiles/Ocr.dir/src/functions/test.c.o" \
"CMakeFiles/Ocr.dir/src/gui.c.o" \
"CMakeFiles/Ocr.dir/src/main.c.o" \
"CMakeFiles/Ocr.dir/src/neural_network/functions.c.o" \
"CMakeFiles/Ocr.dir/src/neural_network/matrix.c.o" \
"CMakeFiles/Ocr.dir/src/neural_network/neural_network.c.o" \
"CMakeFiles/Ocr.dir/src/neural_network/user_inputs_functions.c.o" \
"CMakeFiles/Ocr.dir/src/solver/read_file.c.o" \
"CMakeFiles/Ocr.dir/src/solver/solver.c.o" \
"CMakeFiles/Ocr.dir/src/solver/sudoku.c.o"

# External object files for target Ocr
Ocr_EXTERNAL_OBJECTS =

Ocr: CMakeFiles/Ocr.dir/src/functions/test.c.o
Ocr: CMakeFiles/Ocr.dir/src/gui.c.o
Ocr: CMakeFiles/Ocr.dir/src/main.c.o
Ocr: CMakeFiles/Ocr.dir/src/neural_network/functions.c.o
Ocr: CMakeFiles/Ocr.dir/src/neural_network/matrix.c.o
Ocr: CMakeFiles/Ocr.dir/src/neural_network/neural_network.c.o
Ocr: CMakeFiles/Ocr.dir/src/neural_network/user_inputs_functions.c.o
Ocr: CMakeFiles/Ocr.dir/src/solver/read_file.c.o
Ocr: CMakeFiles/Ocr.dir/src/solver/solver.c.o
Ocr: CMakeFiles/Ocr.dir/src/solver/sudoku.c.o
Ocr: CMakeFiles/Ocr.dir/build.make
Ocr: CMakeFiles/Ocr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tom.brossard/afs/SPE/OCR-Sudoku/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking C executable Ocr"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Ocr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Ocr.dir/build: Ocr
.PHONY : CMakeFiles/Ocr.dir/build

CMakeFiles/Ocr.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Ocr.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Ocr.dir/clean

CMakeFiles/Ocr.dir/depend:
	cd /home/tom.brossard/afs/SPE/OCR-Sudoku && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tom.brossard/afs/SPE/OCR-Sudoku /home/tom.brossard/afs/SPE/OCR-Sudoku /home/tom.brossard/afs/SPE/OCR-Sudoku /home/tom.brossard/afs/SPE/OCR-Sudoku /home/tom.brossard/afs/SPE/OCR-Sudoku/CMakeFiles/Ocr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Ocr.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.22
cmake_policy(SET CMP0009 NEW)

# Ocr_SOURCES at CMakeLists.txt:6 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/tom/Desktop/OCR-Sudoku/neural_network/*.c")
set(OLD_GLOB
  "/home/tom/Desktop/OCR-Sudoku/neural_network/CMakeFiles/3.22.1/CompilerIdC/CMakeCCompilerId.c"
  "/home/tom/Desktop/OCR-Sudoku/neural_network/functions.c"
  "/home/tom/Desktop/OCR-Sudoku/neural_network/matrix.c"
  "/home/tom/Desktop/OCR-Sudoku/neural_network/neural_network.c"
  "/home/tom/Desktop/OCR-Sudoku/neural_network/user_inputs_functions.c"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/tom/Desktop/OCR-Sudoku/neural_network/CMakeFiles/cmake.verify_globs")
endif()

# Ocr_HEADERS at CMakeLists.txt:5 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/tom/Desktop/OCR-Sudoku/neural_network/*.h")
set(OLD_GLOB
  "/home/tom/Desktop/OCR-Sudoku/neural_network/data.h"
  "/home/tom/Desktop/OCR-Sudoku/neural_network/functions.h"
  "/home/tom/Desktop/OCR-Sudoku/neural_network/matrix.h"
  "/home/tom/Desktop/OCR-Sudoku/neural_network/user_inputs_functions.h"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/tom/Desktop/OCR-Sudoku/neural_network/CMakeFiles/cmake.verify_globs")
endif()
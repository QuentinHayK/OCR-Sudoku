cmake_minimum_required(VERSION "3.22")

project("Ocr")

file (GLOB_RECURSE Ocr_SOURCES CONFIGURE_DEPENDS "src/*.c")
file (GLOB_RECURSE Ocr_HEADERS CONFIGURE_DEPENDS "src/*.h")

set (Ocr_INCLUDE_DIRS "")

foreach (_headerFile ${_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND Ocr_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES Ocr_INCLUDE_DIRS)

add_executable(OcrExe ${Ocr_SOURCES})
target_include_directories(OcrExe PRIVATE ${Ocr_INCLUDE_DIRS})


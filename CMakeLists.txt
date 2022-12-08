cmake_minimum_required(VERSION "3.22")

project(Ocr)

file (GLOB_RECURSE Ocr_SOURCES CONFIGURE_DEPENDS "src/*.c")
file (GLOB_RECURSE Ocr_HEADERS CONFIGURE_DEPENDS "src/*.h")

set (Ocr_INCLUDE_DIRS "")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic -rdynamic")

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

PKG_SEARCH_MODULE(GTK3 REQUIRED gtk+-3.0)
# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
# Add other flags to the compiler
add_definitions(${GTK3_CFLAGS_OTHER})

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})


foreach (_headerFile ${_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND Ocr_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES Ocr_INCLUDE_DIRS)

add_executable(Ocr ${Ocr_SOURCES})

target_include_directories(Ocr PRIVATE ${Ocr_INCLUDE_DIRS})
target_link_libraries(Ocr m)
target_link_libraries(Ocr ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

# Link the target to the GTK+ libraries
target_link_libraries(Ocr ${GTK3_LIBRARIES})

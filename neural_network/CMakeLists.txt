cmake_minimum_required(VERSION 3.7)
project(Ocr)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic")

#find_package(SDL2 REQUIRED)
#find_package(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

set(SOURCE_FILES neural_network.c functions.c matrix.c user_inputs_functions.c)
add_executable(Ocr ${SOURCE_FILES})

target_link_libraries(Ocr m)
target_link_libraries(Ocr ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

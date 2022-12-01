cmake_minimum_required(VERSION "3.22")

project("HelloWorld")

add_executable("${PROJECT_NAME}" "src/main.c")

install(TARGETS "${PROJECT_NAME}" DESTINATION bin)  #$(CMAKE_INSTALL_PREFIX)/bin
install(FILES "main.c" DESTINATION src) 			#$(CMAKE_INSTALL_PREFIX)/src


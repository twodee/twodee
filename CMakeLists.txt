cmake_minimum_required(VERSION 2.8)

# This header holds some macros that are set by CMake options.
configure_file(${CMAKE_SOURCE_DIR}/include/twodee/Configuration.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/include/twodee/Configuration.h)

# Raw headers live in the project source directory, but derived ones live in
# the build's include directory.
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)

add_subdirectory(src)
add_subdirectory(test)

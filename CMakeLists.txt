cmake_minimum_required(VERSION 2.8)
project(twodee)

option(WANTS_OPENGL "Enable OpenGL" ON)

if(WANTS_OPENGL)
  # On my Macintosh, CGAL wants to interpose its FindOpenGL, which fails
  # because it doesn't include its own macros file. Let's route around
  # it entirely.
  set(ORIGINAL_MODULE_PATH ${CMAKE_MODULE_PATH})
  set(CMAKE_MODULE_PATH "")
  find_package(OpenGL REQUIRED)
  set(CMAKE_MODULE_PATH ${ORIGINAL_MODULE_PATH})
endif()

# This header holds some macros that are set by CMake options.
configure_file(${PROJECT_SOURCE_DIR}/include/twodee/Configuration.h.in ${CMAKE_BINARY_DIR}/include/twodee/Configuration.h)

# if(OPENGL_FOUND)
  # include_directories({OPENGL_INCLUDE_DIR})
# endif()

# Raw headers live in the project source directory, but derived ones live in
# the build's include directory.
include_directories(${PROJECT_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include ${OPENGL_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(test)

cmake_minimum_required(VERSION 2.8)
project(twodee)

option(WANTS_OPENGL "Enable OpenGL" ON)

if (NOT DEFINED ${CMAKE_CXX_FLAGS})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

if (WANTS_OPENGL)
  # On my Macintosh, CGAL wants to interpose its FindOpenGL, which fails
  # because it doesn't include its own macros file. Let's route around
  # it entirely.
  set(ORIGINAL_MODULE_PATH ${CMAKE_MODULE_PATH})
  set(CMAKE_MODULE_PATH "")
  find_package(OpenGL REQUIRED)
  set(CMAKE_MODULE_PATH ${ORIGINAL_MODULE_PATH})
endif()

# This header holds some macros that are set by CMake options.
option(USE_VAO "Use vertex arrays" ON)
configure_file(${PROJECT_SOURCE_DIR}/include/twodee/Configuration.h.in ${CMAKE_BINARY_DIR}/include/twodee/Configuration.h)

# Raw headers live in the project source directory, but derived ones live in
# the build's include directory.
include_directories(${PROJECT_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include ${OPENGL_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(test)

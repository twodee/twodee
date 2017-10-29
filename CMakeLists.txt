cmake_minimum_required(VERSION 2.8)
project(twodee)

option(WANTS_OPENGL "Enable OpenGL" ON)

if (NOT DEFINED ${CMAKE_CXX_FLAGS})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(TWODEE_LIBRARIES twodee CACHE INTERNAL "FOO")
set(TWODEE_INCLUDE_DIRECTORIES CACHE INTERNAL "FOO")
set(TWODEE_DEFINITIONS CACHE INTERNAL "FOO")

if (WANTS_OPENGL)
  # On my Macintosh, CGAL wants to interpose its FindOpenGL, which fails
  # because it doesn't include its own macros file. Let's route around
  # it entirely.
  set(ORIGINAL_MODULE_PATH ${CMAKE_MODULE_PATH})
  set(CMAKE_MODULE_PATH "")
  find_package(OpenGL REQUIRED)
  set(CMAKE_MODULE_PATH ${ORIGINAL_MODULE_PATH})
  include_directories(${OPENGL_INCLUDE_DIR})
endif()

# This header holds some macros that are set by CMake options.
option(USE_VAO "Use vertex arrays" ON)
option(USE_IMAGEMAGICK "Use ImageMagick" ON)
if (USE_IMAGEMAGICK)
  find_package(ImageMagick COMPONENTS Magick++ REQUIRED)

  set(IMAGEMAGICK_DEFINITIONS -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16)
  add_definitions(${IMAGEMAGICK_DEFINITIONS})
  list(APPEND ImageMagick_INCLUDE_DIRS /usr/include/x86_64-linux-gnu/ImageMagick-6 /usr/include/ImageMagick-6)
  include_directories(${ImageMagick_INCLUDE_DIRS})

  message(${ImageMagick_INCLUDE_DIRS})

  set(TWODEE_INCLUDE_DIRECTORIES ${TWODEE_INCLUDE_DIRECTORIES} ${ImageMagick_INCLUDE_DIRS} CACHE INTERNAL "FOO")
  set(TWODEE_DEFINITIONS ${TWODEE_DEFINITIONS} ${IMAGEMAGICK_DEFINITIONS} CACHE INTERNAL "FOO")
  set(TWODEE_LIBRARIES ${TWODEE_LIBRARIES} ${ImageMagick_LIBRARIES} CACHE INTERNAL "FOO")
endif()
configure_file(${PROJECT_SOURCE_DIR}/include/twodee/Configuration.h.in ${CMAKE_BINARY_DIR}/include/twodee/Configuration.h)

# Raw headers live in the project source directory, but derived ones live in
# the build's include directory.
include_directories(${PROJECT_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)

add_subdirectory(src)
add_subdirectory(test)

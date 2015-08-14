cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
INCLUDE (CheckIncludeFiles)

project("SViGGLe") 

CHECK_INCLUDE_FILES (GL/glew.h AUTO_GLEW_H)

if(NOT ${AUTO_GLEW_H})

  set(GLEW_INCLUDE "" CACHE PATH "Provide path to glew include:")

  if(NOT EXISTS ${GLEW_INCLUDE})
    message(SEND_ERROR "You need to set GLEW_INCLUDE variable to point at glew include path.")
    message(FATAL_ERROR "e.g. cmake -DGLEW_INCLUDE:STRING=path/to/glew/include") 
  endif(NOT EXISTS ${GLEW_INCLUDE})

  include_directories(${GLEW_INCLUDE})

endif(NOT ${AUTO_GLEW_H})

include_directories(src)

file(GLOB_RECURSE SVIGGLE_CC
    "src/*.cc"
)

add_library(SViGGLe ${SVIGGLE_CC})

set_property(TARGET SViGGLe PROPERTY CXX_STANDARD 11)

target_link_libraries(SViGGLe glew)

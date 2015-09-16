cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project("SViGGLe") 


INCLUDE (CheckIncludeFiles)
INCLUDE (FindFreetype)


CHECK_INCLUDE_FILES (GL/glew.h AUTO_GLEW_H)

if(NOT ${AUTO_GLEW_H})

  set(GLEW_INCLUDE "" CACHE PATH "Provide path to glew include:")

  if(NOT EXISTS ${GLEW_INCLUDE})
    message(SEND_ERROR "You need to set GLEW_INCLUDE variable to point at the glew include path or install glew to the default library path. GLEW is available at http://glew.sourceforge.net")
    message(FATAL_ERROR "e.g. cmake -DGLEW_INCLUDE:STRING=path/to/glew/include") 
  endif(NOT EXISTS ${GLEW_INCLUDE})

  include_directories(${GLEW_INCLUDE})

endif(NOT ${AUTO_GLEW_H})

CHECK_INCLUDE_FILES (png.h AUTO_PNG_H)

if(NOT ${AUTO_PNG_H})

  set(PNG_INCLUDE "" CACHE PATH "Provide path to png include:")

  if(NOT EXISTS ${PNG_INCLUDE})
    message(SEND_ERROR "You need to set PNG_INCLUDE variable to point at the libpng include path or install libpng to the default library path. libpng is available at http://www.libpng.org")
    message(FATAL_ERROR "e.g. cmake -DPNG_INCLUDE:STRING=path/to/png/include") 
  endif(NOT EXISTS ${PNG_INCLUDE})

  include_directories(${PNGW_INCLUDE})

endif(NOT ${AUTO_PNG_H})

include_directories(${FREETYPE_INCLUDE_DIR_ft2build})
CHECK_INCLUDE_FILES (${FREETYPE_INCLUDE_DIR_ft2build}/ft2build.h AUTO_FREETYPE_H)

if(NOT ${AUTO_FREETYPE_H})

  set(FREETYPE_INCLUDE "" CACHE PATH "Provide path to freetype include:")

  if(NOT EXISTS ${FREETYPE_INCLUDE})
    message(SEND_ERROR "You need to set FREETYPE_INCLUDE variable to point at freetype include path or install the freetype library to the default library path. freetype is available at http://www.freetype.org")
    message(FATAL_ERROR "e.g. cmake -DFREETYPE_INCLUDE:STRING=path/to/freetype/include") 
  endif(NOT EXISTS ${FREETYPE_INCLUDE})

  include_directories(${FREETYPE_INCLUDE})

endif(NOT ${AUTO_FREETYPE_H})

include_directories(src)

file(GLOB_RECURSE SVIGGLE_CC
    "src/*.cc"
)

add_library(SViGGLe ${SVIGGLE_CC})

set_property(TARGET SViGGLe PROPERTY CXX_STANDARD 14)

include_directories(test/src)

file(GLOB_RECURSE SVIGGLE_TEST_CC
	"test/src/*.cc"
)

add_executable(SViGGLe_test ${SVIGGLE_TEST_CC})

set_property(TARGET SViGGLe_test PROPERTY CXX_STANDARD 14)

target_link_libraries(SViGGLe_test GL)
target_link_libraries(SViGGLe_test GLU)
target_link_libraries(SViGGLe_test GLEW)
target_link_libraries(SViGGLe_test glfw)
target_link_libraries(SViGGLe_test png)
target_link_libraries(SViGGLe_test freetype)
target_link_libraries(SViGGLe_test SViGGLe)
target_link_libraries(SViGGLe_test dl)

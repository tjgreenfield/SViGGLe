# SViGGLe
SVG rendering in OpenGL

Copyright (c) 2015 Timothy Greenfield <tjgreenfield@gmail.com>

Brief: SViGGLe is a library designed to support rendering of SVG files within an OpenGL context.

I've recently found myself having some free time and I thought I'd apply my recently gained understanding of SVG to refresh my knowledge of OpenGL.
I hope to get this into a state where I could update to the new Vulkan API. 

Dependancies: The library requires opengl and depends on glew for function bindings. 

Setup & Building on linux (Debian/Ubuntu):

	1) (sudo/root) apt-get install build-essential git cmake libglew-dev
	2) git clone https://github.com/tjgreenfield/SViGGLe
	3) mkdir build
	4) cmake ..
	5) make
	
Set up & Building on Windows (MinGW):

	1) Download and install MinGW-w64:
	   http://mingw-w64.org/doku.php/download
	   
	2) Download and install cmake:
	   http://www.cmake.org/download/
	   
	3) Download and install a git client
	   https://git-scm.com/downloads
	
	4) Make sure the path environment variable points at the directories with the *.exe files for the above programs.

	5) Clone the glew repository
	   https://github.com/nigels-com/glew
	   
	5) Clone the repository https://github.com/tjgreenfield/SViGGLe
	
	6) Make a build directory under the location of the cloned repository.
	
	7) Open a command prompt and navigate to the SViGGLe directory.
	
	8) Make a build directory with the following commands:
	
	   makedir build
	   cd build
	   
	9) Set the target build system for cmake
	
	   cmake -G "MinGW Makefiles"
	   
	   (You will get an error message about needing the location of glew includes
	   
   10) Set the location of the build includes (replace path to whereever glew repository was created).
   
       cmake -DGLEW_INCLUDE:STRING=c:\glew\include
       
   11) Build the library
   
       make
       
Set up & Building on Windows (Visual Studios):

	1) Install Visual Studios (e.g. 2015 community edition)
	   https://www.visualstudio.com/en-us/products/visual-studio-community-vs.aspx
	   
	2) Download and install cmake:
	   http://www.cmake.org/download/
	   
	3) Download and install a git client
	   https://git-scm.com/downloads
	
	4) Make sure the path environment variable points at the directories with the *.exe files for the above programs.
	   
	5) Clone the glew repository
	   https://github.com/nigels-com/glew
	   
	5) Clone the repository https://github.com/tjgreenfield/SViGGLe
	
	6) Make a build directory under the location of the cloned repository.
	
	7) Open a command prompt and navigate to the SViGGLe directory.
	
	8) Make a build directory with the following commands:
	
	   makedir build
	   cd build
	   
	9) Set the target build system for cmake
	
	   cmake -G "Visual Studio 14 2015 Win64"
	   
	   (You will get an error message about needing the location of glew includes
	   
   10) Set the location of the build includes (replace path to whereever glew repository was created).
   
       cmake -DGLEW_INCLUDE:STRING=c:\glew\include
       
   11) Open the created visual studio project files, and build.

Status:
* Currently supports loading SVG data from buffer or file. 
* Only path elements are implemented
* CSS code written, but not fully utilised.
* Stroke styles current focus of development (dash array, joins, markers etc).
* Basic plain colour fill implemented.

TODO:
0) Fix build process
1) Finish stroke styles for all path segement types.
2) Work out how to do the more complex paint types.
3) The rest of the shapes using the path code as a basis.
4) Implement fonts
...
x) Figure out the top level API.
x) Switch from GFLW to SDL for test code?
x) Add Use/Defs
x) Consider filters, etc
x) Consider animation
x) Finish XML parser 
x) Add DOM interface, or at least enough to use SViGGLe in some sort of UI capacity.

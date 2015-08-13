# SViGGLe
SVG rendering in OpenGL

Copyright (c) 2015 Timothy Greenfield <tjgreenfield@gmail.com>

Brief: SViGGLe is a library designed to support rendering of SVG files within an OpenGL context.

I've recently found myself having some free time and I thought I'd apply my recently gained understanding of SVG to refresh my knowledge of OpenGL.
I hope to get this into a state where I could update to the new Vulkan API. 

Dependancies: The library requires opengl and depends on glew for function bindings. 

Building: I'm only uploading the c source files at the moment as I'm currently migrating my build process from Visual Studios to MinGW/Eclispe.

Headers: opengl, glew. Also include the path to the SViGGLe "src" directory.

SViGGLe_Test: depends on opengl, glew, sfml & SViGGLe. The "src" directory is currently the includes directory as there is no external interface work done yet.


Status:
* Currently supports loading SVG data from buffer or file. 
* Only path elements are implemented at this stage.
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
x) Swith from SFML to SDL?
x) Add Use/Defs
x) Consider filters, etc
x) Consider animation
x) Finish XML parser 
x) Add DOM interface, or at least enough to use SViGGLe in some sort of UI capacity.

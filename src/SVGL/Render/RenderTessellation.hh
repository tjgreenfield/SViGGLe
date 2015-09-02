/**
 *  Copyright (c) 2015 Timothy Greenfield <tjgreenfield@gmail.com>
 *
 * This file is part of SViGGLe.
 *
 * SViGGLe is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 * SViGGLe is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with SViGGLe.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include <SVGL/PathCommands/Buffer/PathCommandsPolygon.hh>
#include <SVGL/GL/gl.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define CALLBACK __stdcall
#else
#define CALLBACK
#endif // WIN32


namespace SVGL
{
    namespace Render
    {
        GLvoid CALLBACK callbackBegin(GLint type);

        GLvoid CALLBACK callbackVertex(GLvoid *vertex_data);

        GLvoid CALLBACK callbackCombine(GLdouble coords[3], void *vertex_data[4],
                                         GLfloat weight[4], void **outData);

        GLvoid CALLBACK callbackEnd();

        void gluTessPointsSet(PathCommands::Polygon* src, PathCommands::Polygon* dst);
    }
}

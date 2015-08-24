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

#include "RenderContext.hh"

#include <SVGL/GL/gl.h>

#include <iostream>

namespace SVGL
{
    namespace Render
    {
        void Context::updateTransform()
        {
            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);

            GLint location = glGetUniformLocation(program, "transform");
            glUniformMatrix3x2dv(location, 1, GL_FALSE, &worldTransform.a);
        }

        void Context::pushTransform(Transform* t)
        {
            transformStack.push_back(worldTransform);
            worldTransform *= *t;

            updateTransform();
        }

        void Context::popTransform()
        {
            worldTransform = transformStack.back();
            transformStack.pop_back();

            updateTransform();
        }

        void Context::pushColor(unsigned int c)
        {
            colorStack.push_back(color);
            color = c;

            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);

            int location = glGetUniformLocation(program, "pen");
            glUniform4f(location,
                        ((float)((color >> 16) & 0xff)) / 0xff,
                        ((float)((color >> 8) & 0xff)) / 0xff,
                        ((float)((color) & 0xff)) / 0xff,
                        ((float)((color >> 24) & 0xff)) / 0xff);
        }

        void Context::popColor()
        {
            color = colorStack.back();
            colorStack.pop_back();

            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);

            int location = glGetUniformLocation(program, "pen");
            glUniform4f(location,
                        ((float)((color >> 16) & 0xff)) / 0xff,
                        ((float)((color >> 8) & 0xff)) / 0xff,
                        ((float)((color) & 0xff)) / 0xff,
                        ((float)((color >> 24) & 0xff)) / 0xff);
        }

        void Context::incrementDepth()
        {
            ++depth;

            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);

            int location = glGetUniformLocation(program, "depth");
            glUniform1f(location, -((float)depth) / 10000);
        }

    }
}

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

#include "RenderColor.hh"

#include <SVGL/Render/RenderContext.hh>
#include <SVGL/Render/RenderPathBuffer.hh>

namespace SVGL
{
    namespace Render
    {
        Color::Color(unsigned int _rgba) :
            rgba(_rgba)
        {

        }

        void Color::setColor(unsigned int rgb)
        {
            rgba = RGBA(rgb, (rgba >> 24) & 0xFF);
        }

        void Color::setAlpha(unsigned int a)
        {
            rgba = RGBA(rgba, a);
        }

        void Color::enable(Context* context) const
        {
            context->setColorShader();

            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);

            int location = glGetUniformLocation(program, "pen");
            glUniform4f(location,
                        ((float)((rgba >> 16) & 0xff)) / 0xff,
                        ((float)((rgba >> 8) & 0xff)) / 0xff,
                        ((float)((rgba) & 0xff)) / 0xff,
                        ((float)((rgba >> 24) & 0xff)) / 0xff);
        }

        void Color::renderFill(Context* context, const PathBuffer& buffer) const
        {
            enable(context);
            buffer.renderFill();
        }

        void Color::renderStroke(Context* context, const PathBuffer& buffer) const
        {
            enable(context);
            buffer.renderStroke();
        }
    }
}

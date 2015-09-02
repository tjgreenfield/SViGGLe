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

#include <SVGL/PathCommands/PathCommands.hh>
#include <SVGL/PathCommands/PathCommandsList.hh>
#include <SVGL/PathCommands/Buffer/PathCommandsPolygon.hh>
#include "RenderContext.hh"
#include <SVGL/GL/gl.h>

#include <vector>

namespace SVGL
{
    namespace Render
    {
        class PathBuffer
        {
            typedef std::vector<GLuint> GlIntV;
            GlIntV strokeGLBuffers;
            GlIntV strokeVertexArrays;
            GlIntV strokeArraySizes;

            GlIntV fillBuffers;
            GlIntV fillVertexArrays;
            GlIntV fillArraySizes;
            GlIntV fillArrayTypes;

        public:

            /* Prevent copying */
            PathBuffer() = default;
            PathBuffer(const PathBuffer&) = delete;
            PathBuffer& operator=(const PathBuffer&) = delete;
            PathBuffer(PathBuffer&&) = default;
            PathBuffer& operator=(PathBuffer&&) = default;
            ~PathBuffer() = default;

            PathBuffer(const PathCommands::List& commandList, const Styles::Vector& style, double tolerance);

            void buffer(const PathCommands::List& commandList, const Styles::Vector& style, double tolerance);

            void clear();

            void render(Render::Context* context, const Styles::Vector& style) const;
            void renderFill() const;
            void renderStroke() const;
        };
    }
}

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

#include "RenderPathBuffer.hh"

#include <SVGL/Path/PathClosePath.hh>
#include <SVGL/Path/Buffer/PathStroker.hh>
#include <SVGL/Render/RenderTessellation.hh>

namespace SVGL
{
    namespace Render
    {
        PathBuffer::PathBuffer(const PathCommand::CommandSet& commandSet, const Styles::Vector& style, double tolerance)
        {
            buffer(commandSet, style, tolerance);
        }

        void PathBuffer::buffer(const PathCommand::CommandSet& commandSet, const Styles::Vector& style, double tolerance)
        {
            if (commandSet.size() == 0)
            {
                return;
            }
            PathCommand::Stroker stroker(tolerance, commandSet[0].get(), style);

            for (const PathCommand::Command_uptr& command : commandSet)
            {
                command->buffer(&stroker);
            }

            if (dynamic_cast<PathCommand::ClosePath*>(commandSet.back().get()))
            {
                // final join is done in close path command
            }
            else
            {
                stroker.bufferEndCap();
            }

            strokeGLBuffers.resize(stroker.strokeBuffer.size(), 0);
            strokeVertexArrays.resize(stroker.strokeBuffer.size(), 0);
            strokeArraySizes.resize(stroker.strokeBuffer.size(), 0);

            glGenBuffers(strokeGLBuffers.size(), &strokeGLBuffers[0]);
            glGenVertexArrays(strokeVertexArrays.size(), &strokeVertexArrays[0]);

            for (unsigned int i = 0; i < stroker.strokeBuffer.size(); ++i)
            {
                PathCommand::Contour& p = stroker.strokeBuffer[i];

                strokeArraySizes[i] = p.size();

                glBindBuffer(GL_ARRAY_BUFFER, strokeGLBuffers[i]);
                glBufferData(GL_ARRAY_BUFFER, p.size() * 2 * sizeof(double), &p[0], GL_STATIC_DRAW);

                glBindVertexArray(strokeVertexArrays[i]);
                glEnableVertexAttribArray(0); // ??
                glBindBuffer(GL_ARRAY_BUFFER, strokeGLBuffers[i]);
                glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 0, (GLubyte*)NULL);
            }

            PathCommand::Polygon fillPointBuffer;

            Render::gluTessPointsSet(&stroker.pointBuffer, &fillPointBuffer);

            fillBuffers.resize(fillPointBuffer.size(), 0);
            fillVertexArrays.resize(fillPointBuffer.size(), 0);
            fillArraySizes.resize(fillPointBuffer.size(), 0);
            fillArrayTypes.resize(fillPointBuffer.size(), 0);

            glGenBuffers(fillBuffers.size(), &fillBuffers[0]);
            glGenVertexArrays(fillVertexArrays.size(), &fillVertexArrays[0]);

            for (unsigned int i = 0; i < fillPointBuffer.size(); ++i)
            {
                PathCommand::Contour& p = fillPointBuffer[i];

                fillArraySizes[i] = p.size();
                fillArrayTypes[i] = p.type;

                glBindBuffer(GL_ARRAY_BUFFER, fillBuffers[i]);
                glBufferData(GL_ARRAY_BUFFER, p.size() * 2 * sizeof(double), &p[0], GL_STATIC_DRAW);

                glBindVertexArray(fillVertexArrays[i]);
                glEnableVertexAttribArray(0); // ??
                glBindBuffer(GL_ARRAY_BUFFER, fillBuffers[i]);
                glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 0, (GLubyte*)NULL);
            }
        }

        void PathBuffer::clear()
        {
            if (!strokeGLBuffers.empty())
            {
                glDeleteBuffers(strokeGLBuffers.size(), &strokeGLBuffers[0]);
                strokeGLBuffers.clear();
            }
            if (!strokeVertexArrays.empty())
            {
                glDeleteBuffers(strokeVertexArrays.size(), &strokeVertexArrays[0]);
                strokeVertexArrays.clear();
            }
            if (!fillBuffers.empty())
            {
                glDeleteBuffers(fillBuffers.size(), &fillBuffers[0]);
                fillBuffers.clear();
            }
            if (!fillVertexArrays.empty())
            {
                glDeleteBuffers(fillVertexArrays.size(), &fillVertexArrays[0]);
                fillVertexArrays.clear();
            }
        }

        void PathBuffer::render(Render::Context* context, const Styles::Vector& style) const
        {
            if (style.hasStroke())
            {
                context->pushColor(style.stroke);
                renderStroke();
                context->popColor();
            }
            if (style.hasFill())
            {
                context->pushColor(style.fill);
                renderFill();
                context->popColor();
            }
        }

        void PathBuffer::renderFill() const
        {
            for (unsigned int i = 0; i < fillVertexArrays.size(); ++i)
            {
                glBindVertexArray(fillVertexArrays[i]);
                glDrawArrays(fillArrayTypes[i], 0, fillArraySizes[i]);
            }
        }

        void PathBuffer::renderStroke() const
        {
            for (unsigned int i = 0; i < strokeVertexArrays.size(); ++i)
            {
                glBindVertexArray(strokeVertexArrays[i]);
                glDrawArrays(GL_TRIANGLE_STRIP, 0, strokeArraySizes[i]);
            }
        }
    }
}

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

#include <SVGL/PathCommands/PathCommandsClosePath.hh>
#include <SVGL/PathCommands/Buffer/PathCommandsStroker.hh>
#include <SVGL/Render/RenderTessellation.hh>

namespace SVGL
{
    namespace Render
    {
        PathBuffer::PathBuffer(const PathCommands::List& commandList, const Styles::Vector& style, double tolerance)
        {
            buffer(commandList, style, tolerance);
        }

        PathBuffer::~PathBuffer()
        {
            clear();
        }

        PathBuffer::PathBuffer(PathBuffer&& _pathBuffer)
        {
            strokeGLBuffers = std::move(_pathBuffer.strokeGLBuffers);
            strokeVertexArrays = std::move(_pathBuffer.strokeVertexArrays);
            strokeArraySizes = std::move(_pathBuffer.strokeArraySizes);

            fillBuffers = std::move(_pathBuffer.fillBuffers);
            fillVertexArrays = std::move(_pathBuffer.fillVertexArrays);
            fillArraySizes = std::move(_pathBuffer.fillArraySizes);
            fillArrayTypes = std::move(_pathBuffer.fillArrayTypes);
            _pathBuffer.clear();
        }

        PathBuffer& PathBuffer::operator=(PathBuffer&& _pathBuffer)
        {
            clear();
            strokeGLBuffers = std::move(_pathBuffer.strokeGLBuffers);
            strokeVertexArrays = std::move(_pathBuffer.strokeVertexArrays);
            strokeArraySizes = std::move(_pathBuffer.strokeArraySizes);

            fillBuffers = std::move(_pathBuffer.fillBuffers);
            fillVertexArrays = std::move(_pathBuffer.fillVertexArrays);
            fillArraySizes = std::move(_pathBuffer.fillArraySizes);
            fillArrayTypes = std::move(_pathBuffer.fillArrayTypes);
            _pathBuffer.clear();
            return *this;
        }

        void PathBuffer::buffer(const PathCommands::List& commandList, const Styles::Vector& style, double tolerance)
        {
            if (commandList.size() == 0)
            {
                return;
            }
            PathCommands::Stroker stroker(tolerance, commandList[0].get(), style);

            for (const PathCommands::Command_uptr& command : commandList)
            {
                command->buffer(&stroker);
            }

            if (dynamic_cast<PathCommands::ClosePath*>(commandList.back().get()))
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
                PathCommands::Contour& p = stroker.strokeBuffer[i];

                strokeArraySizes[i] = p.size();

                glBindBuffer(GL_ARRAY_BUFFER, strokeGLBuffers[i]);
                glBufferData(GL_ARRAY_BUFFER, p.size() * 2 * sizeof(double), &p[0], GL_STATIC_DRAW);

                glBindVertexArray(strokeVertexArrays[i]);
                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, strokeGLBuffers[i]);
                glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 0, (GLubyte*)NULL);
            }

            PathCommands::Polygon fillPointBuffer;

            Render::gluTessPointsSet(&stroker.pointBuffer, &fillPointBuffer);

            fillBuffers.resize(fillPointBuffer.size(), 0);
            fillVertexArrays.resize(fillPointBuffer.size(), 0);
            fillArraySizes.resize(fillPointBuffer.size(), 0);
            fillArrayTypes.resize(fillPointBuffer.size(), 0);

            glGenBuffers(fillBuffers.size(), &fillBuffers[0]);
            glGenVertexArrays(fillVertexArrays.size(), &fillVertexArrays[0]);

            for (unsigned int i = 0; i < fillPointBuffer.size(); ++i)
            {
                PathCommands::Contour& p = fillPointBuffer[i];

                fillArraySizes[i] = p.size();
                fillArrayTypes[i] = p.type;

                glBindBuffer(GL_ARRAY_BUFFER, fillBuffers[i]);
                glBufferData(GL_ARRAY_BUFFER, p.size() * 2 * sizeof(double), &p[0], GL_STATIC_DRAW);

                glBindVertexArray(fillVertexArrays[i]);
                glEnableVertexAttribArray(0);
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
            strokeArraySizes.clear();
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
            fillArraySizes.clear();
            fillArrayTypes.clear();

        }

        void PathBuffer::render(Render::Context* context, const Styles::Vector& style) const
        {
            if (style.hasFill())
            {
                style.fill->renderFill(context, *this);
            }
            context->incrementDepth();
            if (style.hasStroke())
            {
                style.stroke->renderStroke(context, *this);
            }
            context->incrementDepth();
        }

        void PathBuffer::renderFill() const
        {
            for (unsigned int i = 0; i < fillVertexArrays.size(); ++i)
            {
                if (glIsBuffer(fillBuffers[i]))
                {
                    glBindVertexArray(fillVertexArrays[i]);
                    glDrawArrays(fillArrayTypes[i], 0, fillArraySizes[i]);
                }
            }
        }

        void PathBuffer::renderStroke() const
        {
            for (unsigned int i = 0; i < strokeVertexArrays.size(); ++i)
            {
                if (glIsBuffer(strokeGLBuffers[i]))
                {
                    glBindVertexArray(strokeVertexArrays[i]);
                    glDrawArrays(GL_TRIANGLE_STRIP, 0, strokeArraySizes[i]);
                }
            }
        }
    }
}

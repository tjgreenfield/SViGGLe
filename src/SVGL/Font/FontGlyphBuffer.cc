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

#include "FontGlyphBuffer.hh"

#include <SVGL/Render/RenderTessellation.hh>

namespace SVGL
{
    namespace Font
    {
        /*
        GlyphBuffer::GlyphBuffer(GlyphBuffer&& glyphBuffer)
        {
            strokeGLBuffers = std::move(glyphBuffer.strokeGLBuffers);
            strokeVertexArrays = std::move(glyphBuffer.strokeVertexArrays);
            strokeArraySizes = std::move(glyphBuffer.strokeArraySizes);

            fillBuffers = std::move(glyphBuffer.fillBuffers);
            fillVertexArrays = std::move(glyphBuffer.fillVertexArrays);
            fillArraySizes = std::move(glyphBuffer.fillArraySizes);
            fillArrayTypes = std::move(glyphBuffer.fillArrayTypes);
        }

        GlyphBuffer& GlyphBuffer::operator=(GlyphBuffer&& glyphBuffer)
        {
            strokeGLBuffers = std::move(glyphBuffer.strokeGLBuffers);
            strokeVertexArrays = std::move(glyphBuffer.strokeVertexArrays);
            strokeArraySizes = std::move(glyphBuffer.strokeArraySizes);

            fillBuffers = std::move(glyphBuffer.fillBuffers);
            fillVertexArrays = std::move(glyphBuffer.fillVertexArrays);
            fillArraySizes = std::move(glyphBuffer.fillArraySizes);
            fillArrayTypes = std::move(glyphBuffer.fillArrayTypes);

            return *this;
        }

        GlyphBuffer::GlyphBuffer(Glyph& glyph, double tolerance)
        {
            if (glyph.commandSet.size() == 0) return;
            Buffer::BufferingState buffers(tolerance, glyph.commandSet[0].get(), nullptr);

            for (PathCommand::PathCommandSet::iterator i = glyph.commandSet.begin(); i != glyph.commandSet.end(); ++i)
            {
                (*i)->buffer(&buffers);
            }

            Buffer::Polygon fillPointBuffer;

            Render::gluTessPointsSet(&buffers.pointBuffer, &fillPointBuffer);

            fillBuffers.resize(fillPointBuffer.size(), 0);
            fillVertexArrays.resize(fillPointBuffer.size(), 0);
            fillArraySizes.resize(fillPointBuffer.size(), 0);
            fillArrayTypes.resize(fillPointBuffer.size(), 0);

            glGenBuffers(fillBuffers.size(), &fillBuffers[0]);
            glGenVertexArrays(fillVertexArrays.size(), &fillVertexArrays[0]);

            for (unsigned int i = 0; i < fillPointBuffer.size(); ++i)
            {
                Buffer::Contour& p = fillPointBuffer[i];

                fillArraySizes[i] = p.size();
                fillArrayTypes[i] = p.type;

                glBindBuffer(GL_ARRAY_BUFFER, fillBuffers[i]);
                glBufferData(GL_ARRAY_BUFFER, p.size() * 2 * sizeof (double), &p[0], GL_STATIC_DRAW);

                glBindVertexArray(fillVertexArrays[i]);
                glEnableVertexAttribArray(0); // ??
                glBindBuffer(GL_ARRAY_BUFFER, fillBuffers[i]);
                glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 0, (GLubyte*) NULL);
            }
        }

        GlyphBuffer::~GlyphBuffer()
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

        void GlyphBuffer::render(Render::Context*)
        {
          	for (unsigned int i = 0; i < fillVertexArrays.size(); ++i)
            {
                glBindVertexArray(fillVertexArrays[i]);
                glDrawArrays(fillArrayTypes[i], 0, fillArraySizes[i]);
            }
        }
        */
    }
}

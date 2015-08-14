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
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "ElementsPath.hh"
#include "Path/PathParser.hh"
#include <SVGL/Buffer/BufferPolygon.hh>
#include <SVGL/Render/RenderTessellation.hh>
#include <SVGL/Render/RenderStroke.hh>

#include <GL/glew.h>
#include <GL/gl.h>

namespace SVGL
{
    Path::~Path()
    {
        clearBuffers();
    }

    /**
     * Get the Style object for the current element.
     *
     * @details The style object is used to apply styles from the stylesheets.
     * @return A pointer to the Style object.
     */
    CSS::Style* Path::getStyle()
    {
        return &style;
    }

    /**
     * Get the tag name of the element.
     */
    const char* Path::getTagName() const
    {
        return "path";
    }

    /**
     * Get the value of the specified attribute.
     *
     * @param[in] attributeName The name of the attribute to get.
     */
    const char* Path::getAttributeValue(const char* attributeName) const
    {
        return "";
    }

    void Path::setAttribute(unsigned int index, SubString name, SubString value)
    {
        switch (index)
        {
        case D:
            commandSet = PathCommand::Parser(value.start).readPathCommandSet();
            break;
        default:
            Element::setAttribute(index, name, value);
            break;
        }
    }

    std::ostream& Path::stream(std::ostream& out) const
    {
        out << "path(" << commandSet.size() << "|" << styleDeclarations.map.size() << ")";
        return out;
    }

    void Path::clearBuffers()
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
    }

    void Path::buffer(double tolerance)
    {
        if (!dirty) return;
        clearBuffers();
        Buffer::Polygon pointBuffer;
        Buffer::Polygon strokeBuffer;
        Point at(*commandSet[0]);

        for (PathCommand::PathCommandSet::iterator i = commandSet.begin(); i != commandSet.end(); ++i)
        {
            (*i)->buffer(&pointBuffer, tolerance);
            (*i)->bufferStroke(&strokeBuffer, &at, &style, tolerance);
        }

        // TODO: linecaps
        // If last pathcommand isn't "Z", then Stroke::bufferEndCap(...)

        strokeGLBuffers.resize(strokeBuffer.size(), 0);
        strokeVertexArrays.resize(strokeBuffer.size(), 0);
        strokeArraySizes.resize(strokeBuffer.size(), 0);

        glGenBuffers(strokeGLBuffers.size(), &strokeGLBuffers[0]);
        glGenVertexArrays(strokeVertexArrays.size(), &strokeVertexArrays[0]);

        for (unsigned int i = 0; i < strokeBuffer.size(); ++i)
        {
            Buffer::Contour& p = strokeBuffer[i];

            strokeArraySizes[i] = p.size();

            glBindBuffer(GL_ARRAY_BUFFER, strokeGLBuffers[i]);
            glBufferData(GL_ARRAY_BUFFER, p.size() * 2 * sizeof(double), &p[0], GL_STATIC_DRAW);

            glBindVertexArray(strokeVertexArrays[i]);
            glEnableVertexAttribArray(0); // ??
            glBindBuffer(GL_ARRAY_BUFFER, strokeGLBuffers[i]);
            glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 0, (GLubyte*)NULL);
        }

        Buffer::Polygon fillPointBuffer;

        Render::gluTessPointsSet(&pointBuffer, &fillPointBuffer);

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
            glBufferData(GL_ARRAY_BUFFER, p.size() * 2 * sizeof(double), &p[0], GL_STATIC_DRAW);

            glBindVertexArray(fillVertexArrays[i]);
            glEnableVertexAttribArray(0); // ??
            glBindBuffer(GL_ARRAY_BUFFER, fillBuffers[i]);
            glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 0, (GLubyte*)NULL);
        }
        dirty = false;
    }

    void Path::render(Render::Context* context)
    {
        if (style.hasFill())
        {
            context->pushColor(style.getFill());
            for (unsigned int i = 0; i < fillVertexArrays.size(); ++i)
            {
                glBindVertexArray(fillVertexArrays[i]);
                glDrawArrays(fillArrayTypes[i], 0, fillArraySizes[i]);
            }
            context->popColor();
        }

        if (style.hasStroke())
        {
            context->pushColor(style.getStroke());
            for (unsigned int i = 0; i < strokeVertexArrays.size(); ++i)
            {
                glBindVertexArray(strokeVertexArrays[i]);
                glDrawArrays(GL_TRIANGLE_STRIP, 0, strokeArraySizes[i]);
            }
            context->popColor();
        }
    }
}

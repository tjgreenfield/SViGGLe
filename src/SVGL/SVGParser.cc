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

#include "SVGParser.hh"
#include "Elements.hh"
#include "Document.hh"

namespace SVGL
{
    ElementTypeMap elementTypeMap = {
        { "svg", ET_SVG },
        { "g", ET_G },
        { "path", ET_PATH },
        { "rect", ET_RECT },
        { "circle", ET_CIRCLE},
        { "ellipse", ET_ELLIPSE},
        { "line", ET_LINE},
        { "polyline", ET_POLYLINE},
        { "polygon", ET_POLYGON},
    };

    ElementType getElementType(SubString tag)
    {
        auto i = elementTypeMap.find(tag);
        if (i != elementTypeMap.end())
        {
            return i->second;
        }
        return ET_INVALID;
    }

    XML::Node_uptr Parser::createElement(SubString tag)
    {
        ElementType type = getElementType(tag);
        switch (type)
        {
        case ET_SVG:
            return std::move(Node_uptr(new Document()));
        case ET_G:
            return std::move(Node_uptr(new Group()));
        case ET_PATH:
            return std::move(Node_uptr(new Path()));
        case ET_RECT:
            return std::move(Node_uptr(new Rect()));
        case ET_CIRCLE:
            return std::move(Node_uptr(new Circle()));
        case ET_ELLIPSE:
            return std::move(Node_uptr(new Ellipse()));
        case ET_LINE:
            return std::move(Node_uptr(new Line()));
        case ET_POLYLINE:
            return std::move(Node_uptr(new PolyLine()));
        case ET_POLYGON:
            return std::move(Node_uptr(new Polygon()));
        default:
            return std::move(Node_uptr(new XML::Node()));
        }
    }
}

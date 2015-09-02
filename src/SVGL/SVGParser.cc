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
        { "text", ET_TEXT},
        { "style", ET_STYLE}
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
        default:
        case ET_INVALID:
            return std::move(XML::Node_uptr(new XML::Node()));
        case ET_SVG:
            return std::move(XML::Node_uptr(new Document()));
        case ET_G:
            return std::move(XML::Node_uptr(new Elements::Group()));
        case ET_PATH:
            return std::move(XML::Node_uptr(new Elements::Path()));
        case ET_RECT:
            return std::move(XML::Node_uptr(new Elements::Rect()));
        case ET_CIRCLE:
            return std::move(XML::Node_uptr(new Elements::Circle()));
        case ET_ELLIPSE:
            return std::move(XML::Node_uptr(new Elements::Ellipse()));
        case ET_LINE:
            return std::move(XML::Node_uptr(new Elements::Line()));
        case ET_POLYLINE:
            return std::move(XML::Node_uptr(new Elements::PolyLine()));
        case ET_POLYGON:
            return std::move(XML::Node_uptr(new Elements::Polygon()));
        case ET_TEXT:
            return std::move(XML::Node_uptr(new Elements::Text()));
        case ET_STYLE:
            return std::move(XML::Node_uptr(new Elements::Style()));
        }
    }
}

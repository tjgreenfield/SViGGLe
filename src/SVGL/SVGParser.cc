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

#include "SVGParser.hh"
#include "Elements.hh"
#include "Document.hh"

namespace SVGL
{
    ElementTypeMap elementTypeMap = {
        { "svg", ET_SVG },
        { "g", ET_G },
        { "path", ET_PATH }
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
        default:
            return std::move(Node_uptr(new XML::Node()));
        }
    }
}

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

#include "ElementsTag.hh"

namespace SVGL
{
    namespace Elements
    {
        Tag::Map Tag::map = {
            { "svg", Tag::Index::SVG },
            { "g", Tag::Index::G },
            { "path", Tag::Index::PATH },
            { "rect", Tag::Index::RECT },
            { "circle", Tag::Index::CIRCLE},
            { "ellipse", Tag::Index::ELLIPSE},
            { "line", Tag::Index::LINE},
            { "polyline", Tag::Index::POLYLINE},
            { "polygon", Tag::Index::POLYGON},
            { "text", Tag::Index::TEXT},
            { "style", Tag::Index::STYLE},
            { "image", Tag::Index::IMAGE},
            { "defs", Tag::Index::DEFS},
            { "use", Tag::Index::USE}
        };

        Tag::Index Tag::getIndex(SubString tag)
        {
            auto i = map.find(tag);
            if (i != map.end())
            {
                return i->second;
            }
            return Index::INVALID;
        }
    }
}

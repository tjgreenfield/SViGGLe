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
            { "svg", Tag::SVG },
            { "g", Tag::G },
            { "path", Tag::PATH },
            { "rect", Tag::RECT },
            { "circle", Tag::CIRCLE},
            { "ellipse", Tag::ELLIPSE},
            { "line", Tag::LINE},
            { "polyline", Tag::POLYLINE},
            { "polygon", Tag::POLYGON},
            { "text", Tag::TEXT},
            { "style", Tag::STYLE},
            { "image", Tag::IMAGE},
            { "defs", Tag::DEFS},
            { "use", Tag::USE},
            { "linearGradient", Tag::LINEAR_GRADIENT},
            { "radialGradient", Tag::RADIAL_GRADIENT},
            { "stop", Tag::STOP},
        };

        Tag::Index Tag::getIndex(SubString tag)
        {
            auto i = map.find(tag);
            if (i != map.end())
            {
                return i->second;
            }
            return INVALID;
        }
    }
}


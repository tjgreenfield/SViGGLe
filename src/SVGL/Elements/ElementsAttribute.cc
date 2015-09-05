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

#include "ElementsAttribute.hh"

namespace SVGL
{
    namespace Elements
    {
        Attribute::Map Attribute::map = {
            { "id", Attribute::Index::ID },
            { "class", Attribute::Index::CLASS },
            { "style", Attribute::Index::STYLE },
            { "transform", Attribute::Index::TRANSFORM },
            { "d", Attribute::Index::D },
            { "pathLength", Attribute::Index::PATH_LENGTH },
            { "x", Attribute::Index::X },
            { "y", Attribute::Index::Y },
            { "x1", Attribute::Index::X1 },
            { "y1", Attribute::Index::Y1 },
            { "x2", Attribute::Index::X2 },
            { "y2", Attribute::Index::Y2 },
            { "width", Attribute::Index::WIDTH },
            { "height", Attribute::Index::HEIGHT },
            { "rx", Attribute::Index::RX },
            { "ry", Attribute::Index::RY },
            { "cx", Attribute::Index::CX },
            { "cy", Attribute::Index::CY },
            { "r", Attribute::Index::R },
            { "points", Attribute::Index::POINTS },
            { "xlink:href", Attribute::Index::XLINK_HREF },
            { "type", Attribute::Index::TYPE },
            { "media", Attribute::Index::MEDIA },
            { "title", Attribute::Index::TITLE },
        };

        Attribute::Index Attribute::getIndex(SubString attribute)
        {
            auto i = map.find(attribute);
            if (i != map.end())
            {
                return i->second;
            }
            return Index::INVALID;
        }
    }
}

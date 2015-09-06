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
            { "id", Attribute::ID },
            { "class", Attribute::CLASS },
            { "style", Attribute::STYLE },
            { "transform", Attribute::TRANSFORM },
            { "d", Attribute::D },
            { "pathLength", Attribute::PATH_LENGTH },
            { "x", Attribute::X },
            { "y", Attribute::Y },
            { "x1", Attribute::X1 },
            { "y1", Attribute::Y1 },
            { "x2", Attribute::X2 },
            { "y2", Attribute::Y2 },
            { "width", Attribute::WIDTH },
            { "height", Attribute::HEIGHT },
            { "rx", Attribute::RX },
            { "ry", Attribute::RY },
            { "cx", Attribute::CX },
            { "cy", Attribute::CY },
            { "fx", Attribute::FX },
            { "fy", Attribute::FY },
            { "r", Attribute::R },
            { "points", Attribute::POINTS },
            { "xlink:href", Attribute::XLINK_HREF },
            { "type", Attribute::TYPE },
            { "media", Attribute::MEDIA },
            { "title", Attribute::TITLE },
            { "stop-color", Attribute::STOP_COLOR },
            { "stop-opacity", Attribute::STOP_OPACITY },
            { "offset", Attribute::OFFSET },
            { "gradientUnits", Attribute::GRADIENT_UNITS },
            { "gradientTransform", Attribute::GRADIENT_TRANSFORM },
            { "spreadMethod", Attribute::SPREAD_METHOD },
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

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

#pragma once

#include <SVGL/Types/SubString.hh>

#include <unordered_map>

namespace SVGL
{
    namespace Elements
    {
        class Attribute
        {
        public:
            enum Index {
                // Primary attribute list
                INVALID = 0,
                ID,
                CLASS,
                STYLE,
                TRANSFORM,
                D,
                PATH_LENGTH,
                X,
                Y,
                X1,
                Y1,
                X2,
                Y2,
                WIDTH,
                HEIGHT,
                RX,
                RY,
                CX,
                CY,
                R,
                POINTS,
                XLINK_HREF,
                //...

                TYPE,
                MEDIA,
                TITLE

                // TODO Include "event" attributes
                // TODO Include "conditional processing" attributes
                };


            typedef std::unordered_map<SubString, Index> Map;
            static Map map;

            static Index getIndex(SubString attribute);
        };
    }
}

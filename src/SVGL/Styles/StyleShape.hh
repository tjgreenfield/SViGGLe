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

#include "StyleTypes.hh"
#include "StyleSVG.hh"
#include "StyleVector.hh"
#include <SVGL/CSS/CSS.hh>

#include <bitset>
#include <unordered_map>

namespace SVGL
{
    namespace Styles
    {
        class Shape : public Vector
        {

            unsigned int marker;

            /*
            ‘marker’
            ‘marker-start’
            ‘marker-mid’
            ‘marker-end’
            ‘shape-rendering’
            */
        public:
            /*virtual unsigned int getMarker()
            {
            if (inheritedShape[0])
            {
            return parent ? parent->getMarker() : 0;
            }
            return marker;
            }*/
        };
    }
}

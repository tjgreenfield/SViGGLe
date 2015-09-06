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

#include <SVGL/Types/Point.hh>

#include <ostream>
#include <cmath>

namespace SVGL
{
    class BoundingBox
    {
    public:
        Point pMin;
        Point pMax;

        inline BoundingBox& operator=(const Point& point)
        {
            pMin = pMax = point;
            return *this;
        }

        inline BoundingBox& operator+=(const Point& point)
        {
            pMin.x = std::min(pMin.x, point.x);
            pMin.y = std::min(pMin.y, point.y);

            pMax.x = std::max(pMax.x, point.x);
            pMax.y = std::max(pMax.y, point.y);
            return *this;
        }

        inline BoundingBox& operator+=(const BoundingBox& boundingBox)
        {
            *this += boundingBox.pMin;
            *this += boundingBox.pMax;
            return *this;
        }

    };

}

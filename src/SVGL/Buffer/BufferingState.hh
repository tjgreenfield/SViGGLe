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

#include "BufferPolygon.hh"

#include <SVGL/Styles/StyleSVG.hh>
#include <SVGL/Types/Point.hh>

namespace SVGL
{
    namespace Buffer
    {
        struct BufferingState
        {
            Polygon pointBuffer;
            Polygon strokeBuffer;
            Point at;
            Styles::SVG* style;
            double tolerance;
            const Styles::DashArray* dashArray;
            unsigned int dashIndex;
            double dashDistance;

            inline BufferingState(double tolerance, Point* _at, Styles::SVG* _style) :
                    at(*_at),
                    style(_style),
                    tolerance(tolerance),
                    dashArray(style->getStrokeDashArray()),
                    dashIndex(0),
                    dashDistance(style->getStrokeDashOffset())
            {
                if (dashArray)
                {
                    while (dashDistance > (*dashArray)[dashIndex])
                    {
                        dashDistance -= (*dashArray)[dashIndex];
                        dashIndex = (dashIndex + 1) % dashArray->size();
                    }
                }
            }
        };
    }
}

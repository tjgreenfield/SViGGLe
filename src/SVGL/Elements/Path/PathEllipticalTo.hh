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

#pragma once

#include "PathCommand.hh"
#include <SVGL/Buffer/BufferPolygon.hh>

namespace SVGL
{
    namespace PathCommand
    {
        class EllipticalTo : public PathCommand
        {
        public:
            double rx, ry, xAxisRotation, largeArcFlag, sweepFlag;

            double cosp, sinp, t1, dt, cx, cy; // calculated values

            EllipticalTo(Point p, double _rx, double _ry, double _xAxisRotation, double _largeArcFlag, double _sweepFlag, PathCommand* prev);

            void buffer(Buffer::Polygon* pointBuffer, double tolerance) const override;

            void bufferStroke(Buffer::Polygon* strokeBuffer, Point* at, Styles::SVG* style, double tolerance) const override;
        };
    }
}

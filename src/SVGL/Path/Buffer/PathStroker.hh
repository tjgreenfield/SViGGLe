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

#include "PathPolygon.hh"

#include <SVGL/Styles/StyleVector.hh>
#include <SVGL/GL/gl.h>

#include <vector>

namespace SVGL
{
    namespace PathCommand
    {
        class Stroker
        {
        public:

            Polygon pointBuffer;
            Polygon strokeBuffer;
            Point at;
            const Styles::Vector& style;
            double tolerance;
            const Styles::Vector::DashArray* dashArray;
            unsigned int dashIndex;
            double dashDistance;

        public:

            Stroker(double _tolerance, Point* _at, const Styles::Vector& _style);

            /* DashArray */
            void bufferDash(const Point& to);


            /* Line Caps */
            void bufferStartCap(const Point& dir);

            void bufferEndCap();

            void bufferCap(const Point& dir);

            void bufferStartCapSquare(const Point& dir);

            void bufferEndCapSquare(const Point& dir);

            void bufferStartCapRound(const Point& dir);

            void bufferEndCapRound(const Point& dir);


            /* Line Joins */
            void bufferJoin(const Point& to);

            void bufferMiterJoin(const Point& offset);

            void bufferRoundJoin(const Point& offset);

            void bufferBevelJoin(const Point& offset);

        };
    }
}

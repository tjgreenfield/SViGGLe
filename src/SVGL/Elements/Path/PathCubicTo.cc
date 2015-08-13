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

#include "PathCubicTo.hh"
#include <algorithm>

#include <iostream>

namespace SVGL
{
    namespace PathCommand
    {
        void CubicTo::buffer(Buffer::Polygon* pointBuffer, double tolerance) const
        {
            Point op = pointBuffer->getLastPoint();

            // this might need adjusting
            double dt = std::min(tolerance / (p1.distance() + p2.distance(&p1) + distance(&p2)) * 3, 0.5);

            for (double t = dt; t < 1; t += dt)
            {
                double nt = 1 - t;
                double a = nt * nt * nt;
                double b = 3 * t * nt * nt;
                double c = 3 * t * t * nt;
                double d = t * t * t;

                Point pOut(a * op.x + b * p1.x + c * p2.x + d*x,
                        a * op.y + b * p1.y + c * p2.y + d * y);
                pointBuffer->pushPoint(&pOut);
            }
            pointBuffer->pushPoint(this);
        }

        void CubicTo::bufferStroke(Buffer::Polygon* strokeBuffer, Point* at, Styles::SVG* style, double tolerance) const
        {
            double strokeWidth = style->getStrokeWidth();

            Point offset(strokeWidth * at->normal(&p1));

            Point a(*at + offset);
            Point b(*at - offset);

            Stroke::bufferJoin(strokeBuffer, a, b, style, tolerance);

            // this might need adjusting
            double dt = std::min(tolerance / (p1.distance() + p2.distance(&p1) + distance(&p2)) * 3, 0.5);

            Point prevCentre = *at;

            for (double t = dt; t < 1; t += dt)
            {
                double nt = 1 - t;
                double a = nt * nt * nt;
                double b = 3 * t * nt * nt;
                double c = 3 * t * t * nt;
                double d = t * t * t;

                Point pCentre(a * at->x + b * p1.x + c * p2.x + d * x,
                              a * at->y + b * p1.y + c * p2.y + d * y);

                offset = strokeWidth * prevCentre.normal(&pCentre);

                strokeBuffer->pushPoint(pCentre + offset);
                strokeBuffer->pushPoint(pCentre - offset);

                prevCentre = pCentre;
            }

            offset = strokeWidth * prevCentre.normal(this);

            strokeBuffer->pushPoint(*this + offset);
            strokeBuffer->pushPoint(*this - offset);

            *at = *this;
        }
    }
}

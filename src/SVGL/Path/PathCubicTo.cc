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

#include "PathCubicTo.hh"
#include <algorithm>

#include <iostream>

namespace SVGL
{
    namespace PathCommand
    {
        void CubicTo::buffer(Stroker* stroker) const
        {
            Point op = stroker->pointBuffer.getLastPoint();

            // this might need adjusting
            unsigned int vertexCount = std::max(2.0, (p1.distance() + p2.distance(p1) + distance(p2)) / (3 * stroker->tolerance));

            for (unsigned int i = 1; i <= vertexCount; ++i)
            {
                double t = ((double)i) / ((double) vertexCount);
                double nt = 1 - t;
                double a = nt * nt * nt;
                double b = 3 * t * nt * nt;
                double c = 3 * t * t * nt;
                double d = t * t * t;

                // fill
                Point pCentre(a * op.x + b * p1.x + c * p2.x + d * x,
                              a * op.y + b * p1.y + c * p2.y + d * y);
                stroker->pointBuffer.pushPoint(&pCentre);

                if (i == 1)
                {
                    stroker->bufferJoin(pCentre);
                }

                stroker->bufferDash(pCentre);
            }
        }
    }
}

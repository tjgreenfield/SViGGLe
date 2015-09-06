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

#include "PathCommandsCubicTo.hh"
#include <algorithm>

#include <iostream>

namespace SVGL
{
    namespace PathCommands
    {
        void CubicTo::buffer(Stroker* stroker) const
        {
            //op = stroker->pointBuffer.getLastPoint();

            // this might need adjusting
            unsigned int vertexCount = std::max(4.0, (p1.distance() + p2.distance(p1) + distance(p2)) / (3 * stroker->tolerance));

            for (unsigned int i = 1; i <= vertexCount; ++i)
            {
                double t = ((double)i) / ((double) vertexCount);
                double nt = 1 - t;
                double t0 = nt*nt*nt;
                double t1 = 3*t*nt*nt;
                double t2 = 3*t*t*nt;
                double t3 = t*t*t;

                // fill
                Point pCentre(t0*op.x + t1*p1.x + t2*p2.x + t3*x,
                              t0*op.y + t1*p1.y + t2*p2.y + t3*y);
                stroker->pointBuffer.pushPoint(&pCentre);

                if (i == 1)
                {
                    stroker->bufferJoin(pCentre);
                }

                stroker->bufferDash(pCentre);
            }
        }

        void CubicTo::calculateBoundingBox(BoundingBox* boundingBox)
        {
            Point out1;
            Point out2;
            // x
            {
                double a = x - 3*p2.x + 3*p1.x - op.x;
                double b = 2*(p2.x - 3*p1.x + op.x);
                double c = p2.x - x;

                double s = sqrt(b*b - 4*a*c);

                // first x
                {
                    double t = (a == 0) ? (-c / b) : (-b - s) / (2*a);

                    double nt = 1 - t;
                    double t0 = nt*nt*nt;
                    double t1 = 3*t*nt*nt;
                    double t2 = 3*t*t*nt;
                    double t3 = t*t*t;

                    out1.x = t0*op.x + t1*p1.x + t2*p2.x + t3*x;
                }

                // second x
                {
                    double t = (a == 0) ? (-c / b) : (-b - s) / (2*a);

                    double nt = 1 - t;
                    double t0 = nt*nt*nt;
                    double t1 = 3*t*nt*nt;
                    double t2 = 3*t*t*nt;
                    double t3 = t*t*t;

                    out2.x = t0*op.x + t1*p1.x + t2*p2.x + t3*x;
                }
            }

            // y
            {
                double a = y - 3*p2.y + 3*p1.y - op.y;
                double b = 2*(p2.y - 3*p1.y + op.y);
                double c = p2.y - y;

                double s = sqrt(b*b - 4*a*c);

                // first y
                {
                    double t = (a == 0) ? (-c / b) : (-b - s) / (2*a);

                    double nt = 1 - t;
                    double t0 = nt*nt*nt;
                    double t1 = 3*t*nt*nt;
                    double t2 = 3*t*t*nt;
                    double t3 = t*t*t;

                    out1.y = t0*op.y + t1*p1.y + t2*p2.y + t3*y;

                }

                // second y
                {
                    double t = (a == 0) ? (-c / b) : (-b - s) / (2*a);

                    double nt = 1 - t;
                    double t0 = nt*nt*nt;
                    double t1 = 3*t*nt*nt;
                    double t2 = 3*t*t*nt;
                    double t3 = t*t*t;

                    out2.y = t0*op.y + t1*p1.y + t2*p2.y + t3*y;
                }
            }
            *boundingBox += op;
            *boundingBox += out1;
            *boundingBox += out2;
            *boundingBox += *this;
        }
    }
}


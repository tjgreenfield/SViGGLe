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

#include "PathCommandsEllipticalTo.hh"
#include <SVGL/Transforms/Transforms.hh>
#include <SVGL/Types/Consts.hh>
#include <algorithm>
#include <cstdlib>

namespace SVGL
{
    namespace PathCommands
    {
        EllipticalTo::EllipticalTo(Point p, double _rx, double _ry, double _xAxisRotation, double _largeArcFlag, double _sweepFlag, Point* prev) :
            Command(p),
            rx(_rx),
            ry(_ry),
            xAxisRotation(_xAxisRotation),
            largeArcFlag(_largeArcFlag),
            sweepFlag(_sweepFlag)
        {

            double& x1 = prev->x;
            double& y1 = prev->y;
            double& x2 = x;
            double& y2 = y;

            // Calculate centre coordinates - http://www.w3.org/TR/SVG/implnote.html#ArcImplementationNotes
            // Step 1
            cosp = cos(xAxisRotation);
            sinp = sin(xAxisRotation);

            double x_a = (x1 - x2) / 2;
            double y_a = (y1 - y2) / 2;

            double x1_ = cosp * x_a + sinp * y_a;
            double y1_ = -sinp * x_a + cosp * y_a;

            // Step 2
            double rx2 = rx * rx;
            double ry2 = ry * ry;

            double x1_2 = x1_ * x1_;
            double y1_2 = y1_ * y1_;

            double q = (rx2 * ry2 - rx2 * y1_2 - ry2 * x1_2)
                / (rx2 * y1_2 + ry2 * x1_2);

            double m = sqrt(q);

            if (largeArcFlag == sweepFlag)
            {
                m = -m;
            }

            double cx_ = m * rx * y1_ / ry;
            double cy_ = m * -ry * x1_ / rx;

            // step 3
            cx = (cosp * cx_) - (sinp * cy_) + ((x1 + x2) / 2);
            cy = (sinp * cx_) + (cosp * cy_) + ((y1 + y2) / 2);

            // step 4
            double v1_x = (x1_ - cx_) / rx;
            double v1_y = (y1_ - cy_) / ry;
            double v1_m = sqrt(v1_x * v1_x + v1_y * v1_y);

            t1 = acos(1 * v1_x / v1_m);

            // do the sign
            if (v1_y >= 0 && t1 < 0)
            {
                t1 = -t1;
            }
            else if (v1_y < 0 && t1 > 0)
            {
                t1 = -t1;
            }

            double v2_x = (-x1_ - cx_) / rx;
            double v2_y = (-y1_ - cy_) / ry;
            double v2_m = sqrt(v2_x * v2_x + v2_y * v2_y);

            dt = acos((v1_x * v2_x + v1_y * v2_y)
                             / (v1_m * v2_m));

            double k = v1_x * v2_y - v1_y * v2_x;

            // do the sign
            if (k >= 0 && dt < 0)
            {
                dt = -dt;
            }
            else if (k < 0 && dt > 0)
            {
                dt = -dt;
            }

            // modulus
            if (sweepFlag == 0 && dt > 0)
            {
                dt -= PI * 2;
            }
            else if (sweepFlag == 1 && dt < 0)
            {
                dt += PI * 2;
            }
        }


        void EllipticalTo::buffer(Stroker* stroker) const
        {
            // this might need adjusting
            //int vertexCount = std::max(abs(int(std::max(std::abs(rx), std::abs(ry)) * dt / PI / stroker->tolerance)), 4);
            //double deltaT = (dt / (vertexCount - 1));

            double ratio = 1 - (stroker->tolerance / std::max(std::abs(rx), std::abs(ry)));
            double deltaT = (ratio > SQRT2_2) ? acos(ratio) : PI_4;
            int vertexCount = std::abs(dt / deltaT);
            deltaT = (dt / (vertexCount - 1));

            Transforms::Rotate current(t1);
            Transforms::Rotate rotate(deltaT);

            for (int i = 1; i < vertexCount; i++)
            {
                current *= rotate;
                Point pCentre((cosp * rx * current.a) + (sinp * ry * current.b) + cx, //x
                              (cosp * ry * current.c) + (sinp * rx * current.d) + cy); //y

                stroker->pointBuffer.pushPoint(pCentre);

                if (i == 1)
                {
                    stroker->bufferJoin(pCentre);
                }

                stroker->bufferDash(pCentre);
            }
        }
    }
}

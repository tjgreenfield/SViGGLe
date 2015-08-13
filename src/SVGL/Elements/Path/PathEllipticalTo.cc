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

#include "PathEllipticalTo.hh"
#include <SVGL/Types/Consts.hh>
#include <algorithm>
#include <cstdlib>

namespace SVGL
{
    namespace PathCommand
    {

        EllipticalTo::EllipticalTo(Point p, double _rx, double _ry, double _xAxisRotation, double _largeArcFlag, double _sweepFlag, PathCommand* prev) :
            PathCommand(p),
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


        void EllipticalTo::buffer(Buffer::Polygon* pointBuffer, double tolerance) const
        {
            int vertexCount = int(std::max(rx, ry) * dt / PI / tolerance);
            for (int i = 1; i < vertexCount; i++)
            {
                double t = (((double)i) / ((double)(vertexCount - 1))) * dt + t1;
                double cost = cos(t);
                double sint = sin(t);

                Point p((cosp * rx * cost) - (sinp * ry * sint) + cx, //x
                        (sinp * rx * cost) + (cosp * ry * sint) + cy); //y

                pointBuffer->pushPoint(&p);
            }
            pointBuffer->pushPoint(this);
        }

        void EllipticalTo::bufferStroke(Buffer::Polygon* strokeBuffer, Point* at, Styles::SVG* style, double tolerance) const
        {
            double strokeWidth = style->getStrokeWidth();

            double t = t1;
            double cost = cos(t);
            double sint = sin(t);

             // The derviative of the pCentre position function below is used to get the direction
            Point dir (-(cosp * rx * sint) - (sinp * ry * cost), //x
                                             -(sinp * rx * sint) + (cosp * ry * cost)); //y
            if (dt < 0) // need to make sure we're going in the right direction
            {
                dir *= -1;
            }

            // The normal of the direction is used for the direction of the offset
            Point offset(strokeWidth * dir.normal());

            Point a(*at + offset);
            Point b(*at - offset);

            Stroke::bufferJoin(strokeBuffer, a, b, style, tolerance);

            // this might need adjusting
            int vertexCount = abs(int(std::max(std::abs(rx), std::abs(ry)) * dt / PI / tolerance));

            Point prevCentre = *at;

            for (int i = 1; i < vertexCount; i++)
            {
                t = (((double)i) / ((double)(vertexCount - 1))) * dt + t1;
                cost = cos(t);
                sint = sin(t);

                Point pCentre((cosp * rx * cost) - (sinp * ry * sint) + cx, //x
                              (sinp * rx * cost) + (cosp * ry * sint) + cy); //y

                offset = strokeWidth * prevCentre.normal(&pCentre);

                strokeBuffer->pushPoint(pCentre + offset);
                strokeBuffer->pushPoint(pCentre - offset);

                prevCentre = pCentre;
            }

            // Assume that the above loop ends close enough to the specified end point of this command
            *at = *this;
        }
    }
}

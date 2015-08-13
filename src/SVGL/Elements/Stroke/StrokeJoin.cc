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

#include "StrokeJoin.hh"
#include <SVGL/Types/Consts.hh>

#include <cmath>
#include <iostream>

namespace SVGL
{
    namespace Stroke
    {
        void bufferJoin(Buffer::Polygon* output, Point a, Point b, const Styles::SVG* style, double tolerance)
        {
            if (output->back().size() > 2)
            {
                switch (style->getStrokeLineJoin())
                {
                default:
                case Styles::LJ_MITER:
                    bufferMiterJoin(output, a, b, style, tolerance);
                    break;
                case Styles::LJ_ROUND:
                    bufferRoundJoin(output, a, b, style, tolerance);
                    break;
                case Styles::LJ_BEVEL:
                    bufferBevelJoin(output, a, b, style, tolerance);
                    break;
                }
            }
            else
            {
                Point c(0.5 * (a + b));
                Point d(0.5 * (a - b));
                Point e(c + 2 * d);
                Point f(c - 2 * d);

                output->pushPoint(a);
                output->pushPoint(b);
                //output->pushPoint(e);
                //output->pushPoint(f);
            }
        }

        void bufferMiterJoin(Buffer::Polygon* output, Point a, Point b, const Styles::SVG* style, double tolerance)
        {
            double strokeWidth(style->getStrokeWidth());
            Point y(output->getSecondLastPoint());
            Point z(output->getLastPoint());
            Point zy(z - y);
            Point zyNorm(zy.normal());
            Point ba(b - a);
            Point baNorm(ba.normal());

            double angle(baNorm.angle(&zyNorm));

            angle = angle / 2;
            double miter(tan(angle) * strokeWidth);

            Point m(y + miter * zyNorm);
            Point n(z - miter * zyNorm);

            Point c(0.5 * (m + n));
            Point q(c + 3 * (m - c));
            Point r(c + 3 * (n - c));


            output->pushPoint(m);
            output->pushPoint(n);
            //output->pushPoint(q);
            //output->pushPoint(r);
            output->pushPoint(a);
            output->pushPoint(b);
        }

        void bufferRoundJoin(Buffer::Polygon* output, Point a, Point b, const Styles::SVG* style, double tolerance)
        {
            //double strokeWidth = style->getStrokeWidth();
            
            output->pushPoint(a);
            output->pushPoint(b);
        }

        void bufferBevelJoin(Buffer::Polygon* output, Point a, Point b, const Styles::SVG* style, double tolerance)
        {
            //double strokeWidth = style->getStrokeWidth();
            
            output->pushPoint(a);
            output->pushPoint(b);
        }
    }
}

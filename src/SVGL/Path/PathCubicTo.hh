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

#include "PathCommand.hh"

namespace SVGL
{
    namespace PathCommand
    {
        class CubicTo : public Command
        {
        public:
            Point p1, p2;

            inline CubicTo(double _p1x, double _p1y, double _p2x, double _p2y, double _x, double _y) :
                Command(_x, _y),
                p1(_p1x, _p1y),
                p2(_p2x, _p2y)
            {

            }

            inline CubicTo(Point _p1, Point _p2, Point _pend) :
                Command(_pend),
                p1(_p1),
                p2(_p2)
            {

            }

            void buffer(Stroker* stroker) const override;
        };
    }
}

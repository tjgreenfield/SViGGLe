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

#include "PathCommandsCommand.hh"
#include "Buffer/PathCommandsPolygon.hh"

namespace SVGL
{
    namespace PathCommands
    {
        class MoveTo : public Command
        {
        public:
            inline MoveTo() :
                Command(Point(0, 0))
            {}

            inline MoveTo(Point _p) :
                Command(_p)
            {}

            MoveTo(double _x, double _y) :
                Command(_x, _y)
            {}

            void buffer(Stroker* stroker) const override;

            void calculateBoundingBox(BoundingBox* boundingBox) override;
        };
    }
}

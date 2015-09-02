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

#include "Buffer/PathCommandsPolygon.hh"
#include "Buffer/PathCommandsStroker.hh"

#include <SVGL/Types/Point.hh>


#include <memory>

namespace SVGL
{
    namespace PathCommands
    {

        class Command : public Point
        {
        public:
            virtual ~Command() = default;

            inline Command(Point _p) :
                Point(_p)
            {

            }

            inline Command(double _x, double _y) :
                Point(_x, _y)
            {

            }

            virtual void buffer(Stroker* state) const = 0;
        };

        typedef std::unique_ptr<Command> Command_uptr;
    }
}

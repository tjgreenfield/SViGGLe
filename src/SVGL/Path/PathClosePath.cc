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

#include "PathClosePath.hh"
#include <SVGL/Stroke/StrokeJoin.hh>
#include <SVGL/Stroke/StrokeDash.hh>

namespace SVGL
{
    namespace PathCommand
    {
        void ClosePath::buffer(Buffer::BufferingState* state) const
        {
            Point first(state->pointBuffer.getFirstPoint());
            Point dir(state->pointBuffer.getDir());

            // fill
            state->pointBuffer.pushPoint(&first);

            Stroke::bufferJoin(state, first);

            Stroke::bufferDash(state, first);
            // closing join
            Stroke::bufferJoin(state, first + dir);
        }
    }
}

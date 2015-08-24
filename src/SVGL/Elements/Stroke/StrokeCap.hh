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

#include <SVGL/Buffer/BufferingState.hh>
#include <SVGL/Types/Point.hh>

namespace SVGL
{
    namespace Stroke
    {
        void bufferStartCap(Buffer::BufferingState* state, const Point& dir);

        void bufferEndCap(Buffer::BufferingState* state);

        void bufferCap(Buffer::BufferingState* state, const Point& dir);

        void bufferStartCapSquare(Buffer::BufferingState* state, const Point& dir);

        void bufferEndCapSquare(Buffer::BufferingState* state, const Point& dir);

        void bufferStartCapRound(Buffer::BufferingState* state, const Point& dir);

        void bufferEndCapRound(Buffer::BufferingState* state, const Point& dir);
    }
}

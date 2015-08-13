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

#include "PathMoveTo.hh"

namespace SVGL
{
    namespace PathCommand
    {
        void MoveTo::buffer(Buffer::Polygon* pointBuffer, double tolerance) const
        {
            pointBuffer->newSet();
            pointBuffer->pushPoint(this);
        }

        void MoveTo::bufferStroke(Buffer::Polygon* strokeBuffer, Point* at, Styles::SVG* style, double tolerance) const
        {
            // TODO Line caps
            // Stroke::bufferEndCap(...)
            strokeBuffer->newSet();
            *at = *this;
            // Stroke::bufferStartCap(...)
        }
    }
}

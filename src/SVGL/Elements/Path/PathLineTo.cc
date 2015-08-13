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

#include "PathLineTo.hh"

namespace SVGL
{
    namespace PathCommand
    {
        void LineTo::buffer(Buffer::Polygon* pointBuffer, double tolerance) const
        {
            pointBuffer->pushPoint(this);
        }

        void LineTo::bufferStroke(Buffer::Polygon* strokeBuffer, Point* at, Styles::SVG* style, double tolerance) const
        {
            double strokeWidth = style->getStrokeWidth();
            Point offset = strokeWidth * at->normal(this);

            Point a(*at + offset);
            Point b(*at - offset);

            Stroke::bufferJoin(strokeBuffer, a, b, style, tolerance);

            const Styles::DashArray* dashArray = style->getStrokeDashArray();

            if (dashArray)
            {
                unsigned int dashIndex(0);
                Point relative(*this - *at);
                double length(relative.length());
                Point direction(relative.normalise());


                while (length > 0)
                {
                    // On dash
                    if (length > (*dashArray)[dashIndex])
                    {
                        *at += (*dashArray)[dashIndex] * direction;
                        strokeBuffer->pushPoint(*at + offset);
                        strokeBuffer->pushPoint(*at - offset);
                        length -= (*dashArray)[dashIndex];
                        dashIndex = (dashIndex + 1) % dashArray->size();
                    }
                    else
                    {
                        *at = *this;
                        strokeBuffer->pushPoint(*at + offset);
                        strokeBuffer->pushPoint(*at - offset);
                        break;
                    }
                    // Off dash
                    if (length > (*dashArray)[dashIndex])
                    {
                        *at += (*dashArray)[dashIndex] * direction;
                        strokeBuffer->newSet();
                        strokeBuffer->pushPoint(*at + offset);
                        strokeBuffer->pushPoint(*at - offset);
                        length -= (*dashArray)[dashIndex];
                        dashIndex = (dashIndex + 1) % dashArray->size();
                    }
                    else
                    {
                        strokeBuffer->newSet();
                        break;
                    }
                }
            }
            else
            {
                strokeBuffer->pushPoint(*this + offset);
                strokeBuffer->pushPoint(*this - offset);
            }
            *at = *this;
        }
    }
}

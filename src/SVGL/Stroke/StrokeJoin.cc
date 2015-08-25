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

#include "StrokeJoin.hh"
#include "StrokeCap.hh"
#include <SVGL/Types/Consts.hh>

#include <cmath>
#include <algorithm>

namespace SVGL
{
    namespace Stroke
    {
        void bufferJoin(Buffer::BufferingState* state, const Point& to)
        {
            if ((state->dashIndex & 0x01) == 1)
            {
                // don't do a join if we're in between dashes
                return;
            }
            // no movement, no join
            if (state->at == to)
            {
                return;
            }

            double strokeWidth = state->style->getStrokeWidth();
            Point delta(to - state->at);
            Point offset(strokeWidth * delta.normal());

            if (state->strokeBuffer.back().size() > 2)
            {
                switch (state->style->getStrokeLineJoin())
                {
                default:
                case Styles::LJ_MITER:
                    bufferMiterJoin(state, offset, strokeWidth);
                    break;
                case Styles::LJ_ROUND:
                    bufferRoundJoin(state, offset, strokeWidth);
                    break;
                case Styles::LJ_BEVEL:
                    bufferBevelJoin(state, offset);
                    break;
                }
            }
            else
            {
                bufferStartCap(state, delta);
                bufferBevelJoin(state, offset);
            }
        }

        void bufferMiterJoin(Buffer::BufferingState* state, const Point& offset, double strokeWidth)
        {
            /*
             *           a---------->
             *
             *        y  c  z
             *        |     |
             *        |  b--+------->
             *        |     |
             */

            double strokeMiterLimit(state->style->getStrokeMiterLimit());
            Point a(state->at + offset);
            Point b(state->at - offset);
            Point y(state->strokeBuffer.getSecondLastPoint());
            Point z(state->strokeBuffer.getLastPoint());
            Point zy(z - y);
            Point zyNorm(zy.normal());
            Point ba(b - a);
            Point baNorm(ba.normal());

            double angle(baNorm.angle(&zyNorm));

            angle = angle / 2;
            // TODO: this isn't the correct comparision for strokeMiterLimit
            double miter(std::min(tan(angle), strokeMiterLimit) * strokeWidth);

            Point m(y + miter * zyNorm);
            Point n(z - miter * zyNorm);

            state->strokeBuffer.pushPoint(m);
            state->strokeBuffer.pushPoint(n);

            state->strokeBuffer.pushPoint(a);
            state->strokeBuffer.pushPoint(b);
        }

        void bufferRoundJoin(Buffer::BufferingState* state, const Point& offset, double strokeWidth)
        {
            /*
             *           a---------->
             *
             *        y  c  z
             *        |     |
             *        |  b--+------->
             *        |     |
             */
            Point a(state->at + offset);
            Point b(state->at - offset);
            Point y(state->strokeBuffer.getSecondLastPoint());

            Point cy(y - state->at);
            Point u(1, 0);

            Point ca(a - state->at);

            double t0(u.angle(&cy));
            double dt = cy.angle(&ca);

            // this might need adjusting
            int vertexCount = std::max(abs(strokeWidth * dt / state->tolerance), 2);

            for (int i = 0; i <= vertexCount; ++i)
            {
                double t = t0 + (((double)i) / ((double)vertexCount)) * dt;
                double sint = sin(t);
                double cost = cos(t);
                Point m(state->at.x + cost * strokeWidth, state->at.y + sint * strokeWidth);
                Point n(state->at.x - cost * strokeWidth, state->at.y - sint * strokeWidth);
                state->strokeBuffer.pushPoint(m);
                state->strokeBuffer.pushPoint(n);
            }
            state->strokeBuffer.pushPoint(a);
            state->strokeBuffer.pushPoint(b);
        }

        void bufferBevelJoin(Buffer::BufferingState* state, const Point& offset)
        {

            /*
             *           a---------->
             *
             *        y  c  z
             *        |     |
             *        |  b--+------->
             *        |     |
             */
            Point a(state->at + offset);
            Point b(state->at - offset);

            state->strokeBuffer.pushPoint(a);
            state->strokeBuffer.pushPoint(b);
        }
    }
}

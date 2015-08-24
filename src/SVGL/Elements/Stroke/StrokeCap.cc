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

#include "StrokeCap.hh"
#include <SVGL/Types/Consts.hh>

namespace SVGL
{
    namespace Stroke
    {
        void bufferStartCap(Buffer::BufferingState* state, const Point& dir)
        {
            switch (state->style->getStrokeLineCap())
            {
            case Styles::LC_BUTT:
                break;
            case Styles::LC_ROUND:
                bufferStartCapRound(state, dir);
                break;
            case Styles::LC_SQUARE:
                bufferStartCapSquare(state, dir);
                break;
            }
        }

        void bufferEndCap(Buffer::BufferingState* state)
        {
            Point y(state->pointBuffer.getSecondLastPoint());
            Point dir(state->at - y);

            switch (state->style->getStrokeLineCap())
            {
            case Styles::LC_BUTT:
                break;
            case Styles::LC_ROUND:
                bufferEndCapRound(state, dir);
                break;
            case Styles::LC_SQUARE:
                bufferEndCapSquare(state, dir);
                break;
            }
        }

        void bufferStartCapSquare(Buffer::BufferingState* state, const Point& dir)
        {
            double strokeWidth = state->style->getStrokeWidth();
            Point step(-strokeWidth * dir.normalise());
            Point offset(strokeWidth * dir.normal());
            Point centre(state->at + step);

            Point m(centre + offset);
            Point n(centre - offset);

            state->strokeBuffer.pushPoint(m);
            state->strokeBuffer.pushPoint(n);
        }

        void bufferEndCapSquare(Buffer::BufferingState* state, const Point& dir)
        {
            double strokeWidth = state->style->getStrokeWidth();
            Point step(strokeWidth * dir.normalise());
            Point offset(strokeWidth * dir.normal());
            Point centre(state->at + step);

            Point m(centre + offset);
            Point n(centre - offset);

            state->strokeBuffer.pushPoint(m);
            state->strokeBuffer.pushPoint(n);
        }

        void bufferStartCapRound(Buffer::BufferingState* state, const Point& dir)
        {
            double strokeWidth = state->style->getStrokeWidth();

            // this might need adjusting
            int vertexCount = std::max(abs(int(4 * strokeWidth / state->tolerance)), 2);

            Point step(-strokeWidth * dir.normalise());
            Point offset(strokeWidth * dir.normal());

            for (int i = vertexCount; i >= 0; --i)
            {
                double t = ((double)i) / ((double)vertexCount) * PI / 2;
                double cost = cos(t);
                double sint = sin(t);

                Point m(state->at + (cost * offset) + (sint * step));
                Point n(state->at - (cost * offset) + (sint * step));

                state->strokeBuffer.pushPoint(m);
                state->strokeBuffer.pushPoint(n);
            }
        }

        void bufferEndCapRound(Buffer::BufferingState* state, const Point& dir)
        {
            double strokeWidth = state->style->getStrokeWidth();

            // this might need adjusting
            int vertexCount = std::max(abs(int(4 * strokeWidth / state->tolerance)), 2);

            Point step(strokeWidth * dir.normalise());
            Point offset(strokeWidth * dir.normal());

            for (int i = 0; i <= vertexCount; ++i)
            {
                double t = ((double)i) / ((double)vertexCount) * PI / 2;
                double cost = cos(t);
                double sint = sin(t);

                Point m(state->at + (cost * offset) + (sint * step));
                Point n(state->at - (cost * offset) + (sint * step));

                state->strokeBuffer.pushPoint(m);
                state->strokeBuffer.pushPoint(n);
            }
        }
    }
}





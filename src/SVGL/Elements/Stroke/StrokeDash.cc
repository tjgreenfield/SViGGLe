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

#include "StrokeDash.hh"
#include "StrokeCap.hh"

namespace SVGL
{
    namespace Stroke
    {
        void bufferDash(Buffer::BufferingState* state, const Point& to)
        {
            Point delta(to - state->at);
            double strokeWidth = state->style->getStrokeWidth();
            Point offset = strokeWidth * delta.normal();

            if (!state->dashArray)
            {
                // if there is no dash array, just add the end points
                Point end(state->at + delta);
                state->strokeBuffer.pushPoint(end + offset);
                state->strokeBuffer.pushPoint(end - offset);
                state->at = end;
                return;
            }
            Point direction(delta.normalise());
            double remaining(delta.length());

            while (remaining > 0)
            {
                double dashRemaining = (*state->dashArray)[state->dashIndex] - state->dashDistance;

                if ((state->dashIndex & 0x01) == 0)
                {
                    // on dash
                    if (remaining > dashRemaining)
                    {
                        // stroke the remaining dash length, move to the next dash index
                        state->at += dashRemaining * direction;
                        state->strokeBuffer.pushPoint(state->at + offset);
                        state->strokeBuffer.pushPoint(state->at - offset);
                        Stroke::bufferEndCap(state);
                        state->dashIndex = (state->dashIndex + 1) % state->dashArray->size();
                        state->dashDistance = 0;
                        remaining -= dashRemaining;
                    }
                    else
                    {
                        // stroke the remaining line length, break as we're done
                        state->at += remaining * direction;
                        state->strokeBuffer.pushPoint(state->at + offset);
                        state->strokeBuffer.pushPoint(state->at - offset);
                        state->dashDistance += remaining;
                        break; // remaining = 0
                    }
                }
                else
                {
                    // off dash
                    if (remaining > dashRemaining)
                    {
                        // start a new stroke at the end of the remaining dash length, move to the next dash index
                        state->strokeBuffer.newSet();
                        state->at += dashRemaining * direction;
                        Stroke::bufferStartCap(state, direction);
                        state->strokeBuffer.pushPoint(state->at + offset);
                        state->strokeBuffer.pushPoint(state->at - offset);
                        state->dashIndex = (state->dashIndex + 1) % state->dashArray->size();
                        state->dashDistance = 0;
                        remaining -= dashRemaining;
                    }
                    else
                    {
                        // skip the remaining line length, break as we're done
                        state->at += remaining * direction;
                        state->dashDistance += remaining;
                        break; // remaining = 0
                    }
                }
            }
        }
    }
}



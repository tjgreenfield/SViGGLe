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

#include "FontGlyph.hh"

namespace SVGL
{
    namespace Font
    {
        Glyph::Glyph(FT_Outline outline, double _advance) :
            advance(_advance)
        {
            int p1x, p1y, p2x, p2y, x, y, startX, startY, startP1x, startP1y, startP2x, startP2y;
            int tag, prevTag = FT_CURVE_TAG_ON, startTag = FT_CURVE_TAG_ON;
            int point = 0;

            for (int contour = 0; contour < outline.n_contours; ++contour)
            {
                bool firstPointInContour = true;
                while (point <= outline.contours[contour])
                {
                    x = outline.points[point].x;
                    y = outline.points[point].y;
                    tag = FT_CURVE_TAG(outline.tags[point]);

                    if (firstPointInContour)
                    {
                        startTag = tag;
                        switch (tag)
                        {
                        case FT_CURVE_TAG_CONIC:
                            startP1x = x;
                            startP1y = y;
                            break;
                        case FT_CURVE_TAG_CUBIC: // Invalid?
                            if (prevTag == FT_CURVE_TAG_CUBIC)
                            {
                                startP2x = x;
                                startP2y = y;
                            }
                            else
                            {
                                startP1x = x;
                                startP1y = y;
                            }
                            break;
                        case FT_CURVE_TAG_ON:
                        default:
                            commandSet.emplace_back(new PathCommand::MoveTo(x, y));
                            startX = x;
                            startY = y;
                            firstPointInContour = false;
                            break;
                        }
                    }
                    else
                    {
                        switch (tag)
                        {
                        case FT_CURVE_TAG_CONIC:
                            if (prevTag == FT_CURVE_TAG_CONIC)
                            {
                                commandSet.emplace_back(new PathCommand::CubicTo(p1x, p1y, p1x, p1y, (x + p1x) >> 1, (y + p1y) >> 1));
                                p1x = x;
                                p1y = y;
                            }
                            else //(prevTag == FT_CURVE_TAG_ON)
                            {
                                p1x = x;
                                p1y = y;
                            }
                            break;
                        case FT_CURVE_TAG_CUBIC:
                            if (prevTag == FT_CURVE_TAG_CUBIC)
                            {
                                p2x = x;
                                p2y = y;
                            }
                            else //(prevTag == FT_CURVE_TAG_ON)
                            {
                                p1x = x;
                                p1y = y;
                            }
                            break;
                        case FT_CURVE_TAG_ON:
                        default:
                            if (prevTag == FT_CURVE_TAG_ON)
                            {
                                commandSet.emplace_back(new PathCommand::LineTo(x, y));
                            }
                            else if (prevTag == FT_CURVE_TAG_CONIC)
                            {
                                commandSet.emplace_back(new PathCommand::CubicTo(p1x, p1y, p1x, p1y, x, y));
                            }
                            else if (prevTag == FT_CURVE_TAG_CUBIC)
                            {
                                commandSet.emplace_back(new PathCommand::CubicTo(p1x, p1y, p2x, p2y, x, y));
                            }
                            break;
                        }
                    }
                    prevTag = tag;
                    ++point;
                }
                if (prevTag == FT_CURVE_TAG_ON)
                {
                    if (startTag == FT_CURVE_TAG_ON)
                    {
                        commandSet.emplace_back(new PathCommand::ClosePath());
                    }
                    else // startTag == FT_CURVE_TAG_CONIC
                    {
                        commandSet.emplace_back(new PathCommand::CubicTo(startP1x, startP1y, startP2x, startP2y, startX, startY));
                    }
                    // shouldn't be any conic ones
                }
                else if (prevTag == FT_CURVE_TAG_CONIC)
                {
                    commandSet.emplace_back(new PathCommand::CubicTo(p1x, p1y, p1x, p1y, startX, startY));
                }
                else if (prevTag == FT_CURVE_TAG_CUBIC)
                {
                    commandSet.emplace_back(new PathCommand::CubicTo(p1x, p1y, p2x, p2y, startX, startY));
                }
                prevTag = FT_CURVE_TAG_ON;
            }
        }

        const PathCommand::CommandSet& Glyph::getCommandSet() const
        {
            return commandSet;
        }

        double Glyph::getAdvance() const
        {
            return advance;
        }
    }
}

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

#include <SVGL/Types/KeywordMapper.hh>

#include <unordered_map>
#include <vector>
#include <string>

namespace SVGL
{
    namespace CSS
    {
        namespace Property
        {
            enum Index
            {
                ERROR = 0,

                // Graphic
                COLOR,
                CURSOR,
                DISPLAY,
                CLIP_RULE,
                CLIP_PATH,
                MASK,
                OPACITY,
                FILTER,
                POINTER_EVENTS,
                COLOR_INTERPOLATION,
                COLOR_RENDERING,

                // Vector
                FILL,
                FILL_RULE,
                FILL_OPACITY,
                STROKE,
                STROKE_DASHARRAY,
                STROKE_DASHOFFSET,
                STROKE_LINECAP,
                STROKE_LINEJOIN,
                STROKE_MITERLIMIT,
                STROKE_OPACITY,
                STROKE_WIDTH,

                // Shape
                MARKER,
                MARKER_START,
                MARKER_MID,
                MARKER_END,
                SHAPE_RENDERING,

                // Image
                COLOR_PROFILE,
                IMAGE_RENDERING,

                // Text
                FONT,
                FONT_FAMILY,
                FONT_SIZE,
                FONT_SIZE_ADJUST,
                FONT_STRETCH,
                FONT_STYLE,
                FONT_VARIANT,
                FONT_WEIGHT,
                DIRECTION,
                LETTER_SPACING,
                TEXT_DECORATION,
                UNICODE_BIDI,
                WORD_SPACING,
                ALIGNMENT_BASELINE,
                BASELINE_SHIFT,
                DOMINANT_BASELINE,
                GLYPH_ORIENTATION_HORIZONTAL,
                GLYPH_ORIENTATION_VERTICAL,
                KERNING,
                TEXT_ANCHOR,
                WRITING_MODE,
                TEXT_RENDERING,

                // viewport
                CLIP,
                OVERFLOW,

                // filter
                ENABLE_BACKGROUND,
                COLOR_INTERPOLATION_FILTERS,

                // feFlood
                FLOOD_COLOR,
                FLOOD_OPACITY,

                // lighting
                LIGHTING_COLOR,

                // gradient
                STOP_COLOR,
                STOP_OPACITY,

                PROPERTY_COUNT
            };
        }

        typedef KeywordMapper<Property::Index> PropertyMap;

        namespace Property
        {
            extern PropertyMap map;
        }

    }
}

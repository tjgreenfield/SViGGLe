
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

#include "CSSProperty.hh"

namespace SVGL
{
    namespace CSS
    {
        namespace Property
        {

            PropertyMap map({
                {"color", COLOR},
                {"cursor", CURSOR},
                {"display", DISPLAY},
                {"clip-rule", CLIP_RULE},
                {"clip-mask", CLIP_PATH},
                {"mask", MASK},
                {"opacity", OPACITY},
                {"filter", FILTER},
                {"pointer-events", POINTER_EVENTS},
                {"color-interpolation", COLOR_INTERPOLATION},
                {"color-rendering", COLOR_RENDERING},

                // Vector
                {"fill", FILL},
                {"fill-rule", FILL_RULE},
                {"fill-opacity", FILL_OPACITY},
                {"stroke", STROKE},
                {"stroke-dasharray", STROKE_DASHARRAY},
                {"stroke-dashoffset", STROKE_DASHOFFSET},
                {"stroke-linecap", STROKE_LINECAP},
                {"stroke-linejoin", STROKE_LINEJOIN},
                {"stroke-miterlimit", STROKE_MITERLIMIT},
                {"stroke-opacity", STROKE_OPACITY},
                {"stroke-width", STROKE_WIDTH},

                // Shape
                {"marker", MARKER},
                {"marker-start", MARKER_START},
                {"marker-mid", MARKER_MID},
                {"marker-end", MARKER_END},
                {"shape-rendering", SHAPE_RENDERING},

                // Image
                {"color-profile", COLOR_PROFILE},
                {"image-rendering", IMAGE_RENDERING},

                // Text
                {"font", FONT},
                {"font-family", FONT_FAMILY},
                {"font-size", FONT_SIZE},
                {"font-size-adjust", FONT_SIZE_ADJUST},
                {"font-stretch", FONT_STRETCH},
                {"font-style", FONT_STYLE},
                {"font-variant", FONT_VARIANT},
                {"font-weight", FONT_WEIGHT},
                {"direction", DIRECTION},
                {"letter-spacing", LETTER_SPACING},
                {"text-direction", TEXT_DECORATION},
                {"unicode-bidi", UNICODE_BIDI},
                {"word-spacing", WORD_SPACING},
                {"alignment-baseline", ALIGNMENT_BASELINE},
                {"baseline-shift", BASELINE_SHIFT},
                {"dominant-baseline", DOMINANT_BASELINE},
                {"glyph-orientation-horizontal", GLYPH_ORIENTATION_HORIZONTAL},
                {"glyph-orientation-vertical", GLYPH_ORIENTATION_VERTICAL},
                {"kerning", KERNING},
                {"text-anchor", TEXT_ANCHOR},
                {"writing-mode", WRITING_MODE},
                {"text-rendering", TEXT_RENDERING},

                // viewport
                {"clip", CLIP},
                {"overflow", OVERFLOW},

                // filter
                {"enable-background", ENABLE_BACKGROUND},

                // feFlood
                {"flood-color", FLOOD_COLOR},
                {"flood-opacity", FLOOD_OPACITY},

                // lighting
                {"lighting-color", LIGHTING_COLOR},

                // gradient
                {"stop-clor", STOP_COLOR},
                {"stop-opacity", STOP_OPACITY},
            });
        }
    }
}

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

#pragma once

#include "StyleTypes.hh"
#include "StyleSVG.hh"
#include <SVGL/CSS/CSS.hh>

#include <bitset>
#include <unordered_map>

namespace SVGL
{
    namespace Styles
    {
        class Text : public Vector
        {
        public:
            class TextInherit
            {
            public:
                enum {
                    // Text (21)
                    FONT, // can overlapp with shape & image
                    FONT_FAMILY,
                    FONT_SIZE,
                    FONT_SIZE_ADJUST,
                    FONT_STRETCH,
                    FONT_VARIANT,
                    FONT_WEIGHT,
                    DIRECTION,
                    LETTER_SPACING,
                    TEXT_DECORATION,
                    UNICODE_BIDI,
                    WORD_SPACING,

                    ALAIGNMENT_BASELINE,
                    BASELINE_SHIFT,
                    DOMINATE_BASELINE,
                    GLYPH_ORIENTATION_HORIZONTAL,
                    GLYPH_ORIENTATION_VERTICAL,
                    KERNING,
                    TEXT_ANCHOR,
                    WRITING_MODE,
                    TEXT_RENDERING
                };
            };

            std::bitset<32> textFlags;
            /*
            Font properties :
            ‘font’
            ‘font - family’
            ‘font - size’
            ‘font - size - adjust’
            ‘font - stretch’
            ‘font - style’
            ‘font - variant’
            ‘font - weight’
            Text properties :
            ‘direction’
            ‘letter - spacing’
            ‘text - decoration’
            ‘unicode - bidi’
            ‘word - spacing’

            SVG Text:
            ‘alignment-baseline’
            ‘baseline-shift’
            ‘dominant-baseline’
            ‘glyph-orientation-horizontal’
            ‘glyph-orientation-vertical’
            ‘kerning’
            ‘text-anchor’
            ‘writing-mode’

            ‘text-rendering’
            */
        };
    }
}

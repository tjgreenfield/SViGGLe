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

#include "StyleVector.hh"



namespace SVGL
{
    namespace Styles
    {
        class Text : public Vector
        {

        public:
            unsigned int textBits;

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
            */
            std::vector<std::string> fontFamilies;
            double fontSize;

            BITRANGE_IMPL(hasFontSizeAdjust, bits, 19, 1);
            double fontSizeAdjust;

            // Note: this enum must be kept in order
            struct FontStretch {enum {
                ULTRA_CONDENSED = 0,
                EXTRA_CONDENSED,
                CONDENSED,
                SEMI_CONDENSED,
                NORMAL,
                SEMI_EXPANDED,
                EXPANDED,
                EXTRA_EXPANDED,
                ULTRA_EXPANDED,
                WIDER,
                NARROWER
            };};
            BITRANGE_IMPL(fontStretch, bits, 20, 4);

            struct FontStyle { enum {
                NORMAL,
                ITALIC,
                OBLIQUE
            };};
            BITRANGE_IMPL(fontStyle, bits, 24, 2);

            struct FontVariant { enum {
                NORMAL,
                SMALLCAPS,
            };};
            BITRANGE_IMPL(fontVariant, bits, 26, 1);

            struct FontWeight { enum {
                NORMAL,
                BOLD,
                BOLDER,
                LIGHTER,
                _100,
                _200,
                _300,
                _400,
                _500,
                _600,
                _700,
                _800,
                _900
            };};
            BITRANGE_IMPL(fontWeight, bits, 27, 4);

            /*
            Text properties :
            ‘direction’
            ‘letter - spacing’
            ‘text - decoration’
            ‘unicode - bidi’
            ‘word - spacing’
            */
            struct Direction {enum {
                LTR,
                RTL
            };};
            BITRANGE_IMPL(direction, bits, 31, 1);

            BITRANGE_IMPL(normalLetterSpacing, textBits, 0, 1);
            double letterSpacing;

            struct TextDecoration {enum {
                NONE,
                UNDERLINE = (1 << 0),
                OVERLINE = (1 << 1),
                LINE_THROUGH = (1 << 2),
                BLINK = (1 << 3)
            };};
            BITRANGE_IMPL(textDecoration, textBits, 1, 4);

            struct UnicodeBidi {enum {
                NORMAL,
                EMBED,
                BIDI_OVERRIDE
            };};
            BITRANGE_IMPL(unicodeBidi, textBits, 5, 2);

            BITRANGE_IMPL(normalWordSpacing, textBits, 7, 1);
            double wordSpacing;

            /*
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
            struct AlignmentBaseline {enum {
                AUTO,
                BASELINE,
                BEFORE_EDGE,
                TEXT_BEFORE_EDGE,
                MIDDLE,
                CENTRAL,
                AFTER_EDGE,
                TEXT_AFTER_EDGE,
                IDEOGRAPHIC,
                ALPHABETIC,
                HANGING,
                MATHEMATICAL
            };};
            BITRANGE_IMPL(alignmentBaseline, textBits, 8, 4);

            struct BaselineShift {enum {
                BASELINE,
                SUB,
                SUPER,
                VALUE
            };};
            BITRANGE_IMPL(baselineShift, textBits, 12, 2);

            double baselineShiftValue;

            struct DominantBaseline {enum {
                AUTO,
                USE_SCRIPT,
                NO_CHANGE,
                RESET_SIZE,
                TEXT_BEFORE_EDGE,
                CENTRAL,
                MIDDLE,
                IDEOGRAPHIC,
                TEXT_AFTER_EDGE,
                ALPHABETIC,
                HANGING,
                MATHEMATICAL,

            };};
            BITRANGE_IMPL(dominantBaseline, textBits, 14, 4);

            struct GlyphOrientation {enum {
                AUTO,
                _0,
                _90,
                _180,
                _270
            };};
            BITRANGE_IMPL(glyphOrientationHorizontal, textBits, 18, 3);
            BITRANGE_IMPL(glyphOrientationVertical, textBits, 21, 3);

            BITRANGE_IMPL(autoKerning, textBits, 24, 1);
            double kerning;

            struct TextAnchor {enum {
                START,
                MIDDLE,
                END
            };};
            BITRANGE_IMPL(textAnchor, textBits, 25, 2);

            struct WritingMode {enum {
                LR_TB,
                RL_TB,
                TB_RL,
                LR,
                RL,
                TB
            };};
            BITRANGE_IMPL(writingMode, textBits, 27, 3);

            struct TextRendering {enum {
                AUTO,
                OPTIMIZE_SPEED,
                OPTIMIZE_LEGIBILITY,
                GEOMETRIC_PRECISION
            };};
            BITRANGE_IMPL(textRendering, textBits, 30, 2);

            void applyPropertySet(const CSS::PropertySet& propertySet, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) override;

            void updateSizeContext(CSS::SizeContext* sizeContext) override;
        };
    }
}


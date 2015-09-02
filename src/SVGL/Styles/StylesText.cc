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

#include "StylesText.hh"


#include <SVGL/Fonts/FontsCollection.hh>

namespace SVGL
{
    namespace Styles
    {
        void Text::applyPropertySet(const CSS::PropertySet& propertySet, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext)
        {
            using namespace CSS;
            using namespace CSS::Property;
            constexpr auto keywordFromValue = &Keyword::keywordFromValue;

            // font-family
            fontFamilies.clear();
            if (auto list = dynamic_cast<const CSS::ValueList*>(propertySet[Property::FONT_FAMILY]))
            {
                fontFamilies.reserve(list->vector.size());
                for (const CSS::Value_uptr& value : list->vector)
                {
                    if (auto str = dynamic_cast<const CSS::String*>(value.get()))
                    {
                        fontFamilies.push_back(str->str);
                    }
                    else if (auto ident = dynamic_cast<const CSS::Ident*>(value.get()))
                    {
                        fontFamilies.push_back(ident->ident);
                    }
                }
            }
            else if (auto str = dynamic_cast<const CSS::String*>(propertySet[Property::FONT_FAMILY]))
            {
                fontFamilies.push_back(str->str);
            }
            else if (auto ident = dynamic_cast<const CSS::Ident*>(propertySet[Property::FONT_FAMILY]))
            {
                fontFamilies.push_back(ident->ident);
            }
            else
            {
                fontFamilies.push_back("courier");
            }

            // font-size
            if (auto dimension = dynamic_cast<const CSS::Dimension*>(propertySet[Property::FONT_SIZE]))
            {
                fontSize = dimension->calculate(sizeContext);
            }
            else
            {
                switch (keywordFromValue(propertySet[Property::FONT_SIZE]))
                {
                default:
                    fontSize = 10;
                    break;
                case Keyword::XX_SMALL:
                    fontSize = 6;
                    break;
                case Keyword::X_SMALL:
                    fontSize = 7;
                    break;
                case Keyword::SMALL:
                    fontSize = 8;
                    break;
                case Keyword::MEDIUM:
                    fontSize = 10;
                    break;
                case Keyword::LARGE:
                    fontSize = 12;
                    break;
                case Keyword::X_LARGE:
                    fontSize = 14;
                    break;
                case Keyword::XX_LARGE:
                    fontSize = 17;
                    break;
                case Keyword::LARGER:
                    fontSize = sizeContext.fontSize * 1.2;
                    break;
                case Keyword::SMALLER:
                    fontSize = sizeContext.fontSize / 1.2;
                    break;
                }
            }

            // font-size-adjust
            if (auto dimension = dynamic_cast<const CSS::Dimension*>(propertySet[Property::FONT_SIZE_ADJUST]))
            {
                fontSizeAdjust = dimension->calculate(sizeContext);
                hasFontSizeAdjust() = 1;
            }
            else
            {
                fontSizeAdjust = 0.5;
                switch (keywordFromValue(propertySet[Property::FONT_SIZE_ADJUST]))
                {
                default:
                case Keyword::NONE:
                    hasFontSizeAdjust() = 0;
                    break;
                }
            }

            // ‘font - stretch’
            switch (keywordFromValue(propertySet[Property::FONT_STRETCH]))
            {
            default:
                fontStretch() = FontStretch::NORMAL;
                break;
            case Keyword::WIDER:
                fontStretch() = sizeContext.fontStretch < FontStretch::ULTRA_EXPANDED ? sizeContext.fontStretch + 1: FontStretch::ULTRA_EXPANDED;
                break;
            case Keyword::NARROWER:
                fontStretch() = sizeContext.fontStretch > FontStretch::ULTRA_CONDENSED ? sizeContext.fontStretch - 1: FontStretch::ULTRA_EXPANDED;
                break;
            case Keyword::ULTRA_CONDENSED:
                fontStretch() = FontStretch::ULTRA_CONDENSED;
                break;
            case Keyword::EXTRA_CONDENSED:
                fontStretch() = FontStretch::EXTRA_CONDENSED;
                break;
            case Keyword::CONDENSED:
                fontStretch() = FontStretch::CONDENSED;
                break;
            case Keyword::SEMI_CONDENSED:
                fontStretch() = FontStretch::SEMI_CONDENSED;
                break;
            case Keyword::NORMAL:
                fontStretch() = FontStretch::NORMAL;
                break;
            case Keyword::SEMI_EXPANDED:
                fontStretch() = FontStretch::SEMI_EXPANDED;
                break;
            case Keyword::EXPANDED:
                fontStretch() = FontStretch::EXPANDED;
                break;
            case Keyword::EXTRA_EXPANDED:
                fontStretch() = FontStretch::EXTRA_EXPANDED;
                break;
            case Keyword::ULTRA_EXPANDED:
                fontStretch() = FontStretch::ULTRA_EXPANDED;
                break;
            }

            // ‘font - style’
            switch (keywordFromValue(propertySet[Property::FONT_STYLE]))
            {
            default:
            case Keyword::NORMAL:
                fontStyle() = FontStyle::NORMAL;
                break;
            case Keyword::ITALIC:
                fontStyle() = FontStyle::ITALIC;
                break;
            case Keyword::OBLIQUE:
                fontStyle() = FontStyle::OBLIQUE;
                break;
            }

            // ‘font - variant’
            switch (keywordFromValue(propertySet[Property::FONT_VARIANT]))
            {
            default:
            case Keyword::NORMAL:
                fontVariant() = FontVariant::NORMAL;
                break;
            case Keyword::SMALLCAPS:
                fontVariant() = FontVariant::SMALLCAPS;
                break;
            }

            // ‘font - weight’
            if (auto dimension = dynamic_cast<const CSS::Dimension*>(propertySet[Property::FONT_WEIGHT]))
            {
                switch (((int)dimension->specified) / 100)
                {
                default:
                    fontVariant() = FontWeight::_400;
                    break;
                case 1:
                    fontVariant() = FontWeight::_100;
                    break;
                case 2:
                    fontVariant() = FontWeight::_200;
                    break;
                case 3:
                    fontVariant() = FontWeight::_300;
                    break;
                case 4:
                    fontVariant() = FontWeight::_400;
                    break;
                case 5:
                    fontVariant() = FontWeight::_500;
                    break;
                case 6:
                    fontVariant() = FontWeight::_600;
                    break;
                case 7:
                    fontVariant() = FontWeight::_700;
                    break;
                case 8:
                    fontVariant() = FontWeight::_800;
                    break;
                case 9:
                    fontVariant() = FontWeight::_900;
                    break;
                }
            }
            else
            {
                switch (keywordFromValue(propertySet[Property::FONT_WEIGHT]))
                {
                default:
                case Keyword::NORMAL:
                    fontVariant() = FontWeight::_400;
                    break;
                case Keyword::BOLD:
                    fontVariant() = FontWeight::_700;
                    break;
                case Keyword::BOLDER:
                    fontVariant() = sizeContext.fontWeight < FontWeight::_900 ? sizeContext.fontWeight + 1 : FontWeight::_900;
                    break;
                case Keyword::LIGHTER:
                    fontVariant() = sizeContext.fontWeight > FontWeight::_100 ? sizeContext.fontWeight - 1 : FontWeight::_100;
                    break;
                }
            }


            //‘direction’
            switch (keywordFromValue(propertySet[Property::DIRECTION]))
            {
            default:
            case Keyword::LTR:
                direction() = Direction::LTR;
                break;
            case Keyword::RTL:
                direction() = Direction::RTL;
                break;
            }

            //‘letter - spacing’
            if (auto dimension = dynamic_cast<const CSS::Dimension*>(propertySet[Property::LETTER_SPACING]))
            {
                letterSpacing = dimension->calculate(sizeContext);
                normalLetterSpacing() = 0;
            }
            else
            {
                letterSpacing = 0;
                switch (keywordFromValue(propertySet[Property::LETTER_SPACING]))
                {
                default:
                case Keyword::NORMAL:
                    normalLetterSpacing() = 1;
                    break;
                }
            }

            //‘text - decoration’
            if (auto list = dynamic_cast<const CSS::ValueList*>(propertySet[Property::TEXT_DECORATION]))
            {
                textDecoration() = 0;
                for (const CSS::Value_uptr& value : list->vector)
                {
                    switch (keywordFromValue(value.get()))
                    {
                    default:
                    case Keyword::NONE:
                        textDecoration() |= TextDecoration::NONE;
                        break;
                    case Keyword::UNDERLINE:
                        textDecoration() |= TextDecoration::UNDERLINE;
                        break;
                    case Keyword::OVERLINE:
                        textDecoration() |= TextDecoration::OVERLINE;
                        break;
                    case Keyword::LINE_THROUGH:
                        textDecoration() |= TextDecoration::LINE_THROUGH;
                        break;
                    case Keyword::BLINK:
                        textDecoration() |= TextDecoration::BLINK;
                        break;
                    }
                }
            }
            else
            {
                switch (keywordFromValue(propertySet[Property::TEXT_DECORATION]))
                {
                default:
                case Keyword::NONE:
                    textDecoration() = TextDecoration::NONE;
                    break;
                case Keyword::UNDERLINE:
                    textDecoration() = TextDecoration::UNDERLINE;
                    break;
                case Keyword::OVERLINE:
                    textDecoration() = TextDecoration::OVERLINE;
                    break;
                case Keyword::LINE_THROUGH:
                    textDecoration() = TextDecoration::LINE_THROUGH;
                    break;
                case Keyword::BLINK:
                    textDecoration() = TextDecoration::BLINK;
                    break;
                }
            }
            //‘unicode - bidi’
            switch (keywordFromValue(propertySet[Property::UNICODE_BIDI]))
            {
            default:
            case Keyword::NORMAL:
                unicodeBidi() = UnicodeBidi::NORMAL;
                break;
            case Keyword::EMBED:
                unicodeBidi() = UnicodeBidi::EMBED;
                break;
            case Keyword::BIDI_OVERRIDE:
                unicodeBidi() = UnicodeBidi::BIDI_OVERRIDE;
                break;
            }

            //‘word - spacing’
            if (auto dimension = dynamic_cast<const CSS::Dimension*>(propertySet[Property::WORD_SPACING]))
            {
                wordSpacing = dimension->calculate(sizeContext);
                normalWordSpacing() = 0;
            }
            else
            {
                wordSpacing = 0;
                switch (keywordFromValue(propertySet[Property::WORD_SPACING]))
                {
                default:
                case Keyword::NORMAL:
                    normalWordSpacing() = 1;
                    break;
                }
            }

            //‘alignment-baseline’
            switch (keywordFromValue(propertySet[Property::ALIGNMENT_BASELINE]))
            {
            default:
            case Keyword::AUTO:
                alignmentBaseline() = AlignmentBaseline::AUTO;
                break;
            case Keyword::BASELINE:
                alignmentBaseline() = AlignmentBaseline::BASELINE;
                break;
            case Keyword::BEFORE_EDGE:
                alignmentBaseline() = AlignmentBaseline::BEFORE_EDGE;
                break;
            case Keyword::TEXT_BEFORE_EDGE:
                alignmentBaseline() = AlignmentBaseline::TEXT_BEFORE_EDGE;
                break;
            case Keyword::MIDDLE:
                alignmentBaseline() = AlignmentBaseline::MIDDLE;
                break;
            case Keyword::CENTRAL:
                alignmentBaseline() = AlignmentBaseline::CENTRAL;
                break;
            case Keyword::AFTER_EDGE:
                alignmentBaseline() = AlignmentBaseline::AFTER_EDGE;
                break;
            case Keyword::TEXT_AFTER_EDGE:
                alignmentBaseline() = AlignmentBaseline::TEXT_AFTER_EDGE;
                break;
            case Keyword::IDEOGRAPHIC:
                alignmentBaseline() = AlignmentBaseline::IDEOGRAPHIC;
                break;
            case Keyword::ALPHABETIC:
                alignmentBaseline() = AlignmentBaseline::ALPHABETIC;
                break;
            case Keyword::HANGING:
                alignmentBaseline() = AlignmentBaseline::HANGING;
                break;
            case Keyword::MATHEMATICAL:
                alignmentBaseline() = AlignmentBaseline::MATHEMATICAL;
                break;
            }

            //‘baseline-shift’
            if (auto dimension = dynamic_cast<const CSS::Dimension*>(propertySet[Property::BASELINE_SHIFT]))
            {
                baselineShiftValue = dimension->calculate(sizeContext);
                baselineShift() = BaselineShift::VALUE;
            }
            else
            {
                baselineShiftValue = 0;
                switch (keywordFromValue(propertySet[Property::BASELINE_SHIFT]))
                {
                default:
                case Keyword::BASELINE:
                    baselineShift() = BaselineShift::BASELINE;
                    break;
                case Keyword::SUB:
                    baselineShift() = BaselineShift::SUB;
                    break;
                case Keyword::SUPER:
                    baselineShift() = BaselineShift::SUPER;
                    break;
                }
            }

            //‘dominant-baseline’
            switch (keywordFromValue(propertySet[Property::DOMINANT_BASELINE]))
            {
            default:
            case Keyword::AUTO:
                dominantBaseline() = DominantBaseline::AUTO;
                break;
            case Keyword::USE_SCRIPT:
                dominantBaseline() = DominantBaseline::USE_SCRIPT;
                break;
            case Keyword::NO_CHANGE:
                dominantBaseline() = DominantBaseline::NO_CHANGE;
                break;
            case Keyword::RESET_SIZE:
                dominantBaseline() = DominantBaseline::RESET_SIZE;
                break;
            case Keyword::TEXT_BEFORE_EDGE:
                dominantBaseline() = DominantBaseline::TEXT_BEFORE_EDGE;
                break;
            case Keyword::MIDDLE:
                dominantBaseline() = DominantBaseline::MIDDLE;
                break;
            case Keyword::CENTRAL:
                dominantBaseline() = DominantBaseline::CENTRAL;
                break;
            case Keyword::TEXT_AFTER_EDGE:
                dominantBaseline() = DominantBaseline::TEXT_AFTER_EDGE;
                break;
            case Keyword::IDEOGRAPHIC:
                dominantBaseline() = DominantBaseline::IDEOGRAPHIC;
                break;
            case Keyword::ALPHABETIC:
                dominantBaseline() = DominantBaseline::ALPHABETIC;
                break;
            case Keyword::HANGING:
                dominantBaseline() = DominantBaseline::HANGING;
                break;
            case Keyword::MATHEMATICAL:
                dominantBaseline() = DominantBaseline::MATHEMATICAL;
                break;
            }

            //‘glyph-orientation-horizontal’
            if (auto dimension = dynamic_cast<const CSS::Dimension*>(propertySet[Property::GLYPH_ORIENTATION_HORIZONTAL]))
            {
                switch (((int)dimension->specified))
                {
                default:
                case 0:
                    glyphOrientationHorizontal() = GlyphOrientation::_0;
                    break;
                case 90:
                    glyphOrientationHorizontal() = GlyphOrientation::_90;
                    break;
                case 180:
                    glyphOrientationHorizontal() = GlyphOrientation::_180;
                    break;
                case 270:
                    glyphOrientationHorizontal() = GlyphOrientation::_270;
                    break;
                }
            }
            else
            {
                glyphOrientationHorizontal() = GlyphOrientation::_0;
            }

            //‘glyph-orientation-vertical’
            if (auto dimension = dynamic_cast<const CSS::Dimension*>(propertySet[Property::GLYPH_ORIENTATION_VERTICAL]))
            {
                switch (((int)dimension->specified))
                {
                default:
                    glyphOrientationHorizontal() = GlyphOrientation::AUTO;
                    break;
                case 0:
                    glyphOrientationHorizontal() = GlyphOrientation::_0;
                    break;
                case 90:
                    glyphOrientationHorizontal() = GlyphOrientation::_90;
                    break;
                case 180:
                    glyphOrientationHorizontal() = GlyphOrientation::_180;
                    break;
                case 270:
                    glyphOrientationHorizontal() = GlyphOrientation::_270;
                    break;
                }
            }
            else
            {
                switch (keywordFromValue(propertySet[Property::GLYPH_ORIENTATION_VERTICAL]))
                {
                default:
                case Keyword::AUTO:
                    glyphOrientationHorizontal() = GlyphOrientation::AUTO;
                    break;
                }
            }

            //‘kerning’
             if (auto dimension = dynamic_cast<const CSS::Dimension*>(propertySet[Property::KERNING]))
            {
                kerning = dimension->calculate(sizeContext);
                autoKerning() = 0;
            }
            else
            {
                kerning = 0;
                switch (keywordFromValue(propertySet[Property::KERNING]))
                {
                default:
                case Keyword::AUTO:
                    autoKerning() = 1;
                    break;
                }
            }

            //‘text-anchor’
            switch (keywordFromValue(propertySet[Property::TEXT_ANCHOR]))
            {
            default:
            case Keyword::START:
                textAnchor() = TextAnchor::START;
                break;
            case Keyword::MIDDLE:
                textAnchor() = TextAnchor::MIDDLE;
                break;
            case Keyword::END:
                textAnchor() = TextAnchor::END;
                break;
            }

            //‘writing-mode’
            switch (keywordFromValue(propertySet[Property::WRITING_MODE]))
            {
            default:
            case Keyword::LR_TB:
                writingMode() = WritingMode::LR_TB;
                break;
            case Keyword::RL_TB:
                writingMode() = WritingMode::RL_TB;
                break;
            case Keyword::TB_RL:
                writingMode() = WritingMode::TB_RL;
                break;
             case Keyword::LR:
                writingMode() = WritingMode::LR;
                break;
            case Keyword::RL:
                writingMode() = WritingMode::RL;
                break;
            case Keyword::TB:
                writingMode() = WritingMode::TB;
                break;
            }


            //‘text-rendering’
            switch (keywordFromValue(propertySet[Property::TEXT_RENDERING]))
            {
            default:
            case Keyword::AUTO:
                textRendering() = TextRendering::AUTO;
                break;
            case Keyword::OPTIMIZE_SPEED:
                textRendering() = TextRendering::OPTIMIZE_SPEED;
                break;
            case Keyword::OPTIMIZE_LEGIBILITY:
                textRendering() = TextRendering::OPTIMIZE_LEGIBILITY;
                break;
             case Keyword::GEOMETRIC_PRECISION:
                textRendering() = TextRendering::GEOMETRIC_PRECISION;
                break;
            }

            Vector::applyPropertySet(propertySet, inherit, sizeContext);

            /* Scale stroke properties by font size */
            Font::Face* face(nullptr);
            Font::Collection::lookup(&face, fontFamilies, "Regular");
            if (face)
            {
                double scale = face->ftFace->units_per_EM / fontSize;
                strokeWidth *= scale;
                strokeDashOffset *= scale;
                for (double& dash : strokeDashArray)
                {
                    dash *= scale;
                }
            }

        }

        void Text::updateSizeContext(CSS::SizeContext* sizeContext)
        {
            Vector::updateSizeContext(sizeContext);
            sizeContext->fontSize = fontSize;
            sizeContext->fontXHeight = 0.4 * fontSize; // TODO open font and calculate xheight
            sizeContext->fontStretch = fontStretch();
            sizeContext->fontWeight = fontWeight();
        }
    }
}

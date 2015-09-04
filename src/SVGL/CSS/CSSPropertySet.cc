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

#include "CSSPropertySet.hh"
#include <SVGL/CSS/Structures/CSSDeclarationBlock.hh>


namespace SVGL
{
    namespace CSS
    {
        PropertySet::PropertySet() :
            std::vector<const Value*>()
        {
            resize(Property::PROPERTY_COUNT, nullptr);
        }

        PropertySet::PropertySet(const PropertySet& _propertySet) :
            std::vector<const Value*>()
        {
            resize(Property::PROPERTY_COUNT, nullptr);
            for (unsigned int i = 0; i < Property::PROPERTY_COUNT; ++i)
            {
                at(i) = _propertySet[i];
            }
        }

        void PropertySet::set(const DeclarationBlock* specifiedStyle)
        {
            for (const auto& i : specifiedStyle->map)
            {
                at(i.first) = i.second->value.get();
            }
        }

#define INHERIT(x) if (at(Property::x) ? (Keyword::keywordFromValue(at(Property::x)) == Keyword::INHERIT) : true) at(Property::x) = inherit[Property::x]
#define OTHERINHERIT(x) if (at(Property::x) ? (Keyword::keywordFromValue(at(Property::x)) == Keyword::INHERIT) : false) at(Property::x) = inherit[Property::x]

        void PropertySet::inherit(const PropertySet& inherit)
        {
            INHERIT(COLOR);
            INHERIT(CURSOR);
            INHERIT(CLIP_RULE);
            INHERIT(POINTER_EVENTS);
            INHERIT(COLOR_INTERPOLATION);
            INHERIT(COLOR_RENDERING);

            // Vector (11)
            INHERIT(FILL);
            INHERIT(FILL_RULE);
            INHERIT(FILL_OPACITY);
            INHERIT(STROKE);
            INHERIT(STROKE_DASHARRAY);
            INHERIT(STROKE_DASHOFFSET);
            INHERIT(STROKE_LINECAP);
            INHERIT(STROKE_LINEJOIN);
            INHERIT(STROKE_MITERLIMIT);
            INHERIT(STROKE_OPACITY);
            INHERIT(STROKE_WIDTH);

            // Shape (5)
            INHERIT(MARKER);
            INHERIT(MARKER_START);
            INHERIT(MARKER_MID);
            INHERIT(MARKER_END);
            INHERIT(SHAPE_RENDERING);


            // Image (1)
            INHERIT(COLOR_PROFILE);
            INHERIT(IMAGE_RENDERING);

            // Text (21)
            //FONT,
            INHERIT(FONT_FAMILY);
            INHERIT(FONT_SIZE); // TODO: computed
            INHERIT(FONT_SIZE_ADJUST);
            INHERIT(FONT_STRETCH);
            INHERIT(FONT_VARIANT);
            INHERIT(FONT_WEIGHT);
            INHERIT(DIRECTION);
            INHERIT(LETTER_SPACING);
            OTHERINHERIT(TEXT_DECORATION);
            OTHERINHERIT(UNICODE_BIDI);
            INHERIT(WORD_SPACING);
            OTHERINHERIT(ALIGNMENT_BASELINE);
            OTHERINHERIT(BASELINE_SHIFT);
            OTHERINHERIT(DOMINANT_BASELINE);
            INHERIT(GLYPH_ORIENTATION_HORIZONTAL);
            INHERIT(GLYPH_ORIENTATION_VERTICAL);
            INHERIT(KERNING);
            INHERIT(TEXT_ANCHOR);
            INHERIT(WRITING_MODE);
            INHERIT(TEXT_RENDERING);

            // viewport
            OTHERINHERIT(CLIP);
            OTHERINHERIT(OVERFLOW);

            // filter
            OTHERINHERIT(ENABLE_BACKGROUND);

            // feFlood
            OTHERINHERIT(FLOOD_COLOR);
            OTHERINHERIT(FLOOD_OPACITY);

            // lighting
            OTHERINHERIT(LIGHTING_COLOR);

            // gradient
            OTHERINHERIT(STOP_COLOR);
            OTHERINHERIT(STOP_OPACITY);
        }


    }
}

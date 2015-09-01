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

#include "ElementText.hh"

namespace SVGL
{
    namespace Element
    {


        /**
         * Get the tag name of the element.
         */
        const char* Text::getTagName() const
        {
            return "text";
        }

        /**
         * Calculate the relative units
         */
        void Text::calculate(const CSS::SizeContext& sizeContext)
        {
            x.calculate(sizeContext, CSS::Calculable::PercentMode::X);
            y.calculate(sizeContext, CSS::Calculable::PercentMode::Y);
        }

        /**
         * Get the Style object for the current element.
         *
         * @details The style object is used to apply styles from the stylesheets.
         * @return A pointer to the Style object.
         */
        CSS::Style* Text::getStyle()
        {
            return &style;
        }

        /**
         * Test the value of the specified attribute.
         *
         * @param[in] index The attribute index of the attribute to test.
         * @param[in] attributeValue The value of the attribute to test.
         */
        bool Text::testAttributeValue(unsigned int index, const char* attributeValue) const
        {
            return Graphic::testAttributeValue(index, attributeValue);
        }

        void Text::setAttribute(unsigned int index, SubString name, SubString value)
        {
            switch (index)
            {
            case Attribute::D:
                break;
            default:
                Graphic::setAttribute(index, name, value);
                break;
            }
        }

        void Text::appendText(SubString data)
        {
            text.append(data.start, data.count);
        }

        void Text::buffer(double tolerance)
        {
            if (!dirty)
            {
                return;
            }
            Font::StyledFaceKey testKey(style);
            if (styledFaceKey != testKey)
            {
                styledFaceKey = testKey;
                styledFace = Font::Collection::request(styledFaceKey);
            }
            // TODO adjust tolerance by font size
            if (styledFace)
            {
                styledFace->buffer(style, text.c_str(), tolerance);
                dirty = false;
            }
        }

        void Text::render(Render::Context* context)
        {
            Transform t;
            t.scaleR(styledFaceKey.effectiveFontSize, styledFaceKey.effectiveFontSize);

            context->pushTransform(&t);
            context->pushColor(style.stroke);
            if (styledFace)
            {
                styledFace->render(context, style, text.c_str());
            }
            context->popColor();
            context->popTransform();
        }
    }
}

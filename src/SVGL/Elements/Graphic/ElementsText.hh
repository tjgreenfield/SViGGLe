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

#include <SVGL/CSS/CSSCalculableCache.hh>
#include <SVGL/Elements/Abstract/ElementsGraphic.hh>
#include <SVGL/Styles/StylesText.hh>
#include <SVGL/Fonts/FontsCollection.hh>


namespace SVGL
{
    namespace Elements
    {
        class Text : public Graphic
        {
        protected:
            CSS::CalculableCache x, y;
            Styles::Text style;
            Font::StyledFaceKey styledFaceKey;
            Font::StyledFaceHandle styledFace;
            std::string text;

        public:
            Text(Root* _parent = nullptr);

            /* From CSS::Element */

            /**
             * Get the tag name of the element.
             */
            const char* getTagName() const override;

            /**
             * Calculate the relative units
             */
            void calculate(const CSS::SizeContext& sizeContext) override;

            /**
             * Test the value of the specified attribute.
             *
             * @param[in] index The attribute index of the attribute to test.
             * @param[in] attributeValue The value of the attribute to test.
             */
            bool testAttributeValue(unsigned int index, const char* attributeValue) const override;

            /**
             * Get the Style object for the current element.
             *
             * @details The style object is used to apply styles from the stylesheets.
             * @return A pointer to the Style object.
             */
            CSS::Style* getStyle() override;

            /* From XML::Node */

            void setAttribute(unsigned int index, SubString name, SubString value) override;

            void appendText(SubString data) override;

            /* From Element */

            void buffer(double tolerance) override;

            void render(Render::Context* context) override;
        };
    }
}

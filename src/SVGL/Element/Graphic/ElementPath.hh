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

#include <SVGL/Element/Abstract/ElementGraphic.hh>
#include <SVGL/Path/PathCommandSet.hh>
#include <SVGL/Render/RenderPathBuffer.hh>
#include <SVGL/Styles/StyleShape.hh>
#include <SVGL/CSS/CSSCalculableCache.hh>

namespace SVGL
{
    namespace Element
    {
        class Path : public Graphic
        {
        protected:
            Styles::Shape style;

            PathCommand::CommandSet commandSet;
            Render::PathBuffer renderBuffer;

        public:

            ~Path();

            /* From CSS::Element */

            /**
             * Get the Style object for the current element.
             *
             * @details The style object is used to apply styles from the stylesheets.
             * @return A pointer to the Style object.
             */
            CSS::Style* getStyle() override;

            /**
             * Get the tag name of the element.
             */
            const char* getTagName() const override;

            /**
             * Test the value of the specified attribute.
             *
             * @param[in] index The attribute index of the attribute to test.
             * @param[in] attributeValue The value of the attribute to test.
             */
            bool testAttributeValue(unsigned int index, const char* attributeValue) const override;


            /* From XML::Node */

            void setAttribute(unsigned int index, SubString name, SubString value) override;

            /**
             * Output to stream
             */
            std::ostream& stream(std::ostream& out) const override;

            void clearBuffers() override;

            void buffer(double tolerance) override;

            void render(Render::Context* context) override;
        };
    }
}

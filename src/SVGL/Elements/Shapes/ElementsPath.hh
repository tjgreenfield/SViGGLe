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

#include <SVGL/Elements/Abstracts/ElementsInstance.hh>

#include <SVGL/Elements/Abstracts/ElementsStyled.hh>
#include <SVGL/PathCommands/PathCommandsList.hh>
#include <SVGL/Render/RenderPathBuffer.hh>
#include <SVGL/Styles/StylesShape.hh>
#include <SVGL/CSS/CSSCalculable.hh>

namespace SVGL
{
    namespace Elements
    {
        class Path : public Styled
        {
        protected:
            PathCommands::List commandList;

            class Instance : public Elements::Instance
            {
            protected:
                const Path* path;
                Styles::Shape style;
                Render::PathBuffer renderBuffer;

            public:
                Instance(const Path* _path, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext);

                void buffer(double tolerance) override;

                void render(Render::Context* context) const override;

                void calculateBoundingBox(BoundingBox* boundingBox) const override;
            };

        public:

            Path(Root* _parent = nullptr);
            ~Path();

            /***** From CSS::Element *****/

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


            /***** From XML::Node *****/

            void setAttribute(unsigned int index, SubString value) override;

            /**
             * Output to stream
             */
            std::ostream& stream(std::ostream& out) const override;

            /***** From Elements::Root *****/

            Instance_uptr calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) override;
       };
    }
}

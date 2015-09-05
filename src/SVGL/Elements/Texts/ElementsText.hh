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
#include <SVGL/Elements/Abstracts/ElementsStyled.hh>
#include <SVGL/Styles/StylesText.hh>
#include <SVGL/Fonts/FontsCollection.hh>


namespace SVGL
{
    namespace Elements
    {
        class Text : public Styled
        {
        protected:
            class Instance : public Elements::Instance
            {
            protected:
                const Text* text;
                double x;
                double y;
                Styles::Text style;
                Font::StyledFaceKey styledFaceKey;
                Font::StyledFaceHandle styledFace;

            public:
                Instance(const Text* _text, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext);

                void buffer(double tolerance) override;

                void render(Render::Context* context) override;
            };

            CSS::Calculable x;
            CSS::Calculable y;
            std::string text;

        public:
            Text(Root* _parent = nullptr);

            /***** From CSS::Element *****/
            const char* getTagName() const override;

            /***** From XML::Node *****/
            void setAttribute(unsigned int index, SubString name, SubString value) override;

            void appendText(SubString data) override;

            /***** From Element::Root *****/
            Instance_uptr calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) override;
        };
    }
}

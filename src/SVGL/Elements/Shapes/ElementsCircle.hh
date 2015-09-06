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

#include <SVGL/Elements/Abstracts/ElementsStyled.hh>
#include <SVGL/Elements/Abstracts/ElementsInstance.hh>
#include <SVGL/Render/RenderPathBuffer.hh>
#include <SVGL/Styles/StylesShape.hh>
#include <SVGL/CSS/CSSCalculable.hh>

namespace SVGL
{
    namespace Elements
    {
        class Circle : public Styled
        {
        protected:
            class Instance : public Elements::Instance
            {
            protected:
                const Circle* circle;
                Styles::Shape style;
                Render::PathBuffer renderBuffer;
                double cx;
                double cy;
                double r;

            public:
                Instance(const Circle* _circle, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext);

                void buffer(double tolerance) override;

                void render(Render::Context* context) const override;

                void calculateBoundingBox(BoundingBox* boundingBox) const override;
            };

            CSS::Calculable cx;
            CSS::Calculable cy;
            CSS::Calculable r;

        public:
            Circle(Root* _parent = nullptr);

            /***** CSS::Element *****/

            const char* getTagName() const override;

            /***** XML::Node *****/

            void setAttribute(unsigned int index, SubString value) override;

            /***** Elements::Root *****/

            Instance_uptr calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) override;
        };
    }
}

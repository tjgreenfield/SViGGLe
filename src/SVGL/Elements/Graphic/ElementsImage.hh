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

#include <SVGL/Elements/Abstract/ElementsGraphic.hh>
#include <SVGL/Images/ImagesImage.hh>
#include <SVGL/Styles/StylesImage.hh>
#include <SVGL/CSS/CSSStyle.hh>
#include <SVGL/CSS/CSSSizeContext.hh>
#include <SVGL/CSS/CSSCalculableCache.hh>


namespace SVGL
{
    namespace Elements
    {
        class Image : public Graphic
        {
        protected:
            class Instance : public Elements::Instance
            {
            protected:
                const Image* image;
                Styles::Image style;
                Images::Image* texture;
                Transforms::Transform imageTransform;

                double x;
                double y;
                double width;
                double height;

            public:
                Instance(const Image* _image, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext);

                void buffer(double tolerance) override;

                void render(Render::Context* context) override;
            };

            std::string href;
            CSS::Calculable x;
            CSS::Calculable y;
            CSS::Calculable width;
            CSS::Calculable height;


        public:
            Image(Root* _parent = nullptr);

            /***** CSS::Element *****/

            const char* getTagName() const override;

            /***** XML::Node *****/

            void setAttribute(unsigned int index, SubString name, SubString value);

            /***** Elements::Root *****/

            Instance_uptr calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) override;

        };
    }
}

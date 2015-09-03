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

#include "ElementsImage.hh"
#include <SVGL/Images/ImagesCollection.hh>

namespace SVGL
{
    namespace Elements
    {
        Image::Image(Root* _parent) :
            Graphic(_parent),
            x(0),
            y(0),
            width(0),
            height(0),
            image(nullptr)
        {

        }

        /**
         * Get the tag name of the element.
         */
        const char* Image::getTagName() const
        {
            return "image";
        }

        CSS::Style* Image::getStyle()
        {
            return &style;
        }

        /**
         * Calculate the relative units
         */
        void Image::calculate(const CSS::SizeContext& sizeContext)
        {
            x.calculate(sizeContext, CSS::Calculable::PercentMode::X);
            y.calculate(sizeContext, CSS::Calculable::PercentMode::Y);
            width.calculate(sizeContext, CSS::Calculable::PercentMode::X);
            height.calculate(sizeContext, CSS::Calculable::PercentMode::Y);
        }

        void Image::setAttribute(unsigned int index, SubString name, SubString value)
        {
            switch (index)
            {
            case Attribute::X:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        x = *dimension;
                    }
                }
                break;
            case Attribute::Y:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        y = *dimension;
                    }
                }
                break;
            case Attribute::WIDTH:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        width = *dimension;
                    }
                }
                break;
            case Attribute::HEIGHT:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        height = *dimension;
                    }
                }
            break;
            case Attribute::XLINK_HREF:
                {
                    href.assign(value.start, value.count);
                }
                break;
            default:
                Graphic::setAttribute(index, name, value);
                break;
            }
        }

        void Image::clearBuffers()
        {

        }

        void Image::buffer(double)
        {
            if (!image)
            {
                image = Images::Collection::loadImage(href.c_str());
            }
            imageTransform.identity();
            imageTransform.translateR(x, y);
            imageTransform.scaleR(width, height);
        }

        void Image::render(Render::Context* context)
        {
            if (!image)
            {
                return;
            }
            context->pushTransform(&transform);
            context->pushTransform(&imageTransform);

            context->setTextureShader();
            image->render(context, style);
            context->setColorShader();

            context->popTransform();
            context->popTransform();
        }
    }
}

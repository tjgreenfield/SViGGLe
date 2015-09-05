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
            Styled(_parent),
            x(0),
            y(0),
            width(1),
            height(1)
        {

        }

        /***** CSS::Element *****/
        const char* Image::getTagName() const
        {
            return "image";
        }

        /***** XML::Node *****/
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
                Styled::setAttribute(index, name, value);
                break;
            }
        }

        /***** Elements::Root *****/

        Instance_uptr Image::calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext)
        {
            return std::move(Instance_uptr(new Instance(this, inherit, sizeContext)));
        }

        /***** Elements::Image::Instance *****/

        Image::Instance::Instance(const Image* _image, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) :
            image(_image),
            texture(nullptr)
        {
            style.applyPropertySets(image->cascadedStyles, inherit, sizeContext);
            x = image->x.calculate(sizeContext, CSS::Calculable::PercentMode::X);
            y = image->y.calculate(sizeContext, CSS::Calculable::PercentMode::Y);
            width = image->width.calculate(sizeContext, CSS::Calculable::PercentMode::X);
            height = image->height.calculate(sizeContext, CSS::Calculable::PercentMode::Y);

        }

        void Image::Instance::buffer(double)
        {
            if (!texture)
            {
                texture = Images::Collection::loadImage(image->href.c_str());
            }
            imageTransform.identity();
            imageTransform.translateR(x, y);
            imageTransform.scaleR(width, height);
        }

        void Image::Instance::render(Render::Context* context)
        {
            if (!image)
            {
                return;
            }
            context->pushTransform(&image->transform);
            context->pushTransform(&imageTransform);

            context->setTextureShader();
            texture->render(context, style);
            context->setColorShader();

            context->popTransform();
            context->popTransform();
        }
    }
}

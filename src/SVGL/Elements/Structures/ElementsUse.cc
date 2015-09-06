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

#include "ElementsUse.hh"
#include <SVGL/SVGLDocument.hh>
#include <SVGL/Images/ImagesCollection.hh>

namespace SVGL
{
    namespace Elements
    {
        Use::Use(Root* _parent) :
            Styled(_parent),
            href(""),
            x(0),
            y(0),
            width(0),
            height(0)
        {

        }

        /***** From CSS::Element *****/
        const char* Use::getTagName() const
        {
            return "use";
        }

        /***** From XML::Node *****/
        void Use::setAttribute(unsigned int index, SubString value)
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
                Styled::setAttribute(index, value);
                break;
            }
        }

        /***** From Elements::Root *****/
        Instance_uptr Use::calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext)
        {
            CSS::PropertySet propertySet(cascadedStyles);
            propertySet.set(getSpecifiedStyle());
            propertySet.inherit(inherit);

            Document* document = getDocument();
            if (document)
            {
                if (href.size() > 0)
                {
                    if (href.at(0) == '#')
                    {
                        Elements::Root* target = document->getElementByID(href.c_str() + 1);

                        return Instance_uptr(new Instance(this, std::move(target->calculateInstance(propertySet, sizeContext)), propertySet, sizeContext));
                    }
                }
            }
            return Instance_uptr(nullptr);

        }

        /***** Elements::Use::Instance *****/

        Use::Instance::Instance(const Use* _use, Instance_uptr&& _target, const CSS::PropertySet& , const CSS::SizeContext& sizeContext) :
            use(_use),
            target(std::move(_target))
        {
            //style.applyPropertySets(use->cascadedStyles, sizeContext);
            useTransform.translateR(use->x.calculate(sizeContext), use->y.calculate(sizeContext));
        }

        void Use::Instance::buffer(double tolerance)
        {
            if (target)
            {
                target->buffer(tolerance);
            }
        }

        void Use::Instance::render(Render::Context* context) const
        {
            if (target)
            {
                context->pushTransform(&use->transform);
                context->pushTransform(&useTransform);
                target->render(context);
                context->popTransform();
                context->popTransform();
            }
        }

        void Use::Instance::calculateBoundingBox(BoundingBox* boundingBox) const
        {
            if (target)
            {
                target->calculateBoundingBox(boundingBox);
            }
        }
    }
}

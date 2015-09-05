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

#include "ElementsRect.hh"

#include <SVGL/CSS/CSSValues.hh>
#include <SVGL/PathCommands/PathCommands.hh>

namespace SVGL
{
    namespace Elements
    {
        Rect::Rect(Root* _parent) :
            Styled(_parent),
            x(0),
            y(0),
            width(0),
            height(0),
            rx(0),
            ry(0)
        {

        }

        /***** CSS::Element *****/
        const char* Rect::getTagName() const
        {
            return "rect";
        }

        /***** XML::Node *****/
        void Rect::setAttribute(unsigned int index, SubString name, SubString value)
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
            case Attribute::RX:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        rx = *dimension;
                    }
                }
                break;
            case Attribute::RY:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        ry = *dimension;
                    }
                }
                break;
            case Attribute::D:
                break;
            default:
                Styled::setAttribute(index, name, value);
                break;
            }
        }

        /***** Elements::Root *****/

        Instance_uptr Rect::calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext)
        {
            return std::move(Instance_uptr(new Instance(this, inherit, sizeContext)));
        }

        /***** Elements::Rect::Instance *****/

        Rect::Instance::Instance(const Rect* _rect, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) :
            rect(_rect)
        {
            style.applyPropertySets(rect->cascadedStyles, inherit, sizeContext);
            x = rect->x.calculate(sizeContext, CSS::Calculable::PercentMode::X);
            y = rect->y.calculate(sizeContext, CSS::Calculable::PercentMode::Y);
            width = rect->width.calculate(sizeContext, CSS::Calculable::PercentMode::X);
            height = rect->height.calculate(sizeContext, CSS::Calculable::PercentMode::Y);
            rx = rect->rx.calculate(sizeContext, CSS::Calculable::PercentMode::X);
            ry = rect->ry.calculate(sizeContext, CSS::Calculable::PercentMode::Y);
        }

        void Rect::Instance::buffer(double tolerance)
        {
            PathCommands::List commandList;
            if ((rx == 0) && (ry == 0))
            {
                commandList.emplace_back(new PathCommands::MoveTo(x, y));
                commandList.emplace_back(new PathCommands::LineTo(x + width, y));
                commandList.emplace_back(new PathCommands::LineTo(x + width, y + height));
                commandList.emplace_back(new PathCommands::LineTo(x, y + height));
                commandList.emplace_back(new PathCommands::ClosePath());
            }
            else
            {
                double rx_(rx), ry_(ry);
                if (rx_ == 0)
                {
                    rx_ = ry;
                }
                if (ry_ == 0)
                {
                    ry_ = rx;
                }
                rx_ = std::min(rx_, width * 0.5);
                ry_ = std::min(ry_, height * 0.5);

                commandList.emplace_back(new PathCommands::MoveTo(x + rx_, y));
                commandList.emplace_back(new PathCommands::LineTo(x + width - rx_, y));
                commandList.emplace_back(new PathCommands::EllipticalTo(Point(x + width, y + ry_), rx_, ry_, 0, 0, 1, commandList.back().get()));
                commandList.emplace_back(new PathCommands::LineTo(x + width, y + height - ry_));
                commandList.emplace_back(new PathCommands::EllipticalTo(Point(x + width - rx_, y + height), rx_, ry_, 0, 0, 1, commandList.back().get()));
                commandList.emplace_back(new PathCommands::LineTo(x + rx_, y + height));
                commandList.emplace_back(new PathCommands::EllipticalTo(Point(x, y + height - ry_), rx_, ry_, 0, 0, 1, commandList.back().get()));
                commandList.emplace_back(new PathCommands::LineTo(x, y + ry_));
                commandList.emplace_back(new PathCommands::EllipticalTo(Point(x + rx_, y), rx_, ry_, 0, 0, 1, commandList.back().get()));
                commandList.emplace_back(new PathCommands::ClosePath());
            }

            tolerance = rect->transform.transformTolerance(tolerance);
            renderBuffer.clear();
            renderBuffer.buffer(commandList, style, tolerance);
        }

        void Rect::Instance::render(Render::Context* context)
        {
            context->pushTransform(&rect->transform);
            renderBuffer.render(context, style);
        }
    }
}

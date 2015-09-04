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

#include "ElementsEllipse.hh"

#include <SVGL/CSS/CSSValues.hh>
#include <SVGL/PathCommands/PathCommands.hh>

namespace SVGL
{
    namespace Elements
    {
        Ellipse::Ellipse(Root* _parent) :
            Graphic(_parent),
            cx(0),
            cy(0),
            rx(0),
            ry(0)
        {

        }

        /***** CSS::Element ****/

        const char* Ellipse::getTagName() const
        {
            return "ellipse";
        }

        /***** XML::Node *****/

        void Ellipse::setAttribute(unsigned int index, SubString name, SubString value)
        {
            switch (index)
            {
            case Attribute::CX:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        cx = *dimension;
                    }
                }
                break;
            case Attribute::CY:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        cy = *dimension;
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
                Graphic::setAttribute(index, name, value);
                break;
            }
        }

        /***** Elements::Root *****/

        Instance_uptr Ellipse::calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext)
        {
            return std::move(Instance_uptr(new Instance(this, inherit, sizeContext)));
        }

        /***** Elements::Ellipse::Instance *****/

        Ellipse::Instance::Instance(const Ellipse* _ellipse, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) :
            ellipse(_ellipse)
        {
            style.applyPropertySets(ellipse->cascadedStyles, inherit, sizeContext);
            cx = _ellipse->cx.calculate(sizeContext, CSS::Calculable::PercentMode::X);
            cy = _ellipse->cy.calculate(sizeContext, CSS::Calculable::PercentMode::Y);
            rx = _ellipse->rx.calculate(sizeContext, CSS::Calculable::PercentMode::X);
            ry = _ellipse->ry.calculate(sizeContext, CSS::Calculable::PercentMode::Y);
        }

        void Ellipse::Instance::buffer(double tolerance)
        {
            PathCommands::List commandList;
            commandList.emplace_back(new PathCommands::MoveTo(cx + rx, cy));
            commandList.emplace_back(new PathCommands::EllipticalTo(Point(cx - rx, cy), rx, ry, 0, 0, 1, commandList.back().get()));
            commandList.emplace_back(new PathCommands::EllipticalTo(Point(cx + rx, cy), rx, ry, 0, 0, 1, commandList.back().get()));
            commandList.emplace_back(new PathCommands::ClosePath());

            tolerance = ellipse->transform.transformTolerance(tolerance);
            renderBuffer.clear();
            renderBuffer.buffer(commandList, style, tolerance);
        }

        void Ellipse::Instance::render(Render::Context* context)
        {
            context->pushTransform(&ellipse->transform);
            renderBuffer.render(context, style);
            context->popTransform();
        }
    }
}


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

#include "ElementsCircle.hh"

#include <SVGL/CSS/CSSValues.hh>
#include <SVGL/PathCommands/PathCommands.hh>

namespace SVGL
{
    namespace Elements
    {
        Circle::Circle(Root* _parent) :
            Styled(_parent),
            cx(0),
            cy(0),
            r(0)
        {

        }

        /***** CSS::Element *****/

        const char* Circle::getTagName() const
        {
            return "circle";
        }

        /***** XML::Node *****/

        void Circle::setAttribute(unsigned int index, SubString value)
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
            case Attribute::R:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        r = *dimension;
                    }
                }
                break;
            case Attribute::D:
                break;
            default:
                Styled::setAttribute(index, value);
                break;
            }
        }

        /***** Elements::Root *****/

        Instance_uptr Circle::calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext)
        {
            return std::move(Instance_uptr(new Instance(this, inherit, sizeContext)));
        }

        /***** Elements::Circle::Instance *****/

        Circle::Instance::Instance(const Circle* _circle, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) :
            circle(_circle)
        {
            style.applyPropertySets(circle->cascadedStyles, inherit, sizeContext);
            cx = _circle->cx.calculate(sizeContext, CSS::Calculable::PercentMode::X);
            cy = _circle->cy.calculate(sizeContext, CSS::Calculable::PercentMode::Y);
            r = _circle->r.calculate(sizeContext, CSS::Calculable::PercentMode::DIAGONAL);
        }

        void Circle::Instance::buffer(double tolerance)
        {
            style.buffer(*this);

            PathCommands::List commandList;
            commandList.emplace_back(new PathCommands::MoveTo(cx + r, cy));
            commandList.emplace_back(new PathCommands::EllipticalTo(Point(cx - r, cy), r, r, 0, 0, 1, commandList.back().get()));
            commandList.emplace_back(new PathCommands::EllipticalTo(Point(cx + r, cy), r, r, 0, 0, 1, commandList.back().get()));
            commandList.emplace_back(new PathCommands::ClosePath());

            tolerance = circle->transform.transformTolerance(tolerance);
            renderBuffer.clear();
            renderBuffer.buffer(commandList, style, tolerance);
        }

        void Circle::Instance::render(Render::Context* context) const
        {
            context->pushTransform(&circle->transform);
            renderBuffer.render(context, style);
            context->popTransform();
        }

        void Circle::Instance::calculateBoundingBox(BoundingBox* boundingBox) const
        {
            boundingBox->pMin.x = cx - r;
            boundingBox->pMin.y = cy - r;

            boundingBox->pMax.x = cx + r;
            boundingBox->pMax.y = cy + r;
        }
    }

}

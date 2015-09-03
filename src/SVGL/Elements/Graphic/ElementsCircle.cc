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
            Path(_parent),
            cx(0),
            cy(0),
            r(0)
        {

        }

        /**
         * Get the tag name of the element.
         */
        const char* Circle::getTagName() const
        {
            return "circle";
        }

        /**
         * Calculate the relative units
         */
        void Circle::calculate(const CSS::SizeContext& sizeContext)
        {
            cx.calculate(sizeContext, CSS::Calculable::PercentMode::X);
            cy.calculate(sizeContext, CSS::Calculable::PercentMode::Y);
            r.calculate(sizeContext, CSS::Calculable::PercentMode::DIAGONAL);
        }

        void Circle::setAttribute(unsigned int index, SubString name, SubString value)
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
                Path::setAttribute(index, name, value);
                break;
            }
        }

        void Circle::clearBuffers()
        {
            commandList.clear();
            Path::clearBuffers();
        }

        void Circle::buffer(double tolerance)
        {
            commandList.clear();
            commandList.emplace_back(new PathCommands::MoveTo(r, 0));
            commandList.emplace_back(new PathCommands::EllipticalTo(Point(-r, 0), r, r, 0, 0, 1, commandList.back().get()));
            commandList.emplace_back(new PathCommands::EllipticalTo(Point(r, 0), r, r, 0, 0, 1, commandList.back().get()));
            commandList.emplace_back(new PathCommands::ClosePath());
            Path::buffer(tolerance);
        }
    }

}

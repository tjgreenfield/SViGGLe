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

#include "ElementsLine.hh"

#include <SVGL/CSS/CSSValues.hh>
#include <SVGL/PathCommands/PathCommands.hh>

namespace SVGL
{
    namespace Elements
    {
        Line::Line(Root* _parent) :
            Path(_parent),
            x1(0),
            y1(0),
            x2(0),
            y2(0)
        {

        }

        /**
         * Get the tag name of the element.
         */
        const char* Line::getTagName() const
        {
            return "line";
        }

        /**
         * Calculate the relative units
         */
        void Line::calculate(const CSS::SizeContext& sizeContext)
        {
            x1.calculate(sizeContext, CSS::Calculable::PercentMode::X);
            y1.calculate(sizeContext, CSS::Calculable::PercentMode::Y);
            x2.calculate(sizeContext, CSS::Calculable::PercentMode::X);
            y2.calculate(sizeContext, CSS::Calculable::PercentMode::Y);
        }

        void Line::setAttribute(unsigned int index, SubString name, SubString value)
        {
            switch (index)
            {
            case Attribute::X1:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        x1 = *dimension;
                    }
                }
                break;
            case Attribute::Y1:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        y1 = *dimension;
                    }
                }
                break;
            case Attribute::X2:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        x2 = *dimension;
                    }
                }
                break;
            case Attribute::Y2:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        y2 = *dimension;
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

        void Line::clearBuffers()
        {
            commandList.clear();
            Path::clearBuffers();
        }

        void Line::buffer(double tolerance)
        {
            commandList.clear();
            commandList.emplace_back(new PathCommands::MoveTo(x1, y1));
            commandList.emplace_back(new PathCommands::LineTo(x2, y2));
            Path::buffer(tolerance);
        }
    }
}

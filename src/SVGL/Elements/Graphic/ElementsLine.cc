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
            Graphic(_parent),
            x1(0),
            y1(0),
            x2(0),
            y2(0)
        {

        }

        /***** CSS::Elements *****/

        const char* Line::getTagName() const
        {
            return "line";
        }

        /***** XML::Node *****/

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
                Graphic::setAttribute(index, name, value);
                break;
            }
        }

        /***** Elements::Root *****/

        Instance_uptr Line::calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext)
        {
            return std::move(Instance_uptr(new Instance(this, inherit, sizeContext)));
        }

        /***** Elements::Line::Instance *****/

        Line::Instance::Instance(const Line* _line, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) :
            line(_line)
        {
            style.applyPropertySets(line->cascadedStyles, inherit, sizeContext);
            x1 = _line->x1.calculate(sizeContext, CSS::Calculable::PercentMode::X);
            y1 = _line->y1.calculate(sizeContext, CSS::Calculable::PercentMode::Y);
            x2 = _line->x2.calculate(sizeContext, CSS::Calculable::PercentMode::X);
            y2 = _line->y2.calculate(sizeContext, CSS::Calculable::PercentMode::Y);
        }

        void Line::Instance::buffer(double tolerance)
        {
            PathCommands::List commandList;
            commandList.emplace_back(new PathCommands::MoveTo(x1, y1));
            commandList.emplace_back(new PathCommands::LineTo(x2, y2));

            tolerance = line->transform.transformTolerance(tolerance);
            renderBuffer.clear();
            renderBuffer.buffer(commandList, style, tolerance);
        }

        void Line::Instance::render(Render::Context* context)
        {
            context->pushTransform(&line->transform);
            renderBuffer.render(context, style);
        }
    }
}

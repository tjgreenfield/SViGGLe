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
#include <SVGL/Path/PathCommands.hh>

namespace SVGL
{
    Rect::Rect() :
        x(0),
        y(0),
        width(0),
        height(0),
        rx(0),
        ry(0)
    {

    }

    void Rect::setAttribute(unsigned int index, SubString name, SubString value)
    {
        switch (index)
        {
        case Attribute::X:
            {
                CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                if (CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                {
                    x = dimension->get();
                }
            }
            break;
        case Attribute::Y:
            {
                CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                if (CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                {
                    y = dimension->get();
                }
            }
            break;
        case Attribute::WIDTH:
            {
                CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                if (CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                {
                    width = dimension->get();
                }
            }
            break;
        case Attribute::HEIGHT:
            {
                CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                if (CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                {
                    height = dimension->get();
                }
            }
            break;
        case Attribute::RX:
            {
                CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                if (CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                {
                    rx = dimension->get();
                }
            }
            break;
        case Attribute::RY:
            {
                CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                if (CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                {
                    ry = dimension->get();
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

    void Rect::clearBuffers()
    {
        commandSet.clear();
        Path::clearBuffers();
    }

    void Rect::buffer(double tolerance)
    {
        commandSet.clear();
        if ((rx == 0) && (ry == 0))
        {
            commandSet.emplace_back(new PathCommand::MoveTo(x, y));
            commandSet.emplace_back(new PathCommand::LineTo(x + width, y));
            commandSet.emplace_back(new PathCommand::LineTo(x + width, y + height));
            commandSet.emplace_back(new PathCommand::LineTo(x, y + height));
            commandSet.emplace_back(new PathCommand::ClosePath());
        }
        else
        {
            if (rx == 0)
            {
                rx = ry;
            }
            if (ry == 0)
            {
                ry = rx;
            }
            rx = std::min(rx, width * 0.5);
            ry = std::min(ry, height * 0.5);

            commandSet.emplace_back(new PathCommand::MoveTo(x + rx, y));
            commandSet.emplace_back(new PathCommand::LineTo(x + width - rx, y));
            commandSet.emplace_back(new PathCommand::EllipticalTo(Point(x + width, y + ry), rx, ry, 0, 0, 1, commandSet.back().get()));
            commandSet.emplace_back(new PathCommand::LineTo(x + width, y + height - ry));
            commandSet.emplace_back(new PathCommand::EllipticalTo(Point(x + width - rx, y + height), rx, ry, 0, 0, 1, commandSet.back().get()));
            commandSet.emplace_back(new PathCommand::LineTo(x + rx, y + height));
            commandSet.emplace_back(new PathCommand::EllipticalTo(Point(x, y + height - ry), rx, ry, 0, 0, 1, commandSet.back().get()));
            commandSet.emplace_back(new PathCommand::LineTo(x, y + ry));
            commandSet.emplace_back(new PathCommand::EllipticalTo(Point(x + rx, y), rx, ry, 0, 0, 1, commandSet.back().get()));
            commandSet.emplace_back(new PathCommand::ClosePath());
        }
        Path::buffer(tolerance);
    }
}

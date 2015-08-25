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
#include <SVGL/Path/PathCommands.hh>

namespace SVGL
{
    Ellipse::Ellipse() :
        cx(0),
        cy(0),
        rx(0),
        ry(0)
    {

    }

    void Ellipse::setAttribute(unsigned int index, SubString name, SubString value)
    {
        switch (index)
        {
        case Attribute::CX:
            {
                CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                if (CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                {
                    cx = dimension->get();
                }
            }
            break;
        case Attribute::CY:
            {
                CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                if (CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                {
                    cy = dimension->get();
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

    void Ellipse::clearBuffers()
    {
        commandSet.clear();
        Path::clearBuffers();
    }

    void Ellipse::buffer(double tolerance)
    {
        commandSet.clear();
        commandSet.emplace_back(new PathCommand::MoveTo(rx, 0));
        commandSet.emplace_back(new PathCommand::EllipticalTo(Point(-rx, 0), rx, ry, 0, 0, 1, commandSet.back().get()));
        commandSet.emplace_back(new PathCommand::EllipticalTo(Point(rx, 0), rx, ry, 0, 0, 1, commandSet.back().get()));
        commandSet.emplace_back(new PathCommand::ClosePath());
        Path::buffer(tolerance);
    }
}

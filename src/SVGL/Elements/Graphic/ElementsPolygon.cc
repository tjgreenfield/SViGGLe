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

#include "ElementsPolygon.hh"
#include "ElementsPointsParser.hh"

#include <SVGL/CSS/CSSValues.hh>
#include <SVGL/PathCommands/PathCommands.hh>

namespace SVGL
{
    namespace Elements
    {
        Polygon::Polygon()
        {

        }

        /**
         * Get the tag name of the element.
         */
        const char* Polygon::getTagName() const
        {
            return "polygon";
        }

        void Polygon::setAttribute(unsigned int index, SubString name, SubString value)
        {
            switch (index)
            {
            case Attribute::POINTS:
                PointsParser(value.start).readPoints(&points);
                break;
            case Attribute::D:
                break;
            default:
                Path::setAttribute(index, name, value);
                break;
            }
        }

        void Polygon::clearBuffers()
        {
            commandList.clear();
            Path::clearBuffers();
        }

        void Polygon::buffer(double tolerance)
        {
            commandList.clear();
            if (points.size() > 0)
            {
                commandList.emplace_back(new PathCommands::MoveTo(points.front()));
                for (unsigned int i = 1; i < points.size(); ++i)
                {
                    commandList.emplace_back(new PathCommands::LineTo(points[i]));
                }
                commandList.emplace_back(new PathCommands::ClosePath());
            }
            Path::buffer(tolerance);
        }
    }
}

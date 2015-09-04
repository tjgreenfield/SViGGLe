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

#include "ElementsPolyLine.hh"
#include "ElementsPointsParser.hh"

#include <SVGL/CSS/CSSValues.hh>
#include <SVGL/PathCommands/PathCommands.hh>

namespace SVGL
{
    namespace Elements
    {
        PolyLine::PolyLine(Root* _parent) :
            Graphic(_parent)
        {
        }

        /***** CSS::Elements *****/
        const char* PolyLine::getTagName() const
        {
            return "polyline";
        }

        /***** XML::Node *****/
        void PolyLine::setAttribute(unsigned int index, SubString name, SubString value)
        {
            switch (index)
            {
            case Attribute::POINTS:
                PointsParser(value.start).readPoints(&points);
                break;
            case Attribute::D:
                break;
            default:
                Graphic::setAttribute(index, name, value);
                break;
            }
        }

         /***** Elements::Root *****/

        Instance_uptr PolyLine::calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext)
        {
            return std::move(Instance_uptr(new Instance(this, inherit, sizeContext)));
        }

        /***** Elements::PolyLine::Instance *****/

        PolyLine::Instance::Instance(const PolyLine* _polyline, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) :
            polyline(_polyline)
        {
            style.applyPropertySets(polyline->cascadedStyles, inherit, sizeContext);
        }

        void PolyLine::Instance::buffer(double tolerance)
        {
            PathCommands::List commandList;
            if (polyline->points.size() > 0)
            {
                commandList.emplace_back(new PathCommands::MoveTo(polyline->points.front()));
                for (unsigned int i = 1; i < polyline->points.size(); ++i)
                {
                    commandList.emplace_back(new PathCommands::LineTo(polyline->points[i]));
                }
            }

            tolerance = polyline->transform.transformTolerance(tolerance);
            renderBuffer.clear();
            renderBuffer.buffer(commandList, style, tolerance);
        }

        void PolyLine::Instance::render(Render::Context* context)
        {
            context->pushTransform(&polyline->transform);
            renderBuffer.render(context, style);
            context->popTransform();
        }
    }
}

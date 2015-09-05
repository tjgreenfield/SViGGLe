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
        Polygon::Polygon(Root* _parent) :
            Styled(_parent)
        {
        }

        /***** CSS::Elements *****/
        const char* Polygon::getTagName() const
        {
            return "polygon";
        }

        /***** XML::Node *****/

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
                Styled::setAttribute(index, name, value);
                break;
            }
        }

        /***** Elements::Root *****/

        Instance_uptr Polygon::calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext)
        {
            return std::move(Instance_uptr(new Instance(this, inherit, sizeContext)));
        }

        /***** Elements::Polygon::Instance *****/

        Polygon::Instance::Instance(const Polygon* _polygon, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) :
            polygon(_polygon)
        {
            style.applyPropertySets(polygon->cascadedStyles, inherit, sizeContext);
        }

        void Polygon::Instance::buffer(double tolerance)
        {
            PathCommands::List commandList;
            if (polygon->points.size() > 0)
            {
                commandList.emplace_back(new PathCommands::MoveTo(polygon->points.front()));
                for (unsigned int i = 1; i < polygon->points.size(); ++i)
                {
                    commandList.emplace_back(new PathCommands::LineTo(polygon->points[i]));
                }
                commandList.emplace_back(new PathCommands::ClosePath());
            }

            tolerance = polygon->transform.transformTolerance(tolerance);
            renderBuffer.clear();
            renderBuffer.buffer(commandList, style, tolerance);
        }

        void Polygon::Instance::render(Render::Context* context)
        {
            context->pushTransform(&polygon->transform);
            renderBuffer.render(context, style);
            context->popTransform();
        }
    }
}

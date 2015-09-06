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

#include "ElementsPath.hh"
#include <SVGL/PathCommands/PathCommandsParser.hh>

namespace SVGL
{
    namespace Elements
    {
        Path::Path(Root* _parent) :
            Styled(_parent)
        {
        }

        Path::~Path()
        {
            // TODO clean up instances?
        }

        /***** CSS::Element *****/
        const char* Path::getTagName() const
        {
            return "path";
        }

        // TODO: testAttributeValue() for all elements
        bool Path::testAttributeValue(unsigned int index, const char* attributeValue) const
        {
            return Styled::testAttributeValue(index, attributeValue);
        }

        /***** XML::Node *****/

        void Path::setAttribute(unsigned int index, SubString value)
        {
            switch (index)
            {
            case Attribute::D:
                commandList = PathCommands::Parser(value.start).readPathCommandsList();
                break;
            default:
                Styled::setAttribute(index, value);
                break;
            }
        }

        std::ostream& Path::stream(std::ostream& out) const
        {
            out << "path(" << commandList.size() << "|" << styleDeclarations.map.size() << ")";
            return out;
        }

        /***** Elements::Root *****/

        Instance_uptr Path::calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext)
        {
            return std::move(Instance_uptr(new Instance(this, inherit, sizeContext)));
        }

        /***** Path::Instance *****/

        Path::Instance::Instance(const Path* _path, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) :
            path(_path)
        {
            style.applyPropertySets(path->cascadedStyles, inherit, sizeContext);
        }

        void Path::Instance::buffer(double tolerance)
        {
            style.buffer(*this);

            renderBuffer.clear();
            tolerance = path->transform.transformTolerance(tolerance);
            renderBuffer.buffer(path->commandList, style, tolerance);
        }

        void Path::Instance::render(Render::Context* context) const
        {
            context->pushTransform(&path->transform);
            renderBuffer.render(context, style);
            context->popTransform();
        }

        void Path::Instance::calculateBoundingBox(BoundingBox* boundingBox) const
        {
            if (path->commandList.size())
            {
                *boundingBox = *path->commandList[0];

                for (const auto& command : path->commandList)
                {
                    command->calculateBoundingBox(boundingBox);
                }
            }
        }
    }
}

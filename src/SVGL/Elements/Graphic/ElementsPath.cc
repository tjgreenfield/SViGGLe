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
        Path::~Path()
        {
            clearBuffers();
        }

        /**
         * Get the Style object for the current element.
         *
         * @details The style object is used to apply styles from the stylesheets.
         * @return A pointer to the Style object.
         */
        CSS::Style* Path::getStyle()
        {
            return &style;
        }

        /**
         * Get the tag name of the element.
         */
        const char* Path::getTagName() const
        {
            return "path";
        }

        /**
         * Test the value of the specified attribute.
         *
         * @param[in] index The attribute index of the attribute to test.
         * @param[in] attributeValue The value of the attribute to test.
         */
        bool Path::testAttributeValue(unsigned int index, const char* attributeValue) const
        {
            return Graphic::testAttributeValue(index, attributeValue);
        }

        void Path::setAttribute(unsigned int index, SubString name, SubString value)
        {
            switch (index)
            {
            case Attribute::D:
                commandList = PathCommands::Parser(value.start).readPathCommandsList();
                break;
            default:
                Graphic::setAttribute(index, name, value);
                break;
            }
        }

        std::ostream& Path::stream(std::ostream& out) const
        {
            out << "path(" << commandList.size() << "|" << styleDeclarations.map.size() << ")";
            return out;
        }

        void Path::clearBuffers()
        {
            renderBuffer.clear();
            dirty = true;
        }

        void Path::buffer(double tolerance)
        {
            if (!dirty)
            {
                return;
            }
            Path::clearBuffers();
            tolerance = transform.transformTolerance(tolerance);
            renderBuffer.buffer(commandList, style, tolerance);

            dirty = false;
        }

        void Path::render(Render::Context* context)
        {
            context->pushTransform(&transform);
            renderBuffer.render(context, style);
            context->popTransform();
        }
    }
}

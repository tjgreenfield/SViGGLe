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
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "CSSTypeSelector.hh"

namespace SVGL
{
    namespace CSS
    {
        /**
         * TypeSelector
         */
        /**
         * Move Constructor
         * @param[in] _move Source of type
         */
        /*TypeSelector::TypeSelector(TypeSelector&& _move)
        {
            type = std::move(_move.type);
        }*/

        /**
         * Constructor
         * @param[in] _type Tag name the selector will match. Use "*" or "" for universal selector.
         */
        TypeSelector::TypeSelector(std::string&& _type) :
            type(std::move(_type))
        {
            
        }

        /**
         * Constructor
         * @param[in] _type Tag name the selector will match. Use "*" or "" for universal selector.
         */
        TypeSelector::TypeSelector(SubString _type) :
            type(_type)
        {
            
        }

        /**
         * Test if the type selector matches the element
         * @param[in] element The element to test
         * @retval true Selector matches element.
         * @retval false Selector doesn't match element.
         */
        bool TypeSelector::match(const Element* element) const
        {
            return type.empty() || type == "*" || type == element->getTagName();
        }

        /**
         * Output to stream
         */
        std::ostream& operator<<(std::ostream& out, const TypeSelector& typeSelector)
        {
            out << typeSelector.type;
            return out;
        }

    }
}

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

#include "CSSIDSelector.hh"

namespace SVGL
{
    namespace CSS
    {
        /**
         * ID selector.
         */
        /**
         * Constructor
         * @param[in] _id ID to match
         */
        IDSelector::IDSelector(std::string&& _id) :
            id(std::move(_id))
        {

        }

        /**
         * Constructor
         * @param[in] _id ID to match
         */
        IDSelector::IDSelector(SubString _id) :
            id(_id)
        {

        }

        /**
         * Destructor
         */
        IDSelector::~IDSelector()
        {
        
        }

        /**
         * Output to stream
         */
        std::ostream& IDSelector::stream(std::ostream& out) const
        {
            out << (const char*) "#";
            out << id;
            return out;
        }

        /**
         * Test if the attribute selector matches the element
         * @param[in] element The element to test
         * @retval true Selector matches element.
         * @retval false Selector doesn't match element.
         */
        bool IDSelector::match(const Element* element) const
        {
            return id == element->getAttributeValue("id");
        }

    }
}

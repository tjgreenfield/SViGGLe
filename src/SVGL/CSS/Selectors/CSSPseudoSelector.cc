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

#include "CSSPseudoSelector.hh"
#include <ostream>

namespace SVGL
{
    namespace CSS
    {
        /**
         * Pseudo selector, ie :first-child, :link, :visted, :hover, etc
         */

        /**
         * Constructor
         * @param[in] _type Type of the pseudoi selector
         * @param[in] _subtype Subtype of the pseudoi selector
         */
        PseudoSelector::PseudoSelector(std::string&& _type, std::string&& _subtype) :
            type(std::move(_type)),
            subtype(std::move(_subtype))
        {

        }

        /**
         * Constructor
         * @param[in] _type Type of the pseudoi selector
         * @param[in] _subtype Subtype of the pseudoi selector
         */
        PseudoSelector::PseudoSelector(SubString _type, SubString _subtype) :
            type(_type),
            subtype(_subtype)
        {

        }

        /**
         * Destructor
         */
        PseudoSelector::~PseudoSelector()
        {

        }

        /**
         * Output to stream
         */
        std::ostream& PseudoSelector::stream(std::ostream& out) const
        {
            out << ":" << type;
            if (subtype != "")
            {
                out << "(" << subtype << ")";
            }
            return out;
        }

        /**
         * Test if the attribute selector matches the element
         * @param[in] element The element to test
         * @retval true Selector matches element.
         * @retval false Selector doesn't match element.
         */
        bool PseudoSelector::match(const Element*) const
        {
            // TODO
            return false;
        }
    }
}

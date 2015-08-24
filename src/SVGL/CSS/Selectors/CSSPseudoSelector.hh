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

#pragma once

#include "CSSSubSelector.hh"
#include <SVGL/CSS/CSSElement.hh>
#include <SVGL/Types/SubString.hh>
#include <string>

namespace SVGL
{
    namespace CSS
    {
        /**
         * Pseudo selector, ie :first-child, :link, :visted, :hover, etc
         */
        class PseudoSelector : public SubSelector
        {
        protected:
            std::string type; //!< Type of the pseudo selector
            std::string subtype; //!< Subtype of the pseudo selector

        public:
            /**
             * Constructor
             * @param[in] _type Type of the pseudoi selector
             * @param[in] _subtype Subtype of the pseudoi selector
             */
            PseudoSelector(std::string&& _type, std::string&& _subtype = "");

            /**
             * Constructor
             * @param[in] _type Type of the pseudoi selector
             * @param[in] _subtype Subtype of the pseudoi selector
             */
            PseudoSelector(SubString _type, SubString _subtype = SubString(""));

            /**
             * Destructor
             */
            ~PseudoSelector();

            /**
             * Test if the attribute selector matches the element
             * @param[in] element The element to test
             * @retval true Selector matches element.
             * @retval false Selector doesn't match element.
             */
            bool match(const Element* element) const override;

            /**
             * Output to stream
             */
            std::ostream& stream(std::ostream& out) const override;
        };
    }
}

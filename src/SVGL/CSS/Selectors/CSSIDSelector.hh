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
         * ID selector.
         */class IDSelector : public SubSelector
        {
        protected:
            std::string id; //!< The id to match

        public:
            /**
             * Constructor
             * @param[in] _id ID to match
             */
            IDSelector(std::string&& _id);

            /**
             * Constructor
             * @param[in] _id ID to match
             */
            IDSelector(SubString _id);

            /**
             * Destructor
             */
            ~IDSelector();

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

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

#include <SVGL/CSS/CSSElement.hh>
#include <SVGL/Types/SubString.hh>
#include <string>
#include <memory>

namespace SVGL
{
    namespace CSS
    {


        /**
         * Virtual class that represents interface between various types of sub selectors
         */
        class SubSelector
        {
        public:
            /**
             * Virtual Destructor
             */
            virtual ~SubSelector();

            /**
             * Test if the subselector matches the element
             * @param[in] element The element to test
             * @retval true Selector matches element.
             * @retval false Selector doesn't match element.
             */
            virtual bool match(const Element* element) const = 0;

            virtual std::ostream& stream(std::ostream& out) const = 0;
        };

        typedef std::unique_ptr<SubSelector> SubSelector_uptr;

        std::ostream& operator<<(std::ostream& out, const SubSelector& subSelector);
    }
}

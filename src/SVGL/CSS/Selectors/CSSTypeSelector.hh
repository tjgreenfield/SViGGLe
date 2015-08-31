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

namespace SVGL
{
    namespace CSS
    {
        class CSSElement;

        /**
          * Selector that represents a specific element type (includes universal selector with empty string)
          */
        class TypeSelector
        {
            friend class Parser;
            friend std::ostream& operator<<(std::ostream& out, const TypeSelector& typeSelector);

        protected:
            std::string type; //!< The string that represents the element tag name or "*"/"" for universal selector

        public:
            /**
             * Move Constructor
             * @param[in] _move Source of type
             */
            //TypeSelector(TypeSelector&& _move);

            /**
             * Constructor
             * @param[in] _type Tag name the selector will match. Use "*" or "" for universal selector.
             */
            TypeSelector(std::string&& _type);

            /**
             * Constructor
             * @param[in] _type Tag name the selector will match. Use "*" or "" for universal selector.
             */
            TypeSelector(SubString _type);

            /**
             * Test if the type selector matches the element
             * @param[in] element The element to test
             * @retval true Selector matches element.
             * @retval false Selector doesn't match element.
             */
            bool match(const CSSElement* element) const;
        };

        std::ostream& operator<<(std::ostream& out, const TypeSelector& typeSelector);
    }
}

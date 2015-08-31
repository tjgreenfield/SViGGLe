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
#include "CSSTypeSelector.hh"
#include <SVGL/CSS/CSSElement.hh>
#include <SVGL/Types/SubString.hh>
#include <string>
#include <memory>

namespace SVGL
{
    namespace CSS
    {
        typedef unsigned int SelectorSpecificity;
        namespace Specificity
        {
            const unsigned int A = 1 << 24;
            const unsigned int B = 1 << 16;
            const unsigned int C = 1 << 8;
            const unsigned int D = 1;
        }

        /**
         * Simple selector. Combination of a type selector and a set of subselectors
         */
        class SimpleSelector
        {
            friend std::ostream& operator<<(std::ostream& out, const SimpleSelector& simpleSelector);

        public:

            typedef std::vector<SubSelector_uptr> SubSelectors; //!< Set of subselectors

            TypeSelector type; //!< The main element type for this simple selector
            SubSelectors subSelectors; //!< The set of subselectors

        public:
            /**
             * Constructor
             * param[in] _type Element type to match
             */
            SimpleSelector(std::string&& _type);

            /**
             * Constructor
             * param[in] _type Element type to match
             */
            SimpleSelector(SubString _type = SubString(""));

            /**
             * Test if the simple selector matches the element
             * @param[in] element The element to test
             * @retval true Selector matches element.
             * @retval false Selector doesn't match element.
             */
            bool match(const CSSElement* element) const;

            /**
             * Calculate the specificity of this selector
             * @return The specificity of the selector
             */
            SelectorSpecificity calcSpecificity() const;
        };

        typedef std::unique_ptr<SimpleSelector> SimpleSelector_uptr;

        std::ostream& operator<<(std::ostream& out, const SimpleSelector& simpleSelector);
    }
}

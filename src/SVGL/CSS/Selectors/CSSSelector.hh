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
#include "CSSSimpleSelector.hh"
#include "CSSCombinator.hh"
#include <SVGL/CSS/CSSElement.hh>
#include <SVGL/Types/SubString.hh>
#include <string>
#include <memory>

namespace SVGL
{
    namespace CSS
    {
        /**
         * A chain of simple selectors, linked by combinators, optionally ending with pseduo selector.
         * It can calculate its specificity
         */
        class Selector
        {
            friend std::ostream& operator<<(std::ostream& out, const Selector& selector);

        public:
            typedef std::vector<Combinator> Conbinators; //!< A set of combinators (w/selectors)

            Conbinators combinators; //!< The set of combinators (w/selectors)
            SelectorSpecificity specificity; //!< cached specificity calculation

        public:
            /**
             * Constructor
             * param[in] _first The first simple selector
             */
            Selector(SimpleSelector_uptr&& _first);

            /**
             * Calculate the specificity of this selector
             * @return The specificity of the selector
             */
            void calcSpecificity();

            /**
             * Get the specificity of this selector, calculate if necessary
             * @return The specificity of the selector
             */
            SelectorSpecificity getSpecificity();

            /**
             * Test if the simple selector matches the element
             * @param[in] element The element to test
             * @retval true Selector matches element.
             * @retval false Selector doesn't match element.
             */
            bool match(const Element* element) const;
        };

        typedef std::unique_ptr<Selector> Selector_uptr;

        std::ostream& operator<<(std::ostream& out, const Selector& selector);
    }
}

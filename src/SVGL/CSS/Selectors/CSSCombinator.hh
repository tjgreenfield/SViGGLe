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
#include <SVGL/CSS/CSSElement.hh>
#include <SVGL/Types/SubString.hh>
#include <string>
#include <memory>

namespace SVGL
{
    namespace CSS
    {
        /**
         * A combinator and a selector
         */
        class Combinator
        {
            friend std::ostream& operator<<(std::ostream& out, const Combinator& combinator);
        public:
            /**
             * The range of combinator types
             */
            enum Type { FIRST, DECENDANT, CHILD, ADJACENT_SIBLING, INVALID };

        public:
            Type type; //!< The type of this combinator
            SimpleSelector_uptr selector; //!< The selector

        public:

            /**
             * Move Constructor
             */
            Combinator(Combinator&& combinator);

            /**
             * Constructor
             * param[in] _type The type of the combinator
             * param[in] _selector The selector the combinator links to
             */
            Combinator(Type _type, SimpleSelector_uptr&& _selector);

            /**
             * Tests if valid
             */
            inline operator bool() const
            {
                return type != INVALID;
            }
        };

        std::ostream& operator<<(std::ostream& out, const Combinator& combinator);
    }
}

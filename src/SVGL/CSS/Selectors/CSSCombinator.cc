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

#include "CSSCombinator.hh"
#include <utility>

namespace SVGL
{
    namespace CSS
    {
        /**
         * A combinator and a selector
         */
        /**
         * Move Constructor
         */
        Combinator::Combinator(Combinator&& _move) :
            type(std::move(_move.type)),
            selector(std::move(_move.selector))
        {

        }

        /**
         * Constructor
         * param[in] _type The type of the combinator
         * param[in] _selector The selector the combinator links to
         */
        Combinator::Combinator(Type _type, SimpleSelector_uptr&& _selector) :
            type(_type),
            selector(std::move(_selector))
        {
        }

        /**
         * Output to stream
         */
        std::ostream& operator<<(std::ostream& out, const Combinator& combinator)
        {
            switch (combinator.type)
            {
            default:
            case Combinator::INVALID:
            case Combinator::FIRST:
                break;
            case Combinator::DECENDANT:
                out << " ";
                break;
            case Combinator::CHILD:
                out << ">";
                break;
            case Combinator::ADJACENT_SIBLING:
                out << "+";
                break;
            }
            out << *combinator.selector;
            return out;
        }
    }
}

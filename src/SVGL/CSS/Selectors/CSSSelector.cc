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

#include "CSSSelector.hh"

namespace SVGL
{
    namespace CSS
    {
        /**
         * A chain of simple selectors, linked by combinators, optionally ending with pseduo selector.
         * It can calculate its specificity
         */

        /**
         * Constructor
         * param[in] _first The first simple selector
         */
        Selector::Selector(SimpleSelector_uptr&& _first) :
            specificity(0)
        {
            combinators.push_back(Combinator(Combinator::FIRST, std::move(_first)));
        }

        /**
         * Output to stream
         */
        std::ostream& operator<<(std::ostream& out, const Selector& selector)
        {
            for (const Combinator& i : selector.combinators)
            {
                out << i;
            }
            return out;
        }

        /**
         * Calculate the specificity of this selector
         * @return The specificity of the selector
         */
        void Selector::calcSpecificity()
        {
            specificity = 0;
            for (const Combinator& i : combinators)
            {
                specificity += i.selector->calcSpecificity();
            }
        }

        /**
         * Get the specificity of this selector, calculate if necessary
         * @return The specificity of the selector
         */
        SelectorSpecificity Selector::getSpecificity()
        {
            if (!specificity)
            {
                calcSpecificity();
            }
            return specificity;
        }

        /**
         * Test if the simple selector matches the element
         * @param[in] element The element to test
         * @retval true Selector matches element.
         * @retval false Selector doesn't match element.
         */
        bool Selector::match(const Element* element) const
        {
            int i(combinators.size() - 1);
            while ((element && i >= 0) ? combinators[i].selector->match(element) : false)
            {
                switch (combinators[i].type)
                {
                    case Combinator::FIRST:
                        return true;
                    case Combinator::DECENDANT:
                        --i;
                        element = element->getParent();
                        while (element ? !combinators[i].selector->match(element) : false)
                        {
                            element = element->getParent();
                        }
                        break;
                    case Combinator::CHILD:
                        --i;
                        element = element->getParent();
                        break;
                    case Combinator::ADJACENT_SIBLING:
                        --i;
                        element = element->getPrevSibling();
                        break;
                    case Combinator::INVALID:
                    default:
                        return false;
                }
            }
            return false;
        }
    }
}

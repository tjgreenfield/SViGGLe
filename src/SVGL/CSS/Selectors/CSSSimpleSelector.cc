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

#include "CSSSimpleSelector.hh"
#include "CSSIDSelector.hh"

namespace SVGL
{
    namespace CSS
    {
        /**
         * Simple selector. Combination of a type selector and a set of subselectors
         */

        /**
         * Constructor
         * param[in] _type Element type to match
         */
        SimpleSelector::SimpleSelector(std::string&& _type) :
            type(std::move(_type))
        {
        
        }

        /**
         * Constructor
         * param[in] _type Element type to match
         */
        SimpleSelector::SimpleSelector(SubString _type) :
            type(_type)
        {
        
        }

        /**
         * Output to stream
         */
        std::ostream& operator<<(std::ostream& out, const SimpleSelector& simpleSelector)
        {
            out << simpleSelector.type;
            for (const SubSelector_uptr& i : simpleSelector.subSelectors)
            {
                out << *i.get();
            }
            return out;
        }

        /**
         * Test if the simple selector matches the element
         * @param[in] element The element to test
         * @retval true Selector matches element.
         * @retval false Selector doesn't match element.
         */
        bool SimpleSelector::match(const Element* element) const
        {
            if (!type.match(element)) return false;
            for (const SubSelector_uptr& i : subSelectors)
            {
                if (!i->match(element)) return false;
            }
            return true;
        }

        /**
         * Calculate the specificity of this selector
         * @return The specificity of the selector
         */
        SelectorSpecificity SimpleSelector::calcSpecificity() const
        {
            SelectorSpecificity result(Specificity::D);
            for (const SubSelector_uptr& i : subSelectors)
            {
                if (typeid(*i) == typeid(IDSelector))
                {
                    result += Specificity::B;
                }
                else // Attribute & Pseudo Selectors
                {
                    result += Specificity::C;
                }
            }
            return result;
        }
    }
}

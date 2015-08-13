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
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "CSSAttributeSelector.hh"

namespace SVGL
{
    namespace CSS
    {
        /**
         * Constructor
         * @param[in] _name Attribute name
         * @param[in] _value Attribute value to match
         * @param[in] _mode Matching mode
         */
        AttributeSelector::AttributeSelector(std::string&& _name, std::string&& _value, Mode _mode) :
            name(std::move(_name)),
            value(std::move(_value)),
            mode(_mode)
        {

        }

        /**
         * Constructor
         * @param[in] _name Attribute name
         * @param[in] _value Attribute value to match
         * @param[in] _mode Matching mode
         */
        AttributeSelector::AttributeSelector(SubString _name, SubString _value, Mode _mode) :
            name(_name),
            value(_value),
            mode(_mode)
        {

        }
        
        /**
         * Destructor
         */
        AttributeSelector::~AttributeSelector()
        {
        
        }

        /**
         * Output to stream
         */
        std::ostream& AttributeSelector::stream(std::ostream& out) const
        {
            switch (mode)
            {
                case EMPTY:
                    out << "[" << name << "]";
                    break;
                case CLASS:
                    out << "." << value;
                    break;
                case MATCH:
                    out << "[" << name << "='" << value << "']";
                    break;
                case LIST_MATCH:
                    out << "[" << name << "~='" << value << "']";
                    break;
                case STARTS_WITH:
                    out << "[" << name << "|='" << value << "']";
                    break;
            }
            return out;
        }

        /**
         * Test if the attribute selector matches the element
         * @param[in] element The element to test
         * @retval true Selector matches element.
         * @retval false Selector doesn't match element.
         */
        bool AttributeSelector::match(const Element* element) const
        {
            const char* attrValue = element->getAttributeValue(name.c_str());
            switch (mode)
            {
                case MATCH:
                    return value == attrValue;

                case LIST_MATCH:
                    return false; // TODO

                case STARTS_WITH:
                    return false; // TODO

                case EMPTY:
                default:
                    return attrValue != nullptr;
            }
        }
    }
}

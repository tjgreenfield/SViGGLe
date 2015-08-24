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

#include "CSSDeclaration.hh"

namespace SVGL
{
    namespace CSS
    {
        /**
         * Declaration: Combination of name, value and important flag
         */
        /**
         * Constructor
         * @param[in] _name The name of the attribute
         * @param[in] _value The value to be assigned
         * @param[in] _important Important flag
         */
        Declaration::Declaration(std::string&& _name, Value_uptr _value, bool _important) :
            name(std::move(_name)),
            value(std::move(_value)),
            important(_important)
        {

        }

        /**
         * Constructor
         * @param[in] _name The name of the attribute
         * @param[in] _value The value to be assigned
         * @param[in] _important Important flag
         */
        Declaration::Declaration(SubString _name, Value_uptr _value, bool _important) :
            name(_name),
            value(std::move(_value)),
            important(_important)
        {

        }

        /**
         * Constructor
         * @param[in] _name The name of the attribute
         * @param[in] _value The value to be assigned
         * @param[in] _important Important flag
         */
        Declaration::Declaration(const char* _name, Value_uptr _value, bool _important) :
            name(_name),
            value(std::move(_value)),
            important(_important)
        {

        }

        /**
         * Output to stream
         */
        std::ostream& operator<<(std::ostream& out, const Declaration& declaration)
        {
            out << declaration.name;
            out << ":";
            out << *declaration.value;
            return out;
        }
    }
}

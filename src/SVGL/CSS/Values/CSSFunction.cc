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

#include "CSSFunction.hh"
#include <ostream>

namespace SVGL
{
    namespace CSS
    {

        /**
         * Function: A function call consisting of a function name and a set of parameters.
         */

        /**
         * Constructor with initial value
         * param[in] _hash The initial string value
         */
        Function::Function(std::string&& _function) :
            function(std::move(_function))
        {
        }

        /**
         * Constructor with initial value
         * param[in] _hash The initial string value
         */
        Function::Function(SubString _function) :
            function(_function)
        {
        }

        /**
         * Output to stream.
         */
        std::ostream& Function::stream(std::ostream& out) const
        {
            out << function;
            bool first(true);
            for (const Value_uptr& i : parameters)
            {
                if (!first)
                {
                    out << ",";
                }
                else
                {
                    first = false;
                }
                out << *i;
            }
            return out;
        }
    }
}

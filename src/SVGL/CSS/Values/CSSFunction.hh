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

#include "CSSValue.hh"
#include <SVGL/Types/SubString.hh>

#include <vector>
#include <string>
#include <memory>

namespace SVGL
{
    namespace CSS
    {
        /**
         * A function call consisting of a function name and a set of parameters.
         */
        class Function : public Value
        {
        public:
            typedef std::vector<Value_uptr> Parameters; //!< Set of values representing function parameters

            std::string function; //!< The name of the function.
            Parameters parameters; //!< The set of parameters.

            /**
             * Constructor with initial value
             * param[in] _function The function name
             */
            Function(std::string&& _function);

            /**
             * Constructor with initial value
             * param[in] _function The function name
             */
            Function(SubString _function);

            /**
             * Output to stream.
             */
            std::ostream& stream(std::ostream& out) const override;
        };

        typedef std::unique_ptr<Function> Function_uptr; //!< Used to manage ownership of Function objects
    }
}

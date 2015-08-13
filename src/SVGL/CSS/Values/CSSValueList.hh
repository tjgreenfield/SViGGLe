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

#pragma once

#include <SVGL/CSS/Values/CSSValue.hh>
#include <SVGL/Types/SubString.hh>

#include <vector>
#include <string>

namespace SVGL
{
    namespace CSS
    {
        /**
         * Set of multiple values
         */
        class ValueList : public Value
        {
        public:
            typedef std::vector<Value_uptr> Vector; //!< Set of values representing the list of values

            Vector vector; //!< The set of values

            /**
             * Output to stream.
             */
            std::ostream& stream(std::ostream& out) const override;
        };
    }
}

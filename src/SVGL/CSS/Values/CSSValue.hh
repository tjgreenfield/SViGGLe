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

#include <string>
#include <memory>
#include <ostream>

namespace SVGL
{
    namespace CSS
    {
        /**
          * An abstract class representing a generic CSS property values.
          */
        class Value
        {
        public:
            /**
             * Virtual destructor
             */
            virtual ~Value();

            /**
             * Output to stream.
             */
            virtual std::ostream& stream(std::ostream& out) const = 0;
        };

        typedef std::unique_ptr<Value> Value_uptr; //!< Used to manage ownership of Value objects

        std::ostream& operator<<(std::ostream& out, const Value& value);
    }
}

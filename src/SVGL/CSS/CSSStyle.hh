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

#include <SVGL/CSS/CSSValues.hh>

namespace SVGL
{
    namespace CSS
    {
        /**
         * An abstract class for implementation style classes
         */
        class Style
        {
        public:

            /**
             * Virtualised destructor
             */
            virtual ~Style();

            /**
             * Set the style property of the style object.
             * @details
             * Compiles the value string into a Value object before calling the virtual version of the function
             *
             * @param[in] name The name of the style property to set.
             * @param[in] value The a string representation of the value to assign to the property.
             */
            void setProperty(const char* name, const char* value);

            /**
             * Set the style property of the style object.
             *
             * @param[in] name The name of the style property to set.
             * @param[in] value The value to assign to the property.
             */
            virtual void setProperty(const char* name, const Value* value) = 0;
        };
    }
}

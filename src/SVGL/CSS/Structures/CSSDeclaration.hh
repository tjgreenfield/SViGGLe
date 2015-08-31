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

#include <SVGL/CSS/CSSProperty.hh>
#include <SVGL/CSS/CSSValues.hh>
#include <SVGL/Types/SubString.hh>
#include <string>
#include <memory>

namespace SVGL
{
    namespace CSS
    {
        /**
         * Declaration, combination of name, value and important flag
         */
        class Declaration
        {
            friend std::ostream& operator<<(std::ostream& out, const Declaration& declaration);

        protected:

        public:
            Property::Index property; //!< The name of the property
            Value_uptr value; //!< The value to be assigned
            bool important; //!< Important flag

            /**
             * Constructor
             * @param[in] _name The name of the property
             * @param[in] _value The value to be assigned
             * @param[in] _important Important flag
             */
            Declaration(std::string& _name, Value_uptr _value = nullptr, bool _important = false);

            /**
             * Constructor
             * @param[in] _name The name of the property
             * @param[in] _value The value to be assigned
             * @param[in] _important Important flag
             */
            Declaration(SubString _name, Value_uptr _value = nullptr, bool _important = false);

            /**
             * Constructor
             * @param[in] _name The name of the property
             * @param[in] _value The value to be assigned
             * @param[in] _important Important flag
             */
            Declaration(const char* _name = "", Value_uptr _value = nullptr, bool _important = false);

            /**
             * Constructor
             * @param[in] _name The name of the property
             * @param[in] _value The value to be assigned
             * @param[in] _important Important flag
             */
            Declaration(Property::Index _property, Value_uptr _value = nullptr, bool _important = false);
        };

        typedef std::unique_ptr<Declaration> Declaration_uptr;

        std::ostream& operator<<(std::ostream& out, const Declaration& declaration);
    }
}

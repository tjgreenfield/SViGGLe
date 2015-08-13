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

#include "CSSValue.hh"
#include <SVGL/Types/SubString.hh>
#include <string>

namespace SVGL
{
    namespace CSS
    {
        /**
         * An identifier value.
         */
        class Ident : public Value
        {
        public:
            std::string ident; //!< The identifier

            /**
             * Constructor
             *
             * param[in] _ident The identifier
             */
            Ident(std::string&& _ident);

            /**
             * Constructor
             *
             * param[in] _ident The identifier
             */
            Ident(SubString _ident);

            /**
             * Output to stream.
             */
            std::ostream& stream(std::ostream& out) const override;
        };
    }
}

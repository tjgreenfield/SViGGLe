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

#include "CSSIdent.hh"

namespace SVGL
{
    namespace CSS
    {

        /**
         * Ident: An identifier value.
         */

        /**
         * Constructor
         *
         * param[in] _ident The identifier
         */
        Ident::Ident(std::string&& _ident) :
            ident(std::move(_ident))
        {

        }

        /**
         * Constructor
         *
         * param[in] _ident The identifier
         */
        Ident::Ident(SubString _ident) :
            ident(_ident.start, _ident.count)
        {

        }


        /**
         * Output to stream.
         */
        std::ostream& Ident::stream(std::ostream& out) const
        {
            return out << ident;
        }
    }
}

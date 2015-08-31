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

#include "CSSValues.hh"
#include <SVGL/Types/Color.hh>

#include <string>

namespace SVGL
{
    namespace CSS
    {
        enum ColorState { COLOR, INHERIT, NONE };

        class Hash;
        class Function;
        bool colorFromHash(Color* color, const Hash* hash, unsigned char alpha = 255);
        bool colorFromRGBFunc(Color* color, const Function* function, unsigned char alpha = 255);
        bool colorFromValue(Color* color, const Value* value, unsigned char alpha = 255);

    }


}


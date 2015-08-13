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

#include "CSSValues.hh"
#include <SVGL/Types/Color.hh>
#include <string>
#include <map>

namespace SVGL
{
    namespace CSS
    {
        typedef std::map<std::string, int> ColorMap;
        enum ColorState { COLOR, INHERIT, NONE };

        class Hash;
        class Function;
        Color colorFromHash(const Hash* hash);
        Color colorFromRGBFunc(const Function* function);
        Color colorFromValue(const Value* value, ColorState* state);

        extern ColorMap colorMap;
    }

    
}


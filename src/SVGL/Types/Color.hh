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

namespace SVGL
{
    typedef unsigned int Color;

    /**
     * Create color from r, g & b values.
     */
    constexpr Color RGB(unsigned int r, unsigned int g, unsigned int b)
    {
        return (255 << 24) + (r << 16) + (g << 8) + b;
    }

    /**
     * Create color from rgb & a values.
     */
    constexpr Color RGBA(unsigned int rgb, unsigned int a)
    {
        return (a << 24) + (0xFFFFFF & rgb);
    }

    /**
     * Create color from r, g, b & a values.
     */
    constexpr Color RGBA(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
    {
        return (a << 24) + (r << 16) + (g << 8) + b;
    }
}

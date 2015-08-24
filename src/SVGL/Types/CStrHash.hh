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
#include <cstring>

namespace SVGL
{
    /**
     * Equals type for const char* based unordered_map
     */
    class CStrEquals
    {
    public:
        /**
         * Equals operator
         * @param[in] a a
         * @param[in] b b
         */
        bool operator()(const char* a, const char* b) const
        {
            return strcmp(a, b) == 0;
        }
    };

    /**
     * Hash type for const char* based unordered_map
     */
    class CStrHash
    {
    public:
        /**
         * BJD hash algorithm
         * @param[in] s String to hash
         */
        int operator()(const char* s)const
        {
            unsigned int hash = 5381;
            while (*s)
            {
                hash += (hash << 5) + (*s);
                ++s;
            }
            return hash;
        }
    };
}

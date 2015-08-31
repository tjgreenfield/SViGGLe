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

#include <vector>
#include <cstring>
#include <string>
#include <functional>
#include <ostream>
#include <utility>

namespace SVGL
{

    /**
     * SubString: struct that points to a string of particular length
     * @details
     * The memory containing the string must be managed elsewhere and must remain valid for the life of the SubString object
     */
    struct SubString
    {
        const char* start;
        unsigned int count;

        /**
         * Constructor
         */
        inline SubString(const char* _start, unsigned int _count) :
            start(_start),
            count(_count)
        {
        }

        /**
         * Constructor
         */
        inline SubString(const char* _start) :
            start(_start),
            count(strlen(_start))
        {
        }

        /**
         * Default Constructor
         */
        inline SubString() :
            start(nullptr),
            count(0)
        {
        }

        /**
         * Allows simple validioty test
         */
        inline operator bool() const
        {
            return start != nullptr;
        }

        /**
         * Comparison operator
         * @retval true If both strings are valid and contents of the strings match
         * @retval false If either string is not valid or contents differ
         */
        inline bool operator==(const SubString& other) const
        {
            if (start && other.start)
            {
                if (count == other.count)
                {
                    return strncmp(start, other.start, count) == 0;
                }
            }
            return false;
        }

        /**
         * Convert to std::string
         */
        inline operator std::string() const
        {
            return std::string(start, count);
        }
    };
}

namespace std
{
    /**
     * SubString Template for std::hash to allow SubString to be used as map key
     */
    template<>
    struct hash<SVGL::SubString>
    {
        typedef SVGL::SubString argument_type;
        typedef std::size_t result_type;

        /**
         * BJD hash algorithm
         * @param[in] s SubString to hash
         */
        inline result_type operator()(argument_type const& subString) const
        {
            unsigned int hashValue = 5381;
            const char* s = subString.start;
            const char* e = subString.start + subString.count;
            while ( (*s) && (s < e))
            {
                hashValue += (hashValue << 5) + (*s);
                ++s;
            }
            return hashValue;
        }
    };
}

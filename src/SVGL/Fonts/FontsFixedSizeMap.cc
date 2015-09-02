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

#include "FontsFixedSizeMap.hh"

namespace SVGL
{
    namespace Font
    {
        LookupCode FixedSizeMap::lookup(const File** file, const std::string& style, int fsize) const
        {
            if (empty()) return FLC_FAIL_STYLE_SIZE;

            int returnCode = FLC_SUCCESS;
            const StyleMap* styleMap;

            const_iterator i = find(fsize);
            if (i != end())
            {
                // use the exact size if found
                styleMap = &(i->second);
            }
            else
            {
                const_reverse_iterator ri;
                returnCode = FLC_FAIL_SIZE;
                // go through in reverse order to find the biggest size, that's smaller than the requested size
                for (ri = rbegin(); ri != rend(); ++ri)
                {
                    if (ri->first < fsize)
                    {
                        styleMap = &(ri->second);
                        break;
                    }
                }
                // if none are smaller, just return the smallets
                if (ri == rend())
                {
                    styleMap = &(begin()->second);
                }
            }
            returnCode |= styleMap->lookup(file, style);
            return (LookupCode)returnCode;
        }

        void FixedSizeMap::insert(const char* path, int index, const std::string& style, int sizeIndex, int fsize)
        {
            iterator i = find(fsize);
            if (i == end())
            {
                emplace(fsize, StyleMap());
            }
            at(fsize).emplace(style, std::move(File(path, index, sizeIndex, fsize)));
        }
    }
}

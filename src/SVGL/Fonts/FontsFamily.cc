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

#include "FontsFamily.hh"

namespace SVGL
{
    namespace Font
    {
        LookupCode Family::lookup(const File** file, const std::string& style, int fsize) const
        {
            if (fsize == -1)
            {
                return styleMap.lookup(file, style);
            }
            else
            {
                return fixedSizeMap.lookup(file, style, fsize);
            }
        }

        void Family::insert(const char* path, int index, const std::string& style, int sizeIndex, int fsize)
        {
            if (fsize == -1)
            {
                styleMap.emplace(style, std::move(File(path, index, sizeIndex, fsize)));
            }
            else
            {
                fixedSizeMap.insert(path, index, style, sizeIndex, fsize);
            }
        }
    }
}

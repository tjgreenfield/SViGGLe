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

#include "ImagesCollection.hh"
#include "ImagesPNG.hh"

namespace SVGL
{
    namespace Images
    {
        Collection::Map Collection::map;

        Image* Collection::loadImage(const char* path)
        {
            const auto& i = map.find(path);
            if (i != map.end())
            {
                return &i->second;
            }

            const auto& e = map.emplace(path, std::move(Image()));
            if (PNG::loadTexture(&e.first->second.texture, path))
            {
                return &e.first->second;
            }
            else
            {
                map.erase(path);
                return nullptr;
            }
        }
    }
}

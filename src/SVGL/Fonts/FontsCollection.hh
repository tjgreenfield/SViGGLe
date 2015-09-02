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

#include "FontsFile.hh"
#include "FontsFamily.hh"
#include "FontsFace.hh"
#include "FontsStyledFace.hh"
#include "FontsStyledFaceKey.hh"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <map>
#include <vector>
#include <string>

namespace SVGL
{
    namespace Font
    {
        class Collection
        {
            friend class Face;
            friend class StyledFaceHandle;

        protected:
            static FT_Library ftLibrary;

            typedef std::map<int, Face> FontFileIndexMap;
            typedef std::map<std::string, FontFileIndexMap> FontFileMap;
            static FontFileMap fontFileMap;

            typedef std::map<std::string, Family> FamilyMap;
            static FamilyMap familyMap;

            typedef std::map<std::string, std::string> GenericMap;
            static GenericMap genericMap;

            typedef std::map<StyledFaceKey, StyledFace> StyledFaceMap;
            static StyledFaceMap styledFaceMap;

            static void release(const StyledFaceKey& key);

        public:

            static int ftInit();

            static void scanFile(const char* path);

            static void scanDirectory(const char* path);

            static void scanFace(FT_Face face, const char* path, int index);

            static Family& getFamily(const std::string& family);

            static Face* getFontByFile(const std::string& path, int index=0);

            static void setGeneric(const std::string& generic, const std::string& family);

            static LookupCode lookup(const File** file, const std::string& family, const std::string& style, int fsize = -1);
            static LookupCode lookup(const File** file, const std::vector<std::string>& families, const std::string& style, int fsize = -1);

            static LookupCode lookup(Face** face, const std::string& family, const std::string& style, int fsize = -1);
            static LookupCode lookup(Face** face, const std::vector<std::string>& families, const std::string& style, int fsize = -1);

            static StyledFaceHandle request(const StyledFaceKey& key);
        };
    }
}

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

#include "FontCollection.hh"

#include <SVGL/External/tinydir.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <iostream>

namespace SVGL
{
    namespace Font
    {
        FT_Library Collection::ftLibrary;
        Collection::FontFileMap Collection::fontFileMap;

        Collection::FamilyMap Collection::familyMap;

        Collection::GenericMap Collection::genericMap;

        Collection::StyledFaceMap Collection::styledFaceMap;

        int Collection::ftInit()
        {
            return FT_Init_FreeType(&ftLibrary);
        }

        void Collection::scanDirectory(const char* path)
        {
            tinydir_dir dir;
            tinydir_open(&dir, path);

            std::string nextpath;

            while (dir.has_next)
            {
                tinydir_file file;
                tinydir_readfile(&dir, &file);

                if (file.name[0] == '.')
                {
                    if (file.name[1] == '.')
                    {
                        tinydir_next(&dir);
                        continue;
                    }
                    else if (file.name[1] == 0)
                    {
                        tinydir_next(&dir);
                        continue;
                    }
                }
                if (file.is_dir)
                {
                    scanDirectory(file.path);
                }
                else if (file.is_reg)
                {
                    scanFile(file.path);
                }
                tinydir_next(&dir);
            }
        }

        Family& Collection::getFamily(const std::string& family)
        {
            FamilyMap::iterator i = familyMap.find(family);
            if (i == familyMap.end())
            {
                return familyMap[family] = Family();
            }
            return i->second;
        }

        Face* Collection::getFontByFile(const std::string& path, int index)
        {
            FontFileIndexMap* indexMap;

            FontFileMap::iterator iFile = fontFileMap.find(path);
            if (iFile != fontFileMap.end())
            {
                indexMap = &(iFile->second);
            }
            else
            {
                indexMap = &(fontFileMap.emplace(path, FontFileIndexMap()).first->second);
            }

            FontFileIndexMap::iterator iIndex = indexMap->find(index);
            if (iIndex != indexMap->end())
            {
                return &(iIndex->second);
            }
            else
            {
                return &(indexMap->emplace(index, std::move(Face(path, index))).first->second);
            }
        }

        void Collection::scanFace(FT_Face face, const char* path, int index)
        {
            if (face->face_flags & FT_FACE_FLAG_SCALABLE)
            {
                getFamily(face->family_name).insert(path, index, face->style_name);
                //std::cout << face->family_name << ":" << face->style_name << " @ " << path << "#" << index << std::endl;

            }
            if (face->face_flags & FT_FACE_FLAG_FIXED_SIZES)
            {
                for (int i = 0; i < face->num_fixed_sizes; ++i)
                {
                    getFamily(face->family_name).insert(path, index, face->style_name, i, face->available_sizes[i].size >> 6);
                    //std::cout << face->family_name << ":" << face->style_name << "$" << (face->available_sizes[i].size >> 6) << " @ " << path << "#" << index << std::endl;
                }
            }
        }

        void Collection::scanFile(const char* path)
        {
            Face face(path);
            if (face.ftFace)
            {
                scanFace(face.ftFace, path, 0);

                int count = face.ftFace->num_faces;
                for (int index = 1; index < count; ++index)
                {
                    Face indexFace(path, index);

                    if (indexFace.ftFace)
                    {
                        scanFace(indexFace.ftFace, path, index);
                    }
                }
            }
        }

        LookupCode Collection::lookup(const File** file, const std::string& family, const std::string& style, int fsize)
        {
            FamilyMap::const_iterator iFamily;
            GenericMap::const_iterator iGeneric = genericMap.find(family);
            if (iGeneric != genericMap.end())
            {
                iFamily = familyMap.find(iGeneric->second.c_str());
            }
            else
            {
                iFamily = familyMap.find(family);
            }

            if (iFamily != familyMap.end())
            {
                return iFamily->second.lookup(file, style, fsize);
            }
            else
            {
                return FLC_FAIL_FAMILY;
            }
        }

        LookupCode Collection::lookup(const File** file, const std::vector<std::string>& families, const std::string& style, int fsize)
        {
            for (const std::string& family : families)
            {
                LookupCode returnCode = lookup(file, family, style, fsize);
                if (returnCode  != FLC_FAIL_FAMILY)
                {
                    return returnCode;
                }
            }
            return FLC_FAIL_FAMILY;
        }

        LookupCode Collection::lookup(Face** face, const std::string& family, const std::string& style, int fsize)
        {
            const File* file(nullptr);

            LookupCode returnCode = lookup(&file, family, style, fsize);
            if (returnCode == FLC_SUCCESS)
            {
                (*face) = getFontByFile(file->path, file->index);
            }
            return returnCode;
        }

        LookupCode Collection::lookup(Face** face, const std::vector<std::string>& families, const std::string& style, int fsize)
        {
            const File* file(nullptr);

            LookupCode returnCode = lookup(&file, families, style, fsize);
            if (returnCode == FLC_SUCCESS)
            {
                (*face) = getFontByFile(file->path, file->index);
            }
            return returnCode;
        }

        void Collection::setGeneric(const std::string& generic, const std::string& family)
        {
            genericMap[generic] = family;
        }

        void Collection::release(const StyledFaceKey& key)
        {
            styledFaceMap.erase(key);
        }

        StyledFaceHandle Collection::request(const StyledFaceKey& key)
        {
            auto i = styledFaceMap.find(key);
            if (i != styledFaceMap.end())
            {
                return StyledFaceHandle(&i->second);
            }
            else
            {
                Face* face(nullptr);
                lookup(&face, key.fontFamily, "Regular");
                if (face)
                {
                    auto j = styledFaceMap.emplace(key, std::move(StyledFace(face)));
                    if (j.first != styledFaceMap.end())
                    {
                        return StyledFaceHandle(&j.first->second);
                    }
                }
            }
            return StyledFaceHandle();
        }
    }
}

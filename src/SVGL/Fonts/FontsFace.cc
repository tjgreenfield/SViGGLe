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

#include "FontsFace.hh"
#include "FontsCollection.hh"

#include <cmath>

namespace SVGL
{
    namespace Font
    {
        Face::Face(Face&& font)
        {
            file = std::move(font.file);
            ftFace = font.ftFace;
            font.ftFace = nullptr;
        }

        Face& Face::operator=(Face&& font)
        {
            file = std::move(font.file);
            ftFace = font.ftFace;
            font.ftFace = nullptr;
            return *this;
        }

        Face::Face(const std::string& path, int index)
        {
            file.path = path;
            file.index = index;

            // TODO manage multiple faces per file
            if (FT_New_Face(Collection::ftLibrary, path.c_str(), index, &ftFace))
            {
                ftFace = nullptr;
            }
        }

        Face::~Face()
        {
            if (ftFace != nullptr)
            {
                FT_Done_Face(ftFace);
            }
        }

        Glyph* Face::getGlyph(const char c)
        {
            GlyphMap::iterator i = glyphMap.find(c);

            if (i != glyphMap.end())
            {
                return &i->second;
            }
            else
            {
                FT_Load_Char(ftFace, c, FT_LOAD_NO_SCALE | FT_LOAD_NO_BITMAP);

                return &(glyphMap.emplace(c, std::move(
                        Glyph(ftFace->glyph->outline, ftFace->glyph->advance.x, ftFace->glyph->metrics.width, ftFace->glyph->metrics.height)
                        )).first->second);
            }
        }

        /*SizedFont* Face::getSizedFont(double fsize)
        {
            int logSize;
            std::frexp(fsize, &logSize);
            return getSizedFont(logSize);
        }

        SizedFont* Face::getSizedFont(int logSize)
        {
            SizedFontMap::iterator i = sizedFontMap.find(logSize);
            if (i != sizedFontMap.end())
            {
                ++i->second.refCount;
                return &i->second;
            }
            else
            {
                return &(sizedFontMap.emplace(logSize, std::move(SizedFont(this, logSize))).first->second);
            }
        }

        void Face::releaseSizedFont(SizedFont *sizedFont)
        {
            SizedFontMap::iterator i = sizedFontMap.find(sizedFont->logsize);
            if (i != sizedFontMap.end())
            {
                if (!--i->second.refCount)
                {
                    sizedFontMap.erase(i);
                }
            }
        }*/
    }
}

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

#include "FontStyledFaceKey.hh"

namespace SVGL
{
    namespace Font
    {
        StyledFaceKey::StyledFaceKey() :
            bits(0)
        {

        }

        StyledFaceKey::StyledFaceKey(const Styles::Text& style)
        {
            /* TODO, do lookups to the collection to confirm font family, style & size */
            valid() = 1;
            strokeLineCap() = style.strokeLineCap();
            strokeLineJoin() = style.strokeLineJoin();

            strokeWidth = style.strokeWidth;
            strokeMiterLimit = style.strokeMiterLimit;
            strokeDashArray = style.strokeDashArray;
            effectiveFontSize = style.fontSize;

            fontStyle() = style.fontStyle();
            fontVariant() = style.fontVariant();
            fontWeight() = style.fontWeight();

            fontFamily = style.fontFamilies[0];
        }

        bool StyledFaceKey::operator<(const StyledFaceKey& key) const
        {
#define LESS(field) if (field < key.field) return true; else if (field > key.field) return false;
            LESS(bits);
            LESS(strokeWidth);
            LESS(strokeDashArray);
            LESS(strokeMiterLimit);
            LESS(effectiveFontSize);

            return (fontFamily < key.fontFamily);
        }

#define NEQUAL(field) if (field != key.field) return true;
        bool StyledFaceKey::operator!=(const StyledFaceKey& key) const
        {
            NEQUAL(bits);
            NEQUAL(strokeWidth);
            NEQUAL(strokeDashArray);
            NEQUAL(strokeMiterLimit);
            NEQUAL(effectiveFontSize);

            return (fontFamily != key.fontFamily);
        }
    }
}

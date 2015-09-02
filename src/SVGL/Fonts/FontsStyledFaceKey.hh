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

#include <SVGL/Render/RenderContext.hh>
#include <SVGL/Render/RenderPathBuffer.hh>
#include <SVGL/Styles/StylesText.hh>

#include <unordered_map>

namespace SVGL
{
    namespace Font
    {
        struct StyledFaceKey
        {
            typedef std::vector<double> DashArray;

            unsigned int bits;

            BITRANGE_IMPL(valid, bits, 0, 1);
            BITRANGE_IMPL(strokeLineCap, bits, 1, 2);
            BITRANGE_IMPL(strokeLineJoin, bits, 3, 2);

            double strokeWidth;
            double strokeMiterLimit;
            DashArray strokeDashArray;
            double effectiveFontSize;

            BITRANGE_IMPL(fontStyle, bits, 5, 2);
            BITRANGE_IMPL(fontVariant, bits, 7, 1);
            BITRANGE_IMPL(fontWeight, bits, 8, 4);

            std::string fontFamily;

            StyledFaceKey();
            StyledFaceKey(const Styles::Text& style);

            bool operator<(const StyledFaceKey& key) const;

            bool operator!=(const StyledFaceKey& key) const;
        };
    }
}

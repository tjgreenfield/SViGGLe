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

#include "CSSSizeContext.hh"

#include <SVGL/Styles/StylesText.hh>

#include <cmath>

namespace SVGL
{
    namespace CSS
    {
        SizeContext::SizeContext(double _viewportWidth, double _viewportHeight, double _fontSize, const std::vector<std::string>&) :
            viewportWidth(_viewportWidth),
            viewportHeight(_viewportHeight),
            fontSize(_fontSize),
            fontStretch(Styles::Text::FontStretch::NORMAL),
            fontWeight(Styles::Text::FontWeight::NORMAL)
        {
            viewportDiagonal = std::sqrt((viewportWidth * viewportWidth) + (viewportHeight * viewportHeight));
            fontXHeight = fontSize / 3; // TODO: read from font?
        }

        void SizeContext::setViewport(double _viewportWidth, double _viewportHeight)
        {
            viewportWidth = _viewportWidth;
            viewportHeight = _viewportHeight;
            viewportDiagonal = std::sqrt((viewportWidth * viewportWidth) + (viewportHeight * viewportHeight));
        }

        void SizeContext::setFontSize(double _fontSize, const std::vector<std::string>&)
        {
            fontSize = _fontSize;
            fontXHeight = fontSize / 3; // TODO: read from font?
        }
    }
}


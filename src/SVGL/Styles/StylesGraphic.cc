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

#include "StylesGraphic.hh"
#include <SVGL/CSS/CSSColor.hh>

namespace SVGL
{
    namespace Styles
    {
        Graphic::Graphic() :
            bits(0),
            color(RGB(0, 0, 0))
            /*clipPath(nullptr),
            mask(nullptr),
            filter(nullptr)*/
        {
            display() = true;
            cursor() = CURSOR_DEFAULT;
            pointerEvents() = PE_VISIBLE_PAINTED;
            clipRule() =CR_NONZERO;
        }

        void Graphic::applyPropertySet(const CSS::PropertySet& propertySet, const CSS::SizeContext& sizeContext)
        {
            using namespace CSS;
            using namespace CSS::Property;

            constexpr auto keywordFromValue = &Keyword::keywordFromValue;

            // display
            switch (keywordFromValue(propertySet[Property::DISPLAY]))
            {
            default:
                display() = 1;
                break;

            case Keyword::NONE:
                display() = 0;
                break;
            }

            // color
            if (!colorFromValue(&color, propertySet[Property::COLOR]))
            {
                color = RGB(0, 0, 0);
            }

            // cursor
            switch (keywordFromValue(propertySet[Property::CURSOR]))
            {
            default:
                cursor() = CURSOR_DEFAULT;
                break;
            case Keyword::AUTO:
                cursor() = CURSOR_AUTO;
                break;
            case Keyword::CROSSHAIR:
                cursor() = CURSOR_CROSSHAIR;
                break;
            case Keyword::DEFAULT:
                cursor() = CURSOR_DEFAULT;
                break;
            case Keyword::POINTER:
                cursor() = CURSOR_POINTER;
                break;
            case Keyword::MOVE:
                cursor() = CURSOR_MOVE;
                break;
            case Keyword::E_RESIZE:
                cursor() = CURSOR_E_RESIZE;
                break;
            case Keyword::NE_RESIZE:
                cursor() = CURSOR_NE_RESIZE;
                break;
            case Keyword::W_RESIZE:
                cursor() = CURSOR_W_RESIZE;
                break;
            case Keyword::NW_RESIZE:
                cursor() = CURSOR_NW_RESIZE;
                break;
            case Keyword::S_RESIZE:
                cursor() = CURSOR_S_RESIZE;
                break;
            case Keyword::SE_RESIZE:
                cursor() = CURSOR_SE_RESIZE;
                break;
            case Keyword::SW_RESIZE:
                cursor() = CURSOR_SW_RESIZE;
                break;
            case Keyword::N_RESIZE:
                cursor() = CURSOR_N_RESIZE;
                break;
            case Keyword::TEXT:
                cursor() = CURSOR_TEXT;
                break;
            case Keyword::WAIT:
                cursor() = CURSOR_WAIT;
                break;
            case Keyword::HELP:
                cursor() = CURSOR_HELP;
                break;
            };

            // clip-rule
            if (keywordFromValue(propertySet[Property::CLIP_RULE]) == Keyword::NONZERO)
            {
                clipRule() = CR_NONZERO;
            }
            else
            {
                clipRule() = CR_EVENODD;
            }

            // TODO clip-path


            // TODO mask


            // opacity
            if (auto dimension = dynamic_cast<const CSS::Dimension*>(propertySet[Property::OPACITY]))
            {
                opacity = 255 * dimension->calculate(sizeContext);
            }
            else
            {
                opacity = 255;
            }

            // TODO filter


            // pointer-events
            switch (keywordFromValue(propertySet[Property::POINTER_EVENTS]))
            {
            case Keyword::VISIBLE_PAINTED:
                pointerEvents() = PE_VISIBLE_PAINTED;
                break;
            case Keyword::VISIBLE_FILL:
                pointerEvents() = PE_VISIBLE_FILL;
                break;
            case Keyword::VISIBLE_STROKE:
                pointerEvents() = PE_VISIBLE_STROKE;
                break;
            case Keyword::VISIBLE:
                pointerEvents() = PE_VISIBLE;
                break;
            case Keyword::PAINTED:
                pointerEvents() = PE_PAINTED;
                break;
            case Keyword::FILL:
                pointerEvents() = PE_FILL;
                break;
            case Keyword::STROKE:
                pointerEvents() = PE_STROKE;
                break;
            case Keyword::ALL:
                pointerEvents() = PE_ALL;
                break;
            case Keyword::NONE:
                pointerEvents() = PE_NONE;
                break;
            default:
                pointerEvents() = PE_NONE;
                break;
            }

            // color-interpolation
            switch (keywordFromValue(propertySet[Property::COLOR_INTERPOLATION]))
            {
            case Keyword::AUTO:
                pointerEvents() = CI_AUTO;
                break;
            case Keyword::SRGB:
                pointerEvents() = CI_SRGB;
                break;
            case Keyword::LINEAR_RGB:
                pointerEvents() = CI_LINEAR_RGB;
                break;
            default:
                pointerEvents() = CI_AUTO;
                break;
            }
        }

    }
}

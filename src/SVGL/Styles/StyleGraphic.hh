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

#include <SVGL/CSS/CSS.hh>
#include <SVGL/Types/BitRange.hh>

namespace SVGL
{
    namespace Styles
    {
        /**
         * Graphic: style basis for containers, shape, text & images
         */
        class Graphic : public CSS::Style
        {
        public:

            /*
            'color'
            'cursor'
            'display'
            'clip-rule'
            'clip-path'
            'mask'
            'opacity'
            'filter'
            'pointer-events'
            'color-interpolation'
            */

            /**
             * Possible cursor values
             */
            enum Cursor {
                CURSOR_AUTO,
                CURSOR_CROSSHAIR,
                CURSOR_DEFAULT,
                CURSOR_POINTER,
                CURSOR_MOVE,
                CURSOR_E_RESIZE,
                CURSOR_NE_RESIZE,
                CURSOR_W_RESIZE,
                CURSOR_NW_RESIZE,
                CURSOR_S_RESIZE,
                CURSOR_SE_RESIZE,
                CURSOR_SW_RESIZE,
                CURSOR_N_RESIZE,
                CURSOR_TEXT,
                CURSOR_WAIT,
                CURSOR_HELP
            };

            /**
             * Possible pointer events
             */
            enum PointerEvents {
                PE_VISIBLE_PAINTED,
                PE_VISIBLE_FILL,
                PE_VISIBLE_STROKE,
                PE_VISIBLE,
                PE_PAINTED,
                PE_FILL,
                PE_STROKE,
                PE_ALL,
                PE_NONE
            };

            /**
             * Color interpolation options
             */
            enum ColorInterpolation {
                CI_AUTO,
                CI_SRGB,
                CI_LINEAR_RGB
            };

            /**
             * Clip rule options
             */
            enum ClipRule {
                CR_NONZERO = 0,
                CR_EVENODD = 1
            };

            unsigned int bits;

            BITRANGE_IMPL(display, bits, 0, 1);
            BITRANGE_IMPL(cursor, bits, 1, 4);
            BITRANGE_IMPL(pointerEvents, bits, 5, 4);
            BITRANGE_IMPL(colorInterpolation, bits, 9, 2);
            BITRANGE_IMPL(clipRule, bits, 11, 1);

            Color color;
            unsigned char opacity;
            /*ClipPathElement* clipPath;
            MaskElement* mask;
            FilterElement* filter;*/

        public:
            Graphic();

            void applyPropertySet(const CSS::PropertySet& propertySet, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) override;

        };
    }
}

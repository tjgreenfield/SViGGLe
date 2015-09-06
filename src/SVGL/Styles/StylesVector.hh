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

#include "StylesGraphic.hh"

#include <SVGL/Render/Paints/RenderPaint.hh>

namespace SVGL
{
    namespace Styles
    {
        // shape & text but not images
        class Vector : public Graphic
        {
        public:
            /*
            'fill'
            'fill-rule'
            ‘fill - opacity’

            ‘stroke’
            ‘stroke-dasharray’
            ‘stroke-dashoffset’
            ‘stroke-linecap’
            ‘stroke-linejoin’
            ‘stroke-miterlimit’
            ‘stroke-opacity’
            ‘stroke-width’
            */

            /**
             * Fill rule options
             */
            enum FillRule {
                FR_NONZERO = 0,
                FR_EVENODD = 1
            };

            /**
             * Line join options
             */
            enum _LineJoin {
                LJ_MITER,
                LJ_ROUND,
                LJ_BEVEL
            };

            /**
             * Line cap options
             */
            enum _LineCap {
                LC_BUTT,
                LC_ROUND,
                LC_SQUARE
            };

            /**
             * Dash array type
             */
            typedef std::vector<double> DashArray;

            BITRANGE_IMPL(hasFill, bits, 12, 1);
            BITRANGE_IMPL(fillRule, bits, 13, 1);
            BITRANGE_IMPL(hasStroke, bits, 14, 1);
            BITRANGE_IMPL(strokeLineCap, bits, 15, 2);
            BITRANGE_IMPL(strokeLineJoin, bits, 17, 2);

            //Color fill;
            //Color stroke;
            Render::Paint_uptr fill;
            float fillOpacity;

            Render::Paint_uptr stroke;
            float strokeOpacity;

            double strokeWidth;
            double strokeMiterLimit;
            double strokeDashOffset;
            DashArray strokeDashArray;

            Vector();

            void applyPropertySet(const CSS::PropertySet& propertySet, const CSS::SizeContext& sizeContext) override;

            void buffer(const Elements::Instance& instance);
        };
    }
}

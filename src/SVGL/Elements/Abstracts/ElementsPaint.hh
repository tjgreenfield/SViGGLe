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

#include "ElementsRoot.hh"

#include <SVGL/Elements/Paints/ElementsStop.hh>
#include <SVGL/Render/Paints/RenderPaint.hh>
#include <SVGL/Types/BitRange.hh>


namespace SVGL
{
    class Document;

    namespace Elements
    {
        class Paint : public Root
        {
        protected:
            struct GradientDerived
            {
                unsigned int flags;
                BITRANGE_IMPL(needGradientUnits, flags, 0, 1);
                BITRANGE_IMPL(needSpreadMethod, flags, 1, 1);
                BITRANGE_IMPL(needStopList, flags, 2, 1);
                BITRANGE_IMPL(needGradientTransform, flags, 3, 1);
                BITRANGE_IMPL(needX1, flags, 4, 1);
                BITRANGE_IMPL(needY1, flags, 5, 1);
                BITRANGE_IMPL(needX2, flags, 6, 1);
                BITRANGE_IMPL(needY2, flags, 7, 1);
                BITRANGE_IMPL(needCX, flags, 8, 1);
                BITRANGE_IMPL(needCY, flags, 9, 1);
                BITRANGE_IMPL(needR, flags, 10, 1);
                BITRANGE_IMPL(needFX, flags, 11, 1);
                BITRANGE_IMPL(needFY, flags, 12, 1);
                BITRANGE_IMPL(needAll, flags, 0, 13);

                unsigned int bits;
                BITRANGE_IMPL(gradientUnits, bits, 0, 2);
                BITRANGE_IMPL(spreadMethod, bits, 2, 2);

                const StopList* stopList;
                const Transforms::Transform* gradientTransform;

                // linear gradient
                Point p1;
                Point p2;

                // radial gradient
                Point centre;
                double radius;
                Point focus;
            };

        public:
            Paint(Root* _parent);

            virtual Render::Paint_uptr calculatePaint(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) const = 0;
        };
    }
}

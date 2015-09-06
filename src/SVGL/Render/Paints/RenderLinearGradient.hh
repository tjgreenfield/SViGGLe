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

#include <SVGL/Elements/Paints/ElementsLinearGradient.hh>

#include "RenderPaint.hh"

namespace SVGL
{
    namespace Render
    {
        class LinearGradient : public Paint
        {
        protected:
            unsigned int bits;
            const Elements::StopList* stopList;
            const Transforms::Transform* gradientTransform;
            Point p1;
            Point p2;

            struct GradientUnits { enum {
                INAVLID,
                USER_SPACE_ON_USE,
                OBJECT_BOUNDING_BOX
            }; };

            struct SpreadMethod  { enum {
                INAVLID,
                PAD,
                REFLECT,
                REPEAT
            }; };

            BITRANGE_IMPL(gradientUnits, bits, 0, 2);
            BITRANGE_IMPL(spreadMethod, bits, 2, 2);

            Point p1Transformed;
            Point pDirTransformed;
            std::vector<float> offsets;
            std::vector<float> colors;


        public:
            LinearGradient(unsigned int _bits, const Elements::StopList* _stopList, const Transforms::Transform* _gradientTransform, const Point& _p1, const Point& _p2);

            void buffer(const Elements::Instance& instance) override;

            void enable(Context* context) const;

            void renderFill(Context* context, const PathBuffer& buffer) const override;

            void renderStroke(Context* context, const PathBuffer& buffer) const override;

        };
    }
}

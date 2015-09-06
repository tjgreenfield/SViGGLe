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

#include "ElementsStop.hh"
#include <SVGL/Elements/Abstracts/ElementsPaint.hh>
#include <SVGL/Types/BitRange.hh>

#include <vector>
#include <string>

namespace SVGL
{
    namespace Render
    {
        class LinearGradient;
    }

    namespace Elements
    {
        class LinearGradient : public Paint
        {
            friend class Render::LinearGradient;
        protected:
            CSS::Calculable x1;
            CSS::Calculable y1;
            CSS::Calculable x2;
            CSS::Calculable y2;
            Transforms::Transform gradientTransform;
            unsigned int bits;

            struct GradientUnits { enum {
                INVALID,
                USER_SPACE_ON_USE,
                OBJECT_BOUNDING_BOX
            }; };

            struct SpreadMethod  { enum {
                INVALID,
                PAD,
                REFLECT,
                REPEAT
            }; };

            BITRANGE_IMPL(gradientUnits, bits, 0, 2);
            BITRANGE_IMPL(spreadMethod, bits, 2, 2);
            BITRANGE_IMPL(hasGradientTransform, bits, 4, 1);

            std::string href;
            StopList stopList;
        public:

            LinearGradient(Root* _parent = nullptr);

            /***** XML::Node *****/
            void setAttribute(SubString name, SubString value) override;

            void appendChild(XML::Node_uptr&& child) override;

            /***** Elements::Root *****/
            Instance_uptr calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) override;

            /***** Elements::Paint *****/
            void calculateGradient(GradientDerived* derived, const CSS::SizeContext& sizeContext) const;

            Render::Paint_uptr calculatePaint(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) const override;
        };
    }
}


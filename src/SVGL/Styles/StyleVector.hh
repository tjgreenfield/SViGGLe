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

#include "StyleGraphic.hh"

#include <SVGL/CSS/CSS.hh>

#include <bitset>
#include <unordered_map>
#include <vector>

namespace SVGL
{
    namespace Styles
    {
        // shape & text but not images
        class Vector : public Graphic
        {
            Color fill;

            Color stroke;
            double strokeWidth;
            double strokeMiterLimit;
            LineJoin strokeLineJoin;
            LineCap strokeLineCap;

            DashArray strokeDashArray;
            double strokeDashOffset;

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
             * Constructor
             */
            Vector(SVG* parent = nullptr);

            /**
             * Test if the fill is none
             * @retval true There is a fill
             * @retval false There is no fill
             */
            bool hasFill() const override;

            /**
             * Get the value of the fill color property
             * @return The color property
             */
            Color getFill() const override;

            /**
             * Test if the stroke is none
             * @retval true There is a stroke
             * @retval false There is no stroke
             */
            bool hasStroke() const override;
            
            /**
             * Get the value of the stroke color property
             * @return The color property
             */
            Color getStroke() const override;
            
            /**
             * Get the value of the stroke width property
             * @return The stroke width
             */
            double getStrokeWidth() const override;

            /**
             * Get the line join type for the stroke
             * @return The stroke line join type
             */
            LineJoin getStrokeLineJoin() const override;

            /**
             * Get the limit for the miter joins
             * @return The limit for the miter joins
             */
            double getStrokeMiterLimit() const override;

            /**
             * Get the line cap type for the stroke
             * @return The stroke line cap type
             */
            LineCap getStrokeLineCap() const override;

            /**
             * Get the stroke dash array
             * @return A pointer to the dash array
             */
            const DashArray* getStrokeDashArray() const override;

            /**
             * Get the stroke dash offset
             * @return The offset length to start into the dash array
             */
            double getStrokeDashOffset() const override;

            /**
             * Set the style property of the style object.
             *
             * @param[in] index The index of the style property to set.
             * @param[in] value The value to assign to the property.
             */
            void setProperty(unsigned int index, const CSS::Value* value) override;
        };
    }
}

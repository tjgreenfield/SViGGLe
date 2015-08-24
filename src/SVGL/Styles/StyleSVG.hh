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

#include "StyleTypes.hh"
#include <SVGL/CSS/CSS.hh>

#include <bitset>
#include <unordered_map>

namespace SVGL
{
    namespace Styles
    {
        /**
         * Base class for the main SVG styles
         */
        class SVG : public CSS::Style
        {
        protected:

            std::bitset<32> flags; //!< Flags - uses the Inerit and Flags enums to map bits

            SVG* parent; //!< Pointer to the parent element, may be nullptr

        public:

            /**
             * Constructor
             * param[in] _flags Initial value for the bitset<32> flags
             * param[in] _parent Pointer to the parent style
             */
            SVG(unsigned int _flags, SVG* _parent = nullptr);

            /**
             * Virtual destructor
             */
            ~SVG() override;

            /**
             * Get the value of the color property
             * @return The color property
             */
            virtual Color getColor() const;

            /**
             * Get the value of the display property
             * @return The display property
             */
            virtual Display getDisplay() const;

            /**
             * Get the value of the clip-rule property
             * @return The clip-rule property
             */
            virtual ClipRule getClipRule() const;

            /**
             * Get the value of the clip-path property
             * @return The clip-path property
             */
            virtual const ClipPathElement* getClipPath() const;

            /**
             * Get the value of the mask property
             * @return The mask property
             */
            virtual const MaskElement* getMask() const;

            /**
             * Get the value of the opacity property
             * @return The opacity property
             */
            virtual Opacity getOpacity() const;

            /**
             * Get the value of the filter property
             * @return The filter property
             */
            virtual const FilterElement* getFilter() const;

            /**
             * Get the value of the pointer-events property
             * @return The pointer-events property
             */
            virtual PointerEvents getPointerEvents() const;

            /**
             * Get the value of the color-interpolation property
             * @return The color-interpolation property
             */
            virtual ColorInterpolation getColorInterpolation() const;

            /*// Vector (11)
            FILL,
            FILL_RULE,
            FILL_OPACITY,
            STROKE,
            STROKE_DASHARRAY,
            STROKE_DASHOFFSET,
            STROKE_LINECAP,
            STROKE_LINEJOIN,
            STROKE_MITERLIMIT,
            STROKE_OPACITY,
            STROKE_WIDTH,*/

            /*// Shape (5)
            MARKER,
            MARKER_START,
            MARKER_MID,
            MARKER_END,
            SHAPE_RENDERING,

            // Image (1)
            COLOR_PROFILE,*/

            /**
             * Test if the fill is none
             * @retval true There is a fill
             * @retval false There is no fill
             */
            virtual bool hasFill() const;

            /**
             * Get the value of the fill color property
             * @return The color property
             */
            virtual Color getFill() const;

            /**
             * Test if the stroke is none
             * @retval true There is a stroke
             * @retval false There is no stroke
             */
            virtual bool hasStroke() const;
            
            /**
             * Get the value of the stroke color property
             * @return The color property
             */
            virtual Color getStroke() const;
            
            /**
             * Get the value of the stroke width property
             * @return The stroke width
             */
            virtual double getStrokeWidth() const;

            /**
             * Get the line join type for the stroke
             * @return The stroke line join type
             */
            virtual LineJoin getStrokeLineJoin() const;

            /**
             * Get the limit for the miter joins
             * @return The limit for the miter joins
             */
            virtual double getStrokeMiterLimit() const;


            /**
             * Get the line cap type for the stroke
             * @return The stroke line cap type
             */
            virtual LineCap getStrokeLineCap() const;

            /**
             * Get the stroke dash array
             * @return A pointer to the dash array
             */
            virtual const DashArray* getStrokeDashArray() const;

            /**
             * Get the stroke dash offset
             * @return The offset length to start into the dash array
             */
            virtual double getStrokeDashOffset() const;

            /**
             * Set the style property of the style object.
             * Looks up the name to find the index then calls the virtual index version of the function
             *
             * @param[in] name The name of the style property to set.
             * @param[in] value The value to assign to the property.
             */
            void setProperty(const char* name, const CSS::Value* value) override;

            /**
             * Set the style property of the style object.
             *
             * @param[in] index The index of the style property to set.
             * @param[in] value The value to assign to the property.
             */
            virtual void setProperty(unsigned int index, const CSS::Value* value) = 0;

        };
    }
}

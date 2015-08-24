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
#include "StyleSVG.hh"
#include <SVGL/CSS/CSS.hh>

#include <bitset>
#include <unordered_map>

namespace SVGL
{
    namespace Styles
    {
        /**
         * Graphic: style basis for containers, shape, text & images
         */
        class Graphic : public SVG
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
        protected:
            ClipPathElement* clipPath; //!< The linked clip-path element
            MaskElement* mask; //!< The linked mask element
            FilterElement* filter; //!< The linked filter element
            Color color; //!< The color property
            Opacity opacity; //!< The opacity property
            Cursor cursor; //!< The cursor property
            PointerEvents pointerEvents; //!< The pointer events property
            ColorInterpolation colorInterpolation; //!< The color interpolation property

        public:
            /**
             * Constructor
             */
            Graphic(SVG* parent = nullptr);

            /**
             * Get the value of the color property
             * @return The color property
             */
            Color getColor() const override;
            
            /**
             * Get the value of the display property
             * @return The display property
             */
            Display getDisplay() const override;
            
            /**
             * Get the value of the clip-rule property
             * @return The clip-rule property
             */
            ClipRule getClipRule() const override;
            
            /**
             * Get the value of the clip-path property
             * @return The clip-path property
             */
            const ClipPathElement* getClipPath() const override;

            /**
             * Get the value of the mask property
             * @return The mask property
             */
            const MaskElement* getMask() const override;
            
            /**
             * Get the value of the opacity property
             * @return The opacity property
             */
            Opacity getOpacity() const override;
            
            /**
             * Get the value of the filter property
             * @return The filter property
             */
            const FilterElement* getFilter() const override;
            
            /**
             * Get the value of the pointer-events property
             * @return The pointer-events property
             */
            PointerEvents getPointerEvents() const override;
            
            /**
             * Get the value of the color-interpolation property
             * @return The color-interpolation property
             */
            ColorInterpolation getColorInterpolation() const override;

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

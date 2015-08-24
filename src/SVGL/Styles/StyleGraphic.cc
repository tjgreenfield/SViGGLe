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

#include "StyleGraphic.hh"

namespace SVGL
{
    namespace Styles
    {
        /**
         * Graphic: style basis for containers, shape, text & images
         */

        /*
         * Default inherit flags for properties
         * TODO: rest of the flags
         */
        unsigned int defaultFlags =
              (1 << Inherit::COLOR)
            + (1 << Inherit::CLIP_RULE)
            + (1 << Inherit::POINTER_EVENTS)
            + (1 << Inherit::COLOR_INTERPOLATION)
            + (1 << Flags::STROKE_NONE);

        /**
         * Constructor
         */
        Graphic::Graphic(SVG* _parent) :
            SVG(defaultFlags, _parent),
            clipPath(nullptr),
            mask(nullptr),
            filter(nullptr),
            color(defaultColor),
            opacity(defaultOpacity),
            cursor(defaultCursor),
            pointerEvents(defaultPointerEvents),
            colorInterpolation(defaultColorInterpolation)
        {

        }

        /**
         * Get the value of the color property
         * @return The color property
         */
        Color Graphic::getColor() const
        {
            if (flags[Inherit::COLOR])
            {
                return parent ? parent->getColor() : defaultColor;
            }
            else
            {
                return color;
            }
        }

        /**
         * Get the value of the display property
         * @return The display property
         */
        Display Graphic::getDisplay() const
        {
            if (flags[Inherit::DISPLAY])
            {
                return parent ? parent->getDisplay() : defaultDisplay;
            }
            else
            {
                return flags[Flags::DISPLAY];
            }
        }

        /**
         * Get the value of the clip-rule property
         * @return The clip-rule property
         */
        ClipRule Graphic::getClipRule() const
        {
            if (flags[Inherit::CLIP_RULE])
            {
                return parent ? parent->getClipRule() : defaultClipRule;
            }
            else
            {
                return flags[Flags::CLIP_RULE];
            }
        }

        /**
         * Get the value of the clip-path property
         * @return The clip-path property
         */
        const ClipPathElement* Graphic::getClipPath() const
        {
            if (flags[Inherit::CLIP_PATH])
            {
                return parent ? parent->getClipPath() : nullptr;
            }
            else
            {
                return clipPath;
            }
        }

        /**
         * Get the value of the mask property
         * @return The mask property
         */
        const MaskElement* Graphic::getMask() const
        {
            if (flags[Inherit::MASK])
            {
                return parent ? parent->getMask() : nullptr;
            }
            else
            {
                return mask;
            }
        }

        /**
         * Get the value of the opacity property
         * @return The opacity property
         */
        Opacity Graphic::getOpacity() const
        {
            if (flags[Inherit::OPACITY])
            {
                return parent ? parent->getOpacity() : defaultOpacity;
            }
            else
            {
                return opacity;
            }
        }

        /**
         * Get the value of the filter property
         * @return The filter property
         */
        const FilterElement* Graphic::getFilter() const
        {
            if (flags[Inherit::FILTER])
            {
                return parent ? parent->getFilter() : nullptr;
            }
            else
            {
                return filter;
            }
        }

        /**
         * Get the value of the pointer-events property
         * @return The pointer-events property
         */
        PointerEvents Graphic::getPointerEvents() const
        {
            if (flags[Inherit::POINTER_EVENTS])
            {
                return parent ? parent->getPointerEvents() : defaultPointerEvents;
            }
            else
            {
                return pointerEvents;
            }
        }

        /**
         * Get the value of the color-interpolation property
         * @return The color-interpolation property
         */
        ColorInterpolation Graphic::getColorInterpolation() const
        {
            if (flags[Inherit::COLOR_INTERPOLATION])
            {
                return parent ? parent->getColorInterpolation() : defaultColorInterpolation;
            }
            else
            {
                return colorInterpolation;
            }
        }

        /**
         * Set the style property of the style object.
         *
         * @param[in] index The index of the style property to set.
         * @param[in] value The value to assign to the property.
         */
        void Graphic::setProperty(unsigned int index, const CSS::Value* value)
        {
            CSS::ColorState state;
            switch (index)
            {
            case Inherit::COLOR:
                color = colorFromValue(value, &state);
                switch (state)
                {
                case CSS::INHERIT:
                    flags[Inherit::COLOR] = true;
                    break;
                default:
                    flags[Inherit::COLOR] = false;
                    break;
                }
                break;
            default:
                break;
            }
        }
    }
}

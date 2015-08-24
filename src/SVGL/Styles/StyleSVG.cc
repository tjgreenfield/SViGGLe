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

#include "StyleSVG.hh"
#include <SVGL/CSS/CSSColor.hh>

namespace SVGL
{
    namespace Styles
    {
        /**
         * SVGStyle: Base class for the main SVG styles
         */
        
        /**
         * Constructor
         */
        SVG::SVG(unsigned int _flags, SVG* _parent) :
            flags(_flags),
            parent(_parent)
        {

        }

        /**
         * Virtual destructor
         */
        SVG::~SVG()
        {

        }

        /**
         * Get the value of the color property
         * @return The color property
         */
        Color SVG::getColor() const
        {
            return parent ? parent->getColor() : defaultColor;
        }

        /**
         * Get the value of the display property
         * @return The display property
         */
        Display SVG::getDisplay() const
        {
            return defaultDisplay;
        }

        /**
         * Get the value of the clip-rule property
         * @return The clip-rule property
         */
        ClipRule SVG::getClipRule() const
        {
            return parent ? parent->getClipRule() : defaultClipRule;
        }

        /**
         * Get the value of the clip-path property
         * @return The clip-path property
         */
        const ClipPathElement* SVG::getClipPath() const
        {
            return nullptr;
        }

        /**
         * Get the value of the mask property
         * @return The mask property
         */
        const MaskElement* SVG::getMask() const
        {
            return nullptr;
        }

        /**
         * Get the value of the opacity property
         * @return The opacity property
         */
        Opacity SVG::getOpacity() const
        {
            return defaultOpacity;
        }

        /**
         * Get the value of the filter property
         * @return The filter property
         */
        const FilterElement* SVG::getFilter() const
        {
            return nullptr;
        }

        /**
         * Get the value of the pointer-events property
         * @return The pointer-events property
         */
        PointerEvents SVG::getPointerEvents() const
        {
            return parent ? parent->getPointerEvents() : defaultPointerEvents;
        }

        /**
         * Get the value of the color-interpolation property
         * @return The color-interpolation property
         */
        ColorInterpolation SVG::getColorInterpolation() const
        {
            return parent ? parent->getColorInterpolation() : defaultColorInterpolation;
        }

        /**
         * Test if the fill is none
         * @retval true There is a fill
         * @retval false There is no fill
         */
        bool SVG::hasFill() const
        {
            return parent ? parent->hasFill() : true;
        }

        /**
         * Get the value of the color property
         * @return The color property
         */
        Color SVG::getFill() const
        {
            return parent ? parent->getFill() : defaultFill;
        }

        /**
         * Test if the stroke is none
         * @retval true There is a stroke
         * @retval false There is no stroke
         */
        bool SVG::hasStroke() const
        {
            return parent ? parent->hasStroke() : true;
        }

        /**
         * Get the value of the color property
         * @return The color property
         */
        Color SVG::getStroke() const
        {
            return parent ? parent->getStroke() : defaultStroke;
        }

        /**
         * Get the value of the stroke width property
         * @return The stroke width
         */
        double SVG::getStrokeWidth() const
        {
            return parent ? parent->getStrokeWidth() : defaultStrokeWidth;
        }

        /**
         * Get the line join type for the stroke
         * @return The stroke line join type
         */
        LineJoin SVG::getStrokeLineJoin() const
        {
            return parent ? parent->getStrokeLineJoin() : defaultStrokeLineJoin;
        }

        /**
         * Get the limit for the miter joins
         * @return The limit for the miter joins
         */
        double SVG::getStrokeMiterLimit() const
        {
            return parent ? parent->getStrokeMiterLimit() : defaultStrokeMiterLimit;
        }

        /**
         * Get the line cap type for the stroke
         * @return The stroke line cap type
         */
        LineCap SVG::getStrokeLineCap() const
        {
            return parent ? parent->getStrokeLineCap() : defaultStrokeLineCap;
        }

        /**
         * Get the stroke dash array
         * @return A pointer to the dash array
         */
        const DashArray* SVG::getStrokeDashArray() const
        {
            return parent ? parent->getStrokeDashArray() : nullptr;
        }

        /**
         * Get the stroke dash offset
         * @return The offset length to start into the dash array
         */
        double SVG::getStrokeDashOffset() const
        {
            return parent ? parent->getStrokeDashOffset() : defaultStrokeDashOffset;
        }

        /**
         * Set the style property of the style object.
         * Looks up the name to find the index then calls the virtual index version of the function
         *
         * @param[in] name The name of the style property to set.
         * @param[in] value The value to assign to the property.
         */
        void SVG::setProperty(const char* name, const CSS::Value* value)
        {
            PropertyMap::iterator i = propertyMap.find(name);
            if (i != propertyMap.end())
            {
                setProperty(i->second, value);
            }
        }

    }
}

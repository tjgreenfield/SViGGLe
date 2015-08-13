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
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "StyleTypes.hh"
#include <SVGL/CSS/CSSColor.hh>

namespace SVGL
{
    namespace Styles
    {
        Color defaultColor(0xFFFFFFFF); //!< Default color: white with full alpha
        Display defaultDisplay(true); //!< Default display: true
        Opacity defaultOpacity(255); //!< Default opacity: full (255)
        PointerEvents defaultPointerEvents(PE_VISIBLE_PAINTED); //!< Default pointer events: visiblePainted
        ColorInterpolation defaultColorInterpolation(CI_SRGB); //!< Default color interpolation: sRGB
        Cursor defaultCursor(CURSOR_DEFAULT); //!< Default cursor: Default
        ClipRule defaultClipRule(CR_NONZERO); //!< Default clip-rule: NonZero

        Color defaultFill(0xFF000000); //!< Default fill color: black
        Color defaultStroke(0x00000000); //!< Default stroke color: none
        double defaultStrokeWidth(1); //!< Default stroke width: 1
        LineJoin defaultStrokeLineJoin(LJ_MITER); //!< Default stroke line join: LJ_MITER
        double defaultStrokeMiterLimit(4); //!< Default stroke miter limit: 4

        /**
         * Global map to map property names to indexes
         */
        PropertyMap propertyMap = {
            // graphics (shape, text & image) properties
            { "color", Inherit::COLOR },
            { "cursor", Inherit::CURSOR },
            { "display", Inherit::DISPLAY },
            { "clip-rule", Inherit::CLIP_RULE },
            { "clip-path", Inherit::CLIP_PATH },
            { "mask", Inherit::MASK },
            { "opacity", Inherit::OPACITY },
            { "filter", Inherit::FILTER },
            { "pointer-events", Inherit::POINTER_EVENTS },
            { "color-interpolation", Inherit::COLOR_INTERPOLATION },

            // vector (shape & text) properties
            { "fill", Inherit::FILL },
            { "fill-rule", Inherit::FILL_RULE },
            { "fill-opacity", Inherit::FILL_OPACITY },
            { "stroke", Inherit::STROKE },
            { "stroke-dasharray", Inherit::STROKE_DASHARRAY },
            { "stroke-dashoffset", Inherit::STROKE_DASHOFFSET },
            { "stroke-linecap", Inherit::STROKE_LINECAP },
            { "stroke-linejoin", Inherit::STROKE_LINEJOIN },
            { "stroke-miterlimit", Inherit::STROKE_MITERLIMIT },
            { "stroke-opacity", Inherit::STROKE_OPACITY },
            { "stroke-width", Inherit::STROKE_WIDTH },

            // shape properties
            { "marker", Inherit::MARKER },
            { "marker-start", Inherit::MARKER_START },
            { "marker-mid", Inherit::MARKER_MID },
            { "marker-end", Inherit::MARKER_END },
            { "shape-rendering", Inherit::SHAPE_RENDERING },

            // image properties
            { "color-profile", Inherit::COLOR_PROFILE }
        };
    }
}

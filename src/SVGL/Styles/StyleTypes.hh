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

#include <SVGL/CSS/CSS.hh>

#include <bitset>
#include <unordered_map>

namespace SVGL
{
    namespace Styles
    {
        class ClipPathElement {};
        class MaskElement {};
        class FilterElement {};

        /**
            * Flags to indicate various properties are to be inherited
            */
        class Inherit
        {
        public:
            enum {
                // Graphic (10 bits)
                COLOR,
                CURSOR,
                DISPLAY,
                CLIP_RULE,
                CLIP_PATH,
                MASK,
                OPACITY,
                FILTER,
                POINTER_EVENTS,
                COLOR_INTERPOLATION,

                // Vector (11 bits)
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
                STROKE_WIDTH,

                // Shape (5 bits)
                MARKER,
                MARKER_START,
                MARKER_MID,
                MARKER_END,
                SHAPE_RENDERING,

                // Image (1 bit)
                COLOR_PROFILE = MARKER,
            };
        };

        /**
         * Flags related to properties with only two states
         */
        class Flags
        {
        public:
            enum {
                DISPLAY = (Inherit::SHAPE_RENDERING + 1),
                CLIP_RULE, // false = NONZERO, true = evenodd
                FILL_NONE, // fill = none
                STROKE_NONE, // stroke = none
                LAST_FLAG
            };
        };

        /**
         * Mapping property names to indexes from the Inherit enum
         */
        typedef std::unordered_map<std::string, unsigned int> PropertyMap;
        extern PropertyMap propertyMap; //!< Global map to map property names to indexes

        /**
         * The way various types of style data are stored
         */
        typedef unsigned int Color;
        typedef unsigned char Opacity;
        typedef unsigned char Cursor;
        typedef unsigned char PointerEvents;
        typedef unsigned char ColorInterpolation;
        typedef bool Display;
        typedef bool ClipRule;

        extern Color defaultColor; //!< Default color: white with full alpha
        extern Display defaultDisplay; //!< Default display: true
        extern Opacity defaultOpacity; //!< Default opacity: full (255)
        extern PointerEvents defaultPointerEvents; //!< Default pointer events: visiblePainted
        extern ColorInterpolation defaultColorInterpolation; //!< Default color interpolation: sRGB
        extern Cursor defaultCursor; //!< Default cursor: Default
        extern ClipRule defaultClipRule; //!< Default clip-rule: NonZero

        typedef unsigned char LineJoin;
        typedef unsigned char LineCap;

        extern Color defaultFill; //!< Default fill color: black
        extern Color defaultStroke; //!< Default stroke color: none
        extern double defaultStrokeWidth; //!< Default stroke width: 1
        extern LineJoin defaultStrokeLineJoin; //!< Default stroke line join: LJ_MITER
        extern double defaultStrokeMiterLimit; //!< Default stroke miter limit: 4
        extern LineCap defaultStrokeLineCap; //!< Default stroke line join: LC_BUTT
        extern double defaultStrokeDashOffset; //!< Default stroke dash offset: 0

        typedef std::vector<double> DashArray;

        /**
          * Possible cursor values
          */
        enum _Cursor {
            CURSOR_AUTO,
            CURSOR_CROSSHAIR,
            CURSOR_DEFAULT,
            CURSOR_POINTER,
            CURSOR_MOVE,
            CURSOR_ERESIZE,
            CURSOR_NERESIZE,
            CURSOR_WRESIZE,
            CURSOR_NWRESIZE,
            CURSOR_SRESIZE,
            CURSOR_SERESIZE,
            CURSOR_SWRESIZE,
            CURSOR_NRESIZE,
            CURSOR_TEXT,
            CURSOR_WAIT,
            CURSOR_HELP
        };

        /**
         * Possible pointer events
         */
        enum _PointerEvents {
            PE_VISIBLE_PAINTED,
            PE_VISIBLE_FILL,
            PE_VISIBLE_STROKE,
            PE_VISIBLE,
            PE_PAINTED,
            PE_FILL,
            PE_STROKE,
            PE_ALL,
            PE_NONE
        };

        /**
         * Color interpolation options
         */
        enum _ColorInterpolation {
            CI_AUTO,
            CI_SRGB,
            CI_LINEAR_RGB
        };

        /**
         * Clip rule options
         */
        enum _ClipRule {
            CR_NONZERO = 0,
            CR_EVENODD = 1
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

    }
}

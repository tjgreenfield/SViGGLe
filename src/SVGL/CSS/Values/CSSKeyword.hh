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

#include "CSSValue.hh"
#include <SVGL/Types/Color.hh>
#include <SVGL/Types/SubString.hh>
#include <SVGL/Types/KeywordMapper.hh>
#include <SVGL/CSS/CSSProperty.hh>
#include <SVGL/CSS/CSSPropertySet.hh>
#include <string>

namespace SVGL
{
    namespace CSS
    {
        class PropertySet;

        /**
         * An keyword value.
         */
        class Keyword : public Value
        {
        public:

            enum Index
            {
                ERROR = 0,

                // common
                INHERIT,
                NONE,
                AUTO,
                NORMAL,

                // clip-rule / fill-rule
                NONZERO,
                EVENODD,

                // cursor
                CROSSHAIR,
                DEFAULT,
                POINTER,
                MOVE,
                E_RESIZE,
                NE_RESIZE,
                W_RESIZE,
                NW_RESIZE,
                S_RESIZE,
                SE_RESIZE,
                SW_RESIZE,
                N_RESIZE,
                TEXT,
                WAIT,
                HELP,

                // pointer-events
                VISIBLE_PAINTED,
                VISIBLE_FILL,
                VISIBLE_STROKE,
                VISIBLE,
                PAINTED,
                FILL,
                STROKE,
                ALL,

                // color-interpolation
                SRGB,
                LINEAR_RGB,

                // stroke-linejoin, stroke-linecap
                MITER,
                ROUND,
                BEVEL,
                BUTT,
                SQUARE,

                // font-size
                XX_SMALL,
                X_SMALL,
                SMALL,
                MEDIUM,
                LARGE,
                X_LARGE,
                XX_LARGE,
                LARGER,
                SMALLER,

                // font-stretch
                WIDER,
                NARROWER,
                ULTRA_CONDENSED,
                EXTRA_CONDENSED,
                CONDENSED,
                SEMI_CONDENSED,
                SEMI_EXPANDED,
                EXPANDED,
                EXTRA_EXPANDED,
                ULTRA_EXPANDED,

                // font-style
                ITALIC,
                OBLIQUE,

                // font-variant
                SMALLCAPS,

                // font-weight
                BOLD,
                BOLDER,
                LIGHTER,

                // direction
                LTR,
                RTL,

                // text-decoration
                UNDERLINE,
                OVERLINE,
                LINE_THROUGH,
                BLINK,

                // unicode-bidi
                EMBED,
                BIDI_OVERRIDE,

                // alignment-baseline
                BASELINE,
                BEFORE_EDGE,
                TEXT_BEFORE_EDGE,
                MIDDLE,
                CENTRAL,
                AFTER_EDGE,
                TEXT_AFTER_EDGE,
                IDEOGRAPHIC,
                ALPHABETIC,
                HANGING,
                MATHEMATICAL,

                // baseline-shift
                SUB,
                SUPER,
                VALUE,

                // dominant-baseline
                USE_SCRIPT,
                NO_CHANGE,
                RESET_SIZE,

                // text-anchor
                START,
                END,

                // writing-mode
                LR_TB,
                RL_TB,
                TB_RL,
                LR,
                RL,
                TB,

                // text rendering
                OPTIMIZE_SPEED,
                OPTIMIZE_LEGIBILITY,
                GEOMETRIC_PRECISION,

                // gradientUnits
                USER_SPACE_ON_USE,
                OBJECT_BOUNDING_BOX,

                // spreadMethod
                PAD,
                REFLECT,
                REPEAT,

                // colors will all be > 4278190080 (0xFF000000)
                ALICEBLUE = RGB(240, 248, 255),
                ANTIQUEWHITE = RGB(250, 235, 215),
                AQUA = RGB(0, 255, 255),
                AQUAMARINE = RGB(127, 255, 212),
                AZURE = RGB(240, 255, 255),
                BEIGE = RGB(245, 245, 220),
                BISQUE = RGB(255, 228, 196),
                BLACK = RGB(0, 0, 0),
                BLANCHEDALMOND = RGB(255, 235, 205),
                BLUE = RGB(0, 0, 255),
                BLUEVIOLET = RGB(138, 43, 226),
                BROWN = RGB(165, 42, 42),
                BURLYWOOD = RGB(222, 184, 135),
                CADETBLUE = RGB(95, 158, 160),
                CHARTREUSE = RGB(127, 255, 0),
                CHOCOLATE = RGB(210, 105, 30),
                CORAL = RGB(255, 127, 80),
                CORNFLOWERBLUE = RGB(100, 149, 237),
                CORNSILK = RGB(255, 248, 220),
                CRIMSON = RGB(220, 20, 60),
                CYAN = RGB(0, 255, 255),
                DARKBLUE = RGB(0, 0, 139),
                DARKCYAN = RGB(0, 139, 139),
                DARKGOLDENROD = RGB(184, 134, 11),
                DARKGRAY = RGB(169, 169, 169),
                DARKGREEN = RGB(0, 100, 0),
                DARKGREY = RGB(169, 169, 169),
                DARKKHAKI = RGB(189, 183, 107),
                DARKMAGENTA = RGB(139, 0, 139),
                DARKOLIVEGREEN = RGB(85, 107, 47),
                DARKORANGE = RGB(255, 140, 0),
                DARKORCHID = RGB(153, 50, 204),
                DARKRED = RGB(139, 0, 0),
                DARKSALMON = RGB(233, 150, 122),
                DARKSEAGREEN = RGB(143, 188, 143),
                DARKSLATEBLUE = RGB(72, 61, 139),
                DARKSLATEGRAY = RGB(47, 79, 79),
                DARKSLATEGREY = RGB(47, 79, 79),
                DARKTURQUOISE = RGB(0, 206, 209),
                DARKVIOLET = RGB(148, 0, 211),
                DEEPPINK = RGB(255, 20, 147),
                DEEPSKYBLUE = RGB(0, 191, 255),
                DIMGRAY = RGB(105, 105, 105),
                DIMGREY = RGB(105, 105, 105),
                DODGERBLUE = RGB(30, 144, 255),
                FIREBRICK = RGB(178, 34, 34),
                FLORALWHITE = RGB(255, 250, 240),
                FORESTGREEN = RGB(34, 139, 34),
                FUCHSIA = RGB(255, 0, 255),
                GAINSBORO = RGB(220, 220, 220),
                GHOSTWHITE = RGB(248, 248, 255),
                GOLD = RGB(255, 215, 0),
                GOLDENROD = RGB(218, 165, 32),
                GRAY = RGB(128, 128, 128),
                GREY = RGB(128, 128, 128),
                GREEN = RGB(0, 128, 0),
                GREENYELLOW = RGB(173, 255, 47),
                HONEYDEW = RGB(240, 255, 240),
                HOTPINK = RGB(255, 105, 180),
                INDIANRED = RGB(205, 92, 92),
                INDIGO = RGB(75, 0, 130),
                IVORY = RGB(255, 255, 240),
                KHAKI = RGB(240, 230, 140),
                LAVENDER = RGB(230, 230, 250),
                LAVENDERBLUSH = RGB(255, 240, 245),
                LAWNGREEN = RGB(124, 252, 0),
                LEMONCHIFFON = RGB(255, 250, 205),
                LIGHTBLUE = RGB(173, 216, 230),
                LIGHTCORAL = RGB(240, 128, 128),
                LIGHTCYAN = RGB(224, 255, 255),
                LIGHTGOLDENRODYELLOW = RGB(250, 250, 210),
                LIGHTGRAY = RGB(211, 211, 211),
                LIGHTGREEN = RGB(144, 238, 144),
                LIGHTGREY = RGB(211, 211, 211),
                LIGHTPINK = RGB(255, 182, 193),
                LIGHTSALMON = RGB(255, 160, 122),
                LIGHTSEAGREEN = RGB(32, 178, 170),
                LIGHTSKYBLUE = RGB(135, 206, 250),
                LIGHTSLATEGRAY = RGB(119, 136, 153),
                LIGHTSLATEGREY = RGB(119, 136, 153),
                LIGHTSTEELBLUE = RGB(176, 196, 222),
                LIGHTYELLOW = RGB(255, 255, 224),
                LIME = RGB(0, 255, 0),
                LIMEGREEN = RGB(50, 205, 50),
                LINEN = RGB(250, 240, 230),
                MAGENTA = RGB(255, 0, 255),
                MAROON = RGB(128, 0, 0),
                MEDIUMAQUAMARINE = RGB(102, 205, 170),
                MEDIUMBLUE = RGB(0, 0, 205),
                MEDIUMORCHID = RGB(186, 85, 211),
                MEDIUMPURPLE = RGB(147, 112, 219),
                MEDIUMSEAGREEN = RGB(60, 179, 113),
                MEDIUMSLATEBLUE = RGB(123, 104, 238),
                MEDIUMSPRINGGREEN = RGB(0, 250, 154),
                MEDIUMTURQUOISE = RGB(72, 209, 204),
                MEDIUMVIOLETRED = RGB(199, 21, 133),
                MIDNIGHTBLUE = RGB(25, 25, 112),
                MINTCREAM = RGB(245, 255, 250),
                MISTYROSE = RGB(255, 228, 225),
                MOCCASIN = RGB(255, 228, 181),
                NAVAJOWHITE = RGB(255, 222, 173),
                NAVY = RGB(0, 0, 128),
                OLDLACE = RGB(253, 245, 230),
                OLIVE = RGB(128, 128, 0),
                OLIVEDRAB = RGB(107, 142, 35),
                ORANGE = RGB(255, 165, 0),
                ORANGERED = RGB(255, 69, 0),
                ORCHID = RGB(218, 112, 214),
                PALEGOLDENROD = RGB(238, 232, 170),
                PALEGREEN = RGB(152, 251, 152),
                PALETURQUOISE = RGB(175, 238, 238),
                PALEVIOLETRED = RGB(219, 112, 147),
                PAPAYAWHIP = RGB(255, 239, 213),
                PEACHPUFF = RGB(255, 218, 185),
                PERU = RGB(205, 133, 63),
                PINK = RGB(255, 192, 203),
                PLUM = RGB(221, 160, 221),
                POWDERBLUE = RGB(176, 224, 230),
                PURPLE = RGB(128, 0, 128),
                RED = RGB(255, 0, 0),
                ROSYBROWN = RGB(188, 143, 143),
                ROYALBLUE = RGB(65, 105, 225),
                SADDLEBROWN = RGB(139, 69, 19),
                SALMON = RGB(250, 128, 114),
                SANDYBROWN = RGB(244, 164, 96),
                SEAGREEN = RGB(46, 139, 87),
                SEASHELL = RGB(255, 245, 238),
                SIENNA = RGB(160, 82, 45),
                SILVER = RGB(192, 192, 192),
                SKYBLUE = RGB(135, 206, 235),
                SLATEBLUE = RGB(106, 90, 205),
                SLATEGRAY = RGB(112, 128, 144),
                SLATEGREY = RGB(112, 128, 144),
                SNOW = RGB(255, 250, 250),
                SPRINGGREEN = RGB(0, 255, 127),
                STEELBLUE = RGB(70, 130, 180),
                TAN = RGB(210, 180, 140),
                TEAL = RGB(0, 128, 128),
                THISTLE = RGB(216, 191, 216),
                TOMATO = RGB(255, 99, 71),
                TURQUOISE = RGB(64, 224, 208),
                VIOLET = RGB(238, 130, 238),
                WHEAT = RGB(245, 222, 179),
                WHITE = RGB(255, 255, 255),
                WHITESMOKE = RGB(245, 245, 245),
                YELLOW = RGB(255, 255, 0),
                YELLOWGREEN = RGB(154, 205, 50)

            };

            Index keyword; //!< The keyword

            /**
             * Constructor
             *
             * param[in] _keyword The identifier
             */
            Keyword(Index _keyword);

            /**
             * Output to stream.
             */
            std::ostream& stream(std::ostream& out) const override;

            typedef KeywordMapper<Keyword::Index> Map;

            static Map map;

            static unsigned int keywordFromValue(const Value* value);
        };
    }
}

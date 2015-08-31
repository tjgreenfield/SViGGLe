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

#include "CSSKeyword.hh"

namespace SVGL
{
    namespace CSS
    {

        /**
         * Keyword: An keyword value.
         */

        /**
         * Constructor
         *
         * param[in] _keyword The keyword
         */
        Keyword::Keyword(Keyword::Index _keyword) :
            keyword(_keyword)
        {

        }
        /**
         * Output to stream.
         */
        std::ostream& Keyword::stream(std::ostream& out) const
        {
            return out << map.lookup(keyword);
        }

        Keyword::Map Keyword::map({
            // common
            {"inherit", INHERIT},
            {"none", NONE},
            {"auto", AUTO},
            {"normal", NORMAL},

            // clip-rule / fill-rule
            {"nonzero", NONZERO},
            {"evenodd", EVENODD},

            // cursor
            {"crosshair", CROSSHAIR},
            {"default", DEFAULT},
            {"pointer", POINTER},
            {"move", MOVE},
            {"e-resize", E_RESIZE},
            {"ne-resize", NE_RESIZE},
            {"w-resize", W_RESIZE},
            {"nw-resize", NW_RESIZE},
            {"s-resize", S_RESIZE},
            {"se-resize", SE_RESIZE},
            {"sw-resize", SW_RESIZE},
            {"n-resize", N_RESIZE},
            {"text", TEXT},
            {"wait", WAIT},
            {"help", HELP},

            // pointer-events
            {"visiblePainted", VISIBLE_PAINTED},
            {"visibleFill", VISIBLE_FILL},
            {"visibleStroke", VISIBLE_STROKE},
            {"visible", VISIBLE},
            {"painted", PAINTED},
            {"fill", FILL},
            {"stroke", STROKE},
            {"all", ALL},

            // color-interpolation
            {"sRGB", SRGB},
            {"linearRGB", LINEAR_RGB},

            // stroke-linejoin, stroke-linecap
            {"miter", MITER},
            {"round", ROUND},
            {"bevel", BEVEL},
            {"butt", BUTT},
            {"square", SQUARE},

            // font-stretch
            {"wider", WIDER},
            {"narrower", NARROWER},
            {"ultra-condensed", ULTRA_CONDENSED},
            {"extra-condensed", EXTRA_CONDENSED},
            {"condensed", CONDENSED},
            {"semi-condensed", SEMI_CONDENSED},
            {"semi-expanded", SEMI_EXPANDED},
            {"expanded", EXPANDED},
            {"extra-expanded", EXTRA_EXPANDED},
            {"ultra-expanded", ULTRA_EXPANDED},

            // font-style
            {"italic", ITALIC},
            {"oblique", OBLIQUE},

             // font-variant
            {"smallcaps", SMALLCAPS},

            // font-weight
            {"bold", BOLD},
            {"bolder", BOLDER},
            {"lighter", LIGHTER},

            // direction
            {"ltr", LTR},
            {"rtl", RTL},

            // text-decoration
            {"underline", UNDERLINE},
            {"overline", OVERLINE},
            {"line-through", LINE_THROUGH},
            {"blink", BLINK},

            // unicode-bidi
            {"embed", EMBED},
            {"bidi-override", BIDI_OVERRIDE},

            // alignment-baseline
            {"baseline", BASELINE},
            {"before-edge", BEFORE_EDGE},
            {"text-before-edge", TEXT_BEFORE_EDGE},
            {"middle", MIDDLE},
            {"central", CENTRAL},
            {"after-edge", AFTER_EDGE},
            {"text-after-edge", TEXT_AFTER_EDGE},
            {"ideographic", IDEOGRAPHIC},
            {"alphabetic", ALPHABETIC},
            {"hanging", HANGING},
            {"mathematical", MATHEMATICAL},

            // baseline-shift
            {"sub", SUB},
            {"super", SUPER},
            {"value", VALUE},

            // dominant-baseline
            {"use-script", USE_SCRIPT},
            {"no-change", NO_CHANGE},
            {"reset-size", RESET_SIZE},

            // text-anchor
            {"start", START},
            {"end", END},

            // writing-mode
            {"lr-tb", LR_TB},
            {"rl-tb", RL_TB},
            {"tb-rl", TB_RL},
            {"lr", LR},
            {"rl", RL},
            {"tb", TB},

            // text-rendering
            {"optimizeSpeed", OPTIMIZE_SPEED},
            {"optimizeLegibility", OPTIMIZE_LEGIBILITY},
            {"geometricPrecision", GEOMETRIC_PRECISION},

            // Colors
            { "aliceblue", ALICEBLUE},
            { "antiquewhite", ANTIQUEWHITE},
            { "aqua", AQUA},
            { "aquamarine", AQUAMARINE},
            { "azure", AZURE},
            { "beige", BEIGE},
            { "bisque", BISQUE},
            { "black", BLACK},
            { "blanchedalmond", BLANCHEDALMOND},
            { "blue", BLUE},
            { "blueviolet", BLUEVIOLET},
            { "brown", BROWN},
            { "burlywood", BURLYWOOD},
            { "cadetblue", CADETBLUE},
            { "chartreuse", CHARTREUSE},
            { "chocolate", CHOCOLATE},
            { "coral", CORAL},
            { "cornflowerblue", CORNFLOWERBLUE},
            { "cornsilk", CORNSILK},
            { "crimson", CRIMSON},
            { "cyan", CYAN},
            { "darkblue", DARKBLUE},
            { "darkcyan", DARKCYAN},
            { "darkgoldenrod", DARKGOLDENROD},
            { "darkgray", DARKGRAY},
            { "darkgreen", DARKGREEN},
            { "darkgrey", DARKGREY},
            { "darkkhaki", DARKKHAKI},
            { "darkmagenta", DARKMAGENTA},
            { "darkolivegreen", DARKOLIVEGREEN},
            { "darkorange", DARKORANGE},
            { "darkorchid", DARKORCHID},
            { "darkred", DARKRED},
            { "darksalmon", DARKSALMON},
            { "darkseagreen", DARKSEAGREEN},
            { "darkslateblue", DARKSLATEBLUE},
            { "darkslategray", DARKSLATEGRAY},
            { "darkslategrey", DARKSLATEGREY},
            { "darkturquoise", DARKTURQUOISE},
            { "darkviolet", DARKVIOLET},
            { "deeppink", DEEPPINK},
            { "deepskyblue", DEEPSKYBLUE},
            { "dimgray", DIMGRAY},
            { "dimgrey", DIMGREY},
            { "dodgerblue", DODGERBLUE},
            { "firebrick", FIREBRICK},
            { "floralwhite", FLORALWHITE},
            { "forestgreen", FORESTGREEN},
            { "fuchsia", FUCHSIA},
            { "gainsboro", GAINSBORO},
            { "ghostwhite", GHOSTWHITE},
            { "gold", GOLD},
            { "goldenrod", GOLDENROD},
            { "gray", GRAY},
            { "grey", GREY},
            { "green", GREEN},
            { "greenyellow", GREENYELLOW},
            { "honeydew", HONEYDEW},
            { "hotpink", HOTPINK},
            { "indianred", INDIANRED},
            { "indigo", INDIGO},
            { "ivory", IVORY},
            { "khaki", KHAKI},
            { "lavender", LAVENDER},
            { "lavenderblush", LAVENDERBLUSH},
            { "lawngreen", LAWNGREEN},
            { "lemonchiffon", LEMONCHIFFON},
            { "lightblue", LIGHTBLUE},
            { "lightcoral", LIGHTCORAL},
            { "lightcyan", LIGHTCYAN},
            { "lightgoldenrodyellow", LIGHTGOLDENRODYELLOW},
            { "lightgray", LIGHTGRAY},
            { "lightgreen", LIGHTGREEN},
            { "lightgrey", LIGHTGREY},
            { "lightpink", LIGHTPINK},
            { "lightsalmon", LIGHTSALMON},
            { "lightseagreen", LIGHTSEAGREEN},
            { "lightskyblue", LIGHTSKYBLUE},
            { "lightslategray", LIGHTSLATEGRAY},
            { "lightslategrey", LIGHTSLATEGREY},
            { "lightsteelblue", LIGHTSTEELBLUE},
            { "lightyellow", LIGHTYELLOW},
            { "lime", LIME},
            { "limegreen", LIMEGREEN},
            { "linen", LINEN},
            { "magenta", MAGENTA},
            { "maroon", MAROON},
            { "mediumaquamarine", MEDIUMAQUAMARINE},
            { "mediumblue", MEDIUMBLUE},
            { "mediumorchid", MEDIUMORCHID},
            { "mediumpurple", MEDIUMPURPLE},
            { "mediumseagreen", MEDIUMSEAGREEN},
            { "mediumslateblue", MEDIUMSLATEBLUE},
            { "mediumspringgreen", MEDIUMSPRINGGREEN},
            { "mediumturquoise", MEDIUMTURQUOISE},
            { "mediumvioletred", MEDIUMVIOLETRED},
            { "midnightblue", MIDNIGHTBLUE},
            { "mintcream", MINTCREAM},
            { "mistyrose", MISTYROSE},
            { "moccasin", MOCCASIN},
            { "navajowhite", NAVAJOWHITE},
            { "navy", NAVY},
            { "oldlace", OLDLACE},
            { "olive", OLIVE},
            { "olivedrab", OLIVEDRAB},
            { "orange", ORANGE},
            { "orangered", ORANGERED},
            { "orchid", ORCHID},
            { "palegoldenrod", PALEGOLDENROD},
            { "palegreen", PALEGREEN},
            { "paleturquoise", PALETURQUOISE},
            { "palevioletred", PALEVIOLETRED},
            { "papayawhip", PAPAYAWHIP},
            { "peachpuff", PEACHPUFF},
            { "peru", PERU},
            { "pink", PINK},
            { "plum", PLUM},
            { "powderblue", POWDERBLUE},
            { "purple", PURPLE},
            { "red", RED},
            { "rosybrown", ROSYBROWN},
            { "royalblue", ROYALBLUE},
            { "saddlebrown", SADDLEBROWN},
            { "salmon", SALMON},
            { "sandybrown", SANDYBROWN},
            { "seagreen", SEAGREEN},
            { "seashell", SEASHELL},
            { "sienna", SIENNA},
            { "silver", SILVER},
            { "skyblue", SKYBLUE},
            { "slateblue", SLATEBLUE},
            { "slategray", SLATEGRAY},
            { "slategrey", SLATEGREY},
            { "snow", SNOW},
            { "springgreen", SPRINGGREEN},
            { "steelblue", STEELBLUE},
            { "tan", TAN},
            { "teal", TEAL},
            { "thistle", THISTLE},
            { "tomato", TOMATO},
            { "turquoise", TURQUOISE},
            { "violet", VIOLET},
            { "wheat", WHEAT},
            { "white", WHITE},
            { "whitesmoke", WHITESMOKE},
            { "yellow", YELLOW},
            { "yellowgreen", YELLOWGREEN},

        });

        int Keyword::keywordFromValue(const Value* value)
        {
            if (const Keyword* keyword = dynamic_cast<const Keyword*>(value))
            {
                return keyword->keyword;
            }
            return ERROR;
        }
    }
}

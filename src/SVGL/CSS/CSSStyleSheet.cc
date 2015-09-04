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

#include "CSSStyleSheet.hh"
#include "CSSStructures.hh"
#include "CSSStyle.hh"
#include "CSSParser.hh"
#include <algorithm>
#include <string>

namespace SVGL
{
    namespace CSS
    {
        /**
         * StyleSheet: A class that provides the abililty to read CSS styles and apply them to elements.
         */

        /**
         * Constructor
         */
        StyleSheet::StyleSheet(const char* code)
        {
            CSS::Parser parser(code);
            while (Ruleset_uptr ruleset = parser.readRuleset())
            {
                rulesets.push_back(std::move(ruleset));
                parser.readWSP();
            }
        }

        /**
         * Add new CSS code to the style sheet
         * param[in] code The string containing the CSS code to add.
         */
        void StyleSheet::add(const char* code)
        {
            CSS::Parser parser(code);
            while (Ruleset_uptr ruleset = parser.readRuleset())
            {
                rulesets.push_back(std::move(ruleset));
                parser.readWSP();
            }
        }

        /**
         * Output StyleSheet to a stream
         */
        std::ostream& operator<<(std::ostream &out, StyleSheet const &styleSheet)
        {
            bool first(true);
            for (const Ruleset_uptr& i: styleSheet.rulesets)
            {
                if (first)
                {
                    first = false;
                }
                else
                {
                    out << std::endl;
                }
                out << *i;
            }
            return out;
        }
    }
}

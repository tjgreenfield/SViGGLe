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

#include "CSSStructures.hh"
#include "CSSPropertySet.hh"
#include "CSSStyle.hh"
#include <memory>

namespace SVGL
{
    namespace CSS
    {
    	class Parser;
        /**
         * A class that provides the abililty to read CSS styles and apply them to elements.
         */
        class StyleSheet
        {
            friend Parser;
            friend class StyleSheetIndex;
            friend std::ostream& operator<<(std::ostream& out, const StyleSheet& styleSheet);

        public:
            /**
             * Constructor
             */
            StyleSheet(const char* code = "");

            /**
             * Add new CSS code to the style sheet
             * param[in] code The string containing the CSS code to add.
             */
            void add(const char* code);


        protected:
            typedef std::vector<Ruleset_uptr> Rulesets; //!< Type for the set of rulesets
            Rulesets rulesets; //!< The set of rulesets
        };

        typedef std::unique_ptr<StyleSheet> StyleSheet_uptr;

        std::ostream& operator<<(std::ostream& out, const StyleSheet& styleSheet);
    }
}

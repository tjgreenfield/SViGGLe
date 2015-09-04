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
#include "CSSStyleSheet.hh"
#include <memory>

namespace SVGL
{
    namespace CSS
    {
    	class Parser;
        /**
         * A class that provides the abililty to read CSS styles and apply them to elements.
         */
        class StyleSheetIndex
        {
        public:
            /**
             * Apply the stylesheet to specified element (where applicable)
             * param[in] element The element to apply the stylesheet to
             */
            void apply(Element* element, PropertySet* propertySet) const;

            /**
             * Add a stylesheet to the index
             */
            void add(const StyleSheet& _styleSheet);

            /**
             * Clear the index
             */
            void clear();


            /**
             * Sort the index in preparation to apply
             */
            void sort();


        protected:
            typedef std::vector<SelectorBlock> SelectorIndex; //!< Type for the indexes
            SelectorIndex selectorIndex; //!< The indexes of selectors for non-important declarations
            SelectorIndex importantSelectorIndex; //!< The indexes of selectors for important declarations
        };

        typedef std::unique_ptr<StyleSheet> StyleSheet_uptr;

        std::ostream& operator<<(std::ostream& out, const StyleSheetIndex& styleSheetIndex);
    }
}

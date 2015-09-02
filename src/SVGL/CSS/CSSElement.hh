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

#include "CSSSizeContext.hh"

#include <SVGL/Types/SubString.hh>
#include <SVGL/CSS/Values/CSSValue.hh>

#include <memory>
#include <vector>
#include <string>

namespace SVGL
{
    namespace CSS
    {
        class Style;
        class StyleSheet;
        class DeclarationBlock;

        /**
         * A virtual class that forms the interface between the CSS Selectors and the document.
         *
         * @details
         *   Specifies an interface through which the selectors can get the tag name, attributes, parent/sibling and style interface of the element.
         */
        class Element
        {
        public:

            /**
             * Virtual destructor
             */
            virtual ~Element() = default;

            /**
             * Get the StyleSheet object that contains the specified styles for the element.
             *
             * @return A pointer to the StyleSheet object.
             * @retval nullptr Indicates there is no specified style information for the element.
             */
            virtual const DeclarationBlock* getSpecifiedStyle() const = 0;

            /**
             * Get the Style object for the current element.
             *
             * @details The style object is used to apply styles from the stylesheets.
             * @return A pointer to the Style object.
             */
            virtual Style* getStyle() = 0;

            /**
             * Calculate any relative units used in the element
             */
            virtual void calculate(const SizeContext& sizeContext) = 0;

            /**
             * Get the tag name of the element.
             */
            virtual const char* getTagName() const = 0;

            /**
             * Get the element id
             */
            virtual const char* getID() const = 0;

            /**
             * Get the value of the specified attribute.
             *
             * @param[in] attributeName The name of the attribute to get.
             */
            virtual bool testAttributeValue(const char* attributeName, const char* attributeValue) const = 0;

            /**
             * Get the parent element.
             *
             * @return A pointer to the ElementInterface object that is the parent of this object.
             * @retval nullptr Indicates there is no parent object.
             */
            virtual const Element* getParent() const = 0;

            /**
             * Get the previous sibling element.
             *
             * @return A pointer to the ElementInterface object that is the previous sibling of this object.
             * @retval nullptr Indicates there is no previous sibling object.
             */
            virtual const Element* getPrevSibling() const = 0;
        };
    }
}

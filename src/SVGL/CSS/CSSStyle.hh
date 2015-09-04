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

#include <SVGL/CSS/CSSValues.hh>
#include <SVGL/CSS/CSSSizeContext.hh>

namespace SVGL
{
    namespace CSS
    {
        /**
         * An abstract class for implementation style classes
         */
        class Style
        {
        public:

            /**
             * Virtualised destructor
             */
            virtual ~Style() = default;

            /**
             * Set the style properties of the style object using the values in the property set
             *
             * @param[in] propertySet The set of properties to apply.
             */
            void applyPropertySets(const PropertySet& propertySet, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext);

            virtual void applyPropertySet(const PropertySet& propertySet, const CSS::SizeContext& sizeContext) = 0;

            virtual void updateSizeContext(SizeContext* sizeContext);
        };
    }
}

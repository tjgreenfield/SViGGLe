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

#include "CSSDeclarationBlock.hh"
#include <SVGL/CSS/CSSSelectors.hh>

namespace SVGL
{
    namespace CSS
    {
        /**
         * Combination of a specific selector and a declaration block. Used in StyleSheet indexes.
         */
        struct SelectorBlock
        {
            Selector* selector; //!< The selector
            DeclarationBlock* block; //!< The declaration block

            /**
             * Constructor
             * @details
             * The selector and declaration block must be managed and must be valid for the life of the SelectorBlock
             * param[in] _selector Pointer to the Selector
             * param[in] _block Pointer to the declaration block
             */
            inline SelectorBlock(Selector* _selector = nullptr, DeclarationBlock* _block = nullptr) :
                selector(_selector),
                block(_block)
            {

            }
        };
    }
}

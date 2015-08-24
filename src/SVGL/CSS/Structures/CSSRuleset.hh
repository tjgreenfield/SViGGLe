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
#include <SVGL/Types/SubString.hh>

#include <string>
#include <memory>

namespace SVGL
{
    namespace CSS
    {
        /**
         * Combination of a set of selectors and a declaration block
         */
        class Ruleset
        {
            friend std::ostream& operator<<(std::ostream& out, const Ruleset& ruleSet);
        public:
            typedef std::vector<Selector_uptr> Selectors; //!< A type for the set of selectors
            Selectors selectors; //!< The set of selectors
            DeclarationBlock_uptr block; //!< The declaration block 
        };

        typedef std::unique_ptr<Ruleset> Ruleset_uptr;

        std::ostream& operator<<(std::ostream& out, const Ruleset& ruleSet);
    }
}

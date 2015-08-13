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
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include "CSSDeclaration.hh"
#include <SVGL/Types/SubString.hh>
#include <SVGL/Types/CStrHash.hh>
#include <unordered_map>
#include <string>
#include <memory>

namespace SVGL
{
    namespace CSS
    {
        class DeclarationBlock;
        typedef std::unique_ptr<DeclarationBlock> DeclarationBlock_uptr;


        /**
         * A set of declarations
         */
        class DeclarationBlock
        {
            friend std::ostream& operator<<(std::ostream& out, const DeclarationBlock& block);

        public:
            typedef std::unordered_map<const char*, Declaration_uptr, CStrHash, CStrEquals> Map; //!< Map type designed to use raw string data from declaration as key
            Map map; //!< Set of not-important declarations
            Map importantMap; //!< Set of important declarations

        public:

            /**
             * Add a declaration ot the block, checking if the delcaration is important or not.
             * @param[in] declaration Declaration to be added (and owned) by the block.
             */
            void put(Declaration_uptr&& declaration);

            /**
             * Add a declaration ot the block, checking if the delcaration is important or not.
             * @param[in] declaration Declaration to be added (and owned) by the block.
             */
            void put();

            /**
             * Merge a declaration ot the block.
             * @param[in] declarationBlock DeclarationBlock to be merged (and owned) by the block.
             */
            void put(DeclarationBlock_uptr&& declarationBlock);

        };

        std::ostream& operator<<(std::ostream& out, const DeclarationBlock& block);
    }
}

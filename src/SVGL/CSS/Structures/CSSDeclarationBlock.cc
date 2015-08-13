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

#include "CSSDeclarationBlock.hh"

namespace SVGL
{
    namespace CSS
    {
        /**
         * Declaration Block: A set of declarations
         */
        /**
          * Add a declaration ot the block, checking if the delcaration is important or not.
          * @param[in] declaration Declaration to be added (and owned) by the block.
          */
        void DeclarationBlock::put(Declaration_uptr&& declaration)
        {
            if (declaration->important)
            {
                importantMap[declaration->name.c_str()] = std::move(declaration);
            }
            else
            {
                map[declaration->name.c_str()] = std::move(declaration);
            }
        }

        /**
         * Merge a declaration ot the block.
         * @param[in] declarationBlock DeclarationBlock to be merged (and owned) by the block.
         */
        void DeclarationBlock::put(DeclarationBlock_uptr&& declarationBlock)
        {
            for (auto&i : declarationBlock->map)
            {
                map[i.first] = std::move(i.second);
            }
            for (auto&i : declarationBlock->importantMap)
            {
                importantMap[i.first] = std::move(i.second);
            }
        }

        /**
         * Output to stream
         */
        std::ostream& operator<<(std::ostream& out, const DeclarationBlock& block)
        {
            for (const auto& i : block.map)
            {
                out << *i.second;
                out << "; ";
            }
            return out;
        }
    }
}

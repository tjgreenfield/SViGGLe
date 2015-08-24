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

#include <SVGL/Types/SubString.hh>
#include <memory>
#include <string>

namespace SVGL
{
    namespace XML
    {
        class Node;

        typedef std::unique_ptr<Node> Node_uptr;

        class Node
        {
        public:
            Node() = default;

            Node(Node& _node) = delete;

            Node& operator=(Node& _node) = delete;

            virtual ~Node();

            virtual void setAttribute(SubString name, SubString value);

            virtual void appendChild(Node_uptr&& child);

            virtual void appendText(SubString data);

            virtual std::ostream& stream(std::ostream& out) const;
        };

        std::ostream& operator<<(std::ostream& out, const Node& node);
    }
}

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

#include "XMLNode.hh"
#include <SVGL/Types/SubString.hh>
#include <string>
#include <vector>

namespace SVGL
{
    namespace XML
    {
        class XMLElement : public Node
        {
            class TextNode : public Node
            {
            public:
                std::string data;

                TextNode(SubString _data);

                virtual operator std::string();
            };

            std::string tag;

            struct Attribute
            {
                std::string name;
                std::string value;

                inline Attribute(SubString _name, SubString _value) :
                    name(_name),
                    value(_value)
                {
                }
            };

            typedef std::vector<Attribute> Attributes;
            Attributes attributes;

            typedef std::vector<Node_uptr> Children;
            Children children;

        public:

            XMLElement(SubString _tag);

            void setAttribute(SubString name, SubString value) override;

            void appendChild(Node_uptr&& child) override;

            void appendText(SubString data) override;

            std::ostream& stream(std::ostream& out) const override;
        };
    }
}

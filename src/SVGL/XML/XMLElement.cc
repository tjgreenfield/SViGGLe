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

#include "XMLNode.hh"
#include "XMLElement.hh"

namespace SVGL
{
    namespace XML
    {
        XMLElement::TextNode::TextNode(SubString _data) :
            data(_data.start, _data.count)
        {

        }

        XMLElement::TextNode::operator std::string()
        {
            return data;
        }

        XMLElement::XMLElement(SubString _tag) :
            tag(_tag.start, _tag.count)
        {

        }

        void XMLElement::setAttribute(SubString name, SubString value)
        {
            attributes.emplace_back(Attribute(name, value));
        }

        void XMLElement::appendChild(Node_uptr&& child)
        {
            children.push_back(std::move(child));
        }

        void XMLElement::appendText(SubString data)
        {
            children.emplace_back(Node_uptr(new TextNode(data)));
        }

        std::ostream& XMLElement::stream(std::ostream& out) const
        {
            out << "<" << tag;
            for (const Attribute& attribute : attributes)
            {
                out << " " << attribute.name << "=\"" << attribute.value << "\"";
            }
            if (children.size() == 0)
            {
                out << "/>";
            }
            else
            {
                out << ">";
                for (const Node_uptr& child : children)
                {
                    out << *child;
                }
                out << "</" << tag << ">";
            }
            return out;
        }
    }
}

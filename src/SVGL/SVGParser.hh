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

#include <SVGL/Document.hh>
#include <SVGL/Types/ElementsTypes.hh>
#include <SVGL/XML/XMLParser.hh>
#include <SVGL/XML/XMLNode.hh>
#include <SVGL/Types/SubString.hh>

#include <unordered_map>

namespace SVGL
{
    typedef std::unordered_map<SubString, ElementType> ElementTypeMap;
    extern ElementTypeMap elementTypeMap;

    ElementType getElementType(SubString tag);

    class Parser : public XML::Parser
    {
    public:
        inline Parser(const char* _s = nullptr) :
            XML::Parser(_s)
        {

        }

        inline Document_uptr readSVG()
        {
            XML::Node_uptr node(readXML());
            if (dynamic_cast<Document*>(node.get()))
            {
                return Document_uptr(dynamic_cast<Document*>(node.release()));
            }
            return Document_uptr();
        }

        virtual XML::Node_uptr createElement(SubString tag);
    };

}

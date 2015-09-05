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

#include "SVGLParser.hh"
#include "Elements.hh"

namespace SVGL
{


    XML::Node_uptr Parser::createElement(SubString tag, XML::Node* _parent)
    {
        Elements::Root* parent = dynamic_cast<Elements::Root*>(_parent);
        Elements::Tag::Index type = Elements::Tag::getIndex(tag);
        switch (type)
        {
        default:
        case Elements::Tag::INVALID:
            return std::move(XML::Node_uptr(new XML::Node()));
        case Elements::Tag::SVG:
            return std::move(XML::Node_uptr(new Elements::SVG(parent)));
        case Elements::Tag::G:
            return std::move(XML::Node_uptr(new Elements::Group(parent)));
        case Elements::Tag::PATH:
            return std::move(XML::Node_uptr(new Elements::Path(parent)));
        case Elements::Tag::RECT:
            return std::move(XML::Node_uptr(new Elements::Rect(parent)));
        case Elements::Tag::CIRCLE:
            return std::move(XML::Node_uptr(new Elements::Circle(parent)));
        case Elements::Tag::ELLIPSE:
            return std::move(XML::Node_uptr(new Elements::Ellipse(parent)));
        case Elements::Tag::LINE:
            return std::move(XML::Node_uptr(new Elements::Line(parent)));
        case Elements::Tag::POLYLINE:
            return std::move(XML::Node_uptr(new Elements::PolyLine(parent)));
        case Elements::Tag::POLYGON:
            return std::move(XML::Node_uptr(new Elements::Polygon(parent)));
        case Elements::Tag::TEXT:
            return std::move(XML::Node_uptr(new Elements::Text(parent)));
        case Elements::Tag::STYLE:
            return std::move(XML::Node_uptr(new Elements::Style(parent)));
        case Elements::Tag::IMAGE:
            return std::move(XML::Node_uptr(new Elements::Image(parent)));
        case Elements::Tag::DEFS:
            return std::move(XML::Node_uptr(new Elements::Defs(parent)));
        case Elements::Tag::USE:
            return std::move(XML::Node_uptr(new Elements::Use(parent)));
        }
    }

    Document_uptr Parser::readSVG()
    {
        Document_uptr document(new Document());
        XML::Node_uptr node(readXML(document.get()));
        if (auto svg = dynamic_cast<Elements::SVG*>(node.get()))
        {
            node.release();
            document->setRoot(Elements::SVG_uptr(svg));
            return std::move(document);
        }
        return Document_uptr();
    }

}

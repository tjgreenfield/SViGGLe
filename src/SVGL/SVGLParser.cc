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
    ElementTypeMap elementTypeMap = {
        { "svg", ET_SVG },
        { "g", ET_G },
        { "path", ET_PATH },
        { "rect", ET_RECT },
        { "circle", ET_CIRCLE},
        { "ellipse", ET_ELLIPSE},
        { "line", ET_LINE},
        { "polyline", ET_POLYLINE},
        { "polygon", ET_POLYGON},
        { "text", ET_TEXT},
        { "style", ET_STYLE},
        { "image", ET_IMAGE}
    };

    ElementType getElementType(SubString tag)
    {
        auto i = elementTypeMap.find(tag);
        if (i != elementTypeMap.end())
        {
            return i->second;
        }
        return ET_INVALID;
    }

    XML::Node_uptr Parser::createElement(SubString tag, XML::Node* _parent)
    {
        Elements::Root* parent = dynamic_cast<Elements::Root*>(_parent);
        ElementType type = getElementType(tag);
        switch (type)
        {
        default:
        case ET_INVALID:
            return std::move(XML::Node_uptr(new XML::Node()));
        case ET_SVG:
            return std::move(XML::Node_uptr(new Elements::SVG(parent)));
        case ET_G:
            return std::move(XML::Node_uptr(new Elements::Group(parent)));
        case ET_PATH:
            return std::move(XML::Node_uptr(new Elements::Path(parent)));
        case ET_RECT:
            return std::move(XML::Node_uptr(new Elements::Rect(parent)));
        case ET_CIRCLE:
            return std::move(XML::Node_uptr(new Elements::Circle(parent)));
        case ET_ELLIPSE:
            return std::move(XML::Node_uptr(new Elements::Ellipse(parent)));
        case ET_LINE:
            return std::move(XML::Node_uptr(new Elements::Line(parent)));
        case ET_POLYLINE:
            return std::move(XML::Node_uptr(new Elements::PolyLine(parent)));
        case ET_POLYGON:
            return std::move(XML::Node_uptr(new Elements::Polygon(parent)));
        case ET_TEXT:
            return std::move(XML::Node_uptr(new Elements::Text(parent)));
        case ET_STYLE:
            return std::move(XML::Node_uptr(new Elements::Style(parent)));
        case ET_IMAGE:
            return std::move(XML::Node_uptr(new Elements::Image(parent)));
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

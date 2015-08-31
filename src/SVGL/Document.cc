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

#include "Document.hh"
#include <SVGL/CSS/CSSSizeContext.hh>

namespace SVGL
{

    Document::Document() :
        ViewPort(1280, 720)
    {
    }

    std::ostream& Document::stream(std::ostream& out) const
    {
        out << "svg:{ ";
        streamChildren(out);
        out << "}";
        return out;
    }

    const Document* Document::getDocument() const
    {
        return this;
    }

    void Document::appendChild(XML::Node_uptr&& child)
    {
        if (Element::Style* childStyle = dynamic_cast<Element::Style*>(child.get()))
        {
            child.release();
            styles.emplace_back(childStyle);
            childStyle->setParent(this);
        }
        else
        {
            Group::appendChild(std::move(child));
        }
    }

    void Document::applyStyleSheets()
    {
        // TODO: merge and apply all?
        CSS::PropertySet inherit;
        CSS::SizeContext sizeContext(width, height, 10);
        Group::applyStyleSheet(&styles.front()->styleSheet, inherit, sizeContext);
    }
}

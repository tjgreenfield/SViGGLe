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

#include "SVGLDocument.hh"
#include <SVGL/CSS/CSSSizeContext.hh>

namespace SVGL
{

    Document::Document()
    {

    }

    void Document::setRoot(Elements::SVG_uptr&& _svg)
    {
        svg = std::move(_svg);
        svg->submitElementIDs(this);
    }

    std::ostream& Document::stream(std::ostream& out) const
    {
        // TODO XML header stuff
        out << *svg;
        return out;
    }

    Document* Document::getDocument()
    {
        return this;
    }

    void Document::submitElementID(const SubString _id, Elements::Root* element)
    {
        idMap.emplace(_id, element);
    }

    void Document::removeElementID(const SubString _id, Elements::Root* element)
    {
        const auto& pair = idMap.equal_range(_id);
        for (auto i = pair.first; i != pair.second; ++i)
        {
            if (i->second == element)
            {
                idMap.erase(i);
                return;
            }
        }
    }

    void Document::addStyleSheet(CSS::StyleSheet& _styleSheet)
    {
        styleSheet += _styleSheet;
    }

    void Document::applyStyleSheets()
    {
        CSS::PropertySet inherit;
        CSS::SizeContext sizeContext(1280, 720, 10);
        svg->applyStyleSheet(&styleSheet, inherit, sizeContext);
    }

    void Document::clearBuffers()
    {
        svg->clearBuffers();
    }

    void Document::setDirty()
    {
        svg->setDirty();
    }

    void Document::buffer(double tolerance)
    {
        svg->buffer(tolerance);
    }

    void Document::render(Render::Context* context)
    {
        svg->render(context);
    }
}

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

#include <SVGL/Element/Structure/ElementViewPort.hh>
#include <SVGL/Element/Structure/ElementStyle.hh>
#include <SVGL/XML/XML.hh>
#include <memory>
#include <iostream>
#include <utility>

namespace SVGL
{
    class Document : public Element::ViewPort
    {
    protected:
        std::vector<Element::Style_uptr> styles;

    public:
        Document();

        /**
         * Output to stream
         */
        std::ostream& stream(std::ostream& out) const override;

        const Document* getDocument() const override;

        /* From XML::Node */

        void appendChild(XML::Node_uptr&& child) override;

        /* From Element::Group */

        //void applyStyleSheet(CSS::StyleSheet* styleSheet) override;

        void applyStyleSheets();
    };

    typedef std::unique_ptr<Document> Document_uptr;
}

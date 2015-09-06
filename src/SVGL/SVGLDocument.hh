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

#include <SVGL/Elements/Structures/ElementsSVG.hh>
#include <SVGL/Elements/Abstracts/ElementsRoot.hh>
#include <SVGL/Elements/Abstracts/ElementsInstance.hh>
#include <SVGL/CSS/CSSStyleSheet.hh>
#include <SVGL/XML/XML.hh>
#include <SVGL/Types/SubString.hh>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <utility>

namespace SVGL
{
    class Document : public Elements::Root
    {
    protected:
        typedef std::unordered_multimap<SubString, Elements::Root*> IDMap;
        IDMap idMap;

        Elements::SVG_uptr svg;
        CSS::StyleSheetIndex styleSheetIndex;
        Elements::Instance_uptr instance;

    public:
        Document();

        void setRoot(Elements::SVG_uptr&& svg);

        /**
         * Output to stream
         */
        std::ostream& stream(std::ostream& out) const override;

        Document* getDocument() const override;

        Elements::Root* getElementByID(const char* _id) const;

        void submitElementID(const SubString _id, Elements::Root* element);

        void removeElementID(const SubString _id, Elements::Root* element);

        void addStyleSheet(CSS::StyleSheet& styleSheet);

        void applyStyleSheets();

        void clearBuffers();

        void setDirty();

        void buffer(double tolerance);

        void render(Render::Context* context);

        Elements::Instance_uptr calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) override;

    };

    typedef std::unique_ptr<Document> Document_uptr;

}

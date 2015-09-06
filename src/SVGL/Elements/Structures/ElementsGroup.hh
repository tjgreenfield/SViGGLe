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

#include <SVGL/Elements/Abstracts/ElementsStyled.hh>
#include <SVGL/Styles/StylesGraphic.hh>

namespace SVGL
{
    namespace Elements
    {
        class Group : public Styled
        {
        protected:
            class Instance : public Elements::Instance
            {
            protected:
                const Group* group;
                Styles::Graphic style;
                std::vector<Instance_uptr> children;

            public:
                Instance(const Group* _group, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext);

                void buffer(double tolerance) override;

                void render(Render::Context* context) const override;

                void calculateBoundingBox(BoundingBox* boundingBox) const override;
            };

            typedef std::vector<Styled_uptr> StyledChildren;
            StyledChildren styledChildren;

            typedef std::vector<Root_uptr> OtherChildren;
            OtherChildren otherChildren;

        public:

            Group(Root* _parent = nullptr);

            /* From CSS::Element */
            const char* getTagName() const override;

            /* From XML::Node */
            void appendChild(XML::Node_uptr&& child) override;


            /* From Elements::Root */

            Root* findElementByID(const char* _id) override;

            void submitElementIDs(Document* document) override;

            std::ostream& stream(std::ostream& out) const override;

            std::ostream& streamChildren(std::ostream& out) const;

            void cascadeStyle(const CSS::StyleSheetIndex& styleSheetIndex) override;

            Instance_uptr calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) override;



        };
    }
}

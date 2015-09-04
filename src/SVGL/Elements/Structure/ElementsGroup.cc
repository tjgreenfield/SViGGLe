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

#include "ElementsGroup.hh"
#include "ElementsDefs.hh"
#include "ElementsStyle.hh"
#include <SVGL/SVGLDocument.hh>

#include <SVGL/CSS/Values/CSSKeyword.hh>

namespace SVGL
{
    namespace Elements
    {
        Group::Group(Root* _parent) :
            Graphic(_parent)
        {
        }


        /***** From CSS::Element *****/

        const char* Group::getTagName() const
        {
            return "g";
        }

        /***** From XML::Node *****/

        void Group::appendChild(XML::Node_uptr&& child)
        {
            if (auto defsChild = dynamic_cast<Defs*>(child.get()))
            {
                child.release();
                otherChildren.emplace_back(defsChild);
            }
            else if (auto graphicChild = dynamic_cast<Graphic*>(child.get()))
            {
                child.release();
                graphicChildren.emplace_back(graphicChild);
            }
            else if (auto styleChlid = dynamic_cast<Style*>(child.get()))
            {
                child.release();
                otherChildren.emplace_back(styleChlid);

                Document* document = getDocument();
                if (document)
                {
                    document->addStyleSheet(styleChlid->styleSheet);
                }
            }
            else if (auto rootChild = dynamic_cast<Root*>(child.get()))
            {
                child.release();
                otherChildren.emplace_back(rootChild);
            }
        }

        /***** From Elements::Root *****/

        Root* Group::findElementByID(const char* _id)
        {
            if (id.compare(_id) == 0)
            {
                return this;
            }
            else
            {
                for (const Graphic_uptr& child : graphicChildren)
                {
                    if (Root* result = child->findElementByID(_id))
                    {
                        return result;
                    }
                }
                for (const Root_uptr& child : otherChildren)
                {
                    if (Root* result = child->findElementByID(_id))
                    {
                        return result;
                    }
                }
            }

            return nullptr;
        }

        void Group::submitElementIDs(Document* document)
        {
            Root::submitElementIDs(document);
            for (const Graphic_uptr& child : graphicChildren)
            {
                child->submitElementIDs(document);
            }
            for (const Root_uptr& child : otherChildren)
            {
                child->submitElementIDs(document);
            }
        }

        std::ostream& Group::streamChildren(std::ostream& out) const
        {
            bool first(true);

            for (const Graphic_uptr& child : graphicChildren)
            {
                if (first)
                {
                    first = false;
                }
                else
                {
                    out << ", ";
                }

                out << *child;
            }

            return out;
        }

        std::ostream& Group::stream(std::ostream& out) const
        {
            out << "g:{ ";
            streamChildren(out);
            out << "}";
            return out;
        }

        void Group::cascadeStyle(const CSS::StyleSheetIndex& styleSheetIndex)
        {
            Graphic::cascadeStyle(styleSheetIndex);
            for (const auto& i : graphicChildren)
            {
                i->cascadeStyle(styleSheetIndex);
            }
            for (const auto& i : otherChildren)
            {
                i->cascadeStyle(styleSheetIndex);
            }
        }

        Instance_uptr Group::calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext)
        {
            return std::move(Instance_uptr(new Instance(this, inherit, sizeContext)));
        }

        /***** Elements::Group::Instance *****/

        Group::Instance::Instance(const Group* _group, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) :
            group(_group)
        {
            CSS::PropertySet propertySet(group->cascadedStyles);
            propertySet.set(group->getSpecifiedStyle());
            propertySet.inherit(inherit);

            style.applyPropertySet(propertySet, sizeContext);

            for (const auto& i : group->graphicChildren)
            {
                children.emplace_back(std::move(i->calculateInstance(propertySet, sizeContext)));
            }
        }

        void Group::Instance::buffer(double tolerance)
        {
            double t(group->transform.transformTolerance(tolerance));
            for (const auto& i : children)
            {
                if (i)
                {
                    i->buffer(t);
                }
            }
        }

        void Group::Instance::render(Render::Context* context)
        {
            context->pushTransform(&group->transform);
            for (const auto& i : children)
            {
                if (i)
                {
                    i->render(context);
                }
            }
            context->popTransform();
        }


    }
}

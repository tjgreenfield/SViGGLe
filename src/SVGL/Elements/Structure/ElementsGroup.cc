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

namespace SVGL
{
    namespace Elements
    {
        /* From CSS::Element */

        Group::Group(Root* _parent) :
            Graphic(_parent)
        {
        }

        /**
         * Get the Style object for the current element.
         *
         * @details The style object is used to apply styles from the stylesheets.
         * @return A pointer to the Style object.
         */
        CSS::Style* Group::getStyle()
        {
            return &style;
        }

        /**
         * Get the tag name of the element.
         */
        const char* Group::getTagName() const
        {
            return "g";
        }

        /**
         * Test the value of the specified attribute.
         *
         * @param[in] index The attribute index of the attribute to test.
         * @param[in] attributeValue The value of the attribute to test.
         */
        bool Group::testAttributeValue(unsigned int index, const char* attributeValue) const
        {
            return Graphic::testAttributeValue(index, attributeValue);
        }

        /* From XML::Node */

        void Group::appendChild(XML::Node_uptr&& child)
        {
            if (Graphic* element = dynamic_cast<Graphic*>(child.get()))
            {
                child.release();
                children.emplace_back(element);
                element->setParent(this);
            }
        }

        Root* Group::findElementByID(const char* _id)
        {
            if (id.compare(_id) == 0)
            {
                return this;
            }
            else
            {
                for (const Graphic_uptr& child : children)
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
            for (const Graphic_uptr& child : children)
            {
                child->submitElementIDs(document);
            }
        }

        void Group::applyStyleSheet(CSS::StyleSheet* styleSheet, const CSS::PropertySet& inherit, CSS::SizeContext& sizeContext)
        {
            CSS::PropertySet propertySet;
            styleSheet->apply(this, &propertySet, inherit, sizeContext);

            CSS::SizeContext mySizeContext(sizeContext);
            style.updateSizeContext(&mySizeContext);

            if (auto dimension = dynamic_cast<const CSS::Dimension*>(propertySet[CSS::Property::FONT_SIZE]))
            {
                mySizeContext.setFontSize(dimension->calculate(sizeContext));
            }

            for (const Graphic_uptr& child : children)
            {
                child->applyStyleSheet(styleSheet, propertySet, mySizeContext);
            }
        }

        std::ostream& Group::streamChildren(std::ostream& out) const
        {
            bool first(true);

            for (const Graphic_uptr& child : children)
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

        /**
         * Clear children buffers
         */
        void Group::clearBuffers()
        {
            for (const Graphic_uptr& child : children)
            {
                child->clearBuffers();
            }

            dirty = true;
        }

        /**
         * Get children to setup buffers
         */
        void Group::buffer(double tolerance)
        {
            double t = transform.transformTolerance(tolerance);

            for (const Graphic_uptr& child : children)
            {
                child->buffer(t);
            }
        }

        /**
         * Draw children
         */
        void Group::render(Render::Context* context)
        {
            context->pushTransform(&transform);

            for (const Graphic_uptr& child : children)
            {
                child->render(context);
            }

            context->popTransform();
        }
    }
}

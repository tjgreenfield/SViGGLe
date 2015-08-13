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
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "ElementsGroup.hh"

namespace SVGL
{
    /* From CSS::Element */

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
     * Get the value of the specified attribute.
     *
     * @param[in] attributeName The name of the attribute to get.
     */
    const char* Group::getAttributeValue(const char* attributeName) const
    {
        return "";
    }

    /* From XML::Node */

    void Group::appendChild(Node_uptr&& child)
    {
        if (Element* element = dynamic_cast<Element*>(child.get()))
        {
            child.release();
            children.emplace_back(element);
            element->setParent(this);
        }
    }

    Element* Group::findElementByID(const char* _id)
    {
        if (id.compare(_id) == 0)
        {
            return this;
        }
        else
        {
            for (const Element_uptr& child : children)
            {
                if (Element* result = child->findElementByID(_id))
                {
                    return result;
                }
            }
        }
        return nullptr;
    }

    void Group::applyStyleSheet(CSS::StyleSheet* styleSheet)
    {
        styleSheet->apply(this);
        for (const Element_uptr& child : children)
        {
            child->applyStyleSheet(styleSheet);
        }
    }

    std::ostream& Group::streamChildren(std::ostream& out) const
    {
        bool first(true);
        for (const Element_uptr& child : children)
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
        for (const Element_uptr& child : children)
        {
            child->clearBuffers();
        }
    }

    /**
     * Get children to setup buffers
     */
    void Group::buffer(double tolerance)
    {
        for (const Element_uptr& child : children)
        {
            child->buffer(tolerance);
        }
    }

    /**
     * Draw children
     */
    void Group::render(Render::Context* context)
    {
        for (const Element_uptr& child : children)
        {
            child->render(context);
        }
    }
}

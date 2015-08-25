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

#include "ElementsElement.hh"

#include <SVGL/Transform/TransformParser.hh>

#include <utility>

namespace SVGL
{
    /**
     * Get the StyleSheet object that contains the specified styles for the element.
     *
     * @return A pointer to the StyleSheet object.
     * @retval nullptr Indicates there is no specified style information for the element.
     */
    const CSS::DeclarationBlock* Element::getSpecifiedStyle() const
    {
        return &styleDeclarations;
    }

    /**
     * Get the element id
     */
    const char* Element::getID() const
    {
        return id.c_str();
    }

    /**
     * Get the parent element.
     *
     * @return A pointer to the Element object that is the parent of this object.
     * @retval nullptr Indicates there is no parent object.
     */
    const Element* Element::getParent() const
    {
        return parent;
    }

    /**
     * Get the previous sibling element.
     *
     * @return A pointer to the Element object that is the previous sibling of this object.
     * @retval nullptr Indicates there is no previous sibling object.
     */
    const Element* Element::getPrevSibling() const
    {
        return parent ? parent->getPrevChild(this) : nullptr;
    }

    /**
     * Get the child before the one specified, used to implement getPrevSibling above
     */
    const Element* Element::getPrevChild(const Element* element) const
    {
        return nullptr;
    }

    Element::AttributeMap Element::attributeMap = {
        { "id", ID },
        { "class", CLASS },
        { "style", STYLE },
        { "transform", TRANSFORM },
        { "d", D },
        { "pathLength", PATH_LENGTH },
        { "x", X },
        { "y", Y },
        { "width", WIDTH },
        { "height", HEIGHT },
        { "rx", RX },
        { "ry", RY },

        { "color", COLOR },
        { "fill", FILL },
        { "stroke", STROKE },
    };

    void Element::setAttribute(SubString name, SubString value)
    {
        auto i = attributeMap.find(name);
        if (i != attributeMap.end())
        {
            setAttribute(i->second, name, value);
        }
    }

    void Element::setAttribute(unsigned int index, SubString name, SubString value)
    {
        CSS::Value_uptr v;
        switch (index)
        {
        case ID:
            id.assign(value);
            break;
        case STYLE:
            styleDeclarations.put(std::move(
                CSS::Parser(value.start).readDeclarationBlock()
                ));
            break;
        case COLOR:
        case FILL:
        case STROKE:
            styleDeclarations.put(
                CSS::Declaration_uptr(new CSS::Declaration(
                name,
                CSS::Parser(value.start).readPropertyValue()
                ))
                );
            break;
        case TRANSFORM:
            {
                TransformParser(value.start).readTransform(&transform);
            }
            break;
        default:
            break;
        }
    }

    Element* Element::findElementByID(const char* _id)
    {
        if (id.compare(_id) == 0)
        {
            return this;
        }
        return nullptr;
    }

    void Element::applyStyleSheet(CSS::StyleSheet* styleSheet)
    {
        styleSheet->apply(this);
    }

    void Element::clearBuffers()
    {
        dirty = true;
    }

    void Element::setDirty()
    {
        dirty = true;
        if (parent)
        {
            parent->setDirty();
        }
    }

    void Element::buffer(double tolerance)
    {
        dirty = false;
    }

    void Element::draw()
    {

    }


    void Element::render(Render::Context* context)
    {

    }

}

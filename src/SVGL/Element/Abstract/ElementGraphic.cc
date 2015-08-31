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

#include "ElementGraphic.hh"

#include <SVGL/Transform/TransformParser.hh>

#include <utility>

namespace SVGL
{
    namespace Element
    {
        Graphic::AttributeMap Graphic::attributeMap =
        {
            { "id", Attribute::ID },
            { "class", Attribute::CLASS },
            { "style", Attribute::STYLE },
            { "transform", Attribute::TRANSFORM },
            { "d", Attribute::D },
            { "pathLength", Attribute::PATH_LENGTH },
            { "x", Attribute::X },
            { "y", Attribute::Y },
            { "x1", Attribute::X1 },
            { "y1", Attribute::Y1 },
            { "x2", Attribute::X2 },
            { "y2", Attribute::Y2 },
            { "width", Attribute::WIDTH },
            { "height", Attribute::HEIGHT },
            { "rx", Attribute::RX },
            { "ry", Attribute::RY },
            { "cx", Attribute::CX },
            { "cy", Attribute::CY },
            { "r", Attribute::R },
            { "points", Attribute::POINTS }
        };

        /**
         * Get the StyleSheet object that contains the specified styles for the element.
         *
         * @return A pointer to the StyleSheet object.
         * @retval nullptr Indicates there is no specified style information for the element.
         */
        const CSS::DeclarationBlock* Graphic::getSpecifiedStyle() const
        {
            return &styleDeclarations;
        }

        /**
         * Calculate the relative units
         */
        void Graphic::calculate(const CSS::SizeContext&)
        {

        }

        /**
         * Get the element id
         */
        const char* Graphic::getID() const
        {
            return id.c_str();
        }

        /**
         * Get the parent element.
         *
         * @return A pointer to the Element object that is the parent of this object.
         * @retval nullptr Indicates there is no parent object.
         */
        const CSS::CSSElement* Graphic::getParent() const
        {
            return dynamic_cast<CSS::CSSElement*>(parent);
        }

        /**
         * Get the previous sibling element.
         *
         * @return A pointer to the CSSElement object that is the previous sibling of this object.
         * @retval nullptr Indicates there is no previous sibling object.
         */
        const CSS::CSSElement* Graphic::getPrevSibling() const
        {
            Graphic* parentGraphic(dynamic_cast<Graphic*>(parent));
            return parentGraphic ? parentGraphic->getPrevChild(this) : nullptr;
        }

        /**
         * Get the child before the one specified, used to implement getPrevSibling above
         */
        const CSS::CSSElement* Graphic::getPrevChild(const Graphic*) const
        {
            return nullptr;
        }



        /**
         * Test the value of the specified attribute.
         *
         * @param[in] attributeName The name of the attribute to test.
         * @param[in] attributeValue The value of the attribute to test.
         */
        bool Graphic::testAttributeValue(const char* attributeName, const char* attributeValue) const
        {
            auto i = attributeMap.find(attributeName);
            if(i != attributeMap.end())
            {
                return testAttributeValue(i->second, attributeValue);
            }
            return false;
        }

        /**
         * Test the value of the specified attribute.
         *
         * @param[in] attributeName The name of the attribute to test.
         * @param[in] attributeValue The value of the attribute to test.
         */
        bool Graphic::testAttributeValue(unsigned int index, const char* attributeValue) const
        {
            switch (index)
            {
            case Attribute::ID:
                return (id == attributeValue) || (attributeValue == nullptr);
            case Attribute::CLASS:
                return (cls == attributeValue) || (attributeValue == nullptr);;
            default:
                return false;
            }
            return false;
        }

        void Graphic::setAttribute(SubString name, SubString value)
        {
            auto i = attributeMap.find(name);
            if(i != attributeMap.end())
            {
                setAttribute(i->second, name, value);
            }
            else if (CSS::Property::Index index = CSS::Property::map.lookup(name))
            {
                styleDeclarations.put(
                    CSS::Declaration_uptr(new CSS::Declaration(
                                          index,
                                          CSS::Parser(value.start).readPropertyValue()
                                      ))
                );
            }
        }

        void Graphic::setAttribute(unsigned int index, SubString, SubString value)
        {
            switch (index)
            {
            case Attribute::ID:
                id.assign(value);
                break;
            case Attribute::CLASS:
                cls.assign(value);
                break;
            case Attribute::STYLE:
                if (CSS::DeclarationBlock_uptr declarationBlock = CSS::Parser(value.start).readDeclarationBlock())
                {
                    styleDeclarations.put(std::move(declarationBlock));
                }
                break;
            case Attribute::TRANSFORM:
                {
                    TransformParser(value.start).readTransform(&transform);
                }
                break;
            default:

                break;
            }
        }

        void Graphic::applyStyleSheet(CSS::StyleSheet* styleSheet, const CSS::PropertySet& inherit, CSS::SizeContext& sizeContext)
        {
            CSS::PropertySet propertySet;
            styleSheet->apply(this, &propertySet, inherit, sizeContext);
        }

        void Graphic::clearBuffers()
        {
            dirty = true;
        }

        void Graphic::setDirty()
        {
            dirty = true;
            Graphic* parentGraphic(dynamic_cast<Graphic*>(parent));
            if (parentGraphic)
            {
                parentGraphic->setDirty();
            }
        }

        void Graphic::buffer(double)
        {
            dirty = false;
        }

        void Graphic::draw()
        {
        }


        void Graphic::render(Render::Context*)
        {
        }
    }
}

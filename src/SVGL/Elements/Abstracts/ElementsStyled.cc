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

#include "ElementsStyled.hh"

#include <SVGL/Transforms/TransformsParser.hh>

#include <utility>

namespace SVGL
{
    namespace Elements
    {


        /**
         * Get the StyleSheet object that contains the specified styles for the element.
         *
         * @return A pointer to the StyleSheet object.
         * @retval nullptr Indicates there is no specified style information for the element.
         */
        const CSS::DeclarationBlock* Styled::getSpecifiedStyle() const
        {
            return &styleDeclarations;
        }

        /**
         * Calculate the relative units
         */
        void Styled::calculate(const CSS::SizeContext&)
        {

        }

        /**
         * Get the element id
         */
        const char* Styled::getID() const
        {
            return id.c_str();
        }

        /**
         * Get the parent element.
         *
         * @return A pointer to the Element object that is the parent of this object.
         * @retval nullptr Indicates there is no parent object.
         */
        const CSS::Element* Styled::getParent() const
        {
            return dynamic_cast<CSS::Element*>(parent);
        }

        /**
         * Get the previous sibling element.
         *
         * @return A pointer to the Element object that is the previous sibling of this object.
         * @retval nullptr Indicates there is no previous sibling object.
         */
        const CSS::Element* Styled::getPrevSibling() const
        {
            Styled* parentGraphic(dynamic_cast<Styled*>(parent));
            return parentGraphic ? parentGraphic->getPrevChild(this) : nullptr;
        }

        /**
         * Get the child before the one specified, used to implement getPrevSibling above
         */
        const CSS::Element* Styled::getPrevChild(const Styled*) const
        {
            return nullptr;
        }



        /**
         * Test the value of the specified attribute.
         *
         * @param[in] attributeName The name of the attribute to test.
         * @param[in] attributeValue The value of the attribute to test.
         */
        bool Styled::testAttributeValue(const char* attributeName, const char* attributeValue) const
        {
            return testAttributeValue(Attribute::getIndex(attributeName), attributeValue);
        }

        /**
         * Test the value of the specified attribute.
         *
         * @param[in] attributeName The name of the attribute to test.
         * @param[in] attributeValue The value of the attribute to test.
         */
        bool Styled::testAttributeValue(unsigned int index, const char* attributeValue) const
        {
            switch (index)
            {
            case Attribute::ID:
                return (id == attributeValue) || (attributeValue == nullptr);
            case Attribute::Index::CLASS:
                return (cls == attributeValue) || (attributeValue == nullptr);;
            default:
                return false;
            }
            return false;
        }

        void Styled::setAttribute(SubString name, SubString value)
        {
            if (unsigned int attributeIndex = Attribute::getIndex(name))
            {
                setAttribute(attributeIndex, value);
            }
            else if (CSS::Property::Index propertyIndex = CSS::Property::map.lookup(name))
            {
                styleDeclarations.put(
                    CSS::Declaration_uptr(new CSS::Declaration(
                                          propertyIndex,
                                          CSS::Parser(value.start).readPropertyValue()
                                      ))
                );
            }
        }

        void Styled::setAttribute(unsigned int index, SubString value)
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
                    Transforms::Parser(value.start).readTransform(&transform);
                }
                break;
            default:

                break;
            }
        }

        void Styled::cascadeStyle(const CSS::StyleSheetIndex& styleSheetIndex)
        {
            cascadedStyles.clear();
            styleSheetIndex.apply(this, &cascadedStyles);
        }

        void Styled::setDirty()
        {
            dirty = true;
            Styled* parentGraphic(dynamic_cast<Styled*>(parent));
            if (parentGraphic)
            {
                parentGraphic->setDirty();
            }
        }
    }
}

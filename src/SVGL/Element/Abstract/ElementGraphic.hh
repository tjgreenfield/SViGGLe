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

#include "ElementRoot.hh"
#include <SVGL/CSS/CSS.hh>
#include <SVGL/Render/RenderContext.hh>
#include <SVGL/Types/SubString.hh>
#include <unordered_map>

namespace SVGL
{
    namespace Element
    {
        class ViewPort;

        class Graphic : public Root, public CSS::CSSElement
        {
        public:
            static const int GRAPHIC_OFFSET = 0x01000000;

            class Attribute
            {
            public:
                enum Index
                {
                    // Primary attribute list
                    ID,
                    CLASS,
                    STYLE,
                    TRANSFORM,
                    D,
                    PATH_LENGTH,
                    X,
                    Y,
                    X1,
                    Y1,
                    X2,
                    Y2,
                    WIDTH,
                    HEIGHT,
                    RX,
                    RY,
                    CX,
                    CY,
                    R,
                    POINTS,
                    //...

                    // Include "event" attributes

                    // Include "conditional processing" attributes
                };
            };



            typedef std::unordered_map<SubString, Attribute::Index> AttributeMap;
            static AttributeMap attributeMap;

        protected:
            std::string cls;
            CSS::DeclarationBlock styleDeclarations;
            Transform transform;
            bool dirty;

        public:

            /**
             * Constructor
             */
            inline Graphic(Root* _parent = nullptr) :
                Root(_parent),
                dirty(true)
            {
            }

            /* From CSS::Element */

            /**
             * Get the StyleSheet object that contains the specified styles for the element.
             *
             * @return A pointer to the StyleSheet object.
             * @retval nullptr Indicates there is no specified style information for the element.
             */
            const CSS::DeclarationBlock* getSpecifiedStyle() const override;

            /**
             * Calculate the relative units
             */
            void calculate(const CSS::SizeContext& sizeContext) override;

            /**
             * Get the element id
             */
            const char* getID() const override;

            /**
             * Test the value of the specified attribute.
             *
             * @param[in] attributeName The name of the attribute to test.
             * @param[in] attributeValue The value of the attribute to test.
             */
            bool testAttributeValue(const char* attributeName, const char* attributeValue) const override;

            /**
             * Test the value of the specified attribute.
             *
             * @param[in] index The attribute index of the attribute to test.
             * @param[in] attributeValue The value of the attribute to test.
             */
            virtual bool testAttributeValue(unsigned int index, const char* attributeValue) const;

            /**
             * Get the parent element.
             *
             * @return A pointer to the Element object that is the parent of this object.
             * @retval nullptr Indicates there is no parent object.
             */
            const CSS::CSSElement* getParent() const override;

            /**
             * Get the previous sibling element.
             *
             * @return A pointer to the Element object that is the previous sibling of this object.
             * @retval nullptr Indicates there is no previous sibling object.
             */
            const CSS::CSSElement* getPrevSibling() const override;

            /**
             * Get the child before the one specified, used to implement getPrevSibling above
             */
            virtual const CSS::CSSElement* getPrevChild(const Graphic* element) const;

            /* From XML::Node */

            void setAttribute(SubString name, SubString value) override;

            virtual void setAttribute(unsigned int index, SubString name, SubString value);

            /* Common interface for all Graphic Elements */

            virtual void applyStyleSheet(CSS::StyleSheet* styleSheet, const CSS::PropertySet& inherit, CSS::SizeContext& sizeContext);

            /*virtual double getWidth();

            virtual double getHeight();

            virtual ViewPort* getViewPort();*/

            virtual void clearBuffers();

            virtual void setDirty();

            virtual void buffer(double tolerance);

            virtual void draw();

            virtual void render(Render::Context* context);

        };

        typedef std::unique_ptr<Graphic> Graphic_uptr;
    }
}

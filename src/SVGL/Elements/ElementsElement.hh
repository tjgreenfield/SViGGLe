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

#pragma once

#include <SVGL/XML/XML.hh>
#include <SVGL/CSS/CSSElement.hh>
#include <SVGL/Styles/StyleTypes.hh>
#include <SVGL/Render/RenderContext.hh>
#include <SVGL/Types/SubString.hh>
#include <unordered_map>
#include <ostream>

namespace SVGL
{
    class ViewPort;

    typedef XML::Node_uptr Node_uptr;

    class Element : public XML::Node, public CSS::Element
    {
    public:
        static const int GRAPHIC_OFFSET = 0x01000000;

        enum AttributeIndex {
            // Primary attribute list
            ID,
            CLASS,
            STYLE,
            TRANSFORM,
            D,
            PATH_LENGTH,
            X,
            Y,
            WIDTH,
            HEIGHT,
            RX,
            RY,
            //...

            // Include "presentation" aka style attributes
            COLOR = GRAPHIC_OFFSET + Styles::Inherit::COLOR,
            // ...

            FILL,
            STROKE,

            // Include "event" attributes

            // Include "conditional processing" attributes
        };


        typedef std::unordered_map<SubString, unsigned int> AttributeMap;
        static AttributeMap attributeMap;

    protected:
        Element* parent;
        std::string id;
        CSS::DeclarationBlock styleDeclarations;
        bool dirty;

    public:

        /**
         * Constructor
         */
        inline Element(Element* _parent = nullptr) :
            parent(_parent),
			dirty(true)
        {

        }

        /**
         * Set the parent
         */
        inline void setParent(Element* _parent)
        {
            parent = _parent;
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
         * Get the element id
         */
        const char* getID() const override;

        /**
         * Get the parent element.
         *
         * @return A pointer to the Element object that is the parent of this object.
         * @retval nullptr Indicates there is no parent object.
         */
        const Element* getParent() const override;

        /**
         * Get the previous sibling element.
         *
         * @return A pointer to the Element object that is the previous sibling of this object.
         * @retval nullptr Indicates there is no previous sibling object.
         */
        const Element* getPrevSibling() const override;

        /**
         * Get the child before the one specified, used to implement getPrevSibling above
         */
        virtual const Element* getPrevChild(const Element* element) const;
        
        /* From XML::Node */

        void setAttribute(SubString name, SubString value) override;

        virtual void setAttribute(unsigned int index, SubString name, SubString value);

        /* Common interface for all SVG Elements */

        virtual Element* findElementByID(const char* _id);

        virtual void applyStyleSheet(CSS::StyleSheet* styleSheet);

        /*virtual double getWidth();

        virtual double getHeight();

        virtual ViewPort* getViewPort();*/

        virtual void clearBuffers();

        virtual void setDirty();

        virtual void buffer(double tolerance);

        virtual void draw();

        virtual void render(Render::Context* context);

    };

    typedef std::unique_ptr<Element> Element_uptr;
}

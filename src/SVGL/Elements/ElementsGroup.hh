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

#include "ElementsElement.hh"
#include <SVGL/Styles/StyleGraphic.hh>

namespace SVGL
{
    class Group : public Element
    {
    protected:
        Styles::Graphic style;
        
        typedef std::vector<Element_uptr> Elements;
        Elements children;

    public:

        /* From CSS::Element */
        
        /**
         * Get the Style object for the current element.
         *
         * @details The style object is used to apply styles from the stylesheets.
         * @return A pointer to the Style object.
         */
        CSS::Style* getStyle() override;

        /**
         * Get the tag name of the element.
         */
        const char* getTagName() const override;

        /**
         * Get the value of the specified attribute.
         *
         * @param[in] attributeName The name of the attribute to get.
         */
        const char* getAttributeValue(const char* attributeName) const override;


        /* From XML::Node */
        
        void appendChild(Node_uptr&& child) override;


        /* From Element */

        Element* findElementByID(const char* _id) override;

        virtual void applyStyleSheet(CSS::StyleSheet* styleSheet);

        /**
         * Output to stream
         */
        std::ostream& stream(std::ostream& out) const override;

        /**
         * Output children to stream
         */
        std::ostream& streamChildren(std::ostream& out) const;

        /**
         * Clear children buffers
         */
        void clearBuffers() override;

        /**
         * Get children to setup buffers
         */
        void buffer(double tolerance) override;

        /**
         * Draw children
         */
        void render(Render::Context* context) override;

    };
}

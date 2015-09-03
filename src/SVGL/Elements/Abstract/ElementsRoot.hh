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

#include <SVGL/XML/XML.hh>
#include <SVGL/CSS/CSSElement.hh>
#include <SVGL/Render/RenderContext.hh>
#include <SVGL/Types/SubString.hh>
#include <unordered_map>

namespace SVGL
{
    class Document;

    namespace Elements
    {
        class Root : public XML::Node
        {
        protected:
            Root* parent;
            std::string id;

        public:

            /**
             * Constructor
             */
            Root(Root* _parent = nullptr);

            /**
             * Virtual Destructor
             */
            ~Root() override;


            /**
             * Set the parent
             */
            void setParent(Root* _parent);

            /* Common interface for all SVG Elements */

            /**
             * Get the element id
             */
            const char* getID() const;

            /**
             * Get the parent element.
             *
             * @return A pointer to the Element object that is the parent of this object.
             * @retval nullptr Indicates there is no parent object.
             */
            const Root* getParent() const;

            virtual Document* getDocument();

            virtual void submitElementIDs(Document* document);

            virtual Root* findElementByID(const char* _id);

            void setAttribute(SubString name, SubString value) override;
        };

        typedef std::unique_ptr<Root> Root_uptr;
    }
}

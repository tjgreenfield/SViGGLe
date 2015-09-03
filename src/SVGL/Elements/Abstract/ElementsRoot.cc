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

#include "ElementsRoot.hh"
#include <SVGL/SVGLDocument.hh>
#include <SVGL/Transforms/TransformsParser.hh>

#include <utility>
#include <string.h>

namespace SVGL
{
    namespace Elements
    {
        Root::Root(Root* _parent) :
            parent(_parent)
        {

        }

        /**
         * Virtual Destructor
         */
        Root::~Root()
        {
            if (!id.empty())
            {
                Document* document = getDocument();
                if (document)
                {
                    document->removeElementID(id, this);
                }
            }
        }

        /**
         * Get the element id
         */
        const char* Root::getID() const
        {
            return id.c_str();
        }

        /**
         * Set the parent
         */
        void Root::setParent(Root* _parent)
        {
            parent = _parent;
        }

        /**
         * Get the parent element.
         *
         * @return A pointer to the Element object that is the parent of this object.
         * @retval nullptr Indicates there is no parent object.
         */
        const Root* Root::getParent() const
        {
            return parent;
        }

        Document* Root::getDocument()
        {
            return parent ? parent->getDocument() : nullptr;
        }

        void Root::setAttribute(SubString name, SubString value)
        {
            if (strncmp(name.start, "id", 3) == 0)
            {
                id.assign(value.start, value.count);
            }
        }

        void Root::submitElementIDs(Document* document)
        {
            if (!id.empty())
            {
                document->submitElementID(id, this);
            }
        }

        /* Common interface for all SVG Elements */
        Root* Root::findElementByID(const char* _id)
        {
            if (id == _id)
            {
                return this;
            }
            else
            {
                return nullptr;
            }
        }
    }
}

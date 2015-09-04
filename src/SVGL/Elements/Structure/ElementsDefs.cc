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

#include "ElementsDefs.hh"
#include "ElementsStyle.hh"
#include <SVGL/SVGLDocument.hh>

namespace SVGL
{
    namespace Elements
    {
        Defs::Defs(Root* _parent) :
            Group(_parent)
        {
        }

        /***** From XML::Node *****/
        void Defs::setAttribute(SubString name, SubString value)
        {
            Group::setAttribute(name, value);
        }

        /***** From Elements::Root *****/
        Instance_uptr Defs::calculateInstance(const CSS::PropertySet& , const CSS::SizeContext& )
        {
            // we don't wany to draw anything under the defs element directly.
            // they are accessed/drawn only by reference, e.g. use element
            return Instance_uptr(nullptr);
        }
    }
}

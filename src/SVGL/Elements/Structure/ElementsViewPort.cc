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

#include "ElementsViewPort.hh"

namespace SVGL
{
    namespace Elements
    {
        ViewPort::ViewPort(Root* _parent) :
            Group(_parent)
        {
        }

        void ViewPort::applyStyleSheet(CSS::StyleSheet* styleSheet, const CSS::PropertySet& inherit, CSS::SizeContext& sizeContext)
        {
            CSS::PropertySet propertySet;
            styleSheet->apply(this, &propertySet, inherit, sizeContext);

            CSS::SizeContext mySizeContext(sizeContext);
            style.updateSizeContext(&mySizeContext);

            mySizeContext.setViewport(width, height);
            if (auto dimension = dynamic_cast<const CSS::Dimension*>(propertySet[CSS::Property::FONT_SIZE]))
            {
                mySizeContext.setFontSize(dimension->calculate(sizeContext));
            }

            for (const Graphic_uptr& child : children)
            {
                child->applyStyleSheet(styleSheet, propertySet, mySizeContext);
            }
        }

        std::ostream& ViewPort::stream(std::ostream& out) const
        {
            out << "viewport:{ ";
            streamChildren(out);
            out << "}";
            return out;
        }
    }
}

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

#include "ElementsSVG.hh"
#include <SVGL/SVGLDocument.hh>
#include <SVGL/CSS/CSSSizeContext.hh>


namespace SVGL
{
    namespace Elements
    {

        SVG::SVG(Root* _parent) :
            Group(_parent),
            x(0),
            y(0),
            width(1280),
            height(720)
        {
        }

        std::ostream& SVG::stream(std::ostream& out) const
        {
            out << "svg:{ ";
            streamChildren(out);
            out << "}";
            return out;
        }

        Instance_uptr SVG::calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext)
        {
            CSS::SizeContext viewport(sizeContext);
            viewport.setViewport(width.calculate(sizeContext), height.calculate(sizeContext));
            transform.identity();
            transform.translateR(x.calculate(sizeContext), y.calculate(sizeContext));
            return Group::calculateInstance(inherit, viewport);
        }
    }
}

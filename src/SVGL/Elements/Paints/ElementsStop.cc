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

#include "ElementsStop.hh"
#include <SVGL/Elements/ElementsAttribute.hh>

namespace SVGL
{
    namespace Elements
    {
        Stop::Stop(Root* _parent) :
            Root(_parent),
            color(0),
            opacity(1.0f),
            offset(0)
        {
        }

        void Stop::setAttribute(SubString name, SubString value)
        {
            switch ((int)Attribute::getIndex(name))
            {
            case Attribute::STOP_COLOR:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    colorFromValue(&color, cssvalue.get());
                }
                break;
            case Attribute::STOP_OPACITY:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        opacity = dimension->calculate();
                    }
                }
                break;
            case Attribute::OFFSET:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        offset = dimension->calculate();
                    }
                }
                break;
            default:
                Root::setAttribute(name, value);
                break;
            }
        }

        Instance_uptr Stop::calculateInstance(const CSS::PropertySet& , const CSS::SizeContext& )
        {
            return std::move(Instance_uptr(nullptr));
        }
    }
}

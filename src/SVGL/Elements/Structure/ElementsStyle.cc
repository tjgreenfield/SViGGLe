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

#include "ElementsStyle.hh"

namespace SVGL
{
    namespace Elements
    {
        Style::AttributeMap Style::attributeMap =
        {
            { "id", Attribute::ID },
            { "type", Attribute::TYPE },
            { "media", Attribute::MEDIA },
            { "title", Attribute::TITLE },
        };

        Style::Style(Root* _parent) :
            Root(_parent)
        {
        }

        void Style::appendText(SubString data)
        {
            styleSheet.add(data.start);
        }

        void Style::setAttribute(SubString name, SubString value)
        {
            AttributeMap::iterator i = attributeMap.find(name);
            if (i != attributeMap.end())
            {
                switch (i->second)
                {
                case Attribute::ID:
                    id.assign(value.start, value.count);
                    break;
                case Attribute::TYPE:
                    type.assign(value.start, value.count);
                    break;
                case Attribute::MEDIA:
                    media.assign(value.start, value.count);
                    break;
                case Attribute::TITLE:
                    title.assign(value.start, value.count);
                    break;
                default:
                    break;
                }
            }
        }

        Instance_uptr Style::calculateInstance(const CSS::PropertySet& , const CSS::SizeContext& )
        {
            return std::move(Instance_uptr(nullptr));
        }
    }
}

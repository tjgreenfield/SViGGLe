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

#include "StyleVector.hh"
#include <iostream>
#include <limits>

namespace SVGL
{
    namespace Styles
    {

        /**
         * Constructor
         */
        Vector::Vector() :
            Graphic(),
            fill(0xFF000000),
            stroke(0x00000000),
            strokeWidth(1),
            strokeMiterLimit(4),
            strokeDashOffset(0),
            strokeDashArray({std::numeric_limits<double>::max(), 0})
        {
            hasStroke() = 0;
            hasFill() = 1;
        }

        void Vector::applyPropertySet(const CSS::PropertySet& propertySet, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext)
        {
            using namespace CSS;
            using namespace CSS::Property;

            constexpr auto keywordFromValue = &Keyword::keywordFromValue;

            // fill
            if (colorFromValue(&fill, propertySet[Property::FILL]))
            {
                hasFill() = 1;
            }
            else
            {
                if (keywordFromValue(propertySet[Property::FILL]) == Keyword::NONE)
                {
                    hasFill() = 0;
                }
                else
                {
                    fill = RGBA(0, 0, 0, (fill >> 24) & 0xFF);
                    hasFill() = 1;
                }
            }


            // fill-rule
            if (keywordFromValue(propertySet[Property::FILL_RULE]) == Keyword::NONZERO)
            {
                fillRule() = CR_NONZERO;
            }
            else
            {
                fillRule() = CR_EVENODD;
            }

            // fill-opacity
            if (auto dimension = dynamic_cast<const CSS::Dimension*>(propertySet[Property::FILL_OPACITY]))
            {
                fill = RGBA(fill, 255 * dimension->calculate(sizeContext));
            }
            else
            {
                fill = RGBA(fill, 255);
            }

            // stroke
            if (colorFromValue(&stroke, propertySet[Property::STROKE]))
            {
                hasStroke() = 1;
            }
            else
            {
                if (keywordFromValue(propertySet[Property::STROKE]) == Keyword::NONE)
                {
                    hasStroke() = 0;
                }
                else
                {
                    stroke = RGBA(0, 0, 0, (stroke >> 24) & 0xFF);
                    hasStroke() = 1;
                }
            }

            // stroke-dasharray
            if (auto list = dynamic_cast<const CSS::ValueList*>(propertySet[Property::STROKE_DASHARRAY]))
            {
                strokeDashArray.clear();
                strokeDashArray.reserve(list->vector.size());
                for (const CSS::Value_uptr& v : list->vector)
                {
                    if (auto dimension = dynamic_cast<const CSS::Dimension*>(v.get()))
                    {
                        strokeDashArray.push_back(dimension->calculate(sizeContext));
                    }
                }
                strokeDashArray.shrink_to_fit();
            }
            else
            {
                strokeDashArray.clear();
            }

            // stroke-dashoffset
            if (auto dimension = dynamic_cast<const CSS::Dimension*>(propertySet[Property::STROKE_DASHOFFSET]))
            {
                strokeDashOffset = dimension->calculate(sizeContext);
            }
            else
            {
                strokeDashOffset = 0;
            }

            // stroke-linecap
            switch (keywordFromValue(propertySet[Property::STROKE_LINECAP]))
            {
            case Keyword::BUTT:
                strokeLineCap() = LC_BUTT;
                break;
            case Keyword::ROUND:
                strokeLineCap() = LC_ROUND;
                break;
            case Keyword::SQUARE:
                strokeLineCap() = LC_SQUARE;
                break;
            default:
                strokeLineCap() = LC_BUTT;
                break;
            }

            // stroke-linejoin
            switch (keywordFromValue(propertySet[Property::STROKE_LINEJOIN]))
            {
            case Keyword::MITER:
                strokeLineJoin() = LJ_MITER;
                break;
            case Keyword::ROUND:
                strokeLineJoin() = LJ_ROUND;
                break;
            case Keyword::BEVEL:
                strokeLineJoin() = LJ_BEVEL;
                break;
            default:
                strokeLineJoin() = LJ_BEVEL;
                break;
            }

            // stroke-miterlimit
            if (auto dimension = dynamic_cast<const CSS::Dimension*>(propertySet[Property::STROKE_MITERLIMIT]))
            {
                strokeMiterLimit = dimension->calculate(sizeContext);
            }
            else
            {
                strokeMiterLimit = 1;
            }


            // stroke-opacity
            if (auto dimension = dynamic_cast<const CSS::Dimension*>(propertySet[Property::STROKE_OPACITY]))
            {
                stroke = RGBA(stroke, 255 * dimension->calculate(sizeContext));
            }
            else
            {
                stroke = RGBA(stroke, 255);
            }

            // stroke-width
            if (auto dimension = dynamic_cast<const CSS::Dimension*>(propertySet[Property::STROKE_WIDTH]))
            {
                strokeWidth = dimension->calculate(sizeContext);
            }
            else
            {
                strokeWidth = 1;
            }

            Graphic::applyPropertySet(propertySet, inherit, sizeContext);
        }
    }
}

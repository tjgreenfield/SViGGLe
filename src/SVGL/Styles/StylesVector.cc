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

#include "StylesVector.hh"

#include <SVGL/Render/Paints/RenderColor.hh>
#include <SVGL/Elements/Abstracts/ElementsPaint.hh>
#include <SVGL/SVGLDocument.hh>

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
            //fill(0xFF000000),
            //stroke(0x00000000),
            strokeWidth(1),
            strokeMiterLimit(4),
            strokeDashOffset(0),
            strokeDashArray({std::numeric_limits<double>::max(), 0})
        {
            hasStroke() = 0;
            hasFill() = 1;
        }

        void Vector::applyPropertySet(const CSS::PropertySet& propertySet, const CSS::SizeContext& sizeContext)
        {
            using namespace CSS;
            using namespace CSS::Property;

            constexpr auto keywordFromValue = &Keyword::keywordFromValue;

            // fill
            unsigned int fillColor;
            if (colorFromValue(&fillColor, propertySet[Property::FILL]))
            {
                fill = Render::Paint_uptr(new Render::Color(fillColor));
                hasFill() = 1;
            }
            else
            {
                if (keywordFromValue(propertySet[Property::FILL]) == Keyword::NONE)
                {
                    fill = nullptr;
                    hasFill() = 0;
                }
                else if (auto hash = dynamic_cast<const CSS::Hash*>(propertySet[Property::FILL]))
                {
                    auto root = sizeContext.document->getElementByID(hash->hash.c_str());
                    if (auto paint = dynamic_cast<const Elements::Paint*>(root))
                    {
                        fill = paint->calculatePaint(propertySet, sizeContext);
                    }
                    if (fill)
                    {
                        hasFill() = 1;
                    }
                    else
                    {
                        hasFill() = 0;
                    }
                }
                else
                {
                    fill = Render::Paint_uptr(new Render::Color(RGB(0, 0, 0)));
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
                fillOpacity = dimension->calculate(sizeContext);
            }
            else
            {
                fillOpacity = 1.0;
            }

            // stroke
            unsigned int strokeColor;
            if (colorFromValue(&strokeColor, propertySet[Property::STROKE]))
            {
                stroke = Render::Paint_uptr(new Render::Color(strokeColor));
                hasStroke() = 1;
            }
            else
            {
                if (keywordFromValue(propertySet[Property::STROKE]) == Keyword::NONE)
                {
                    stroke = nullptr;
                    hasStroke() = 0;
                }
                else if (auto hash = dynamic_cast<const CSS::Hash*>(propertySet[Property::STROKE]))
                {
                    auto root = sizeContext.document->getElementByID(hash->hash.c_str());
                    if (auto paint = dynamic_cast<const Elements::Paint*>(root))
                    {
                        stroke = paint->calculatePaint(propertySet, sizeContext);
                    }
                    if (stroke)
                    {
                        hasStroke() = 1;
                    }
                    else
                    {
                        hasStroke() = 0;
                    }
                }
                else
                {
                    stroke = nullptr;
                    hasStroke() = 0;
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
                strokeOpacity = dimension->calculate(sizeContext);
            }
            else
            {
                strokeOpacity = 1.0;
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

            Graphic::applyPropertySet(propertySet, sizeContext);
        }

        void Vector::buffer(const Elements::Instance& instance)
        {
            if (fill)
            {
                fill->buffer(instance);
            }
            if (stroke)
            {
                stroke->buffer(instance);
            }
        }
    }
}

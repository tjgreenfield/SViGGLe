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
        Vector::Vector(SVG* _parent) :
            Graphic(_parent),
            fill(defaultFill),
            stroke(defaultStroke),
            strokeWidth(defaultStrokeWidth),
            strokeMiterLimit(defaultStrokeMiterLimit),
            strokeLineJoin(defaultStrokeLineJoin),
            strokeDashArray({std::numeric_limits<double>::max(), 0})
        {

        }

        /**
         * Test if the fill is none
         * @retval true There is a fill
         * @retval false There is no fill
         */
        bool Vector::hasFill() const
        {
            if (flags[Inherit::FILL])
            {
                return parent ? parent->hasFill() : false;
            }
            else
            {
                return !flags[Flags::FILL_NONE];
            }
        }


        /**
         * Get the value of the fill color property
         * @return The color property
         */
        Color Vector::getFill() const
        {
            if (flags[Inherit::FILL])
            {
                return parent ? parent->getFill() : defaultFill;
            }
            else
            {
                return fill;
            }
        }

        /**
         * Test if the stroke is none
         * @retval true There is a stroke
         * @retval false There is no stroke
         */
        bool Vector::hasStroke() const
        {
            if (flags[Inherit::STROKE])
            {
                return parent ? parent->hasStroke() : false;
            }
            else
            {
                return !flags[Flags::STROKE_NONE];
            }
        }

        /**
         * Get the value of the stroke color property, including alpha
         * @return The color property
         */
        Color Vector::getStroke() const
        {
            unsigned int strokeColor;
            unsigned int strokeOpacity;
            if (flags[Inherit::STROKE])
            {
                strokeColor = parent ? parent->getStroke() : defaultStroke;
            }
            else
            {
                strokeColor = stroke;
            }
            if (flags[Inherit::STROKE_OPACITY])
            {
                strokeOpacity = parent ? parent->getStroke() : defaultStroke;
            }
            else
            {
                strokeOpacity = stroke;
            }
            return (strokeColor & 0x00FFFFFF) + (strokeOpacity & 0xFF000000);
        }

        /**
         * Get the value of the stroke width property
         * @return The stroke width
         */
        double Vector::getStrokeWidth() const
        {
            if (flags[Inherit::STROKE_WIDTH])
            {
                return parent ? parent->getStrokeWidth() : defaultStrokeWidth;
            }
            else
            {
                return strokeWidth;
            }
        }

        /**
         * Get the line join type for the stroke
         * @return The stroke line join type
         */
        LineJoin Vector::getStrokeLineJoin() const
        {
            if (flags[Inherit::STROKE_LINEJOIN])
            {
                return parent ? parent->getStrokeLineJoin() : defaultStrokeLineJoin;
            }
            else
            {
                return strokeLineJoin;
            }
        }

        /**
         * Get the limit for the miter joins
         * @return The limit for the miter joins
         */
        double Vector::getStrokeMiterLimit() const
        {
            if (flags[Inherit::STROKE_MITERLIMIT])
            {
                return parent ? parent->getStrokeMiterLimit() : defaultStrokeMiterLimit;
            }
            else
            {
                return strokeMiterLimit;
            }
        }

        /**
         * Get the line cap type for the stroke
         * @return The stroke line cap type
         */
        LineCap Vector::getStrokeLineCap() const
        {
            if (flags[Inherit::STROKE_LINECAP])
            {
                return parent ? parent->getStrokeLineCap() : defaultStrokeLineCap;
            }
            else
            {
                return strokeLineCap;
            }
        }

        /**
         * Get the stroke dash array
         * @return A pointer to the dash array
         */
        const DashArray* Vector::getStrokeDashArray() const
        {
            if (flags[Inherit::STROKE_DASHARRAY])
            {
                return parent ? parent->getStrokeDashArray() : nullptr;
            }
            else
            {
                return &strokeDashArray;
            }
        }

        /**
         * Get the stroke dash offset
         * @return The offset length to start into the dash array
         */
        double Vector::getStrokeDashOffset() const
        {
            if (flags[Inherit::STROKE_DASHOFFSET])
            {
                return parent ? parent->getStrokeDashOffset() : defaultStrokeDashOffset;
            }
            else
            {
                return strokeDashOffset;
            }
        }

        /**
         * Set the style property of the style object.
         *
         * @param[in] index The index of the style property to set.
         * @param[in] value The value to assign to the property.
         */
        void Vector::setProperty(unsigned int index, const CSS::Value* value)
        {
            CSS::ColorState state;
            switch (index)
            {
            case Inherit::FILL:
                fill = colorFromValue(value, &state);
                switch (state)
                {
                case CSS::INHERIT:
                    flags[Inherit::FILL] = true;
                    flags[Flags::FILL_NONE] = false;
                    break;
                case CSS::NONE:
                    flags[Flags::FILL_NONE] = true;
                    flags[Inherit::FILL] = false;
                    break;
                case CSS::COLOR:
                default:
                    flags[Flags::FILL_NONE] = false;
                    flags[Inherit::FILL] = false;
                    break;
                }
                break;
            case Inherit::STROKE:
                stroke = colorFromValue(value, &state, (stroke & 0xFF000000) >> 24);
                switch (state)
                {
                case CSS::INHERIT:
                    flags[Inherit::STROKE] = true;
                    flags[Flags::STROKE_NONE] = false;
                    break;
                case CSS::NONE:
                    flags[Inherit::STROKE] = false;
                    flags[Flags::STROKE_NONE] = true;
                    break;
                case CSS::COLOR:
                default:
                    flags[Inherit::STROKE] = false;
                    flags[Flags::STROKE_NONE] = false;
                    break;
                }
                break;
            case Inherit::STROKE_OPACITY:
                if (const CSS::Dimension* dimension = dynamic_cast<const CSS::Dimension*>(value))
                {
                    stroke = (stroke & 0x00FFFFFF) + (((int)(dimension->get() * 255)) << 24);
                    flags[Inherit::STROKE_OPACITY] = false;
                }
                else if (const CSS::Ident* ident = dynamic_cast<const CSS::Ident*>(value))
                {
                    if (ident->ident == "inherit")
                    {
                        flags[Inherit::STROKE_OPACITY] = true;
                    }
                }
                break;
            case Inherit::STROKE_WIDTH:
                if (const CSS::Dimension* dimension = dynamic_cast<const CSS::Dimension*>(value))
                {
                    // Internally stroke width is distance from centre to edge, so half what SVG uses as stroke width
                    strokeWidth = dimension->get() * 0.5;
                    flags[Inherit::STROKE_WIDTH] = false;
                }
                else if (const CSS::Ident* ident = dynamic_cast<const CSS::Ident*>(value))
                {
                    if (ident->ident == "inherit")
                    {
                        flags[Inherit::STROKE_WIDTH] = true;
                    }
                }
                break;
            case Inherit::STROKE_LINEJOIN:
                if (const CSS::Ident* ident = dynamic_cast<const CSS::Ident*>(value))
                {
                    if (ident->ident == "inherit")
                    {
                        flags[Inherit::STROKE_LINEJOIN] = true;
                    }
                    else if (ident->ident == "miter")
                    {
                        flags[Inherit::STROKE_LINEJOIN] = false;
                        strokeLineJoin = LJ_MITER;
                    }
                    else if (ident->ident == "round")
                    {
                        flags[Inherit::STROKE_LINEJOIN] = false;
                        strokeLineJoin = LJ_ROUND;
                    }
                    else if (ident->ident == "bevel")
                    {
                        flags[Inherit::STROKE_LINEJOIN] = false;
                        strokeLineJoin = LJ_BEVEL;
                    }
                }
                break;
            case Inherit::STROKE_MITERLIMIT:
                if (const CSS::Ident* ident = dynamic_cast<const CSS::Ident*>(value))
                {
                    if (ident->ident == "inherit")
                    {
                        flags[Inherit::STROKE_LINEJOIN] = true;
                    }
                }
                else if (const CSS::Dimension* dimension = dynamic_cast<const CSS::Dimension*>(value))
                {
                    flags[Inherit::STROKE_LINEJOIN] = false;
                    strokeMiterLimit = dimension->get();
                }
                break;
            case Inherit::STROKE_LINECAP:
                if (const CSS::Ident* ident = dynamic_cast<const CSS::Ident*>(value))
                {
                    if (ident->ident == "inherit")
                    {
                        flags[Inherit::STROKE_LINECAP] = true;
                    }
                    else if (ident->ident == "butt")
                    {
                        flags[Inherit::STROKE_LINECAP] = false;
                        strokeLineCap = LC_BUTT;
                    }
                    else if (ident->ident == "round")
                    {
                        flags[Inherit::STROKE_LINECAP] = false;
                        strokeLineCap = LC_ROUND;
                    }
                    else if (ident->ident == "square")
                    {
                        flags[Inherit::STROKE_LINECAP] = false;
                        strokeLineCap = LC_SQUARE;
                    }
                }
                break;
            case Inherit::STROKE_DASHARRAY:
                strokeDashArray.clear();
                if (const CSS::ValueList* list = dynamic_cast<const CSS::ValueList*>(value))
                {
                    for (const CSS::Value_uptr& item : list->vector)
                    {
                        if (const CSS::Dimension* dimension = dynamic_cast<const CSS::Dimension*>(item.get()))
                        {
                            strokeDashArray.push_back(dimension->get());
                        }
                    }
                }
                if (strokeDashArray.size() == 0)
                {
                    strokeDashArray.push_back(std::numeric_limits<double>::max());
                    strokeDashArray.push_back(0);
                }
                else if (strokeDashArray.size() % 2 == 1)
                {
                    unsigned int size(strokeDashArray.size());
                    for (unsigned int i=0; i < size; ++i)
                    {
                        strokeDashArray.push_back(strokeDashArray[i]);
                    }
                }
                break;
            case Inherit::STROKE_DASHOFFSET:
                if (const CSS::Dimension* dimension = dynamic_cast<const CSS::Dimension*>(value))
                {
                    flags[Inherit::STROKE_DASHOFFSET] = false;
                    strokeDashOffset = dimension->get();
                }
                else if (const CSS::Ident* ident = dynamic_cast<const CSS::Ident*>(value))
                {
                    if (ident->ident == "inherit")
                    {
                        flags[Inherit::STROKE_DASHOFFSET] = true;
                    }
                }
                break;
            default:
                Graphic::setProperty(index, value);
            }
        }
    }
}

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
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
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
         * Get the value of the stroke color property
         * @return The color property
         */
        Color Vector::getStroke() const
        {
            if (flags[Inherit::STROKE])
            {
                return parent ? parent->getStroke() : defaultStroke;
            }
            else
            {
                return stroke;
            }
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
                stroke = colorFromValue(value, &state);
                switch (state)
                {
                case CSS::INHERIT:
                    flags[Inherit::STROKE] = true;
                    flags[Flags::STROKE_NONE] = false;
                    break;
                case CSS::NONE:
                    flags[Flags::STROKE_NONE] = true;
                    flags[Inherit::STROKE] = false;
                    break;
                case CSS::COLOR:
                default:
                    flags[Flags::STROKE_NONE] = false;
                    flags[Inherit::STROKE] = false;
                    break;
                }
                break;
            case Inherit::STROKE_WIDTH:
                if (const CSS::Dimension* dimension = dynamic_cast<const CSS::Dimension*>(value))
                {
                    strokeWidth = dimension->get();
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
            default:
                Graphic::setProperty(index, value);
            }
        }
    }
}

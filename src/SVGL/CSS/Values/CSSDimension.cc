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

#include "CSSDimension.hh"

namespace SVGL
{
    namespace CSS
    {
        /**
                 * Dimension: An numeric value with optional unit specifier.
                 */
        /**
          * Default Constructor. Results in Unit::INVALID unit
          */
        Dimension::Dimension() :
            Calculable(0, Unit::INVALID)
        {
        }

        /**
         * Constructor with specified values
         * param[in] _value The initial numeric value.
         * param[in] _unit The code of the unit.
         */
        Dimension::Dimension(const double _value, const Unit _unit) :
            Calculable(_value, _unit)
        {

        }

        /**
         * Constructor with specified values
         * param[in] _value The initial numeric value.
         * param[in] _unit String reprensting the unit.
         */
        Dimension::Dimension(const double _value, const char* _unit) :
            Calculable(_value, Unit::USER)
        {
            setUnit(_unit);
        }

        /**
         * Constructor with specified values
         * param[in] _value The initial numeric value.
         * param[in] _unit String reprensting the unit.
         */
        Dimension::Dimension(const double _value, SubString _unit) :
            Calculable(_value, Unit::USER)
        {
            setUnit(_unit.start);
        }

        /**
         * Output to stream.
         */
        std::ostream& Dimension::stream(std::ostream& out) const
        {
            const char* unitStr;
            switch (unit)
            {
            default:
            case Unit::INVALID:
            case Unit::USER:
                unitStr = "";
                break;
            case Unit::PT:
                unitStr = "pt";
                break;
            case Unit::PC:
                unitStr = "pc";
                break;
            case Unit::MM:
                unitStr = "mm";
                break;
            case Unit::CM:
                unitStr = "cm";
                break;
            case Unit::IN:
                unitStr = "in";
                break;
            case Unit::EM:
                unitStr = "em";
                break;
            case Unit::EX:
                unitStr = "ex";
                break;
            case Unit::PERCENT:
                unitStr = "%";
                break;
            }
            return out << specified << unitStr;
        }

        /**
         * Set the unit based on a string
         */
        void Dimension::setUnit(const char* _unit)
        {
            switch (*_unit)
            {
            default:
                unit = Unit::INVALID;
                break;
            case '%':
                // For any x-coordinate value or width value expressed as a percentage of the viewport, the value to use is the specified percentage of the actual-width in user units for the nearest containing viewport, where actual-width is the width dimension of the viewport element within the user coordinate system for the viewport element.
                // For any y-coordinate value or height value expressed as a percentage of the viewport, the value to use is the specified percentage of the actual-height in user units for the nearest containing viewport, where actual-height is the height dimension of the viewport element within the user coordinate system for the viewport element.
                // For any other length value expressed as a percentage of the viewport, the percentage is calculated as the specified percentage of sqrt((actual-width)**2 + (actual-height)**2))/sqrt(2).
                unit = Unit::PERCENT;
                break;
            case 'p':
                switch (*(_unit + 1))
                {
                default:
                    unit = Unit::INVALID;
                    break;
                case 't':
                    unit = Unit::PT;
                    break;
                case 'c':
                    unit = Unit::PC;
                    break;
                }
                break;
            case 'm':
                if (*(_unit + 1) == 'm')
                {
                    unit = Unit::MM;
                }
                else
                {
                    unit = Unit::INVALID;
                }
                break;
            case 'c':
                if (*(_unit + 1) == 'm')
                {
                    unit = Unit::CM;
                }
                else
                {
                    unit = Unit::INVALID;
                }
                break;
            case 'i':
                if (*(_unit + 1) == 'n')
                {
                    unit = Unit::IN;
                }
                else
                {
                    unit = Unit::INVALID;
                }
                break;
            case 'e':
                switch (*(_unit + 1))
                {
                default:
                    unit = Unit::INVALID;
                    break;
                case 'm':
                    unit = Unit::EM;
                    break;
                case 'x':
                    unit = Unit::EX;
                    break;
                }
                break;
            }
        }
    }
}

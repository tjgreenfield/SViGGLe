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

#include "CSSDimension.hh"

namespace SVGL
{
    namespace CSS
    {
        /**
                 * Dimension: An numeric value with optional unit specifier.
                 */
        /**
          * Default Constructor. Results in UNIT_INVALID unit
          */
        Dimension::Dimension() :
            value(0),
            unit(UNIT_INVALID)
        {
        }

        /**
         * Constructor with specified values
         * param[in] _value The initial numeric value.
         * param[in] _unit The code of the unit.
         */
        Dimension::Dimension(const double _value, const Unit _unit) :
            value(_value),
            unit(_unit)
        {

        }

        /**
         * Constructor with specified values
         * param[in] _value The initial numeric value.
         * param[in] _unit String reprensting the unit.
         */
        Dimension::Dimension(const double _value, const char* _unit) :
            value(_value),
            unit(UNIT_USER)
        {
            setUnit(_unit);
        }

        /**
         * Constructor with specified values
         * param[in] _value The initial numeric value.
         * param[in] _unit String reprensting the unit.
         */
        Dimension::Dimension(const double _value, SubString _unit) :
            value(_value),
            unit(UNIT_USER)
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
            case UNIT_USER:
                unitStr = "";
                break;
            case UNIT_PT:
                unitStr = "pt";
                break;
            case UNIT_PC:
                unitStr = "pc";
                break;
            case UNIT_MM:
                unitStr = "mm";
                break;
            case UNIT_CM:
                unitStr = "cm";
                break;
            case UNIT_IN:
                unitStr = "in";
                break;
            case UNIT_EM:
                unitStr = "em";
                break;
            case UNIT_EX:
                unitStr = "ex";
                break;
            case UNIT_PERCENT:
                unitStr = "%";
                break;
            }
            return out << value << unitStr;
        }

        /**
         * Set the unit based on a string
         */
        void Dimension::setUnit(const char* _unit)
        {
            switch (*_unit)
            {
            case 0:
                break;
            case '%':
                // For any x-coordinate value or width value expressed as a percentage of the viewport, the value to use is the specified percentage of the actual-width in user units for the nearest containing viewport, where actual-width is the width dimension of the viewport element within the user coordinate system for the viewport element.
                // For any y-coordinate value or height value expressed as a percentage of the viewport, the value to use is the specified percentage of the actual-height in user units for the nearest containing viewport, where actual-height is the height dimension of the viewport element within the user coordinate system for the viewport element.
                // For any other length value expressed as a percentage of the viewport, the percentage is calculated as the specified percentage of sqrt((actual-width)**2 + (actual-height)**2))/sqrt(2).
                unit = UNIT_PERCENT;
                break;
            case 'p':
                switch (*(_unit + 1))
                {
                case 't':
                    unit = UNIT_PT;
                    break;
                case 'c':
                    unit = UNIT_PC;
                    break;
                }
                break;
            case 'm':
                if (*(_unit + 1) == 'm')
                {
                    unit = UNIT_MM;
                }
                break;
            case 'c':
                if (*(_unit + 1) == 'm')
                {
                    unit = UNIT_CM;
                }
                break;
            case 'i':
                if (*(_unit + 1) == 'n')
                {
                    unit = UNIT_IN;
                }
                break;
            case 'e':
                switch (*(_unit + 1))
                {
                case 'm':
                    unit = UNIT_EM;
                    break;
                case 'x':
                    unit = UNIT_EX;
                    break;
                }
                break;
            }
        }

        /**
         * Get the dimension in display units
         */
        double Dimension::get() const
        {
            switch (unit)
            {
            case UNIT_USER:
                return value;
            case UNIT_PT:
                return value * 1.25; // "1pt" equals "1.25px" (and therefore 1.25 user units)
            case UNIT_PC:
                return value * 156; // "1pc" equals "15px" (and therefore 15 user units)
            case UNIT_MM:
                return value * 3.543307; // "1mm" would be "3.543307px" (3.543307 user units)
            case UNIT_CM:
                return value * 35.43307; // "1cm" equals "35.43307px" (and therefore 35.43307 user units)
            case UNIT_IN:
                return value * 90; // "1in" equals "90px" (and therefore 90 user units)
            case UNIT_EM:
                return value; // TODO get font size of parent
            case UNIT_EX:
                return value; // TODO get font x-size of parent
            case UNIT_PERCENT:
                return value; // TODO get size of viewport
            default:
                return value;
            }
        }
    }
}

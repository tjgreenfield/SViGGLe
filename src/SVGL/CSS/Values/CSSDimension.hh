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

#pragma once

#include "CSSValue.hh"
#include <SVGL/CSS/CSSCalculable.hh>
#include <SVGL/Types/SubString.hh>
#include <string>

namespace SVGL
{
    namespace CSS
    {

        /**
         * An numeric value with optional unit specifier.
         */
        class Dimension : public Value, public Calculable
        {
        public:

            /**
             * Default Constructor. Results in UNIT_INVALID unit
             */
            Dimension();

            /**
             * Constructor with specified values
             * param[in] _value The initial numeric value.
             * param[in] _unit The code of the unit.
             */
            Dimension(const double _value, const Unit _unit = Unit::USER);

            /**
             * Constructor with specified values
             * param[in] _value The initial numeric value.
             * param[in] _unit String reprensting the unit.
             */
            Dimension(const double _value, const char* _unit);

            /**
             * Constructor with specified values
             * param[in] _value The initial numeric value.
             * param[in] _unit String reprensting the unit.
             */
            Dimension(const double _value, SubString _unit);

            /**
             * Used for valid test
             * @retval true If the unit are anything other than UNITS_INVALID
             * @retval false If the unit are UNITS_INVALID
             */
            inline operator bool() const
            {
                return unit != Unit::INVALID;
            }

            /**
             * Output to stream.
             */
            std::ostream& stream(std::ostream& out) const override;

            /**
             * Set the unit based on a string
             */
            void setUnit(const char* _unit);
        };
    }
}

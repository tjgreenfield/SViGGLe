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

#include "CSSSizeContext.hh"

#include <string>
#include <vector>

namespace SVGL
{
    namespace CSS
    {
        class Calculable
        {
        public:
            /**
             * List of units that can be used by this class.
             */
            enum class Unit { USER, PT, PC, MM, CM, IN, EM, EX, PERCENT, INVALID };
            enum class PercentMode { X, Y, DIAGONAL, FONT, RAW };

            double specified;
            Unit unit;

            Calculable();
            Calculable(double _specified, Unit = Unit::USER);

            virtual ~Calculable() = default;

            double calculate(const CSS::SizeContext& sizeContext = CSS::SizeContext(nullptr, 1, 1, 1), PercentMode mode = PercentMode::RAW) const;
            double calculateX(const CSS::SizeContext& sizeContext = CSS::SizeContext(nullptr, 1, 1, 1)) const;
            double calculateY(const CSS::SizeContext& sizeContext = CSS::SizeContext(nullptr, 1, 1, 1)) const;
            double calculateXY(const CSS::SizeContext& sizeContext = CSS::SizeContext(nullptr, 1, 1, 1)) const;
        };
    }
}

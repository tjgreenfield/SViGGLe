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

#include "CSSSizeContext.hh"
#include "CSSCalculable.hh"
#include <cmath>

namespace SVGL
{
    namespace CSS
    {
        Calculable::Calculable() :
            specified(0),
            unit(Unit::INVALID)
        {
        }

        Calculable::Calculable(double _specified, Unit _unit) :
            specified(_specified),
            unit(_unit)
        {

        }

        double Calculable::calculate(const CSS::SizeContext& sizeContext, PercentMode mode) const
        {
            switch (unit)
            {
            default:
            case Unit::INVALID:
            case Unit::USER:
                return specified;
            case Unit::PT:
                return specified * 1.25; // "1pt" equals "1.25px" (and therefore 1.25 user units)
            case Unit::PC:
                return specified * 156; // "1pc" equals "15px" (and therefore 15 user units)
            case Unit::MM:
                return specified * 3.543307; // "1mm" would be "3.543307px" (3.543307 user units)
            case Unit::CM:
                return specified * 35.43307; // "1cm" equals "35.43307px" (and therefore 35.43307 user units)
            case Unit::IN:
                return specified * 90; // "1in" equals "90px" (and therefore 90 user units)
            case Unit::EM:
                return specified * sizeContext.fontSize;
            case Unit::EX:
                return specified * sizeContext.fontXHeight;
            case Unit::PERCENT:
                switch (mode)
                {
                case PercentMode::X:
                    return specified * sizeContext.viewportWidth * 0.01;
                case PercentMode::Y:
                    return specified * sizeContext.viewportHeight * 0.01;
                case PercentMode::DIAGONAL:
                    return specified * sizeContext.viewportDiagonal * 0.01;
                case PercentMode::FONT:
                    return specified * sizeContext.fontSize * 0.01;
                case PercentMode::RAW:
                    return specified * 0.01;
                default:
                    return specified * 0.01;
                }
            }
        }

        double Calculable::calculateX(const CSS::SizeContext& sizeContext) const
        {
            return calculate(sizeContext, PercentMode::X);
        }

        double Calculable::calculateY(const CSS::SizeContext& sizeContext) const
        {
            return calculate(sizeContext, PercentMode::Y);
        }

        double Calculable::calculateXY(const CSS::SizeContext& sizeContext) const
        {
            return calculate(sizeContext, PercentMode::DIAGONAL);
        }
    }
}


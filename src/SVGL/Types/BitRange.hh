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

#define BITRANGE_IMPL(func, var, offset, bits) inline auto func() {return BitRange<offset,bits>(var);} inline auto func() const {return ConstBitRange<offset,bits>(var);}

namespace SVGL
{
    template <unsigned int offset, unsigned int bits>
    class BitRange
    {
    protected:
        static_assert(offset + bits <= sizeof(unsigned int) * 8, "maximum bits of BitRange exceeded");

        unsigned int& value;

    public:
        inline BitRange(unsigned int&  _value) :
            value(_value)
        {
        }

        constexpr unsigned int mask() const
        {
            return ~((-1) << bits);
        }

        constexpr unsigned int rmask() const
        {
            return ~((mask()) << offset);
        }

        inline operator unsigned int () const
        {
            return (value >> offset) & mask();
        }

        inline unsigned int operator=(unsigned int _value)
        {
            value = (value & rmask()) | ((_value & mask()) << offset);
            return _value;
        }

        inline unsigned int operator|=(unsigned int _value)
        {
            value = (value) | ((_value & mask()) << offset);
            return _value;
        }

        inline unsigned int operator&=(unsigned int _value)
        {
            value = (value) & (rmask() | ((_value & mask()) << offset));
            return _value;
        }
    };

    template <unsigned int offset, unsigned int bits>
    class ConstBitRange
    {
    protected:
        static_assert(offset + bits <= sizeof(unsigned int) * 8, "maximum bits of BitRange exceeded");

        const unsigned int& value;

    public:
        inline ConstBitRange(const unsigned int&  _value) :
            value(_value)
        {
        }

        constexpr unsigned int mask() const
        {
            return ~((-1) << bits);
        }

        constexpr unsigned int rmask() const
        {
            return ~((mask()) << offset);
        }

        inline operator unsigned int () const
        {
            return (value >> offset) & mask();
        }
    };
}

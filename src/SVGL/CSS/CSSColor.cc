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

#include "CSSColor.hh"
#include <SVGL/Types/Color.hh>

namespace SVGL
{
    namespace CSS
    {
        inline int hexChar(char c)
        {
            if (c >= '0' && c <= '9')
            {
                return c - '0';
            }
            else if (c >= 'a' && c <= 'f')
            {
                return (c - 'a') + 10;
            }
            else if (c >= 'A' && c <= 'F')
            {
                return (c - 'A') + 10;
            }
            return 0;
        }

        bool colorFromHash(Color* color, const Hash* hash, unsigned char alpha)
        {
            if (hash->hash.length() == 3)
            {
                (*color) = RGBA(
                    (hexChar(hash->hash[0]) << 4) + hexChar(hash->hash[0]),
                    (hexChar(hash->hash[1]) << 4) + hexChar(hash->hash[1]),
                    (hexChar(hash->hash[2]) << 4) + hexChar(hash->hash[2]),
                    alpha
                    );
                return true;
            }
            else if (hash->hash.length() == 6)
            {
                (*color) = RGBA(
                    (hexChar(hash->hash[0]) << 4) + hexChar(hash->hash[1]),
                    (hexChar(hash->hash[2]) << 4) + hexChar(hash->hash[3]),
                    (hexChar(hash->hash[4]) << 4) + hexChar(hash->hash[5]),
                    alpha
                    );
                return true;
            }
            return false;
        }

        bool colorFromRGBFunc(Color* color, const Function* function, unsigned char alpha)
        {
            if (function->function == "rgb")
            {
                if (function->parameters.size() == 3)
                {
                    if (typeid(*function->parameters[0]) == typeid(Dimension)
                        && typeid(*function->parameters[1]) == typeid(Dimension)
                        && typeid(*function->parameters[2]) == typeid(Dimension))
                    {
                        Dimension* r = dynamic_cast<Dimension*>(function->parameters[0].get());
                        Dimension* g = dynamic_cast<Dimension*>(function->parameters[1].get());
                        Dimension* b = dynamic_cast<Dimension*>(function->parameters[2].get());
                        if (r->unit == Dimension::Unit::USER
                            && g->unit == Dimension::Unit::USER
                            && b->unit == Dimension::Unit::USER)
                        {
                            (*color) = RGBA((r->specified), (unsigned int)(g->specified), (unsigned int)(b->specified), alpha);
                            return true;
                        }
                        if (r->unit == Dimension::Unit::PERCENT
                            && g->unit == Dimension::Unit::PERCENT
                            && b->unit == Dimension::Unit::PERCENT)
                        {
                            (*color) = RGBA((unsigned int)(r->specified * 255 / 100), (unsigned int)(g->specified * 255 / 100), (unsigned int)(b->specified * 255 / 100), alpha);
                            return true;
                        }

                    }
                }
            }
            return false;
        }

        bool colorFromValue(Color* color, const Value* value, unsigned char alpha)
        {
            if (const Keyword* keyword = dynamic_cast<const Keyword*>(value))
            {
                // if its a color keyword
                if ((keyword->keyword & 0xFF000000) == 0xFF000000)
                {
                    (*color) = (keyword->keyword & 0xFFFFFF) + (alpha << 24);
                    return true;
                }
                return false;
            }
            else if (const Hash* hash = dynamic_cast<const Hash*>(value))
            {
                return colorFromHash(color, hash, alpha);
            }
            else if (const Function* function = dynamic_cast<const Function*>(value))
            {
                return colorFromRGBFunc(color, function, alpha);
            }
            return false;
        }
    }
}

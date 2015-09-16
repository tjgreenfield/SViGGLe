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

#include "BaseParser.hh"
#include <fstream>
#include <cmath>
#include <ctype.h>
#include <cstdlib>


namespace SVGL
{
    namespace BaseParser
    {
        Parser::~Parser()
        {

        }

        /**
          * Error reporting function
          * @details
          * Override to catch error calls
          * @param[in] message The error message relevant to the current position.
          * @param[in] message (optional) Pointer to the starting point of the error.
          */
        void Parser::error(const char*, State)
        {

        }

        /**
         * Load data from file
         * @param[in] path The path to the file to read data from.
         */
        void Parser::loadFile(const char* path)
        {
			s = nullptr;
			
            // open the file
            std::ifstream file;
            file.open(path);
            if (!file.good())
            {
                error("Failed to open file", nullptr);
                return;
            }

            // get the file size
            file.seekg(0, std::ios::end);
            long long int length = (int)file.tellg();
            file.seekg(0, std::ios::beg);

            // create a buffer
            data = Data(new char[length + 1]);

            // read the whole file into the buffer
            file.read(data.get(), length);
            data[length] = 0;
            file.close();

            s = data.get();
        }

        bool Parser::readNum(double* number)
        {
            double value = 0;
            char push;
            bool valid = false;
            bool sign = false;
            sign = readChar('-');
            if ((push = readNumChar()))
            {
                valid = true;
                value = (value * 10) + (push - '0');
                while ((push = readNumChar()))
                {
                    value = (value * 10) + (push - '0');
                }
            }
            if (readChar('.'))
            {
                double fraction = 0.1;
                valid = true;
                while ((push = readNumChar()))
                {
                    value += (push - '0') * fraction;
                    fraction /= 10;
                }
            }
            if (valid)
            {
                *number = sign ? -value : value;
            }
            return valid;
        }

        bool Parser::readDouble(double* d)
        {
            State save(s);
            bool neg = false;
            bool good = false;
            double v = 0;

            // sign
            if (*s == '+')
            {
                ++s;
            }
            else if (*s == '-')
            {
                neg = true;
                ++s;
            }
            // integer part
            while (*s >= '0' && *s <= '9')
            {
                good = true;
                v *= 10;
                v += (*s - '0');
                ++s;
            }
            // fractional part
            if (*s == '.')
            {
                ++s;
                double f = 0.1;
                while (*s >= '0' && *s <= '9')
                {
                    good = true;
                    v += f * (*s - '0');
                    f *= 0.1;
                    ++s;
                }
            }
            // exponential part
            if (*s == 'e' || *s == 'E')
            {
                ++s;
                double e = 0;
                bool eneg = false;
                // exponential sign
                if (*s == '+')
                {
                    ++s;
                }
                else if (*s == '-')
                {
                    eneg = true;
                    ++s;
                }
                if (!(*s >= '0' && *s <= '9'))
                {
                    set(save);
                }
                else
                {
                    while (*s >= '0' && *s <= '9')
                    {
                        e *= 10;
                        e += (*s - '0');
                        ++s;
                    }
                }
                if (eneg) e = -e;
                v *= std::pow(10, e);
            }
            // apply negative
            if (neg) v = -v;

            // reset point if bad
            if (good)
            {
                //*d = v;
                *d = atof(save);
            }
            else
            {
                set(save);
            }
            return good;
        }

        SubString Parser::readString()
        {
            State save(s);
            char quote = *s;
            if (*s == '\'' || *s == '"')
            {
                ++s;
                SubString subString(s, 0);
                while (*s != quote && *s != 0)
                {
                    ++s;
                }
                if (*s)
                {
                    subString.count = s - subString.start;
                    ++s;
                    return subString;
                }
                error("String not closed", save);
                set(save);
            }
            return SubString();
        }

        bool Parser::readStatic(const char* text)
        {
            State save(s);

            while (*text && *s)
            {
                if (*s != *text)
                {
                    set(save);
                    return false;
                }
                ++s;
                ++text;
            }
            return true;
        }

        bool Parser::readStaticN(const char* text, unsigned int count)
        {
            State save(s);

            while (*text && *s && count)
            {
                if (*s != *text)
                {
                    set(save);
                    return false;
                }
                ++s;
                ++text;
                --count;
            }
            return true;
        }

        bool Parser::readStaticNoCase(const char* text)
        {
            State save(s);

            while (*text)
            {
                if (tolower(*s) != tolower(*text))
                {
                    set(save);
                    return false;
                }
                ++s;
                ++text;
            }
            return true;
        }
    }
}

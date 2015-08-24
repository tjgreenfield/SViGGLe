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

/**
 * A parser base class
 */

#include <SVGL/Types/SubString.hh>

#include <vector>
#include <memory>

namespace SVGL
{
    namespace BaseParser
    {
        /**
         * A general parser class designed to be extended for specific use.
         *
         * @details
         * Internally tracks the progress through a c-style string and has functions to read the contents
         */
        class Parser
        {
            //friend class Parser;

        public:
            typedef const char* State; //!< The State simply represents the current pointer.
            typedef std::unique_ptr<char[]> Data;

        protected:
            const char* s; //!< The current position.
            Data data;

        public:

            /**
             * Constructor
             *
             * @param[in] start The start of the string to parse.
             */
            inline Parser(const char* start = nullptr) :
                s(start),
				data(nullptr)
            {

            }

            /**
             * Constructor
             *
             * @param[in] _data The data to parse.
             */
            inline Parser(Data&& _data) :
                s(data.get()),
				data(std::move(_data))
            {

            }

            /**
             * Load data from file
             * @param[in] path The path to the file to read data from.
             */
            void loadFile(const char* path);

            /**
             * Error reporting function
             * @details
             * Override to catch error calls
             * @param[in] message The error message gernerated at the current position.
             * @param[in] message (optional) Pointer to the starting point of the error.
             */
            virtual void error(const char* message, State begin = nullptr);

            /**
             * Set the parser state to that of the specified state.
             * @param[in] p The state to apply.
             */
            inline void set(const State p)
            {
                s = p;
            }

            /**
             * Get the current pointer.
             * @return The current pointer.
             */
            inline const char* get() const
            {
                return s;
            }

            /**
             * Read the next character if it matches the specific character.
             * @retval true If the character is found.
             * @retval false If the character is not found.
             */
            inline char readChar(const char c)
            {
                if (*s == c)
                {
                    ++s;
                    return c;
                }
                return 0;
            }

            /**
             * Read an alphabetical character if present.
             * @retval true If the character is found.
             * @retval false If the character is not found.
             */
            inline char readAlphaChar()
            {
                if ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z'))
                {
                    return *(s++);
                }
                return 0;
            }

            /**
             * Read a numerical character if present.
             * @retval true If the character is found.
             * @retval false If the character is not found.
             */
            inline char readNumChar()
            {
                if ((*s >= '0' && *s <= '9'))
                {
                    return *(s++);
                }
                return 0;
            }

            /**
             * Reads a character escaped by a backslash "\", excluding new line or hexadecimal numbers
             * @retval true If a escaped character is found.
             * @retval false If a escaped character is not found.
             */
            inline char readEscape()
            {
                if (*s == '\\')
                {
                    switch (*(s + 1))
                    {
                    case '\n':
                    case '\r':
                    case '\f':
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                    case 'a':
                    case 'b':
                    case 'c':
                    case 'd':
                    case 'e':
                    case 'f':
                        return 0;
                    default:
                        ++s;
                        return *(s++);
                    }
                }
                return 0;
            }

            /**
             * Reads a newline escaped by a backslash "\"
             * @retval true If an escaped new line is found.
             * @retval false If an escaped new line is not found.
             */
            inline char readEscapeNewLine()
            {
                if (*s == '\\')
                {
                    switch (*(s + 1))
                    {
                    case '\r':
                        s += 2;
                        if (*s == '\n')
                        {
                            ++s;
                            return '\n';
                        }
                        return '\r';
                    case '\n':
                        s += 2;
                        return '\n';
                    case '\f':
                        s += 2;
                        return '\f';
                    default:
                        return 0;
                    }
                }
                return 0;
            }

            /**
             * Reads a newline
             * @retval true If a new line is found.
             * @retval false If a new line is not found.
             */
            inline char readNewLine()
            {
                if (*s == '\r')
                {
                    ++s;
                    if (*s == '\n')
                    {
                        ++s;
                    }
                    return '\n';
                }
                else if (*s == '\n' || *s == '\f')
                {
                    return '\n';
                }
                return 0;
            }

            /**
             * Reads all the whitespaces found.
             * @retval true If any whitespace characters are found.
             * @retval false If no whitespace cahracters are found.
             */
            inline char readWSP()
            {
                if (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n' || *s == '\f')
                {
                    s++;
                    while (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n' || *s == '\f')
                    {
                        s++;
                    }
                    return ' ';
                }
                return 0;
            }

            /**
             * Read a floating point numerical value if present.
             * @param[out] number Pointer to a double to set as the value. Left unchanged if no numerical value is found.
             * @retval true If a numerical value is found.
             * @retval false If a numerical value is not found.
             */
            bool readNum(double* number);

            /**
             * Read a floating point numerical value if present.
             * @param[out] number Pointer to a double to set as the value. Left unchanged if no numerical value is found.
             * @retval true If a numerical value is found.
             * @retval false If a numerical value is not found.
             */
            bool readDouble(double* number);

            /**
             * Read a string between a set of two single or a set of two double quotes. The string cannot contain unescaped new line characters.
             * @param[out] str Pointer to a string to set as the contents (excludes quotes) of the string. Left unchanged if no quotes are found.
             * @retval true If quotes are found.
             * @retval false If quotes are not found.
             */
            //bool readString(std::string* str);

            /**
             * Read a string between a set of two single or a set of two double quotes.
             * @return A substring contatining the string. Substring will be invalid if no string is present
             */
            SubString readString();

            /**
             * Reads over the specified string if present.
             * @param[in] text Pointer to the string to read.
             * @retval true If the string is found.
             * @retval false If the string is not found.
             */
            bool readStatic(const char* text);

            /**
             * Reads over the specified string if present.
             * @param[in] text Pointer to the string to read.
             * @param[in] count number of characters to read.
             * @retval true If the string is found.
             * @retval false If the string is not found.
             */
            bool readStaticN(const char* text, unsigned int count);

            /**
             * Reads over the specified string if present.
             * @param[in] text SubString of text to read.
             * @retval true If the string is found.
             * @retval false If the string is not found.
             */
            inline bool readStaticN(SubString text)
            {
                return readStaticN(text.start, text.count);
            }

            /**
             * Reads over the specified string, ignoreing case, if present.
             * @param[in] text Pointer to the string to read.
             * @retval true If the string is found.
             * @retval false If the string is not found.
             */
            bool readStaticNoCase(const char* text);
        };
    }
}

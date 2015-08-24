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

#include "PathParser.hh"

namespace SVGL
{
    namespace PathCommand
    {
        PathCommandSet Parser::readPathCommandSet()
        {
            commandSet.clear();
            
            char letter('M');
            
            readWSP();
            if (!readChar('M'))
            {
                // All paths must start with M
                return std::move(commandSet);
            }
            while (letter)
            {
                readWSP();
                switch (letter)
                {
                case 'M':
                    while (readM());
                    break;
                case 'm':
                    while (readm());
                    break;
                case 'L':
                    while (readL());
                    break;
                case 'l':
                    while (readl());
                    break;
                case 'V':
                    while (readV());
                    break;
                case 'v':
                    while (readv());
                    break;
                case 'H':
                    while (readH());
                    break;
                case 'h':
                    while (readh());
                    break;
                case 'C':
                    while (readC());
                    break;
                case 'c':
                    while (readc());
                    break;
                case 'S':
                    while (readS());
                    break;
                case 's':
                    while (reads());
                    break;
                case 'Q':
                    while (readQ());
                    break;
                case 'q':
                    while (readq());
                    break;
                case 'T':
                    while (readT());
                    break;
                case 't':
                    while (readt());
                    break;
                case 'A':
                    while (readA());
                    break;
                case 'a':
                    while (reada());
                    break;
                case 'Z':
                case 'z':
                    readZ();
                    break;
                default:
                    break;
                }

                readWSP();
                letter = readAlphaChar();
            }

            return std::move(commandSet);
        }
    }
}

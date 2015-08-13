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

#pragma once

#include "PathEllipticalTo.hh"
#include "PathCubicTo.hh"
#include "PathClosePath.hh"
#include "PathLineTo.hh"
#include "PathMoveTo.hh"
#include "PathCommand.hh"
#include <SVGL/BaseParser/BaseParser.hh>
#include <SVGL/Types/SubString.hh>
#include <SVGL/Types/Consts.hh>


namespace SVGL
{
    namespace PathCommand
    {
        class Parser : public BaseParser::Parser
        {
        protected:
            PathCommandSet commandSet;

            PathCommand* prev;
            Point p1, p2, pend, flags;
            double rx, ry, xAxisRotation, largeArcFlag, sweepFlag;


        public:
            inline Parser(const char* s = nullptr) :
                BaseParser::Parser(s),
                prev(nullptr)
            {}

            inline bool readCommaWSP()
            {
                readWSP();
                bool comma(readChar(',') ? true : false);
                readWSP();
                return comma;
            }

            inline bool readDoublePair(double* a, double* b)
            {
                readCommaWSP();
                if (!readDouble(a))
                    return false;
                if (!readCommaWSP())
                    return false;
                if (!readDouble(b))
                    return false;
                return true;
            }

            inline bool readPoint(Point* p)
            {
                readCommaWSP();
                if (!readDouble(&p->x))
                    return false;
                if (!readCommaWSP())
                    return false;
                if (!readDouble(&p->y))
                    return false;
                return true;
            }

            inline bool readM()
            {
                readWSP();
                if (!readDouble(&pend.x))
                    return false;
                readCommaWSP();
                if (!readDouble(&pend.y))
                    return false;
                commandSet.emplace_back(prev = new MoveTo(pend));
                return true;
            }

            inline bool readm()
            {
                readWSP();
                if (!readDouble(&pend.x))
                    return false;
                readCommaWSP();
                if (!readDouble(&pend.y))
                    return false;
                commandSet.emplace_back(prev = new MoveTo(pend + *prev));
                return true;
            }

            inline bool readL()
            {
                readWSP();
                if (!readDouble(&pend.x))
                    return false;
                readCommaWSP();
                if (!readDouble(&pend.y))
                    return false;
                commandSet.emplace_back(prev = new LineTo(pend));
                return true;
            }

            inline bool readl()
            {
                readWSP();
                if (!readDouble(&pend.x))
                    return false;
                readCommaWSP();
                if (!readDouble(&pend.y))
                    return false;
                commandSet.emplace_back(prev = new LineTo(pend + *prev));
                return true;
            }

            inline bool readV()
            {
                readWSP();
                if (!readDouble(&pend.y))
                    return false;
                pend.x = prev->x;
                commandSet.emplace_back(prev = new LineTo(pend));
                return true;
            }

            inline bool readv()
            {
                readWSP();
                if (!readDouble(&pend.y))
                    return false;
                pend.x = 0;
                commandSet.emplace_back(prev = new LineTo(pend + *prev));
                return true;
            }

            inline bool readH()
            {
                readWSP();
                if (!readDouble(&pend.x))
                    return false;
                pend.y = prev->y;
                commandSet.emplace_back(prev = new LineTo(pend));
                return true;
            }

            inline bool readh()
            {
                readWSP();
                if (!readDouble(&pend.x))
                    return false;
                pend.y = 0;
                commandSet.emplace_back(prev = new LineTo(pend + *prev));
                return true;
            }

            inline bool readC()
            {
                if (!readPoint(&p1))
                    return false;
                if (!readPoint(&p2))
                    return false;
                if (!readPoint(&pend))
                    return false;
                commandSet.emplace_back(prev = new CubicTo(p1, p2, pend));
                return true;
            }

            inline bool readc()
            {
                if (!readPoint(&p1))
                    return false;
                if (!readPoint(&p2))
                    return false;
                if (!readPoint(&pend))
                    return false;
                commandSet.emplace_back(prev = new CubicTo(p1 + *prev, p2 + *prev, pend + *prev));
                return true;
            }

            inline bool readS()
            {
                if (CubicTo * prevCubic = dynamic_cast<CubicTo*>(prev))
                {
                    p1 = (2 * (*prevCubic)) - (prevCubic->p2);
                }
                else
                {
                    p1 = Point(0, 0);
                }
                if (!readPoint(&p2))
                    return false;
                if (!readPoint(&pend))
                    return false;
                commandSet.emplace_back(prev = new CubicTo(p1, p2, pend));
                return true;
            }

            inline bool reads()
            {
                if (CubicTo * prevCubic = dynamic_cast<CubicTo*>(prev))
                {
                    p1 = (2 * (*prevCubic)) - (prevCubic->p2);
                }
                else
                {
                    p1 = Point(0, 0);
                }
                if (!readPoint(&p2))
                    return false;
                if (!readPoint(&pend))
                    return false;
                commandSet.emplace_back(prev = new CubicTo(p1 + *prev, p2 + *prev, pend + *prev));
                return true;
            }

            inline bool readQ()
            {
                if (!readPoint(&p1))
                    return false;
                if (!readPoint(&pend))
                    return false;
                commandSet.emplace_back(prev = new CubicTo(p1, p1, pend));
                return true;
            }

            inline bool readq()
            {
                if (!readPoint(&p1))
                    return false;
                if (!readPoint(&pend))
                    return false;
                commandSet.emplace_back(prev = new CubicTo(p1 + *prev, p1 + *prev, pend + *prev));
                return true;
            }

            inline bool readT()
            {
                if (CubicTo * prevCubic = dynamic_cast<CubicTo*>(prev))
                {
                    p1 = (2 * (*prevCubic)) - (prevCubic->p2);
                }
                else
                {
                    p1 = Point(0, 0);
                }
                if (!readPoint(&pend))
                    return false;
                commandSet.emplace_back(prev = new CubicTo(p1, p1, pend));
                return true;
            }

            inline bool readt()
            {
                if (CubicTo * prevCubic = dynamic_cast<CubicTo*>(prev))
                {
                    p1 = (2 * (*prevCubic)) - (prevCubic->p2);
                }
                else
                {
                    p1 = Point(0, 0);
                }
                if (!readPoint(&pend))
                    return false;
                commandSet.emplace_back(prev = new CubicTo(p1 + *prev, p1 + *prev, pend + *prev));
                return true;
            }

            inline bool readA()
            {
                if (!readDoublePair(&rx, &ry)) // rx, ry
                    return false;
                readWSP();
                if (!readDouble(&xAxisRotation)) // x-axis rotation
                    return false;
                if (!readDoublePair(&largeArcFlag, &sweepFlag)) // large arc flag, sweep flag
                    return false;
                if (!readPoint(&pend))
                    return false;

                commandSet.emplace_back(prev = new EllipticalTo(pend, rx, ry, xAxisRotation, largeArcFlag, sweepFlag, prev));
                return true;
            }

            inline bool reada()
            {
                if (!readDoublePair(&rx, &ry)) // rx, ry
                    return false;
                readWSP();
                if (!readDouble(&xAxisRotation)) // x-axis rotation
                    return false;
                if (!readDoublePair(&largeArcFlag, &sweepFlag)) // large arc flag, sweep flag
                    return false;
                if (!readPoint(&pend))
                    return false;
                pend += *prev;

                commandSet.emplace_back(prev = new EllipticalTo(pend, rx, ry, xAxisRotation, largeArcFlag, sweepFlag, prev));
                return true;
            }

            inline bool readZ()
            {
                commandSet.emplace_back(prev = new MoveTo(*prev));
                return false;
            }

            PathCommandSet readPathCommandSet();
        };
    }
 
}

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

#include <SVGL/BaseParser/BaseParser.hh>
#include <SVGL/Types/Point.hh>
#include <SVGL/Types/SubString.hh>
#include <SVGL/Types/Consts.hh>
#include <vector>




namespace SVGL
{
    namespace Elements
    {
        class PointsParser : public BaseParser::Parser
        {
        public:
            inline PointsParser(const char* s = nullptr) :
                BaseParser::Parser(s)
            {}

            inline bool readCommaWSP()
            {
                readWSP();
                bool comma(readChar(',') ? true : false);
                readWSP();
                return comma;
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

            inline bool readPoints(std::vector<Point>* points)
            {
                Point p;
                points->clear();
                while (readPoint(&p))
                {
                    points->emplace_back(p);
                }
                return (points->size() > 0);
            }

        };
    }

}

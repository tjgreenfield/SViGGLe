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

#include "PathCommandsContour.hh"
#include <SVGL/Types/Point.hh>
#include <vector>
#include <iostream>

namespace SVGL
{
    namespace PathCommands
    {
        class Polygon : public std::vector<Contour>
        {
        public:

            Polygon();

            ~Polygon();

            Point getLastPoint() const;

            Point getFirstPoint() const;

            Point getSecondPoint() const;

            Point getSecondLastPoint() const;

            Point getDir() const;

            void pushPoint(const Point* p);

            void pushPoint(const Point& p);

            void newSet();

            bool lastSetEmpty();
        };
    }
}

namespace std
{
    inline ostream& operator <<(ostream& out, const SVGL::PathCommands::Contour& contour)
    {
        out << "[";
        for (const SVGL::Point& point : contour)
        {
            out << point;
        }
        out << "]" << std::endl;
        return out;
    }

    inline ostream& operator <<(ostream& out, const SVGL::PathCommands::Polygon& polygon)
    {
        out << "{";
        for (const SVGL::PathCommands::Contour& contour : polygon)
        {
            out << contour;
        }
        out << "}" << std::endl;
        return out;
    }
}

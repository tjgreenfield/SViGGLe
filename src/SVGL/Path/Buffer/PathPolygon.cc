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

#include "PathPolygon.hh"

namespace SVGL
{
    namespace PathCommand
    {
        Polygon::Polygon()
        {

        }

        Polygon::~Polygon()
        {

        }

        Point Polygon::getLastPoint() const
        {
            if (empty())
            {
                return Point();
            }
            if (back().empty())
            {
                return Point();
            }
            return back().back();
        }

        Point Polygon::getSecondLastPoint() const
        {
            if (empty())
            {
                return Point();
            }
            const Contour& contour(back());
            if (contour.size() < 2)
            {
                return Point();
            }
            return contour[contour.size() - 2];
        }

        Point Polygon::getFirstPoint() const
        {
            if (empty())
            {
                return Point();
            }
            if (back().empty())
            {
                return Point();
            }
            return back().front();
        }

        Point Polygon::getSecondPoint() const
        {
            if (empty())
            {
                return Point();
            }
            const Contour& contour(back());
            if (contour.size() < 2)
            {
                return Point();
            }
            return contour[2];
        }

        Point Polygon::getDir() const
        {
            if (empty())
            {
                return Point();
            }
            const Contour& contour(back());
            if (contour.size() < 2)
            {
                return Point();
            }
            Point first(contour.front());
            for (unsigned int i = 1; i < contour.size(); ++i)
            {
                if (first != contour[i])
                {
                    return contour[i] - first;
                }
            }
            return Point();
        }

        void Polygon::pushPoint(const Point* p)
        {
            if (empty())
            {
                newSet();
            }
            back().push_back(*p);
        }

        void Polygon::pushPoint(const Point& p)
        {
            if (empty())
            {
                newSet();
            }
            back().push_back(p);
        }

        void Polygon::newSet()
        {
            if (!empty())
            {
                if (!back().size())
                {
                    return; // don't make a new empty set if we already have one
                }
            }
            emplace_back();
        }

        bool Polygon::lastSetEmpty()
        {
            if (empty())
            {
                return true;
            }
            return back().empty();
        }
    }
}

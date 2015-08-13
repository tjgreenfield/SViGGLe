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

#include "BufferPolygon.hh"

namespace SVGL
{
    namespace Buffer
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
            return back().front();
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
            push_back(Contour());
        }
    }
}

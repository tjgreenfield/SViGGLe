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

#include <ostream>
#include <cmath>

namespace SVGL
{
    class Point
    {
    public:
        double x, y;

        inline Point(double _x = 0, double _y = 0) :
            x(_x),
            y(_y)
        {

        }


        inline Point& operator+=(const Point& p)
        {
            x += p.x;
            y += p.y;
            return *this;
        }

        inline Point operator+(const Point& p) const
        {
            return Point(x + p.x, y + p.y);
        }

        inline Point& operator-=(const Point& p)
        {
            x -= p.x;
            y -= p.y;
            return *this;
        }

        inline Point operator-(const Point& p) const
        {
            return Point(x - p.x, y - p.y);
        }

        inline Point operator-() const
        {
            return Point(-x, -y);
        }

        inline double distance(const Point* p) const
        {
            double dx = p->x - x;
            double dy = p->y - y;
            return std::sqrt(dx * dx + dy * dy);
        }

        inline double length(const Point* p) const
        {
            double dx = p->x - x;
            double dy = p->y - y;
            return std::sqrt(dx * dx + dy * dy);
        }

        inline double distance() const
        {
            return std::sqrt((x * x) + (y * y));
        }

        inline double length() const
        {
            return std::sqrt((x * x) + (y * y));
        }

        inline Point normal(const Point* p) const
        {
            Point diff(p->x - x, p->y - y);
            double dist = diff.distance();
            return Point(-diff.y / dist, diff.x / dist);
        }

        inline Point normal() const
        {
            double dist = distance();
            return Point(-y / dist, x / dist);
        }

        inline Point normalise() const
        {
            double dist = distance();
            return Point(x / dist, y / dist);
        }

        inline double dot(const Point* p) const
        {
            return x * p->x + y * p->y;
        }

        inline double cross(const Point* p) const
        {
            return x * p->y - y * p->x;
        }

        inline double angle(const Point* p) const
        {
            return atan2(cross(p), dot(p));
        }

        inline Point& operator*=(double m)
        {
            x *= m;
            y *= m;
            return *this;
        }

        inline bool operator==(const Point& p) const
        {
            return (x == p.x) && (y == p.y);
        }

        inline bool operator!=(const Point& p) const
        {
            return (x != p.x) || (y != p.y);
        }

        friend std::ostream& operator<<(std::ostream& out, const Point& point);
        friend Point operator*(double m, const Point& p);
    };

    inline std::ostream& operator<<(std::ostream& out, const Point& point)
    {
        out << "(" << point.x << "," << point.y << ")";
        return out;
    }

    inline Point operator*(double m, const Point& p)
    {
        return Point(m * p.x, m * p.y);
    }
}

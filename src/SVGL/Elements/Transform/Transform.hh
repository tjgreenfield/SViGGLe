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

#include <SVGL/Types/Point.hh>
#include <ostream>

namespace SVGL
{
    class Transform
    {
    public:
        double a, b, c, d, e, f;

        Transform();
        Transform(double _a, double _b, double _c, double _d, double _e, double _f);
        Transform(const char* s);
        Transform(const Transform* l, const Transform* r);

        Transform& operator*=(const Transform& t);
        Point operator*(const Point& p);

        double transformTolerance(double t);

        void scaleR(double x, double y = NAN);
        void scaleL(double x, double y = NAN);
        void translateL(double x, double y);
        void translateR(double x, double y);
        void rotateL(double r);
        void rotateR(double r);

        friend std::ostream& operator<<(std::ostream& out, const Transform& transform);
    };

    std::ostream& operator<<(std::ostream& out, const Transform& transform);
}

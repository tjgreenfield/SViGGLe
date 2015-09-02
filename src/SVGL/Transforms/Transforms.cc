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

#include "Transforms.hh"
#include "TransformsParser.hh"
#include <SVGL/BaseParser/BaseParser.hh>
#include <SVGL/Types/Consts.hh>
#include <algorithm>

namespace SVGL
{
    namespace Transforms
    {

        Transform::Transform() :
            a(1), b(0),
            c(0), d(1),
            e(0), f(0)
        {

        }

        Transform::Transform(double _a, double _b, double _c, double _d, double _e, double _f) :
            a(_a), b(_b),
            c(_c), d(_d),
            e(_e), f(_f)
        {

        }

        Transform::Transform(const char* s) :
            a(1), b(0),
            c(0), d(1),
            e(0), f(0)
        {
            Parser(s).readTransform(this);
        }

        // l.a  l.c  l.e      r.a  r.c  r.e
        // l.b  l.d  l.f      r.b  r.d  r.f
        //  0    0    1        0    0    1

        Transform::Transform(const Transform* l, const Transform* r) :
            a(l->a * r->a + l->c * r->b),
            b(l->b * r->a + l->d * r->b),
            c(l->a * r->c + l->c * r->d),
            d(l->b * r->c + l->d * r->d),
            e(l->a * r->e + l->c * r->f + l->e),
            f(l->b * r->e + l->d * r->f + l->f)
        {

        }

        Transform& Transform::operator*=(const Transform& t)
        {
            return *this = Transform(this, &t);
        }

        Point Transform::operator*(const Point& p)
        {
            return Point(a * p.x + c * p.y + e, b * p.x + d * p.y + f);
        }

        double Transform::transformTolerance(double t)
        {
            return std::min(t / sqrt(a * a + c * c), t / (sqrt(b * b + d * d)));
        }

        void Transform::scaleL(double x, double y)
        {
            if (y == NAN)
            {
                y = x;
            }
            // x 0 0   a c e
            // 0 y 0   b d f
            // 0 0 1   0 0 1
            a *= x;
            c *= x;
            e *= x;

            b *= y;
            d *= y;
            f *= y;
        }

        void Transform::scaleR(double x, double y)
        {
            if (y == NAN)
            {
                y = x;
            }
            // a c e   x 0 0
            // b d f   0 y 0
            // 0 0 1   0 0 1
            a *= x;
            c *= y;
            b *= x;
            d *= y;
        }

        void Transform::translateL(double x, double y)
        {
            // 1 0 x   a c e
            // 0 1 y   b d f
            // 0 0 1   0 0 1
            e += x;
            f += y;
        }

        void Transform::translateR(double x, double y)
        {
            // a c e   1 0 x
            // b d f   0 1 y
            // 0 0 1   0 0 1
            e += a*x + c*y;
            f += b*x + d*y;
        }


        void Transform::rotateL(double r)
        {
            double cosr = cos(r);
            double sinr = sin(r);
            double _a(a), _b(b), _c(c), _d(d), _e(e), _f(f);
            // c -s  0    a c e
            // s  c  0    b d f
            // 0  0  1    0 0 1

            a = cosr*_a - sinr*_b;
            b = sinr*_a + cosr*_b;
            c = cosr*_c - sinr*_d;
            d = sinr*_c + cosr*_d;
            e = cosr*_e - sinr*_f;
            f = sinr*_e + cosr*_f;
        }

        void Transform::rotateR(double r)
        {
            double cosr = cos(r);
            double sinr = sin(r);
            double _a(a), _b(b), _c(c), _d(d);
            // a c e    c -s  0
            // b d f    s  c  0
            // 0 0 1    0  0  1

            a = cosr*_a + sinr*_c;
            c = -sinr*_a + cosr*_c;
            b = cosr*_b + sinr*_d;
            d = -sinr*_b + cosr*_d;
        }

        std::ostream& operator<<(std::ostream& os, const Transform &t)
        {
            os << "(" << t.a << "," << t.b << "," << t.c << "," << t.d << "," << t.e << "," << t.f << ")";
            return os;
        }

        Scale::Scale(double s) :
            Transform(s, 0,
                      0, s,
                      0, 0)
        {

        }

        Scale::Scale(double x, double y) :
            Transform(x, 0,
                      0, y,
                      0, 0)
        {

        }

        Translate::Translate(double x, double y) :
            Transform(1, 0,
                      0, 1,
                      x, y)
        {

        }

        Rotated::Rotated(double cosr, double sinr) :
            Transform(cosr, -sinr,
                      sinr,  cosr,
                         0,     0)
        {

        }

        Rotate::Rotate(double r) :
            Rotated(cos(r), sin(r))
        {

        }
    }
}

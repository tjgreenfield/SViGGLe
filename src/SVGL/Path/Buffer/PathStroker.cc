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

#include "PathStroker.hh"
#include <SVGL/Types/Consts.hh>

namespace SVGL
{
    namespace PathCommand
    {
        Stroker::Stroker(double _tolerance, Point* _at, const Styles::Vector& _style) :
                at(*_at),
                style(_style),
                tolerance(_tolerance),
                dashArray(&style.strokeDashArray),
                dashIndex(0),
                dashDistance(style.strokeDashOffset)
        {
            if (dashArray)
            {
                while (dashDistance > (*dashArray)[dashIndex])
                {
                    dashDistance -= (*dashArray)[dashIndex];
                    dashIndex = (dashIndex + 1) % dashArray->size();
                }
            }
        }

        void Stroker::bufferDash(const Point& to)
        {
            Point delta(to - at);
            double strokeWidth = style.strokeWidth;
            Point offset = strokeWidth * delta.normal();

            if (!dashArray)
            {
                // if there is no dash array, just add the end points
                strokeBuffer.pushPoint(to + offset);
                strokeBuffer.pushPoint(to - offset);
                at = to;
                return;
            }
            Point direction(delta.normalise());
            double remaining(delta.length());

            while (remaining > 0)
            {
                double dashRemaining = (*dashArray)[dashIndex] - dashDistance;

                if ((dashIndex & 0x01) == 0)
                {
                    // on dash
                    if (remaining > dashRemaining)
                    {
                        // stroke the remaining dash length, move to the next dash index
                        at += dashRemaining * direction;
                        strokeBuffer.pushPoint(at + offset);
                        strokeBuffer.pushPoint(at - offset);
                        bufferEndCap();
                        dashIndex = (dashIndex + 1) % dashArray->size();
                        dashDistance = 0;
                        remaining -= dashRemaining;
                    }
                    else
                    {
                        // stroke the remaining line length, break as we're done
                        at += remaining * direction;
                        strokeBuffer.pushPoint(at + offset);
                        strokeBuffer.pushPoint(at - offset);
                        dashDistance += remaining;
                        break; // remaining = 0
                    }
                }
                else
                {
                    // off dash
                    if (remaining > dashRemaining)
                    {
                        // start a new stroke at the end of the remaining dash length, move to the next dash index
                        strokeBuffer.newSet();
                        at += dashRemaining * direction;
                        bufferStartCap(direction);
                        strokeBuffer.pushPoint(at + offset);
                        strokeBuffer.pushPoint(at - offset);
                        dashIndex = (dashIndex + 1) % dashArray->size();
                        dashDistance = 0;
                        remaining -= dashRemaining;
                    }
                    else
                    {
                        // skip the remaining line length, break as we're done
                        at += remaining * direction;
                        dashDistance += remaining;
                        break; // remaining = 0
                    }
                }
            }
        }

        void Stroker::bufferStartCap(const Point& dir)
        {
            switch (style.strokeLineCap())
            {
            default:
            case Styles::Vector::LC_BUTT:
                break;
            case Styles::Vector::LC_ROUND:
                bufferStartCapRound(dir);
                break;
            case Styles::Vector::LC_SQUARE:
                bufferStartCapSquare(dir);
                break;
            }
        }

        void Stroker::bufferEndCap()
        {
            Point y(pointBuffer.getSecondLastPoint());
            Point dir(at - y);

            switch (style.strokeLineCap())
            {
            default:
            case Styles::Vector::LC_BUTT:
                break;
            case Styles::Vector::LC_ROUND:
                bufferEndCapRound(dir);
                break;
            case Styles::Vector::LC_SQUARE:
                bufferEndCapSquare(dir);
                break;
            }
        }

        void Stroker::bufferStartCapSquare(const Point& dir)
        {
            double strokeWidth = style.strokeWidth;
            Point step(-strokeWidth * dir.normalise());
            Point offset(strokeWidth * dir.normal());
            Point centre(at + step);

            Point m(centre + offset);
            Point n(centre - offset);

            strokeBuffer.pushPoint(m);
            strokeBuffer.pushPoint(n);
        }

        void Stroker::bufferEndCapSquare(const Point& dir)
        {
            double strokeWidth = style.strokeWidth;
            Point step(strokeWidth * dir.normalise());
            Point offset(strokeWidth * dir.normal());
            Point centre(at + step);

            Point m(centre + offset);
            Point n(centre - offset);

            strokeBuffer.pushPoint(m);
            strokeBuffer.pushPoint(n);
        }

        void Stroker::bufferStartCapRound(const Point& dir)
        {
            double strokeWidth = style.strokeWidth;

            // this might need adjusting
            int vertexCount = std::max(abs(int(4 * strokeWidth / tolerance)), 2);

            Point step(-strokeWidth * dir.normalise());
            Point offset(strokeWidth * dir.normal());

            for (int i = vertexCount; i >= 0; --i)
            {
                double t = ((double)i) / ((double)vertexCount) * PI / 2;
                double cost = cos(t);
                double sint = sin(t);

                Point m(at + (cost * offset) + (sint * step));
                Point n(at - (cost * offset) + (sint * step));

                strokeBuffer.pushPoint(m);
                strokeBuffer.pushPoint(n);
            }
        }

        void Stroker::bufferEndCapRound(const Point& dir)
        {
            double strokeWidth = style.strokeWidth;

            // this might need adjusting
            int vertexCount = std::max(abs(int(4 * strokeWidth / tolerance)), 2);

            Point step(strokeWidth * dir.normalise());
            Point offset(strokeWidth * dir.normal());

            for (int i = 0; i <= vertexCount; ++i)
            {
                double t = ((double)i) / ((double)vertexCount) * PI / 2;
                double cost = cos(t);
                double sint = sin(t);

                Point m(at + (cost * offset) + (sint * step));
                Point n(at - (cost * offset) + (sint * step));

                strokeBuffer.pushPoint(m);
                strokeBuffer.pushPoint(n);
            }
        }

        void Stroker::bufferJoin(const Point& to)
        {
            if ((dashIndex & 0x01) == 1)
            {
                // don't do a join if we're in between dashes
                return;
            }
            // no movement, no join
            if (at == to)
            {
                return;
            }

            Point delta(to - at);
            Point offset(style.strokeWidth * delta.normal());

            if (strokeBuffer.back().size() > 2)
            {
                switch (style.strokeLineJoin())
                {
                default:
                case Styles::Vector::LJ_MITER:
                    bufferMiterJoin(offset);
                    break;
                case Styles::Vector::LJ_ROUND:
                    bufferRoundJoin(offset);
                    break;
                case Styles::Vector::LJ_BEVEL:
                    bufferBevelJoin(offset);
                    break;
                }
            }
            else
            {
                bufferStartCap(delta);
                bufferBevelJoin(offset);
            }
        }

        void Stroker::bufferMiterJoin(const Point& offset)
        {
            /*
             *        m  a---------->
             *
             *        y  c  z
             *        |     |
             *        |  b--n------->
             *        |     |
             */

            double strokeMiterLimit(style.strokeMiterLimit);
            Point a(at + offset);
            Point b(at - offset);
            Point y(strokeBuffer.getSecondLastPoint());
            Point z(strokeBuffer.getLastPoint());
            Point zy(z - y);
            Point zyNorm(zy.normal());
            Point ba(b - a);

            double angle(ba.angle(zy));

            angle = angle / 2;
            // TODO: this isn't the correct comparision for strokeMiterLimit
            double miter(std::min(tan(angle), strokeMiterLimit) * style.strokeWidth);

            if (angle > 0)
            {
                Point m(y + miter * zyNorm);
                Point n(z);
                strokeBuffer.pushPoint(m);
                strokeBuffer.pushPoint(n);
            }
            else
            {
                Point m(y);
                Point n(z - miter * zyNorm);
                strokeBuffer.pushPoint(m);
                strokeBuffer.pushPoint(n);
            }

            strokeBuffer.pushPoint(a);
            strokeBuffer.pushPoint(b);
        }

        void Stroker::bufferRoundJoin(const Point& offset)
        {
            /*
             *           a---------->
             *
             *        y  c  z
             *        |     |
             *        |  b--+------->
             *        |     |
             */
            Point a(at + offset);
            Point b(at - offset);
            Point y(strokeBuffer.getSecondLastPoint());

            Point cy(y - at);
            Point u(1, 0);

            Point ca(a - at);

            double t0(u.angle(cy));
            double dt = cy.angle(ca);

            // this might need adjusting
            int vertexCount = std::max(abs(style.strokeWidth * dt / tolerance), 2);

            for (int i = 0; i <= vertexCount; ++i)
            {
                double t = t0 + (((double)i) / ((double)vertexCount)) * dt;
                double sint = sin(t);
                double cost = cos(t);
                Point m(at.x + cost * style.strokeWidth, at.y + sint * style.strokeWidth);
                Point n(at.x - cost * style.strokeWidth, at.y - sint * style.strokeWidth);
                strokeBuffer.pushPoint(m);
                strokeBuffer.pushPoint(n);
            }
            strokeBuffer.pushPoint(a);
            strokeBuffer.pushPoint(b);
        }

        void Stroker::bufferBevelJoin(const Point& offset)
        {

            /*
             *           a---------->
             *
             *        y  c  z
             *        |     |
             *        |  b--+------->
             *        |     |
             */
            Point a(at + offset);
            Point b(at - offset);

            strokeBuffer.pushPoint(a);
            strokeBuffer.pushPoint(b);
        }
    }
}

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

#include "TransformParser.hh"
#include <SVGL/Types/Consts.hh>

namespace SVGL
{
    bool TransformParser::readTransform(Transform* transform)
    {
        bool state(false);
        bool test(false);
        do
        {
            test = false;
            readWSP();
            if (readStatic("translate"))
            {
                double x(0), y(0);

                readWSP();
                if (!readChar('('))
                {
                    return test;
                }
                readWSP();
                if (!readDouble(&x))
                {
                    return test;
                }
                readWSP();
                readChar(',');
                readWSP();

                readDouble(&y);
                readWSP();
                if (!readChar(')'))
                {
                    return test;
                }
                (*transform) *= Transform(1, 0,
                                          0, 1,
                                          x, y);
                test = true;
            }
            else if (readStatic("scale"))
            {
                double x(0), y(0);

                readWSP();
                if (!readChar('('))
                {
                    return test;
                }
                readWSP();
                if (!readDouble(&x))
                {
                    return test;
                }
                readWSP();
                readChar(',');
                readWSP();
                if (!readDouble(&y))
                {
                    y = x;
                }
                readWSP();
                if (!readChar(')'))
                {
                    return test;
                }
                (*transform) *= Transform(x, 0,
                                          0, y,
                                          0, 0);
                test = true;

            }
            else if (readStatic("rotate"))
            {
                double r(0), x(0), y(0);
                bool centre(false);

                readWSP();
                if (!readChar('('))
                {
                    return test;
                }
                readWSP();
                if (!readDouble(&r))
                {
                    return test;
                }
                readWSP();
                readChar(',');
                readWSP();
                if (readDouble(&x))
                {
                    centre = true;
                    readChar(',');
                    readDouble(&y);
                    readWSP();
                }
                if (!readChar(')'))
                {
                    return test;
                }
                if (centre)
                {
                    (*transform) *= Transform(1, 0,
                                              0, 1,
                                              x, y);
                }
                r *= PI / 180;
                double cosr = cos(r);
                double sinr = sin(r);

                (*transform) *= Transform(cosr, sinr,
                                          -sinr, cosr,
                                          0, 0);

                if (centre)
                {
                    (*transform) *= Transform(1, 0,
                                              0, 1,
                                              -x, -y);
                }
                test = true;
            }
            else if (readStatic("skewX"))
            {
                double r(0);

                readWSP();
                if (!readChar('('))
                {
                    return true;
                }
                readWSP();
                if (!readDouble(&r))
                {
                    return true;
                }
                readWSP();
                if (!readChar(')'))
                {
                    return true;
                }
                r *= PI / 180;
                (*transform) *= Transform(1, 0,
                                          tan(r), 1,
                                          0, 0);
                test = true;
            }
            else if (readStatic("skewY"))
            {
                double r(0);

                readWSP();
                if (!readChar('('))
                {
                    return test;
                }
                readWSP();
                if (!readDouble(&r))
                {
                    return test;
                }
                readWSP();
                if (!readChar(')'))
                {
                    return test;
                }
                r *= PI / 180;
                (*transform) *= Transform(1, tan(r),
                                          0, 1,
                                          0, 0);
                test = true;
            }
            else if (readStatic("matrix"))
            {
                Transform matrix;

                readWSP();
                if (!readChar('('))
                {
                    return test;
                }

                readWSP();
                if (!readDouble(&matrix.a))
                {
                    return test;
                }
                readWSP();
                readChar(',');
                readWSP();
                if (!readDouble(&matrix.b))
                {
                    return test;
                }
                readWSP();
                readChar(',');
                readWSP();
                if (!readDouble(&matrix.c))
                {
                    return test;
                }
                readWSP();
                readChar(',');
                readWSP();
                if (!readDouble(&matrix.d))
                {
                    return test;
                }
                readWSP();
                readChar(',');
                readWSP();
                if (!readDouble(&matrix.e))
                {
                    return test;
                }
                readWSP();
                readChar(',');
                readWSP();
                if (!readDouble(&matrix.f))
                {
                    return test;
                }
                readWSP();
                readChar(',');
                readWSP();
                if (!readChar(')'))
                {
                    return test;
                }

                (*transform) *= matrix;
                test = true;
            }
            if (test)
            {
                state = true;
            }

        } while (test);
        return state;
    }

}

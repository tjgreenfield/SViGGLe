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

#include "RenderTessellation.hh"
#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>
#include <list>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define CALLBACK __stdcall
#else
#define CALLBACK
#endif // WIN32

namespace SVGL
{
    namespace Render
    {
        Buffer::Polygon* gDst;

        struct GluVertex
        {
            double x, y, z;

            GluVertex(double _x, double _y, double _z) : x(_x), y(_y), z(_z)
            {

            }
        };
        typedef std::vector<GluVertex> GluVertexVector;

        GluVertexVector gluRawData;

        typedef std::list<GluVertex> GluVertexList;
        GluVertexList gluCombineData;

        GLvoid CALLBACK callbackBegin(GLint type)
        {
            gDst->newSet();
            gDst->back().type = type;
        }

        GLvoid CALLBACK callbackEnd()
        {

        }

        GLvoid CALLBACK callbackVertex(GLvoid *vertex_data)
        {
            double* v = (double*)vertex_data;

            Point p(v[0], v[1]);
            gDst->pushPoint(&p);
        }

        GLvoid CALLBACK callbackCombine(GLdouble coords[3], void *vertex_data[4],
                                         GLfloat weight[4], void **outData)
        {
            GluVertex v(coords[0], coords[1], coords[2]);
            gluCombineData.push_back(v);

            *outData = &gluCombineData.back();
        }

        typedef void(CALLBACK *_GLUfuncptr)();

        void gluTessPointsSet(Buffer::Polygon* src, Buffer::Polygon* dst)
        {
            gDst = dst;
            GLUtesselator* tess = gluNewTess();
            gluTessCallback(tess, GLU_TESS_BEGIN, (_GLUfuncptr)callbackBegin);
            gluTessCallback(tess, GLU_TESS_VERTEX, (_GLUfuncptr)callbackVertex);
            gluTessCallback(tess, GLU_TESS_END, (_GLUfuncptr)callbackEnd);
            gluTessCallback(tess, GLU_TESS_COMBINE, (_GLUfuncptr)callbackCombine);

            gluRawData.clear();
            int rawSize = 0;
            for (unsigned int i = 0; i < src->size(); ++i)
            {
                rawSize += (*src)[i].size();
            }
            gluRawData.reserve(rawSize);

            gluTessBeginPolygon(tess, NULL);

            for (unsigned int i = 0; i < src->size(); ++i)
            {
                Buffer::Contour& contour = (*src)[i];
                gluTessBeginContour(tess);

                for (unsigned int j = 0; j < contour.size(); ++j)
                {
                    gluRawData.push_back(GluVertex(contour[j].x, contour[j].y, 0.0));
                    gluTessVertex(tess, &gluRawData.back().x, &gluRawData.back().x);
                }

                gluTessEndContour(tess);

            }
            gluTessEndPolygon(tess);
            gluDeleteTess(tess);
            gluRawData.clear();
            gluCombineData.clear();
        }

    }
}

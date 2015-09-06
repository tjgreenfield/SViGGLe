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


namespace SVGL
{
    namespace Render
    {
        namespace Shaders
        {
            const char* colorVert = R"(

                #version 400
                uniform dmat3x2 transform;
                uniform float depth;
                in vec2 vp;
                void main ()
                {
                    gl_Position = vec4 (vp.x * transform[0][0] + vp.y * transform[1][0] + transform[2][0],
                                        vp.x * transform[0][1] + vp.y * transform[1][1] + transform[2][1],
                                        depth,
                                        1.0);
                }

                )";

            const char* colorFrag = R"(

                #version 400
                uniform vec4 pen;
                out vec4 frag_colour;

                void main ()
                {
                    frag_colour = pen;
                }

                )";

        }
    }
}




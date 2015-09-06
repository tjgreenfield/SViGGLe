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
            const char* linearGradientVert = R"(

                #version 400
                uniform dmat3x2 transform;
                uniform dmat3x2 gradientShift;
                uniform float depth;
                in vec2 vp;
                out vec2 grad;
                void main ()
                {
                    grad = vec2(vp.x * gradientShift[0][0] + vp.y * gradientShift[1][0] + gradientShift[2][0],
                                vp.x * gradientShift[0][1] + vp.y * gradientShift[1][1] + gradientShift[2][1]);

                    gl_Position = vec4 (vp.x * transform[0][0] + vp.y * transform[1][0] + transform[2][0],
                                        vp.x * transform[0][1] + vp.y * transform[1][1] + transform[2][1],
                                        depth,
                                        1.0);
                }

                )";

            const char* linearGradientPadFrag = R"(

                #version 400
                uniform vec2 grad1;
                uniform vec2 grad2;
                uniform vec4 colors[256];
                uniform float offsets[256];

                in vec2 grad;
                out vec4 frag_colour;

                void main ()
                {
                    float gradResult = max(min(dot(grad - grad1, grad2), 1), 0);
                    for (int i = 1; i < 256; ++i)
                    {
                        if ((gradResult < offsets[i]) || (offsets[i] == 1))
                        {
                            int j = i - 1;
                            float diff = offsets[i] - offsets[j];
                            frag_colour = (((gradResult - offsets[j]) / diff) * colors[i]) + (((offsets[i] - gradResult) / diff) * colors[j]);
                            return;
                        }
                    }
                }

                )";

            const char* linearGradientReflectFrag = R"(

                #version 400
                uniform vec2 grad1;
                uniform vec2 grad2;
                uniform vec4 colors[256];
                uniform float offsets[256];

                in vec2 grad;
                out vec4 frag_colour;

                void main ()
                {
                    float gradResult = mod(dot(grad - grad1, grad2),2.0f);
                    if (gradResult > 1)
                    {
                        gradResult = 2 - gradResult;
                    }
                    for (int i = 1; i < 256; ++i)
                    {
                        if ((gradResult < offsets[i]) || (offsets[i] == 1))
                        {
                            int j = i - 1;
                            float diff = offsets[i] - offsets[j];
                            frag_colour = (((gradResult - offsets[j]) / diff) * colors[i]) + (((offsets[i] - gradResult) / diff) * colors[j]);
                            return;
                        }
                    }
                }

                )";

            const char* linearGradientRepeatFrag = R"(

                #version 400
                uniform vec2 grad1;
                uniform vec2 grad2;
                uniform vec4 colors[256];
                uniform float offsets[256];

                in vec2 grad;
                out vec4 frag_colour;

                void main ()
                {
                    float gradResult = mod(dot(grad - grad1, grad2), 1.0f);
                    for (int i = 1; i < 256; ++i)
                    {
                        if ((gradResult < offsets[i]) || (offsets[i] == 1))
                        {
                            int j = i - 1;
                            float diff = offsets[i] - offsets[j];
                            frag_colour = (((gradResult - offsets[j]) / diff) * colors[i]) + (((offsets[i] - gradResult) / diff) * colors[j]);
                            return;
                        }
                    }
                }

                )";

        }
    }
}




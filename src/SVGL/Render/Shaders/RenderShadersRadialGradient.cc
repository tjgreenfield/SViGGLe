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
            const char* radialGradientVert = R"(

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

            const char* radialGradientPadFrag = R"(

                #version 400
                uniform vec2 focusCentre;
                uniform float c;
                uniform vec2 focus;
                uniform vec4 colors[256];
                uniform float offsets[256];

                in vec2 grad;
                out vec4 frag_colour;

                void main ()
                {
                    vec2 delta = grad - focus;
                    float a = (delta.x*delta.x + delta.y*delta.y);
                    float b = 2*(delta.x*focusCentre.x + delta.y*focusCentre.y);
                    float calc = 2*a / (-b + sqrt(b*b - 4*a*c));
                    if (calc < 0)
                    {
                        calc = 2*a / (-b - sqrt(b*b - 4*a*c));
                    }

                    float gradResult = max(min(calc, 1), 0);
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

            const char* radialGradientReflectFrag = R"(

                #version 400
                uniform vec2 focusCentre;
                uniform float c;
                uniform vec2 focus;
                uniform vec4 colors[256];
                uniform float offsets[256];

                in vec2 grad;
                out vec4 frag_colour;

                void main ()
                {
                    vec2 delta = grad - focus;
                    float a = (delta.x*delta.x + delta.y*delta.y);
                    float b = 2*(delta.x*focusCentre.x + delta.y*focusCentre.y);
                    float calc = 2*a / (-b + sqrt(b*b - 4*a*c));
                    if (calc < 0)
                    {
                        calc = 2*a / (-b - sqrt(b*b - 4*a*c));
                    }

                    float gradResult = mod(calc, 2.0f);
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

            const char* radialGradientRepeatFrag = R"(

                #version 400
                uniform vec2 focusCentre;
                uniform float c;
                uniform vec2 focus;
                uniform vec4 colors[256];
                uniform float offsets[256];

                in vec2 grad;
                out vec4 frag_colour;

                void main ()
                {
                    vec2 delta = grad - focus;
                    float a = (delta.x*delta.x + delta.y*delta.y);
                    float b = 2*(delta.x*focusCentre.x + delta.y*focusCentre.y);
                    float calc = 2*a / (-b + sqrt(b*b - 4*a*c));
                    if (calc < 0)
                    {
                        calc = 2*a / (-b - sqrt(b*b - 4*a*c));
                    }

                    float gradResult = mod(calc, 1.0f);
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




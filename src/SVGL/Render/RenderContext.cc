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

#include "RenderContext.hh"

#include <SVGL/GL/gl.h>

#include <iostream>

namespace SVGL
{
    namespace Render
    {
        Context::Context() :
            depth(0),
            color(RGBA(255,255,255,255))
        {
            initShaders();
            update();
        }

        GLuint Context::compileShaders(const char* vertexShader, const char* fragmentShader)
        {
            unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vs, 1, &vertexShader, nullptr);
            glCompileShader(vs);
            GLchar buffer[4096];
            GLsizei len;
            GLint status;
            glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
            glGetShaderInfoLog(vs, 4095, &len, buffer);
            if (status != GL_TRUE )
            {
                std::cout << "Vertex Shader Log: (" << status << ") " << buffer << std::endl;
                std::cout << vertexShader << std::endl;
            }



            unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fs, 1, &fragmentShader, nullptr);
            glCompileShader(fs);
            glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
            glGetShaderInfoLog(fs, 4095, &len, buffer);
            if (status != GL_TRUE )
            {
                std::cout << "Fragment Shader Log: (" << status << ") " << buffer << std::endl;
                std::cout << fragmentShader << std::endl;
            }

            unsigned int shaderProgramme = glCreateProgram();
            glAttachShader(shaderProgramme, fs);
            glAttachShader(shaderProgramme, vs);
            glLinkProgram(shaderProgramme);

            return shaderProgramme;
        }

        void Context::initShaders()
        {
            colorShaderProgramme = compileShaders(
                "#version 400\n"
                "uniform dmat3x2 transform;\n"
                "uniform float depth;\n"
                "in vec2 vp;\n"
                "void main () {\n"
                "   gl_Position = vec4 (vp.x * transform[0][0] + vp.y * transform[1][0] + transform[2][0],\n"
                "                      vp.x * transform[0][1] + vp.y * transform[1][1] + transform[2][1],\n"
                "                      depth,\n"
                "                      1.0);\n"
                "}",

                "#version 400\n"
                "uniform sampler2D imageMap;"
                "uniform vec4 pen;"
                "uniform int mode;"
                "out vec4 frag_colour;"
                "void main () {"
                "    frag_colour = pen;"
                "}");

            textureShaderProgramme = compileShaders(
                "#version 400\n"
                "uniform dmat3x2 transform;\n"
                "uniform float depth;\n"
                "in vec2 vp;\n"
                "void main () {\n"
                "   gl_TexCoord[0] = vec4(vp.x, 1 - vp.y, 0, 0);\n"
                "   gl_Position = vec4 (vp.x * transform[0][0] + vp.y * transform[1][0] + transform[2][0],\n"
                "                      vp.x * transform[0][1] + vp.y * transform[1][1] + transform[2][1],\n"
                "                      depth,\n"
                "                      1.0);\n"
                "}",

                "#version 400\n"
                "uniform sampler2D imageMap;"
                "uniform vec4 pen;"
                "uniform int mode;"
                "out vec4 frag_colour;"
                "void main () {"
                "    frag_colour = texture2D(imageMap, gl_TexCoord[0].st);"
                "}");

        }

        void Context::begin()
        {
            transformStack.clear();
            colorStack.clear();
            depth = 0;
            worldTransform = Transforms::Scale(1, 1); // -1); // opengl y is negative
            color = RGBA(255, 255, 255, 255);

            glEnable(GL_BLEND);
            glEnable(GL_DEPTH_TEST);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glLineWidth(1.0);

            glHint(GL_POINT_SMOOTH, GL_NICEST);
            glHint(GL_LINE_SMOOTH, GL_NICEST);
            glHint(GL_POLYGON_SMOOTH, GL_NICEST);

            glEnable(GL_POINT_SMOOTH);
            glEnable(GL_LINE_SMOOTH);
            glEnable(GL_POLYGON_SMOOTH);

            glUseProgram(colorShaderProgramme);

            update();
        }

        void Context::update()
        {
            updateTransform();
            updateColor();
            updateDepth();
        }

        void Context::updateTransform()
        {
            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);

            GLint location = glGetUniformLocation(program, "transform");
            glUniformMatrix3x2dv(location, 1, GL_FALSE, &worldTransform.a);
        }

        void Context::pushTransform(Transforms::Transform* t)
        {
            transformStack.push_back(worldTransform);
            worldTransform *= *t;

            updateTransform();
        }

        void Context::popTransform()
        {
            worldTransform = transformStack.back();
            transformStack.pop_back();

            updateTransform();
        }

        void Context::updateColor()
        {
            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);

            int location = glGetUniformLocation(program, "pen");
            glUniform4f(location,
                        ((float)((color >> 16) & 0xff)) / 0xff,
                        ((float)((color >> 8) & 0xff)) / 0xff,
                        ((float)((color) & 0xff)) / 0xff,
                        ((float)((color >> 24) & 0xff)) / 0xff);
        }

        void Context::pushColor(unsigned int c)
        {
            colorStack.push_back(color);
            color = c;

            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);

            int location = glGetUniformLocation(program, "pen");
            glUniform4f(location,
                        ((float)((color >> 16) & 0xff)) / 0xff,
                        ((float)((color >> 8) & 0xff)) / 0xff,
                        ((float)((color) & 0xff)) / 0xff,
                        ((float)((color >> 24) & 0xff)) / 0xff);
        }

        void Context::popColor()
        {
            color = colorStack.back();
            colorStack.pop_back();

            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);

            int location = glGetUniformLocation(program, "pen");
            glUniform4f(location,
                        ((float)((color >> 16) & 0xff)) / 0xff,
                        ((float)((color >> 8) & 0xff)) / 0xff,
                        ((float)((color) & 0xff)) / 0xff,
                        ((float)((color >> 24) & 0xff)) / 0xff);
        }

        void Context::updateDepth()
        {
            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);

            int location = glGetUniformLocation(program, "depth");
            glUniform1f(location, -((float)depth) / (1 << 20));
        }

        void Context::incrementDepth()
        {
            ++depth;

            updateDepth();
        }

        void Context::setTextureShader()
        {
            glUseProgram(textureShaderProgramme);
            update();
        }

        void Context::setColorShader()
        {
            glUseProgram(colorShaderProgramme);
            update();
        }
    }
}

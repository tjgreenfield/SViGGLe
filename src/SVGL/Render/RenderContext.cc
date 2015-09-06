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

#include <SVGL/Render/Shaders/RenderShadersColor.hh>
#include <SVGL/Render/Shaders/RenderShadersTexture.hh>
#include <SVGL/Render/Shaders/RenderShadersLinearGradient.hh>
#include <SVGL/Render/Shaders/RenderShadersRadialGradient.hh>

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
                getchar();
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
                getchar();
            }

            unsigned int shaderProgramme = glCreateProgram();
            glAttachShader(shaderProgramme, fs);
            glAttachShader(shaderProgramme, vs);
            glLinkProgram(shaderProgramme);

            return shaderProgramme;
        }

        void Context::initShaders()
        {
            colorShaderProgramme = compileShaders(Shaders::colorVert, Shaders::colorFrag);

            textureShaderProgramme = compileShaders(Shaders::textureVert, Shaders::textureFrag);

            linearGradientPadShaderProgramme = compileShaders(Shaders::linearGradientVert, Shaders::linearGradientPadFrag);
            linearGradientReflectShaderProgramme = compileShaders(Shaders::linearGradientVert, Shaders::linearGradientReflectFrag);
            linearGradientRepeatShaderProgramme = compileShaders(Shaders::linearGradientVert, Shaders::linearGradientRepeatFrag);

            radialGradientPadShaderProgramme = compileShaders(Shaders::radialGradientVert, Shaders::radialGradientPadFrag);
            radialGradientReflectShaderProgramme = compileShaders(Shaders::radialGradientVert, Shaders::radialGradientReflectFrag);
            radialGradientRepeatShaderProgramme = compileShaders(Shaders::radialGradientVert, Shaders::radialGradientRepeatFrag);


        }

        void Context::begin()
        {
            transformStack.clear();
            colorStack.clear();
            depth = 0;
            worldTransform = Transforms::Scale(1, 1); // -1); // opengl y is negative
            color = RGBA(255, 255, 255, 255);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);

            glEnable(GL_STENCIL_TEST);
            glStencilFunc(GL_ALWAYS, 0, 0xFFFFFFFF);
            glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

            glLineWidth(1.0);

            glUseProgram(colorShaderProgramme);

            update();
        }

        void Context::update()
        {
            updateTransform();
            updateDepth();
        }

        void Context::updateTransform()
        {
            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);

            GLint location = glGetUniformLocation(program, "transform");
            glUniformMatrix3x2dv(location, 1, GL_FALSE, &worldTransform.a);
        }

        void Context::pushTransform(const Transforms::Transform* t)
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
            int location = glGetUniformLocation(textureShaderProgramme, "imageMap");
            glUniform1f(location, 0);
            update();
        }

        void Context::setColorShader()
        {
            glUseProgram(colorShaderProgramme);

            update();
        }

        void Context::resetGradientShift()
        {
            gradientShiftTransform.identity();
        }

        void Context::gradientShift(const Transforms::Transform& t)
        {
            gradientShiftTransform *= t;
        }
    }
}



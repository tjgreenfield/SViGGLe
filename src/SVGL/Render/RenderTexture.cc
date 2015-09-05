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

#include "RenderTexture.hh"

namespace SVGL
{
    namespace Render
    {
        Texture::Texture()
        {
            glGenTextures(1, &texture);

            if (!buffer)
            {
                initBuffer();
            }
        }

        Texture::Texture(Texture&& _texture)
        {
            texture = _texture.texture;
            _texture.texture = 0;

            if (!buffer)
            {
                initBuffer();
            }
        }

        Texture& Texture::operator=(Texture&& _texture)
        {
            texture = _texture.texture;
            _texture.texture = 0;
            return *this;
        }

        Texture::~Texture()
        {
            if (texture)
            {
                glDeleteTextures(1, &texture);
            }
        }

        void Texture::bind() const
        {
            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);

            GLuint imageMap = glGetUniformLocation(program, "imageMap");
            glUniform1i(imageMap, 0);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
        }

        void Texture::loadRGB(unsigned int width, unsigned int height, const unsigned char* data)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, width, height);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        }

        void Texture::loadRGBA(unsigned int width, unsigned int height, const unsigned char* data)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        }

        void Texture::render() const
        {
            bind();
            glBindVertexArray(vertexArray);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        }

        GLuint Texture::buffer = 0;
        GLuint Texture::vertexArray = 0;

        void Texture::initBuffer()
        {
            double points[] = {
                0, 0,
                1, 0,
                1, 1,
                0, 1,
                };

            glGenBuffers(1, &buffer);
            glGenVertexArrays(1, &vertexArray);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(double), &points[0], GL_STATIC_DRAW);

            glBindVertexArray(vertexArray);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 0, (GLubyte*)NULL);
        }
    }
}

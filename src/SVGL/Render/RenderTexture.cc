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
        }

        Texture::Texture(Texture&& _texture)
        {
            texture = _texture.texture;
            _texture.texture = 0;
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
            /*glActiveTexture(GL_TEXTURE0 + 0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glBindSampler(0, linearFiltering);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/

            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);

            GLuint imageMap = glGetUniformLocation(program, "imageMap");
            glUniform1i(imageMap, 0);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
        }

        void Texture::loadRGB(unsigned int width, unsigned int height, const unsigned char* data)
        {
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        void Texture::loadRGBA(unsigned int width, unsigned int height, const unsigned char* data)
        {
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        void Texture::render() const
        {
            bind();

            glBegin(GL_QUADS);
            glVertex2d(0, 0);
            glVertex2d(1, 0);
            glVertex2d(1, 1);
            glVertex2d(0, 1);
            glEnd();
        }
    }
}

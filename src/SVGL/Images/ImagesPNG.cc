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

#include "ImagesPNG.hh"
#include <png.h>

namespace SVGL
{
    namespace Images
    {
        bool PNG::loadTexture(Render::Texture* texture, const char* path)
        {
            FILE *fp = fopen(path, "rb");
            if (!fp)
            {
                return false; // can't open file
            }
            unsigned char header[8];

            fread(header, 1, 8, fp);

            bool is_png = !png_sig_cmp(header, 0, 8);
            if (!is_png)
            {
                return false; // not a PNG
            }

            png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, (png_voidp)nullptr,  nullptr, nullptr);
            if (!png_ptr)
            {
                return false; // libpng erro
            }

            png_infop info_ptr = png_create_info_struct(png_ptr);
            if (!info_ptr)
            {
                png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
                return false;// libpng error
            }

            png_infop end_info = png_create_info_struct(png_ptr);
            if (!end_info)
            {
                png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
                return false; // libpng error
            }

            if (setjmp(png_jmpbuf(png_ptr)))
            {
                png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
                fclose(fp);
                return false; // png file bad
            }
            png_set_sig_bytes(png_ptr, 8);

            png_init_io(png_ptr, fp);

            png_set_expand(png_ptr);
            png_read_info(png_ptr, info_ptr);

            unsigned int width = png_get_image_width(png_ptr, info_ptr);
            unsigned int height = png_get_image_height(png_ptr, info_ptr);
            unsigned char bit_depth = png_get_bit_depth(png_ptr, info_ptr);
            unsigned char channels = png_get_channels(png_ptr, info_ptr);

            unsigned int pixel_size = bit_depth * channels / 8;

            if (height > PNG_UINT_32_MAX/sizeof(png_byte))
            {
                png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
                fclose(fp);
                return false; // png file bad
            }

            if (width > PNG_UINT_32_MAX/pixel_size)
            {
                png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
                fclose(fp);
                return false; // png file bad
            }

            unsigned char** row_pointers = new unsigned char*[height];
            unsigned int row_size = width * pixel_size;
            unsigned char* data = new unsigned char[height * row_size];

            for (unsigned int i = 0; i < height; ++i)
            {
                row_pointers[i] = data + (i * row_size);
                for (unsigned int j = 0; j < width; j++)
                {
                    ((unsigned int*)row_pointers[i])[j] = 0;
                }
            }
            png_set_rows(png_ptr, info_ptr, row_pointers);

            png_read_image(png_ptr, row_pointers);

            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            fclose(fp);

            if (channels == 3)
            {
                texture->loadRGB(width, height, data);
            }
            else if (channels == 4)
            {
                texture->loadRGBA(width, height, data);
            }

            delete row_pointers;
            delete data;

            return true;
        }
    }
}


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

#include "screenshot.hh"
#include <png.h>
#include <memory>
#include <iostream>
#include <ctime>
#include <vector>

/*
 * Assumes 24 bits per pixel: r,g,b
 */
void screenshot(unsigned char* data, int width, int height)
{
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    char file_name[512];
    strftime(file_name, 254, "test_screenshots/%Y-%m-%d_%H-%M-%S.png", timeinfo);

    png_byte bit_depth = 8;
    png_byte color_type = PNG_COLOR_TYPE_RGB;
    std::vector<png_bytep> row_pointers(height);

    unsigned int row_size = width * 3;

    // 4 byte alignment
    row_size += 3 - ((row_size - 1) % 4);

    for (int row = 0; row < height; ++row)
    {
        row_pointers[row] = data + ((height - row - 1) * row_size);
    }

    FILE *fp = fopen(file_name, "wb");
    if (!fp)
    {
        std::cerr << "png write error!";
        return;
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, (png_voidp)nullptr, nullptr, nullptr);
    if (!png_ptr)
    {
        fclose(fp);
        std::cerr << "png write error!";
        return;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
        fclose(fp);
        std::cerr << "png write error!";
        return;
    }

    png_init_io(png_ptr, fp);

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        png_ptr = NULL;
        info_ptr = NULL;
        fclose(fp);
        std::cerr << "png write error!";
        return ;
    }

    png_init_io(png_ptr, fp);

    png_set_IHDR(png_ptr, info_ptr, width, height,
                     bit_depth, color_type, PNG_INTERLACE_NONE,
                     PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);

    png_write_image(png_ptr, &row_pointers[0]);

    png_write_end(png_ptr, NULL);

    fclose(fp);
}

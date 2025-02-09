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

#pragma once

#include "RenderPaint.hh"

namespace SVGL
{
    namespace Render
    {
        class Color : public Paint
        {
        protected:
            unsigned int rgba;

        public:
            Color(unsigned int _rgba);

            void setColor(unsigned int rgb);

            void setAlpha(unsigned int a);

            void enable(Context* context) const;

            void renderFill(Context* context, const PathBuffer& buffer) const override;

            void renderStroke(Context* context, const PathBuffer& buffer) const override;

        };
    }
}

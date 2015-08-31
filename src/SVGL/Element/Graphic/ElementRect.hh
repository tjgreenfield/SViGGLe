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

#include "ElementPath.hh"

namespace SVGL
{
    namespace Element
    {
        class Rect : public Path
        {
        protected:
            CSS::CalculableCache x;
            CSS::CalculableCache y;
            CSS::CalculableCache width;
            CSS::CalculableCache height;
            CSS::CalculableCache rx;
            CSS::CalculableCache ry;

        public:
            Rect();

            /**
             * Get the tag name of the element.
             */
            const char* getTagName() const override;

            /**
             * Calculate the relative units
             */
            void calculate(const CSS::SizeContext& sizeContext) override;

            void setAttribute(unsigned int index, SubString name, SubString value);

            void clearBuffers() override;

            void buffer(double tolerance) override;
        };
    }
}

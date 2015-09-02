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

#include <SVGL/PathCommands/PathCommands.hh>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

namespace SVGL
{
    namespace Font
    {
        class Glyph
        {
        protected:
            double advance;
            PathCommands::List commandList;

        public:
            Glyph(FT_Outline outline, double _advance);

            const PathCommands::List& getCommandList() const;
            double getAdvance() const;
        };
    }
}

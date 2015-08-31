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

#include "FontFace.hh"
#include "FontStyledFaceKey.hh"

#include <SVGL/Styles/StyleVector.hh>
#include <SVGL/Render/RenderContext.hh>
#include <SVGL/Render/RenderPathBuffer.hh>

#include <map>
#include <memory>

namespace SVGL
{
    namespace Font
    {
        class StyledFaceHandle;

        class StyledFace
        {
            friend class StyledFaceHandle;

        protected:
            Face* face;
            StyledFaceKey key;
            std::map<char, Render::PathBuffer> glyphBuffers;
            unsigned int refCount;

        public:

            /* Prevent copying */
            StyledFace(const StyledFace&) = delete;
            StyledFace& operator=(const StyledFace&) = delete;
            StyledFace(StyledFace&& _styledFace);


            StyledFace& operator=(StyledFace&&) = delete;
            ~StyledFace() = default;
            StyledFace() = delete;

            StyledFace(Face* _face);

            void buffer(const Styles::Vector& style, const char* text, double tolerance);

            void render(Render::Context* context, const Styles::Vector& style, const char* text) const;
        };

        class StyledFaceHandle
        {
        protected:
            StyledFace* styledFace;

        public:
            StyledFaceHandle();

            StyledFaceHandle(StyledFace* _styledFace);

            StyledFaceHandle(const StyledFaceHandle& _styledFaceHandle);

            StyledFaceHandle& operator=(const StyledFaceHandle& _styledFaceHandle);

            StyledFaceHandle(StyledFaceHandle&& _styledFaceHandle);

            StyledFaceHandle& operator=(StyledFaceHandle&& _styledFaceHandle);

            ~StyledFaceHandle();

            StyledFace* operator->() const;

            StyledFace& operator*() const;

            operator bool() const;
        };
    }
}

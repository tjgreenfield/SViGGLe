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

#include "FontsStyledFace.hh"
#include "FontsCollection.hh"

namespace SVGL
{
    namespace Font
    {
        StyledFace::StyledFace(Face* _face) :
            face(_face),
            glyphBuffers(),
            refCount(0)
        {

        }

        StyledFace::StyledFace(StyledFace&& _styledFace) :
            face(_styledFace.face),
            key(_styledFace.key),
            glyphBuffers(std::move(_styledFace.glyphBuffers)),
            refCount(_styledFace.refCount)
        {
            _styledFace.refCount = 0;
        }

        void StyledFace::buffer(const Styles::Text& style, const char* text, double tolerance)
        {
            while (*text)
            {
                if (glyphBuffers.find(*text) == glyphBuffers.end())
                {
                    Glyph* glyph = face->getGlyph(*text);

                    glyphBuffers.emplace(*text, std::move(Render::PathBuffer()));
                    glyphBuffers[*text].buffer(glyph->getCommandList(), style, tolerance * face->ftFace->units_per_EM);
                }
                ++text;
            }
        }

        void StyledFace::render(Render::Context* context, const Styles::Text& style, const char* text) const
        {
            double scale = 1.0 / (face->ftFace->units_per_EM);
            Transforms::Transform t;

            t.scaleR(scale, scale);
            context->pushTransform(&t);

            context->resetGradientShift();

            while (*text)
            {
                auto i = glyphBuffers.find(*text);
                if (i != glyphBuffers.cend())
                {
                    i->second.render(context, style);
                    double advance = face->getGlyph(*text)->getAdvance();
                    context->worldTransform.translateR(advance, 0);
                    context->updateTransform();
                    context->gradientShift(Transforms::Translate(advance, 0));
                }
                else
                {
                    // no glyph buffered!
                }
                ++text;
            }
            context->resetGradientShift();
            context->popTransform();
        }

        void StyledFace::calculateBoundingBox(BoundingBox* boundingBox, const char* text)
        {
            boundingBox->pMin.x = 0;
            boundingBox->pMin.y = 0;
            boundingBox->pMax.x = 0;
            boundingBox->pMax.y = 0;
            while (*text)
            {
                Glyph* glyph = face->getGlyph(*text);
                boundingBox->pMax.y = std::max(boundingBox->pMax.y, glyph->getHeight());
                boundingBox->pMax.x += glyph->getAdvance();
                ++text;
            }
        }

        /***** StyledFaceHandle *****/

        StyledFaceHandle::StyledFaceHandle() :
            styledFace(nullptr)
        {

        }

        StyledFaceHandle::StyledFaceHandle(StyledFace* _styledFace) :
            styledFace(_styledFace)
        {
            ++styledFace->refCount;
        }

        StyledFaceHandle::StyledFaceHandle(const StyledFaceHandle& _styledFaceHandle) :
            styledFace(_styledFaceHandle.styledFace)
        {
            ++styledFace->refCount;
        }

        StyledFaceHandle& StyledFaceHandle::operator=(const StyledFaceHandle& _styledFaceHandle)
        {
            styledFace = _styledFaceHandle.styledFace;
            ++styledFace->refCount;
            return *this;
        }

        StyledFaceHandle::StyledFaceHandle(StyledFaceHandle&& _styledFaceHandle) :
            styledFace(_styledFaceHandle.styledFace)
        {
            _styledFaceHandle.styledFace = nullptr;
        }

        StyledFaceHandle& StyledFaceHandle::operator=(StyledFaceHandle&& _styledFaceHandle)
        {
            styledFace = _styledFaceHandle.styledFace;
            _styledFaceHandle.styledFace = nullptr;
            return *this;
        }

        StyledFaceHandle::~StyledFaceHandle()
        {
            if (styledFace)
            {
                if (--styledFace->refCount)
                {
                    Collection::release(styledFace->key);
                }
            }
        }

        StyledFace* StyledFaceHandle::operator->() const
        {
            return styledFace;
        }

        StyledFace& StyledFaceHandle::operator*() const
        {
            return *styledFace;
        }

        StyledFaceHandle::operator bool() const
        {
            return styledFace;
        }
    }
}

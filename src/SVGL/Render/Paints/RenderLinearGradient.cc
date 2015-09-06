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

#include "RenderLinearGradient.hh"

#include <SVGL/Render/RenderContext.hh>
#include <SVGL/Render/RenderPathBuffer.hh>

#include <SVGL/Elements/Paints/ElementsStop.hh>

namespace SVGL
{
    namespace Render
    {
        LinearGradient::LinearGradient(unsigned int _bits, const Elements::StopList* _stopList, const Transforms::Transform* _gradientTransform, const Point& _p1, const Point& _p2) :
            bits(_bits),
            stopList(_stopList),
            gradientTransform(_gradientTransform),
            p1(_p1),
            p2(_p2)
        {

        }

        void LinearGradient::buffer(const Elements::Instance& instance)
        {
            for (const Elements::Stop_uptr& stop : *stopList)
            {
                offsets.push_back(stop->offset);

                colors.push_back(((float)((stop->color >> 16) & 0xff)) / 0xff);
                colors.push_back(((float)((stop->color >> 8) & 0xff)) / 0xff);
                colors.push_back(((float)((stop->color) & 0xff)) / 0xff);
                colors.push_back(stop->opacity);
            }
            if (!stopList->empty())
            {
                offsets.push_back(1.0);
                colors.push_back(((float)((stopList->back()->color >> 16) & 0xff)) / 0xff);
                colors.push_back(((float)((stopList->back()->color >> 8) & 0xff)) / 0xff);
                colors.push_back(((float)((stopList->back()->color) & 0xff)) / 0xff);
                colors.push_back(stopList->back()->opacity);
            }

            Transforms::Transform effectiveTransform;

            if (gradientUnits() == GradientUnits::OBJECT_BOUNDING_BOX)
            {
                BoundingBox boundingBox;
                instance.calculateBoundingBox(&boundingBox);
                effectiveTransform = Transforms::BoundingBox(boundingBox);
                effectiveTransform *= *gradientTransform;
            }
            else
            {
                effectiveTransform = *gradientTransform;
            }

            p1Transformed = effectiveTransform * p1;
            Point p2Transformed = effectiveTransform * p2;
            pDirTransformed = (p2Transformed - p1Transformed).dotInverse();

        }

        void LinearGradient::enable(Context* context) const
        {
            GLuint program;

            switch (spreadMethod())
            {
            default:
            case SpreadMethod::PAD:
                program = context->linearGradientPadShaderProgramme;
                break;
            case SpreadMethod::REFLECT:
                program = context->linearGradientReflectShaderProgramme;
                break;
            case SpreadMethod::REPEAT:
                program = context->linearGradientRepeatShaderProgramme;
                break;
            }

            glUseProgram(program);

            glUniform2f(glGetUniformLocation(program, "grad1"), p1Transformed.x, p1Transformed.y);
            glUniform2f(glGetUniformLocation(program, "grad2"), pDirTransformed.x, pDirTransformed.y);

            glUniform1fv(glGetUniformLocation(program, "offsets"), offsets.size(), &offsets[0]);
            glUniform4fv(glGetUniformLocation(program, "colors"), colors.size() >> 2, &colors[0]);

            glUniformMatrix3x2dv(glGetUniformLocation(program, "gradientShift"), 1, GL_FALSE, &context->gradientShiftTransform.a);

            context->update();
        }

        void LinearGradient::renderFill(Context* context, const PathBuffer& buffer) const
        {
            enable(context);
            buffer.renderFill();
        }

        void LinearGradient::renderStroke(Context* context, const PathBuffer& buffer) const
        {
            enable(context);
            buffer.renderStroke();
        }
    }
}

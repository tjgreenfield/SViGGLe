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

#include "RenderRadialGradient.hh"

#include <SVGL/Render/RenderContext.hh>
#include <SVGL/Render/RenderPathBuffer.hh>

#include <SVGL/Elements/Paints/ElementsStop.hh>

namespace SVGL
{
    namespace Render
    {
        RadialGradient::RadialGradient(unsigned int _bits, const Elements::StopList* _stopList, const Transforms::Transform* _gradientTransform, const Point& _centre, const Point& _focus, float _r) :
            bits(_bits),
            stopList(_stopList),
            gradientTransform(_gradientTransform),
            centre(_centre),
            focus(_focus),
            r(_r)
        {

        }

        void RadialGradient::buffer(const Elements::Instance& instance)
        {
            for (const Elements::Stop_uptr& stop : *stopList)
            {
                offsets.push_back(stop->offset);

                colors.push_back(((float)((stop->color >> 16) & 0xff)) / 0xff);
                colors.push_back(((float)((stop->color >> 8) & 0xff)) / 0xff);
                colors.push_back(((float)((stop->color) & 0xff)) / 0xff);
                colors.push_back(stop->opacity);
            }
            offsets.push_back(1.0);
            colors.push_back(((float)((stopList->back()->color >> 16) & 0xff)) / 0xff);
            colors.push_back(((float)((stopList->back()->color >> 8) & 0xff)) / 0xff);
            colors.push_back(((float)((stopList->back()->color) & 0xff)) / 0xff);
            colors.push_back(stopList->back()->opacity);

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

            Point focusCentre(focus - centre);
            double focusCentreLength = focusCentre.length();
            if (focusCentreLength > r)
            {
                // move focus to edge of circle (at centre, radius r)
                Point actualFocus = ((r / focusCentreLength) * focusCentre) + centre;
                pFocusTransformed = effectiveTransform * actualFocus;
            }
            else
            {
                pFocusTransformed = effectiveTransform * focus;
            }
            Point pCentreTransformed = effectiveTransform * centre;

            pFocusCentreTransformed = Point(pFocusTransformed - pCentreTransformed);
            double tranformedRadius = effectiveTransform * r;

            c = pFocusCentreTransformed.x*pFocusCentreTransformed.x + pFocusCentreTransformed.y*pFocusCentreTransformed.y - tranformedRadius*tranformedRadius;
        }

        void RadialGradient::enable(Context* context) const
        {
            GLuint program;

            switch (spreadMethod())
            {
            default:
            case SpreadMethod::PAD:
                program = context->radialGradientPadShaderProgramme;
                break;
            case SpreadMethod::REFLECT:
                program = context->radialGradientReflectShaderProgramme;
                break;
            case SpreadMethod::REPEAT:
                program = context->radialGradientRepeatShaderProgramme;
                break;
            }

            glUseProgram(program);
            glUniform2f(glGetUniformLocation(program, "focus"), pFocusTransformed.x, pFocusTransformed.y);
            glUniform2f(glGetUniformLocation(program, "focusCentre"), pFocusCentreTransformed.x, pFocusCentreTransformed.y);
            glUniform1f(glGetUniformLocation(program, "c"), c);


            glUniform1fv(glGetUniformLocation(program, "offsets"), offsets.size(), &offsets[0]);
            glUniform4fv(glGetUniformLocation(program, "colors"), colors.size() >> 2, &colors[0]);
            glUniformMatrix3x2dv(glGetUniformLocation(program, "gradientShift"), 1, GL_FALSE, &context->gradientShiftTransform.a);


            context->update();
        }

        void RadialGradient::renderFill(Context* context, const PathBuffer& buffer) const
        {
            enable(context);
            buffer.renderFill();
        }

        void RadialGradient::renderStroke(Context* context, const PathBuffer& buffer) const
        {
            enable(context);
            buffer.renderStroke();
        }
    }
}

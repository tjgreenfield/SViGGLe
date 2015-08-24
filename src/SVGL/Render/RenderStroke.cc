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

#include "RenderStroke.hh"

namespace SVGL
{
    namespace Render
    {
        /**
         * Create a set of triangle strips in the stroke style based on line segments provided in the input
         */
        void Stroke::rebuffer(const Buffer::Polygon* input, Buffer::Polygon* output, const Styles::Vector* style)
        {
            double strokeWidth = style->getStrokeWidth();

            for (const Buffer::Contour& in : *input)
            {
                Buffer::Contour out;
                
                unsigned int inCount = in.size();
                if (inCount == 1)
                {
                    out.resize(1);
                    out[0] = in[0];
                    continue;
                }
                unsigned int inCountM1 = inCount - 1;
                unsigned int outCount = inCount * 2;
                
                out.resize(outCount);

                Point offset;

                // First start corner point
                offset = strokeWidth * in[0].normal(&in[1]);
                out[0] = in[0] + offset;
                
                // Second start corner point
                out[1] = in[0] - offset;

                // loop over all intermediate points
                for (unsigned int inIndex = 1; inIndex < inCountM1; ++inIndex)
                {
                    offset = strokeWidth * in[inIndex - 1].normal(&in[inIndex + 1]);
                    
                    // add two "out" points for each "in" point
                    unsigned int outIndex = inIndex * 2; 
                    out[outIndex] = in[inIndex] + offset;
                    out[outIndex + 1] = in[inIndex] - offset;
                }

                // First end corner point
                offset = strokeWidth * in[inCountM1 - 1].normal(&in[inCountM1]);
                out[outCount - 2] = in[inCountM1] + offset;

                // Opposite end corner point
                out[outCount - 1] = in[inCountM1] - offset;

                output->push_back(std::move(out));
            }
        }
    }
}

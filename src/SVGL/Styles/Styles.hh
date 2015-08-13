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
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include "StyleTypes.hh"
#include "StyleSVG.hh"
#include "StyleGraphic.hh"
#include "StyleVector.hh"
#include "StyleShape.hh"
#include "StyleText.hh"

namespace SVGL
{
    namespace Styles
    {
        class Image
        {
            /*
            'color-profile'
            */
        };

        class Container // include graphics
        {
            /*
            'enable-background'

            */
        };

        class ViewPort
        {
            /*
            'overflow'
            */
        };


        class Flood
        {
            /*
            'flood-color'
            'flood-opacity'
            */
        };

        class Filter
        {
            /*
            ‘color-interpolation-filters’
            ‘color-rendering’
            */
        };

        class StopElement
        {
            /*
            'stop-color'
            'stop-opacity'

            */
        };

        class FloodElement
        {
            /*
            'flood-color'
            'flood-opacity'
            */
        };

        class Lighting
        {
            /*
            ‘lighting-color’
            */
        };
    }
}

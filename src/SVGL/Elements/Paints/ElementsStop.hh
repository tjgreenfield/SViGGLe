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

#include <SVGL/Elements/Abstracts/ElementsRoot.hh>

#include <memory>

namespace SVGL
{
    namespace Render
    {
        class LinearGradient;
        class RadialGradient;
    }

    namespace Elements
    {
        class Stop : public Root
        {
            friend class Render::LinearGradient;
            friend class Render::RadialGradient;
        protected:
            unsigned int color;
            float opacity;
            double offset;

        public:

            Stop(Root* _parent = nullptr);

            /***** XML::Node *****/

            void setAttribute(SubString name, SubString value) override;

            /***** Elements::Root *****/

            Instance_uptr calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) override;
        };

        typedef std::unique_ptr<Stop> Stop_uptr;

        typedef std::vector<Stop_uptr> StopList;
    }
}


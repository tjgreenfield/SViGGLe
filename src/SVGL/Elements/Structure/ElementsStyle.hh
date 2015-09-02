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

#include <SVGL/Elements/Abstract/ElementsRoot.hh>
#include <SVGL/CSS/CSSStyleSheet.hh>

#include <string>

namespace SVGL
{
    namespace Elements
    {
        class Style : public Root
        {
        public:
            CSS::StyleSheet styleSheet;
        protected:

            std::string type;
            std::string media;
            std::string title;

            class Attribute
            {
            public:
                enum Index
                {
                    // Primary attribute list
                    ID,
                    TYPE,
                    MEDIA,
                    TITLE
                };
            };

            typedef std::unordered_map<SubString, Attribute::Index> AttributeMap;
            static AttributeMap attributeMap;

        public:

            void appendText(SubString data) override;

            void setAttribute(SubString name, SubString value) override;
        };

        typedef std::unique_ptr<Style> Style_uptr;
    }
}


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

#include "ElementsText.hh"

namespace SVGL
{
    namespace Elements
    {
        Text::Text(Root* _parent) :
            Graphic(_parent),
            x(0),
            y(0)
        {
        }

        /***** From CSS::Element *****/
        const char* Text::getTagName() const
        {
            return "text";
        }

        /***** From XML::Node *****/
        void Text::setAttribute(unsigned int index, SubString name, SubString value)
        {
            switch (index)
            {
            case Attribute::D:
                break;
            default:
                Graphic::setAttribute(index, name, value);
                break;
            }
        }

        void Text::appendText(SubString data)
        {
            text.append(data.start, data.count);
        }

        /***** From Element::Root *****/
        Instance_uptr Text::calculateInstance(const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext)
        {
            return std::move(Instance_uptr(new Instance(this, inherit, sizeContext)));
        }

        /***** Elements::Text::Instance *****/

        Text::Instance::Instance(const Text* _text, const CSS::PropertySet& inherit, const CSS::SizeContext& sizeContext) :
            text(_text)
        {
            style.applyPropertySets(text->cascadedStyles, inherit, sizeContext);
            x = text->x.calculate(sizeContext, CSS::Calculable::PercentMode::X);
            y = text->y.calculate(sizeContext, CSS::Calculable::PercentMode::Y);
        }

        void Text::Instance::buffer(double tolerance)
        {
            tolerance = text->transform.transformTolerance(tolerance);
            Font::StyledFaceKey testKey(style);
            if (styledFaceKey != testKey)
            {
                styledFaceKey = testKey;
                styledFace = Font::Collection::request(styledFaceKey);
            }
            // TODO adjust tolerance by font size
            if (styledFace)
            {
                styledFace->buffer(style, text->text.c_str(), tolerance);
            }
        }

        void Text::Instance::render(Render::Context* context)
        {
            Transforms::Transform t;
            t.translateR(x, y);
            t.scaleR(styledFaceKey.effectiveFontSize, styledFaceKey.effectiveFontSize);

            context->pushTransform(&t);
            context->pushColor(style.stroke);
            if (styledFace)
            {
                styledFace->render(context, style, text->text.c_str());
            }
            context->popColor();
            context->popTransform();
        }
    }
}

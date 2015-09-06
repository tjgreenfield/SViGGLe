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

#include "ElementsRadialGradient.hh"
#include "ElementsLinearGradient.hh"

#include <SVGL/Elements/ElementsAttribute.hh>
#include <SVGL/Render/Paints/RenderRadialGradient.hh>
#include <SVGL/Transforms/TransformsParser.hh>
#include <SVGL/CSS/Values/CSSKeyword.hh>
#include <SVGL/SVGLDocument.hh>

namespace SVGL
{
    namespace Elements
    {
        RadialGradient::RadialGradient(Root* _parent) :
            Paint(_parent)
        {

        }

        void RadialGradient::setAttribute(SubString name, SubString value)
        {
            switch ((int)Attribute::getIndex(name))
            {
                case Attribute::CX:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        cx = *dimension;
                    }
                }
                break;
            case Attribute::CY:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        cy = *dimension;
                    }
                }
                break;
            case Attribute::R:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        r = *dimension;
                    }
                }
                break;
            case Attribute::FX:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        fx = *dimension;
                    }
                }
                break;
            case Attribute::FY:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    if(CSS::Dimension* dimension = dynamic_cast<CSS::Dimension*>(cssvalue.get()))
                    {
                        fy = *dimension;
                    }
                }
                break;
            case Attribute::GRADIENT_TRANSFORM:
                {
                    Transforms::Parser parser(value.start);
                    parser.readTransform(&gradientTransform);
                    hasGradientTransform() = 1;
                }
                break;
            case Attribute::GRADIENT_UNITS:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    switch (CSS::Keyword::keywordFromValue(cssvalue.get()))
                    {
                    default:
                    case CSS::Keyword::ERROR:
                    case CSS::Keyword::USER_SPACE_ON_USE:
                        gradientUnits() = GradientUnits::USER_SPACE_ON_USE;
                        break;
                    case CSS::Keyword::OBJECT_BOUNDING_BOX:
                        gradientUnits() = GradientUnits::OBJECT_BOUNDING_BOX;
                        break;
                    }
                }
                break;
            case Attribute::SPREAD_METHOD:
                {
                    CSS::Value_uptr cssvalue = CSS::Parser(value.start).readPropertyValue();
                    switch (CSS::Keyword::keywordFromValue(cssvalue.get()))
                    {
                    default:
                    case CSS::Keyword::ERROR:
                    case CSS::Keyword::PAD:
                        spreadMethod() = SpreadMethod::PAD;
                        break;
                    case CSS::Keyword::REFLECT:
                        spreadMethod() = SpreadMethod::REFLECT;
                        break;
                    case CSS::Keyword::REPEAT:
                        spreadMethod() = SpreadMethod::REPEAT;
                        break;
                    }
                }
                break;
            case Attribute::XLINK_HREF:
                {
                    href.assign(value.start, value.count);
                }
                break;
            default:
                Root::setAttribute(name, value);
                break;
            }
        }

        void RadialGradient::appendChild(XML::Node_uptr&& child)
        {
            if (auto stop = dynamic_cast<Stop*>(child.get()))
            {
                child.release();
                stopList.emplace_back(stop);
            }
        }

        Instance_uptr RadialGradient::calculateInstance(const CSS::PropertySet& , const CSS::SizeContext& )
        {
            return std::move(Instance_uptr(nullptr));
        }

        void RadialGradient::calculateGradient(GradientDerived* derived, const CSS::SizeContext& sizeContext) const
        {
            if ((derived->needSpreadMethod()) && (spreadMethod() != SpreadMethod::INVALID))
            {
                derived->spreadMethod() = spreadMethod();
                derived->needSpreadMethod() = 0;
            }
            if ((derived->needGradientUnits()) && (gradientUnits() != GradientUnits::INVALID))
            {
                derived->gradientUnits() = gradientUnits();
                derived->needGradientUnits() = 0;
            }
            if ((derived->needStopList()) && (!stopList.empty()))
            {
                derived->stopList = &stopList;
                derived->needStopList() = 0;
            }
            if ((derived->needGradientTransform()) && (hasGradientTransform()))
            {
                derived->gradientTransform = &gradientTransform;
                derived->needGradientTransform() = 0;
            }
            if ((derived->needCX()) && (cx.unit != CSS::Calculable::Unit::INVALID))
            {
                derived->centre.x = cx.calculate(sizeContext);
                derived->needCX() = 0;
            }
            if ((derived->needCY()) && (cy.unit != CSS::Calculable::Unit::INVALID))
            {
                derived->centre.y = cy.calculate(sizeContext);
                derived->needCY() = 0;
            }
            if ((derived->needR()) && (r.unit != CSS::Calculable::Unit::INVALID))
            {
                derived->radius = r.calculate(sizeContext);
                derived->needR() = 0;
            }
            if ((derived->needFX()) && (fx.unit != CSS::Calculable::Unit::INVALID))
            {
                derived->focus.x = fx.calculate(sizeContext);
                derived->needFX() = 0;
            }
            if ((derived->needFY()) && (fy.unit != CSS::Calculable::Unit::INVALID))
            {
                derived->focus.y = fy.calculate(sizeContext);
                derived->needFY() = 0;
            }

            if (derived->needAll() != 0)
            {
                if (!href.empty())
                {
                    if (href[0] == '#')
                    {
                        if (const Document* document = getDocument())
                        {
                            Root* root =  document->getElementByID(&href[1]);
                            if (const LinearGradient* linearGradient = dynamic_cast<const LinearGradient*>(root))
                            {
                                linearGradient->calculateGradient(derived, sizeContext);
                            }
                            else if (const RadialGradient* radialGradient = dynamic_cast<const RadialGradient*>(root))
                            {
                                radialGradient->calculateGradient(derived, sizeContext);
                            }
                        }
                    }
                }
            }
        }

        Render::Paint_uptr RadialGradient::calculatePaint(const CSS::PropertySet& , const CSS::SizeContext& sizeContext) const
        {
            GradientDerived derived;
            derived.needAll() = 0xFFF;
            derived.bits = 0;
            derived.gradientUnits() = GradientUnits::OBJECT_BOUNDING_BOX;
            derived.spreadMethod() = SpreadMethod::REFLECT;
            derived.gradientTransform = &gradientTransform;
            derived.stopList = &stopList;
            derived.centre = Point(0, 0);
            derived.radius = 1.0;
            derived.focus = Point(0, 0);
            calculateGradient(&derived, sizeContext);

            return Render::Paint_uptr(new Render::RadialGradient(derived.bits, derived.stopList, derived.gradientTransform, derived.focus, derived.centre, derived.radius));
        }
    }
}

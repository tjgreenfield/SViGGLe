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

#include "CSSStyleSheet.hh"
#include "CSSStructures.hh"
#include "CSSStyle.hh"
#include "CSSParser.hh"
#include <algorithm>
#include <string>

namespace SVGL
{
    namespace CSS
    {
        /**
         * StyleSheet: A class that provides the abililty to read CSS styles and apply them to elements.
         */

        /**
         * Constructor
         */
        StyleSheet::StyleSheet(const char* code)
        {
            CSS::Parser parser(code);
            while (Ruleset_uptr ruleset = parser.readRuleset())
            {
                rulesets.push_back(std::move(ruleset));
                parser.readWSP();
            }
            buildIndex();
        }

        void StyleSheet::applyProperty(PropertySet* propertySet, const PropertySet& inherit, const Property::Index property, const Value* value)
        {
            if (const Keyword* keyword = dynamic_cast<const Keyword*>(value))
            {
                if (keyword->keyword == Keyword::INHERIT)
                {
                    (*propertySet)[property] = inherit[property];
                    return;
                }
            }
            // TODO, decompose 'font' property
            (*propertySet)[property] = value;
        }

        /**
         * Apply the stylesheet to specified element (where applicable)
         * param[in] element The element to apply the stylesheet to
         */
        void StyleSheet::apply(CSSElement* element, PropertySet* propertySet, const PropertySet& inherit, CSS::SizeContext& sizeContext) const
        {
            propertySet->inherit(inherit);
            for (SelectorBlock selectorBlock : selectorIndex)
            {
                if (selectorBlock.selector->match(element))
                {
                    for (auto const& i : selectorBlock.block->map)
                    {
                        applyProperty(propertySet, inherit, i.first, i.second->value.get());
                    }
                }
            }
            for (SelectorBlock selectorBlock : importantSelectorIndex)
            {
                if (selectorBlock.selector->match(element))
                {
                    for (auto const& i : selectorBlock.block->importantMap)
                    {
                        applyProperty(propertySet, inherit, i.first, i.second->value.get());
                    }
                }
            }
            // Apply element's style over the top of the style sheet
            // TODO move into element code?
            const DeclarationBlock* specifiedStyle = element->getSpecifiedStyle();
            for (auto const& i : specifiedStyle->map)
            {
                applyProperty(propertySet, inherit, i.first, i.second->value.get());
            }
            element->calculate(sizeContext);
            element->getStyle()->applyPropertySet(*propertySet, inherit, sizeContext);
        }

        /**
         * Add new CSS code to the style sheet
         * param[in] code The string containing the CSS code to add.
         */
        void StyleSheet::add(const char* code)
        {
            CSS::Parser parser(code);
            while (Ruleset_uptr ruleset = parser.readRuleset())
            {
                rulesets.push_back(std::move(ruleset));
                parser.readWSP();
            }
            buildIndex();
        }


        static bool selectorSort(const SelectorBlock& a, const SelectorBlock& b)
        {
            return ((a.selector->getSpecificity()) < (b.selector->getSpecificity()));
        }

        /**
         * Build the indexes onces the sheet is complete or updated.
         */
        void StyleSheet::buildIndex()
        {
            selectorIndex.clear();
            importantSelectorIndex.clear();
            for (const Ruleset_uptr& ruleset : rulesets)
            {
                for (const Selector_uptr& selector : ruleset->selectors)
                {
                    if (ruleset->block->importantMap.size() > 0)
                    {
                        importantSelectorIndex.push_back(SelectorBlock(selector.get(), ruleset->block.get()));
                    }
                    if (ruleset->block->map.size() > 0)
                    {
                        selectorIndex.push_back(SelectorBlock(selector.get(), ruleset->block.get()));
                    }
                }
            }
            std::sort(selectorIndex.begin(), selectorIndex.end(), selectorSort);
            std::sort(importantSelectorIndex.begin(), importantSelectorIndex.end(), selectorSort);
        }

        /**
         * Output StyleSheet to a stream
         */
        std::ostream& operator<<(std::ostream &out, StyleSheet const &styleSheet)
        {
            bool first(true);
            for (const Ruleset_uptr& i: styleSheet.rulesets)
            {
                if (first)
                {
                    first = false;
                }
                else
                {
                    out << std::endl;
                }
                out << *i;
            }
            return out;
        }
    }
}

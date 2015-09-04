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

#include "CSSStyleSheetIndex.hh"
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
         * Apply the stylesheet to specified element (where applicable)
         * param[in] element The element to apply the stylesheet to
         */
        void StyleSheetIndex::apply(Element* element, PropertySet* propertySet) const
        {
            for (SelectorBlock selectorBlock : selectorIndex)
            {
                if (selectorBlock.selector->match(element))
                {
                    for (auto const& i : selectorBlock.block->map)
                    {
                        (*propertySet)[i.first] = i.second->value.get();
                    }
                }
            }
            for (SelectorBlock selectorBlock : importantSelectorIndex)
            {
                if (selectorBlock.selector->match(element))
                {
                    for (auto const& i : selectorBlock.block->importantMap)
                    {
                        (*propertySet)[i.first] = i.second->value.get();
                    }
                }
            }
            // Apply element's style over the top of the style sheet
            const DeclarationBlock* specifiedStyle = element->getSpecifiedStyle();
            for (auto const& i : specifiedStyle->map)
            {
                (*propertySet)[i.first] = i.second->value.get();
            }
        }

        void StyleSheetIndex::clear()
        {
            selectorIndex.clear();
            importantSelectorIndex.clear();
        }

        /**
         * Merge in another stylesheet object
         */
        void StyleSheetIndex::add(const StyleSheet& _styleSheet)
        {
            for (const Ruleset_uptr& ruleset : _styleSheet.rulesets)
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
        }

        static bool selectorSort(const SelectorBlock& a, const SelectorBlock& b)
        {
            return ((a.selector->getSpecificity()) < (b.selector->getSpecificity()));
        }


        void StyleSheetIndex::sort()
        {
            std::sort(selectorIndex.begin(), selectorIndex.end(), selectorSort);
            std::sort(importantSelectorIndex.begin(), importantSelectorIndex.end(), selectorSort);
        }

        /**
         * Output StyleSheet to a stream
         */
        std::ostream& operator<<(std::ostream &out, const StyleSheetIndex&)
        {
            /*bool first(true);
            for (const Ruleset_uptr& i: styleSheetIndex.rulesets)
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
            }*/
            return out;
        }
    }
}

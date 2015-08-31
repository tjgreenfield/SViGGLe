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

#include "CSSSelectors.hh"
#include "CSSStructures.hh"
#include "CSSElement.hh"
#include "CSSStyleSheet.hh"
#include <SVGL/BaseParser/BaseParser.hh>
#include <SVGL/Types/SubString.hh>

namespace SVGL
{
    namespace CSS
    {

        /**
         * CSS parser
         *
         * @details
         * Extends the generic SVGL::Parser to add CSS specific parsing
         */
        class Parser : public SVGL::BaseParser::Parser
        {
        public:

            /**
             * Constructor
             * param[in] _s Start of the string to parse.
             */
            inline Parser(const char* _s = nullptr) :
                SVGL::BaseParser::Parser(_s)
            {
            }

            /**
             * Reads the includes operator "~=" if present.
             * @retval true If the operator is found.
             * @retval false If the operator is not found.
             */
            inline char readIncludes()
            {
                if (*s == '~')
                {
                    if (*(s + 1) == '=')
                    {
                        ++s;
                        ++s;
                        return 1;
                    }
                }
                return 0;
            }

            /**
             * Reads the dash operator "|=" if present.
             * @retval true If the operator is found.
             * @retval false If the operator is not found.
             */
            inline char readDashMatch()
            {
                if (*s == '|')
                {
                    if (*(s + 1) == '=')
                    {
                        ++s;
                        ++s;
                        return 1;
                    }
                }
                return 0;
            }

            /**
             * Read over comment.
             * @retval true If a comment is found.
             * @retval false If a comment is not found.
             */
            bool readComment();

            /**
             * Read a floating point numerical value only if it is followed by a percent sign "%".
             * @param[out] percent Pointer to a double to set as the value. Left unchanged if no numerical value is found.
             * @retval true If a percent value is found.
             * @retval false If a percent value is not found.
             */
            bool readPercent(double* percent);

            /**
             * Read a floating point numerical value and associated units.
             * @return Dimension object containing the read dimension. Dimension opbject is invalid if no dimension is found.
             */
            Dimension readDimension();

            /**
             * Read a character if it is a valid start of name character
             * @retval true If a valid character is found.
             * @retval false If a valid character is not found.
             */
            char readNmStart();

            /**
             * Read a character if it is a valid name character
             * @retval true If a valid character is found.
             * @retval false If a valid character is not found.
             */
            char readNmChar();

            /**
             * Read a name.
              * @return A SubString containing the name. SubString is invalid is an name is not found.
             */
            SubString readName();

            /**
             * Read an ident.
             * @return A SubString containing the identifier. SubString is invalid is an identifier is not found.
             */
            SubString readIdent();

            /**
             * Read a Type Selector
             * @param[out] type Pointer to the TypeSelector object where to set the ident
             * @retval true If a valid type selector is found.
             * @retval false If a valid type selector is not found.
             */
            bool readTypeSelector(std::string* type);

            /**
             * Read an ID Selector.
             * @return A unique_ptr to a IDSelector object.
             * @retval nullptr if no ID Selector is found.
             */
            SubSelector_uptr readIDSelector();

            /**
             * Read an Class Selector.
             * @return A unique_ptr to a ClassSelector object.
             * @retval nullptr if no Class Selector is found.
             */
            SubSelector_uptr readClassSelector();

            /**
             * Read an Attribute Selector.
             * @return A unique_ptr to a AttributeSelector object.
             * @retval nullptr if no Attribute Selector is found.
             */
            SubSelector_uptr readAttributeSelector();

            /**
             * Read a Pseudo Selector.
             * @return A unique_ptr to a PseudoSelector object.
             * @retval nullptr if no Pseudo Selector is found.
             */
            SubSelector_uptr readPseudoSelector();

            /**
             * Read a Simple Selector.
             * @return A unique_ptr to a Simple Selector object.
             * @retval nullptr if no simple selector is found.
             */
            SimpleSelector_uptr readSimpleSelector();

            /**
             * Read a combinator and following selector
             * @return A Combinator object.
             * @retval Combinator type will be INVALID if no combinator is found.
             */
            Combinator readCombinator();

            /**
             * Read a selector
             * @return A unique_ptr to a Selector object.
             * @retval nullptr if no selector is found.
             */
            Selector_uptr readSelector();

            /**
             * Read a keyword prefixed with "@".
             * @return Substring containing hash. Substring is invalid if not found.
             */
            SubString readAtKeyword();

            /**
             * Read a value prefixed with "#".
             * @return Substring containing hash. Substring is invalid if not found.
             */
            SubString readHash();

            /**
             * Reads the !important signifier if present.
             * @retval true If !important is found.
             * @retval false If !important is not found.
             */
            bool readImportant();

            /**
             * Read the identifier and openning bracket "(" of a function, if present.
             * @return Substring containing function name. Substring is invalid if not found.
             */
            SubString readFunctionStart();

            /**
             * Read the parameters of a function.
             * @param[in] ident Pointer to a string that contains the function identifier.
             * @return A unique_ptr to a Function object.
             */
            Function_uptr readFunctionParams(SubString ident);

            /**
             * Read a function.
             * @return A unique_ptr to a Function object.
             * @retval nullptr if no function is found.
             */
            Function_uptr readFunction();

            /**
             * Read a property value.
             * @return A unique_ptr to a Value object.
             * @retval nullptr if no property is found.
             */
            Value_uptr readPropertyValue();

            /**
             * Read a declaration
             * @return A unique_ptr to a Declaration object.
             * @retval nullptr if no declaration is found.
             */
            Declaration_uptr readDeclaration();

            /**
             * Read a declaration block
             * @return A unique_ptr to a DeclarationBlock object.
             * @retval nullptr if no declaration block is found.
             */
            DeclarationBlock_uptr readDeclarationBlock();

            /**
             * Read a ruleset
             * @return A unique_ptr to a Ruleset object.
             * @retval nullptr if no ruleset is found.
             */
            Ruleset_uptr readRuleset();

            /**
             * Read a style sheet
             * @return A unique_ptr to a StyleSheet object.
             * @retval nullptr if no stylesheet is found.
             */
            StyleSheet_uptr readStyleSheet();
        };
    }
}

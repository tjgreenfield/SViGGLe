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

#include "CSSParser.hh"

namespace SVGL
{
    namespace CSS
    {
        bool Parser::readComment()
        {
            State save(s);
            if (readChar('/'))
            {
                if (readChar('*'))
                {
                    while (*s != '*' && *s != 0)
                    {
                        ++s;
                    }
                    while (*s != '/' && *s != 0)
                    {
                        while (*s != '*' && *s != 0)
                        {
                            ++s;
                        }
                        ++s;
                    }
                    if (*s == '/')
                    {
                        ++s;
                        return true;
                    }
                    error("No end of comment", save);
                    set(save);
                    return false; // bad comment
                }
                set(save);
            }
            return false; // not a comment
        }

        bool Parser::readPercent(double* percent)
        {
            State save(s);
            double value;
            if (readNum(&value))
            {
                if (*s == '%')
                {
                    *percent = value;
                    return true;
                }
                set(save);
            }
            return false;
        }

        Dimension Parser::readDimension()
        {
            Dimension result;
            double value;
            SubString unit;

            if (readNum(&value))
            {
                if (unit = readIdent())
                {
                    return Dimension(value, unit);
                }
                else if (readChar('%'))
                {
                    return Dimension(value, SubString(s - 1 ,1));
                }
                else
                {
                    return Dimension(value, SubString(s - 1 ,0));
                }
            }
            return Dimension();
        }

        char Parser::readNmStart()
        {
            char c;
            if (readChar('_'))
            {
                return '_';
            }
            if ((c = readAlphaChar()))
            {
                return c;
            }
            return 0;
        }

        char Parser::readNmChar()
        {
            char c;
            if (readChar('_'))
            {
                return '_';
            }
            if (readChar('-'))
            {
                return '-';
            }
            if ((c = readAlphaChar()))
            {
                return c;
            }
            if ((c = readNumChar()))
            {
                return c;
            }
            return false;
        }

        SubString Parser::readName()
        {
            State start(s);
            if (readNmChar())
            {
                while (readNmChar());
                return SubString(start, s - start);
            }
            return SubString();
        }

        SubString Parser::readIdent()
        {
            State start(s);
            readChar('-');
            if (readNmStart())
            {
                while (readNmChar());
                return SubString(start, s - start);
            }
            set(start);
            return SubString();
        }

        bool Parser::readTypeSelector(TypeSelector* type)
        {
            if (SubString subString = readIdent())
            {
                type->type.assign(subString.start, subString.count);
                return true;
            }
            else if (readChar('*'))
            {
                type->type = "*";
                return true;
            }
            return false;
        }

        SubSelector_uptr Parser::readIDSelector()
        {
            State save(s);
            SubString ident;
            if (readChar('#'))
            {
                if (ident = readIdent())
                {
                    return SubSelector_uptr(new IDSelector(ident));
                }
                error("Bad ID selector", save);
                set(save);
            }
            return nullptr;
        }

        SubSelector_uptr Parser::readClassSelector()
        {
            State save(s);
            SubString ident;
            if (readChar('.'))
            {
                if (ident = readIdent())
                {
                    return SubSelector_uptr(new AttributeSelector(SubString("class"), ident, AttributeSelector::CLASS));
                }
                error("Bad class selector", save);
                set(save);
            }
            return nullptr;
        }

        SubSelector_uptr Parser::readAttributeSelector()
        {
            State save(s);
            SubString ident;
            SubString value;
            AttributeSelector::Mode mode = AttributeSelector::EMPTY;

            if (readChar('['))
            {
                readWSP();
                if (ident = readIdent())
                {
                    readWSP();
                    if (readChar('='))
                    {
                        mode = AttributeSelector::MATCH;
                    }
                    else if (readIncludes())
                    {
                        mode = AttributeSelector::LIST_MATCH;
                    }
                    else if (readDashMatch())
                    {
                        mode = AttributeSelector::STARTS_WITH;
                    }
                    else
                    {
                        mode = AttributeSelector::EMPTY;
                    }
                    if (mode != AttributeSelector::EMPTY)
                    {
                        readWSP();
                        if (value = readIdent())
                        {

                        }
                        else if (value = readString())
                        {

                        }
                        else
                        {
                            error("Missing attribute value", save);
                            set(save);
                            return nullptr;
                        }
                    }
                    readWSP();
                    if (readChar(']'))
                    {
                        return SubSelector_uptr(new AttributeSelector(ident, value, mode));
                    }
                }
                error("Bad attribute selector", save);
                set(save);
            }
            return nullptr;
        }

        SubSelector_uptr Parser::readPseudoSelector()
        {
            State save(s);
            if (readChar(':'))
            {
                SubString type;
                if (type = readIdent())
                {
                    State save2(s);
                    if (readChar('('))
                    {
                        SubString subtype;
                        if (subtype = readIdent())
                        {
                            if (readChar(')'))
                            {
                                return SubSelector_uptr(new PseudoSelector(type, subtype));
                            }
                        }
                        error("Bad pseudo function selector", save);
                        set(save2);
                    }
                    return SubSelector_uptr(new PseudoSelector(type, SubString("")));
                }
                set(save);
            }
            return nullptr;
        }

        SimpleSelector_uptr Parser::readSimpleSelector()
        {
            bool loop = true;

            SimpleSelector_uptr simpleSelector(new SimpleSelector());
            if (readTypeSelector(&simpleSelector->type))
            {
                while (loop)
                {
                    if (SubSelector_uptr subSelector = readIDSelector())
                    {
                        simpleSelector->subSelectors.push_back(std::move(subSelector));
                    }
                    else if (SubSelector_uptr subSelector = readClassSelector())
                    {
                        simpleSelector->subSelectors.push_back(std::move(subSelector));
                    }
                    else if (SubSelector_uptr subSelector = readAttributeSelector())
                    {
                        simpleSelector->subSelectors.push_back(std::move(subSelector));
                    }
                    else if (SubSelector_uptr subSelector = readPseudoSelector())
                    {
                        simpleSelector->subSelectors.push_back(std::move(subSelector));
                    }
                    else
                    {
                        loop = false;
                    }
                }
                return simpleSelector;
            }
            return nullptr;
        }

        Combinator Parser::readCombinator()
        {
            State save(s);
            Combinator::Type cType(Combinator::INVALID);
            if (readWSP())
            {
                cType = Combinator::DECENDANT;
            }
            if (readChar('>'))
            {
                cType = Combinator::CHILD;
                readWSP();
            }
            else if (readChar('+'))
            {
                cType = Combinator::ADJACENT_SIBLING;
                readWSP();
            }
            if (cType != Combinator::INVALID)
            {
                if (SimpleSelector_uptr simpleSelector = readSimpleSelector())
                {
                    return Combinator(cType, std::move(simpleSelector));
                }
            }
            set(save);
            return Combinator(Combinator::INVALID, nullptr);
        }

        Selector_uptr Parser::readSelector()
        {
            if (SimpleSelector_uptr simpleSelector = readSimpleSelector())
            {
                Selector_uptr selector(new Selector(std::move(simpleSelector)));
                while (Combinator combinator = readCombinator())
                {
                    selector->combinators.push_back(std::move(combinator));
                }
                return selector;
            }
            return nullptr;
        }

        SubString Parser::readAtKeyword()
        {
            State save(s);
            SubString result;
            if (readChar('@'))
            {
                if (result = readIdent())
                {
                    return result;
                }
                error("Bad @ keyword", save);
                set(save);
            }
            return SubString();
        }

        SubString Parser::readHash()
        {
            State save(s);
            SubString result;
            if (readChar('#'))
            {
                if (result = readName())
                {
                    return result;
                }
                error("Bad hash value", save);
                set(save);
            }
            return SubString();
        }

        bool Parser::readImportant()
        {
            State save(s);
            if (readChar('!'))
            {
                readWSP();
                if (readStaticNoCase("important"))
                {
                    return true;
                }
                error("Bad !important indicator", save);
                set(save);
            }
            return false;
        }

        SubString Parser::readFunctionStart()
        {
            State save(s);
            SubString name;
            if (name = readIdent())
            {
                State save2(s);
                if (readChar('('))
                {
                    set(save2);
                    return name;
                }
                set(save);
            }
            return SubString();
        }

        Function_uptr Parser::readFunctionParams(SubString ident)
        {
            State save(s);
            if (readChar('('))
            {
                readWSP();
                Function_uptr func(new Function(ident));

                while (Value_uptr value = readPropertyValue())
                {
                    func->parameters.push_back(std::move(value));
                    readWSP();
                    if (!readChar(','))
                    {
                        if (!readChar('/'))
                        {
                            break;
                        }
                    }
                    readWSP();
                }
                if (readChar(')'))
                {
                    return std::move(func);
                }
                error("Missing ')'", save);
                set(save);
            }
            return nullptr;
        }

        Function_uptr Parser::readFunction()
        {
            SubString name;
            State save(s);
            if (name = readFunctionStart())
            {
                readWSP();
                Function_uptr func(new Function(name));

                while (Value_uptr value = readPropertyValue())
                {
                    func->parameters.push_back(std::move(value));
                    readWSP();
                    if (!readChar(','))
                    {
                        if (!readChar('/'))
                        {
                            break;
                        }
                    }
                    readWSP();
                }
                if (readChar(')'))
                {
                    return func;
                }
            }
            set(save);
            return nullptr;
        }

        Value_uptr Parser::readPropertyValue()
        {
            SubString subString;
            double value;
            Function_uptr func;
            Dimension dimension;

            if (subString = readIdent())
            {
                if (Value_uptr func = readFunctionParams(subString))
                {
                    return func;
                }
                return Value_uptr(new Ident(subString));
            }
            if (dimension = readDimension())
            {
                return Value_uptr(new Dimension(dimension));
            }
            if (readNum(&value))
            {
                return Value_uptr(new Dimension(value));
            }
            //if (readURI(s)) TODO
            if (subString = readHash())
            {
                return Value_uptr(new Hash(subString));
            }
            if (subString = readString())
            {
                return Value_uptr(new String(subString));
            }
            return nullptr;
        }

        Declaration_uptr Parser::readDeclaration()
        {
            State save(s);
            SubString ident;
            if (ident = readIdent())
            {
                Declaration_uptr decl(new Declaration(ident));
                readWSP();
                if (readChar(':'))
                {
                    readWSP();
                    if (decl->value = readPropertyValue())
                    {
                        readWSP();
                        if (readChar(','))
                        {
                            readWSP();
                            ValueList* list = new ValueList();
                            list->vector.push_back(std::move(decl->value));
                            decl->value = Value_uptr(list);
                            while (Value_uptr value = readPropertyValue())
                            {
                                list->vector.push_back(std::move(value));
                                readWSP();
                                if (!readChar(','))
                                {
                                    if (!readChar('/'))
                                    {
                                        break;
                                    }
                                }
                                readWSP();
                            }
                        }
                        if (readImportant())
                        {
                            decl->important = true;
                        }
                        return decl;
                    }
                }
                set(save);
            }
            return nullptr;
        }

        DeclarationBlock_uptr Parser::readDeclarationBlock()
        {
            if (Declaration_uptr declaration = readDeclaration())
            {
                DeclarationBlock_uptr declarationBlock(new DeclarationBlock());
                declarationBlock->put(std::move(declaration));
                readWSP();
                while (readChar(';'))
                {
                    readWSP();
                    if (declaration = readDeclaration())
                    {
                        declarationBlock->put(std::move(declaration));
                        readWSP();
                    }
                    else
                    {
                        break;
                    }
                }
                return declarationBlock;
            }
            return nullptr;
        }

        Ruleset_uptr Parser::readRuleset()
        {
            State save(s);
            if (Selector_uptr selector = readSelector())
            {
                State save2(s);
                Ruleset_uptr ruleset(new Ruleset());
                ruleset->selectors.push_back(std::move(selector));
                readWSP();
                while (readChar(','))
                {
                    readWSP();
                    if (Selector_uptr selector2 = readSelector())
                    {
                        ruleset->selectors.push_back(std::move(selector2));
                        readWSP();
                        save2 = s;
                    }
                    else
                    {
                        set(save2);
                        break;
                    }
                }
                if (readChar('{'))
                {
                    readWSP();
                    if (ruleset->block = readDeclarationBlock())
                    {
                        readWSP();
                        if (readChar('}'))
                        {
                            return ruleset;
                        }
                    }
                }
                set(save);
            }
            return nullptr;
        }

        StyleSheet_uptr Parser::readStyleSheet()
        {
            if (Ruleset_uptr ruleset = readRuleset())
            {
                StyleSheet_uptr styleSheet(new StyleSheet());
                styleSheet->rulesets.push_back(std::move(ruleset));
                readWSP();
                while (Ruleset_uptr ruleset2 = readRuleset())
                {
                    readWSP();
                    styleSheet->rulesets.push_back(std::move(ruleset2));
                }
                styleSheet->buildIndex();
                return styleSheet;
            }
            return nullptr;
        }
    }
}

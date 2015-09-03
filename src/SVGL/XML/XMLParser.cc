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

#include "XMLParser.hh"
#include "XMLElement.hh"

namespace SVGL
{
    namespace XML
    {
        Node_uptr Parser::createElement(SubString tag, Node*)
        {
            return std::move(Node_uptr(new XMLElement(tag)));
        }

        Node_uptr Parser::readXML(Node *parent)
        {
            State save(s);
            if (!readProlog())
            {
                // ERROR
                return nullptr;
            }
            readWSP();
            if (Node_uptr node = readElement(parent))
            {
                while (readMisc());
                return std::move(node);
            }
            // ERROR
            set(save);
            return nullptr;
        }

        SubString Parser::readName()
        {
            State save(s);
            if (readNameStartChar())
            {
                while (readNameChar());
                return SubString(save, s - save);
            }
            return SubString();
        }

        bool Parser::readReference()
        {
            if (readCharRef())
            {
                return true;
            }
            return readEntityRef();
        }

        bool Parser::readCharRef() // TODO convert into character code?
        {
            State save(s);
            if (readStatic("&#x"))
            {
                while ((*s >= '0' && *s <= '9') ||
                       (*s >= 'a' && *s <= 'f') ||
                       (*s >= 'A' && *s <= 'F')) // TODO at least 1
                {
                    ++s;
                }
                if (readChar(';'))
                {
                    return true;
                }
                set(save);
            }
            else if (readStatic("&#"))
            {
                while (*s >= '0' && *s <= '9') // TODO at least 1
                {
                    ++s;
                }
                if (readChar(';'))
                {
                    return true;
                }
                set(save);
            }
            return false;
        }

        bool Parser::readEntityRef()
        {
            State save(s);
            if (readChar('&'))
            {
                if (readName())
                {
                    if (readChar(';'))
                    {
                        return true;
                    }
                }
                set(save);
            }
            return false;
        }

        bool Parser::readPEReference()
        {
            State save(s);
            if (readChar('%'))
            {
                if (readName())
                {
                    if (readChar(';'))
                    {
                        return true;
                    }
                }
                set(save);
            }
            return false;
        }

        SubString Parser::readAttValue()
        {
            State save(s);
            char quote = readChar('"');
            if (!quote)
            {
                quote = readChar('\'');
            }
            if (quote)
            {
                while (!readChar(quote))
                {
                    if (!readReference())
                    {
                        if ((*s != quote) &&
                            (*s != '<') &&
                            (*s != '&'))
                        {
                            ++s;
                        }
                        else
                        {
                            if (*s == quote)
                            {
                                ++s;
                                return SubString(save + 1, s - save - 2);
                            }
                            else
                            {
                                set(save);
                                return SubString();
                            }
                        }
                    }
                }
                return SubString(save + 1, s - save - 2);
            }
            return SubString();
        }

        bool Parser::readEq()
        {
            State save(s);
            readWSP();
            if (readChar('='))
            {
                readWSP();
                return true;
            }
            set(save);
            return false;
        }

        bool Parser::readAttribute(Node* node)
        {
            State save(s);
            if (SubString name = readName())
            {
                if (readEq())
                {
                    SubString value = readAttValue();
                    if (value)
                    {
                        node->setAttribute(name, value);
                        return true;
                    }
                }
                set(save);
            }
            return false;
        }

        bool Parser::readCharData(Node* node)
        {
            State save(s);
            while ((*s != '<') && (*s != '&') && (*s))
            {
                if (readStatic("]]>"))
                {
                    // ERROR
                    set(save);
                    return false;
                }
                ++s;
            }
            if (s != save)
            {
                node->appendText(SubString(save, s - save));
            }
            return true;
        }

        bool Parser::readETag(SubString tag)
        {
            State save(s);
            if (readStatic("</"))
            {
                if (readStaticN(tag))
                {
                    readWSP();
                    if (readChar('>'))
                    {
                        return true;
                    }
                }
                set(save);
            }
            return false;
        }

        bool Parser::readElementForParent(Node* parent)
        {
            if (Node_uptr node = readElement(parent))
            {
                parent->appendChild(std::move(node));
                return true;
            }
            return false;
        }

        Node_uptr Parser::readElement(Node* parent)
        {
            State save(s);
            if (readChar('<'))
            {
                if (readChar('/'))
                {
                    set(save);
                    return nullptr;
                }
                SubString tag(readName());
                if (!tag)
                {
                    set(save);
                    return nullptr;
                }
                Node_uptr node = createElement(tag, parent);

                readWSP();
                while (readAttribute(node.get()))
                {
                    readWSP();
                }
                readWSP();
                if (readChar('>'))
                {
                    readContent(node.get());
                    if (readETag(tag))
                    {
                        return std::move(node);
                    }
                    set(save);
                    return nullptr;
                }
                else if (readStatic("/>"))
                {
                    return std::move(node);
                }
                set(save);
                return nullptr;
            }
            return nullptr;
        }

        bool Parser::readContent(Node* node)
        {
            readCharData(node);
            while (readElementForParent(node)
                   || readReference()
                   || readCDSect()
                   || readPI()
                   || readComment()
                   )
            {
                readCharData(node);
            }
            return true;
        }

        bool Parser::readComment()
        {
            if (readStatic("<!--"))
            {
                while (*s)
                {
                    if (readStatic("-->"))
                    {
                        return true;
                        ++s;
                    }
                }
                set(s);
            }
            return false;
        }

        bool Parser::readCDSect()
        {
            if (readStatic("<![CDATA["))
            {
                while (*s)
                {
                    if (readStatic("]]>"))
                    {
                        return true;
                    }
                    ++s;
                }
                set(s);
            }
            return false;
        }

        bool Parser::readPI()
        {
            State save(s);
            if (readStatic("<?"))
            {
                if (!readPITarget())
                {
                    set(save);
                    return false;
                }
                while (*s)
                {
                    if (readStatic("?>"))
                    {
                        return true;
                    }
                    ++s;
                }
                set(save);
            }
            return false;
        }

        bool Parser::readPITarget()
        {
            State save(s);
            if (readStaticNoCase("xml"))
            {
                return false;
            }
            if (readName())
            {
                return true;
            }
            set(save);
            return true;
        }

        bool Parser::readEncodingDecl()
        {
            State save(s);
            if (readWSP())
            {
                if (!readStatic("encoding"))
                {
                    set(save);
                    return false;
                }
                if (!readEq())
                {
                    // ("Expecting '='");
                    set(save);
                    return false;
                }
                if (readChar('"'))
                {
                    if (!readEncName())
                    {
                        // throw ("Expecting Encoding Name");
                        set(save);
                        return false;
                    }
                    if (!readChar('"'))
                    {
                        // throw ("Expecting Close Quote (\")");
                        set(save);
                        return false;
                    }
                }
                else if (readChar('\''))
                {
                    if (!readEncName())
                    {
                        //throw ("Expecting Encoding Name");
                        set(save);
                        return false;
                    }

                    if (!readChar('\''))
                    {
                        // throw ("Expecting Close Quote (')");
                        set(save);
                        return false;
                    }
                }
                return true;
            }
            return false;
        }

        bool Parser::readEncName()
        {
            if ((*s >= 'A' && *s <= 'Z') ||
                (*s >= 'a' && *s <= 'z'))
            {
                ++s;
                while ((*s >= 'A' && *s <= 'Z') ||
                       (*s >= 'a' && *s <= 'z') ||
                       (*s >= '0' && *s <= '9') ||
                       (*s == '.') ||
                       (*s == '_') ||
                       (*s == '-'))
                {
                    ++s;
                }
                return true;
            }
            return false;
        }

        bool Parser::readSDDecl()
        {
            State save(s);
            readWSP();
            if (readStatic("standalone"))
            {
                readEq();
                return readString();
            }
            set(save);
            return false;
        }

        bool Parser::readProlog()
        {
            if (!readXMLDecl())
            {
                return false;
            }
            while (readMisc());
            if (readDocTypeDecl())
            {
                while (readMisc());
            }
            return true;
        }

        bool Parser::readXMLDecl()
        {
            State save(s);
            if (readStatic("<?xml"))
            {
                readWSP();
                if (!readVersionInfo())
                {
                    // ERROR
                    set(save);
                    return false;
                }
                readEncodingDecl();
                readSDDecl();
                readWSP();
                if (!readStatic("?>"))
                {
                    // ERROR
                    set(save);
                    return false;
                }
                return true;
            }
            return false;
        }

        bool Parser::readVersionInfo()
        {
            State save(s);
            if (readStatic("version"))
            {
                if (!readEq())
                {
                    // ERROR
                    set(save);
                    return false;
                }
                if (!readString())
                {
                    // ERROR
                    set(save);
                    return false;
                }
                return true;
            }
            return false;
        }

        bool Parser::readMisc()
        {
            if (readComment() ||
                readPI() ||
                readWSP())
            {
                while (readComment() ||
                       readPI() ||
                       readWSP());
                return true;
            }
            return false;
        }

        bool Parser::readDocTypeDecl() // TODO
        {
            State save(s);
            if (readStatic("<!DOCTYPE"))
            {
                while (*s)
                {
                    if (readChar('>'))
                    {
                        return true;
                    }
                    ++s;
                }
                // ERROR
                set(save);
            }
            return false;
        }

    }
}

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

#include "XMLNode.hh"
#include <SVGL/BaseParser/BaseParser.hh>

namespace SVGL
{
    namespace XML
    {
        class Parser : public SVGL::BaseParser::Parser
        {
        public:
            inline Parser(const char* s = nullptr) :
                SVGL::BaseParser::Parser(s)
            {
            }

            virtual Node_uptr createElement(SubString tag);

            inline char readNameStartChar()
            {
                if ((*s == ':') ||
                    (*s >= 'A' && *s <= 'Z') ||
                    (*s == '_') ||
                    (*s >= 'a' && *s <= 'z'))
                {
                    return *(s++);
                }
                return 0;
            }

            inline char readNameChar()
            {
                if ((*s == ':') ||
                    (*s >= 'A' && *s <= 'Z') ||
                    (*s == '_') ||
                    (*s >= 'a' && *s <= 'z') ||
                    (*s == '-') ||
                    (*s == '.') ||
                    (*s >= '0' && *s <= '9'))
                {
                    return *(s++);
                }
                return 0;
            }

            Node_uptr readXML();

            SubString readName();

            bool readReference();
            bool readCharRef();
            bool readEntityRef();
            bool readPEReference();

            SubString readAttValue();
            bool readEq();
            bool readAttribute(Node* node);

            bool readCharData(Node* node);

            bool readElement(Node* parent);
            Node_uptr readElement();
            bool readETag(SubString tag);

            bool readContent(Node* node);

            bool readComment();
            bool readCDSect();

            // Prologue Stuff
            bool readPI();
            bool readPITarget();
            bool readEncodingDecl();
            bool readEncName();
            bool readSDDecl();
            
            bool readProlog();
            bool readXMLDecl();
            bool readVersionInfo();
            
            bool readVersionNum();
            bool readMisc();

            bool readDocTypeDecl();
            

            /* TODO list?
            bool readDeclSep();
            bool readIntSubset();
            bool readMarkupDecl();
            
            bool readNameToken(std::string* str); 
            bool readNameTokens(std::string* str);

            bool readEntityValue(std::string* str);
            bool readSystemLiteral();
            bool readPubidLiteral();
            bool readPubidChar1(); // excludes "'"
            bool readPubidChar();

            bool readExtSubset();
            bool readSubsetDecl();

            bool readEntityDecl();
            bool readGEDecl();
            bool readPEDecl();
            bool readEntityDef();
            bool readPEDef();

            bool readExternalID();
            bool readNDataDecl();



            bool readElementDecl();
            bool readContentSpec();

            bool readChildren();
            bool readCP();
            bool readChoice();
            bool readSeq();
            bool readMixed();

            bool readAttlistDecl();
            bool readAttDef();
            bool readAttType();
            bool readStringType();
            bool readTokenizedType();*/
        };
    }
}

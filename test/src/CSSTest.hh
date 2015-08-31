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

#include <string>
#include <iostream>
#include <iomanip>
#include <memory>
#include <cstdio>

#include <SVGL/CSS/CSS.hh>
#include <SVGL/CSS/CSSParser.hh>
#include <SVGL/CSS/CSSStructures.hh>
#include <SVGL/CSS/CSSSelectors.hh>
#include <SVGL/Styles/StyleShape.hh>

using namespace std;
using namespace SVGL;

class TestParser : public CSS::Parser
{
public:
    const char *start;
    TestParser(const char* _data) :
        CSS::Parser(_data),
        start(_data)
    {
    }

    void error(const char* message, const char* begin)
    {
        cout << "Error: '" << message << "'" << endl;
        const char* back(begin);
        int backCount = 10;
        while (back > start)
        {
            if (*back == '\n' || *back == '\r' || *back == '\f')
            {
                break;
            }
            if (--backCount <= 0)
            {
                break;
            }
            --back;
        }

        const char* forward(s);
        int forwardCount = 10;
        while (*forward)
        {
            if (*forward == '\n' || *forward == '\r' || *forward == '\f')
            {
                break;
            }
            if (--forwardCount <= 0)
            {
                break;
            }
            ++forward;
        }

        cout.write(back, forward - back);
        cout << endl;
        std::string indent1(begin - back, ' ');
        std::string indent2(s - begin - 1, ' ');

        cout << indent1 << '|' << indent2 << "^Here." << endl;
        cout << indent1 << "^Starting here." << endl;
    }
};

void testDeclarationBlock(const char* label, const char* s);

void testDeclarationBlock(const char* label, const char* s)
{
    cout << label << endl;
    cout << s << endl;
    TestParser p(s);
    CSS::DeclarationBlock_uptr block = p.readDeclarationBlock();
    if (block)
    {
        cout << *block << endl;
    }
    else
    {
        cout << "Error!" << endl;
    }
    cout << "unused: _" << p.get() << "_" << endl;
    cout << endl;
}

void testSelector(const char* label, const char* s)
{
    cout << label << endl;
    cout << s << endl;
    TestParser p(s);
    CSS::Selector_uptr selector = p.readSelector();
    if (selector)
    {
        cout << *selector << endl;
    }
    else
    {
        cout << "Error!" << endl;
    }
    cout << "unused: _" << p.get() << "_" << endl;
    cout << endl;
}

void testRuleset(const char* label, const char* s)
{
    cout << "*** " << label << " ***" << endl;
    cout << s << endl;
    TestParser p(s);
    CSS::Ruleset_uptr ruleset = p.readRuleset();
    if (ruleset)
    {
        cout << *ruleset << endl;
    }
    else
    {
        cout << "Error" << endl;
    }
    cout << "unused: _" << p.get() << "_" << endl;
}

class StyleSheetTester : public CSS::StyleSheet
{
public:

    void dumpIndex()
    {
        int i(0);
        for (CSS::SelectorBlock sb : selectorIndex)
        {
            cout << i << ": " << hex << setw(8) << setfill('0') << sb.selector->getSpecificity() << " @ " << *sb.selector << endl;
            ++i;
        }
        cout << endl;
    }
};


void testStyleSheet(const char* label, const char* s)
{
    cout << "*** " << label << " ***" << endl;
    cout << s << endl << endl;
    TestParser p(s);
    CSS::StyleSheet_uptr stylesheet = p.readStyleSheet();
    if (stylesheet)
    {
        cout << *stylesheet << endl << endl;

        cout << "unused: _" << p.get() << "_" << endl << endl;

        reinterpret_cast<StyleSheetTester*>(stylesheet.get())->dumpIndex();
    }
    else
    {
        cout << "Error" << endl;
        cout << "unused: _" << p.get() << "_" << endl << endl;
    }
}

class TestElement : public CSS::CSSElement
{
public:
    std::string tag;

    TestElement* parent;
    TestElement* prevSibling;
    std::vector<TestElement*> children;

    CSS::DeclarationBlock specifiedStyle;
    Styles::Graphic style;

    TestElement(const char* name, TestElement* _parent = NULL, TestElement* _prevSibling = NULL) :
        tag(name),
        parent(_parent),
        prevSibling(_prevSibling)
    {

    }

    virtual ~TestElement()
    {
        for (TestElement* e : children)
        {
            delete e;
        }
    }

    void calculate(const CSS::SizeContext& sizeContext) override
    {

    }

    virtual const CSS::DeclarationBlock* getSpecifiedStyle() const
    {
        return &specifiedStyle;
    }

    virtual CSS::Style* getStyle()
    {
        return &style;
    }

    virtual const char* getTagName() const
    {
        return tag.c_str();
    }

    virtual const char* getID() const
    {
        return nullptr;
    }

    bool testAttributeValue(const char* attributeName, const char* attributeValue) const override
    {
        return false;
    }

    virtual CSSElement* getParent() const
    {
        return parent;
    }

    virtual CSSElement* getPrevSibling() const
    {
        return prevSibling;
    }

    TestElement* push(const char* tag)
    {
        TestElement* child(
            new TestElement(
                tag,
                this,
                (children.rbegin() == children.rend()) ? NULL : *(children.rbegin())
                )
            );
        children.push_back(child);
        return child;
    }

    TestElement* push(TestElement* element)
    {
        element->prevSibling = ((children.rbegin() == children.rend()) ? NULL : *(children.rbegin()));
        element->parent = this;
        children.push_back(element);
        return element;
    }

    std::string toString()
    {
        std::string str(tag);
        if (children.size() > 0)
        {
            str += "(";
            for (TestElement* child : children)
            {
                str += child->toString();
                str += ",";
            }
            *str.rbegin() = ')';
        }
        return str;
    }

    void applyStyleSheet(CSS::StyleSheet* styleSheet, const CSS::PropertySet& inherit, CSS::SizeContext& sizeContext)
    {
        CSS::PropertySet propertySet;
        styleSheet->apply(this, &propertySet, inherit, sizeContext);
        for (TestElement* child : children)
        {
            child->applyStyleSheet(styleSheet, propertySet, sizeContext);
        }
    }
};

void CSSTest()
{
    /* CSS Code Testing */
    cout << "testing declaration parsing" << endl;

    testDeclarationBlock("Test 1", "blah : 123");
    testDeclarationBlock("Test 2", "-blah : func(1,2)");
    testDeclarationBlock("Test 3", "blah-1f2 : 15pt");
    testDeclarationBlock("Test 4", "blah-1f2 : 15pt;blah:324 ; asdfadf:'string'");

    testDeclarationBlock("Error 1", "blah-1f2 : 'string");

    cout << endl;

    getchar();

    cout << "testing selector parsing" << endl;

    testSelector("Test 1", "rect");
    testSelector("Test 2a", "rest#id");
    testSelector("Test 2b", "rest#id[name]");
    testSelector("Test 2c", "rest#id[name='bob']");
    testSelector("Test 2d", "rest#id[name='bob'].someclass");
    testSelector("Test 3", "g g > rect+text");

    testSelector("Error 1", "rest# id");
    testSelector("Error 2", "rest#id[name=]");
    testSelector("Error 2", "rest#id[ ='123']");
    testSelector("Error 3", "rest#id[name]. someclass");

    cout << endl;

    getchar();

    cout << "testing ruleset parsing" << endl;

    testRuleset("Test 1", "rect { blah : 123 }");
    testRuleset("Test 2a", "rect#id[name='bob'].someclass { blah : 123 }");
    testRuleset("Test 2b", "rect#id[name='bob'].someclass { blah : 123pt; asdf2-44: 123 }");
    testRuleset("Test 2c", "rect, rect#id[name='bob'].someclass { blah : 123; blah-12:3 ;asdfa:'string' }");

    testRuleset("Error 1", "rect, rect#id[name='bob'].someclass { blah : # ; blah-12:3 ;asdfa:'string' }");

    cout << endl;

    getchar();

    cout << "testing stylesheet parsing & indexing" << endl;

    testStyleSheet("Test 1", "rect { blah : 123 }");
    testStyleSheet("Test 2a", "rect { blah : 123pt } rect#id[name='bob'].someclass { blah : 123 }");
    testStyleSheet("Test 2b", "rect#id[name='bob'].someclass { blah : 123; asdf2-44: 123 } rect, rect#id[name='bob'].someclass { blah : 123 } ");
    testStyleSheet("Test 2c", "rect.someclass { blah : 123pt; blah-12:3 ;asdfa:'string' } rect#id, rect { blah : 123; asdf2-44: 123 } rect[name='bob'].someclass { blah : 123 } ");

    cout << endl;

    getchar();

    CSS::PropertySet inherit;
    CSS::SizeContext sizeContext(1280,720,10);

    cout << "testing applying stylesheet to elements" << endl;

    {


        cout << "Test 1" << endl;

        TestElement* A = new TestElement("A");
        TestElement* B = A->push("B");
        TestElement* C = B->push("C");

        CSS::Parser p("A B C {color:#00FF00}");
        CSS::StyleSheet_uptr styleSheet = p.readStyleSheet();



        cout << A->toString() << endl;
        cout << *styleSheet << endl;
        cout << "before: " << C->style.color << endl;
        A->applyStyleSheet(styleSheet.get(), inherit, sizeContext);
        cout << "after: " << C->style.color << endl;

        delete A;

        cout << endl;
    }

    {
        cout << "Test 2" << endl;

        TestElement* A = new TestElement("A");
        TestElement* X = A->push("X");
        TestElement* Y = X->push("Y");
        TestElement* B = Y->push("B");
        TestElement* Z = B->push("Z");
        TestElement* C = Z->push("C");

        CSS::Parser p("A B C {color:#00FF00}");
        CSS::StyleSheet_uptr styleSheet = p.readStyleSheet();


        cout << A->toString() << endl;
        cout << *styleSheet << endl;
        cout << "before: " << C->style.color << endl;
        A->applyStyleSheet(styleSheet.get(), inherit, sizeContext);
        cout << "after: " << C->style.color << endl;

        delete A;

        cout << endl;
    }

    {
        cout << "Test 3a" << endl;

        TestElement* A = new TestElement("A");
        TestElement* B = A->push("B");
        TestElement* C = B->push("C");

        CSS::Parser p("A>B>C {color:#00FF00}");
        CSS::StyleSheet_uptr styleSheet = p.readStyleSheet();


        cout << A->toString() << endl;
        cout << *styleSheet << endl;
        cout << "before: " << C->style.color << endl;
        A->applyStyleSheet(styleSheet.get(), inherit, sizeContext);
        cout << "after: " << C->style.color << endl;

        delete A;

        cout << endl;
    }

    {
        cout << "Test 3b" << endl;

        TestElement* A = new TestElement("A");
        TestElement* X = A->push("X");
        TestElement* Y = X->push("Y");
        TestElement* B = Y->push("B");
        TestElement* Z = B->push("Z");
        TestElement* C = Z->push("C");

        CSS::Parser p("A>B>C {color:#00FF00}");
        CSS::StyleSheet_uptr styleSheet = p.readStyleSheet();

        cout << A->toString() << endl;
        cout << *styleSheet << endl;
        cout << "before: " << C->style.color << endl;
        A->applyStyleSheet(styleSheet.get(), inherit, sizeContext);
        cout << "after: " << C->style.color << endl;

        delete A;

        cout << endl;
    }

    {
        cout << "Test 4a" << endl;

        TestElement* P = new TestElement("A");
        P->push("A");
        P->push("B");
        TestElement* C = P->push("C");

        CSS::Parser p("A+B+C {color:#00FF00}");
        CSS::StyleSheet_uptr styleSheet = p.readStyleSheet();

        cout << P->toString() << endl;
        cout << *styleSheet << endl;
        cout << "before: " << C->style.color << endl;
        P->applyStyleSheet(styleSheet.get(), inherit, sizeContext);
        cout << "after: " << C->style.color << endl;

        delete P;

        cout << endl;
    }

    {
        cout << "Test 4b" << endl;

        TestElement* P = new TestElement("A");
        P->push("A");
        P->push("B");
        P->push("B");
        TestElement* C = P->push("C");

        CSS::Parser p("A+B+C {color:#00FF00}");
        CSS::StyleSheet_uptr styleSheet = p.readStyleSheet();


        cout << P->toString() << endl;
        cout << *styleSheet << endl;
        cout << "before: " << C->style.color << endl;
        P->applyStyleSheet(styleSheet.get(), inherit, sizeContext);
        cout << "after: " << C->style.color << endl;

        delete P;

        cout << endl;
    }

    getchar();
}

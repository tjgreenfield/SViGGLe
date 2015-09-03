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

#include <SVGL/XML/XML.hh>
#include <SVGL/XML/XMLParser.hh>

#include <string>
#include <iostream>
#include <iomanip>
#include <memory>
#include <fstream>

using namespace std;
using namespace SVGL;

void parserTest(const char* title, const char* xml)
{
    cout << title << endl;
    cout << xml << endl;
    XML::Parser p(xml);
    XML::Node_uptr node = p.readElement(nullptr);
    if (node)
    {
        cout << *node << endl;
    }
    else
    {
        cout << "FAIL!" << endl;
    }
    cout << endl << endl;
}

void parserFileTest(const char* filename)
{
    std::ifstream file;
    file.open(filename);
    if (!file.good())
    {
        cout << "File not opened: " << filename << endl;
        return;
    }
    file.seekg(0, ios::end);
    int length = (int)file.tellg();
    file.seekg(0, ios::beg);
    char* data = new char[length+1];
    file.read(data, length);
    data[length] = 0;
    file.close();

    cout << filename << ": " << length << " bytes read." << endl;

    XML::Parser p(data);
    XML::Node_uptr node = p.readXML();
    if (node)
    {
        cout << *node << endl;
    }
    else
    {
        cout << "FAIL!" << endl;
    }
    cout << endl << endl;
    delete data;
}

void XMLTest()
{
    parserTest("test 1", "<tag/>");
    parserTest("test 2", "<tag></tag>");
    parserTest("test 3", "<tag>stuff</tag>");
    parserTest("test 4", "<tag attrib=\"value\">stuff</tag>");
    parserTest("test 5", "<tag attrib=\"value\"> some stuff <subtag/> some more stuff </tag>");

    getchar();
    parserFileTest("data/example.svg");
    getchar();
}

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
    XML::Node_uptr node = p.readElement();
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
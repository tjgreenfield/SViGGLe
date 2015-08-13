#include <SVGL/SVGParser.hh>
#include <SVGL/Document.hh>

#include <string>
#include <iostream>
#include <iomanip>
#include <memory>
#include <fstream>

using namespace std;
using namespace SVGL;

void svgParserTest(const char* title, const char* xml)
{
    cout << title << endl;
    cout << xml << endl;
    Parser p(xml);
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

void svgParserFileTest(const char* filename)
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

    Parser p(data);
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

void SVGTest()
{
    svgParserTest("test 1", "<tag/>");
    svgParserTest("test 2", "<tag></tag>");
    svgParserTest("test 3", "<tag>stuff</tag>");
    svgParserTest("test 4", "<tag attrib=\"value\">stuff</tag>");
    svgParserTest("test 5", "<tag attrib=\"value\"> some stuff <subtag/> some more stuff </tag>");

    getchar();
    svgParserFileTest("data/example.svg");
    getchar();
}
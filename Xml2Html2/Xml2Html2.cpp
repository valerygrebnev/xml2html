/*
* Created by Valery Grebnev as a part coding challenge exercise for OpenText interview, 2023.
* This file contains the 'main' function. Program execution begins and ends there.
*/
#include <iostream>
#include "Xml2HtmlConverter.h"

/*
* For testing:
*   The Xml2HtmlConverter wrapper class below is used for
*   testing large internal buffers, CdDetailsBuffer, when running
*   the XML2HTML I/O operations to allocate the std::array<> buffers
*   on the heap to prevent the stack overflow.
*/
class Xml2HtmlConverterWrapper {
public:
    Xml2HtmlConverterWrapper(const std::string& path) : mPath(path) {}
    Xml2HtmlConverterWrapper() {
        if (converter != nullptr) delete converter;
    }
    void convert() {
        if (converter == nullptr) converter = new Xml2HtmlConverter(mPath);
        converter->convert();
    }
private:
    Xml2HtmlConverter* converter = nullptr;
    const std::string mPath;
};

/*
* Print program usage
*/
void printUsage() {
    std::cout << "Usage: Xml2Http.exe <xml file name>" << std::endl;
    std::cout << "Example: Xml2Http.exe cd_catalog.xml" << std::endl;
}

int main(int argc, char* argv[]) {

    std::string path;

    if (argc < 2) {
        printUsage();
        return 1;
    }
    else {
        path = argv[1];
    }

    std::cout << "Parsing file: " << path << std::endl;

    Xml2HtmlConverterWrapper converter(path);
    converter.convert();

    std::cout << "Parsing and converting completed."  << std::endl;
}
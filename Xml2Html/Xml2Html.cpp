/*
* Created by Valery Grebnev as part of coding challenge for an interview with OpenText.
* The project build and tested in Visual Studio 2022, C++ 14.
*
* Xml2Html.cpp : This file contains the 'main' function. Program execution begins and ends there.
*/
#include <iostream>
#include "XmlCdParser.h"
#include "HtmlDiskCatalogWriter.h"


/*
* Print program usage
*/
void printUsage() {
    std::cout << "Usage: Xml2Http.exe <xml file name>" << std::endl;
    std::cout << "Example: Xml2Http.exe cd_catalog.xml" << std::endl;
}


/*
* Construct html file name from the program input (xml file name)
*/
std::string getHtmlFileName(const std::string& fileName) {
    std::string::size_type const p(fileName.find_last_of('.'));
    std::string result = fileName.substr(0, p);
    return result + ".html";
}

int main(int argc, char* argv[]) {

    std::string path;

    if (argc < 2) {
        printUsage();
        return 1;
    } else {
        path = argv[1];
    }

    std::cout << "Parsing file: " << path << std::endl;

    // Create XML parser
    XmlDiskCatalogParser catalogParser(path);

    // Parse
    if (!catalogParser.parse()) {
        std::cout << "Failed to parse XML file: " << path << std::endl;
        return 1;
    }

    // Get results and convert to HTML
    const std::vector<CdDetails> parsingResult = catalogParser.getCatalog();
   
    std::cout << "Completed parsing file: " << path << std::endl;

    if (!parsingResult.empty()) {
        std::string pathHtml = getHtmlFileName(path);
        HtmlDiskCatalogWriter htmlWriter(pathHtml);
        htmlWriter.write(parsingResult);
        std::cout << "Completed writing html file: " << pathHtml << std::endl;
    }
    else {
        std::cout << "Could not create an html file. The XML parsing result is empty" << std::endl;
    }


    return 0;
}


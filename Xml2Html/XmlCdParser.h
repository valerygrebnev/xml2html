/*
* Created by Valery Grebnev as a part of coding challenge for OpenText interview, 2023.
*
* The implementation is using TinyXML2 library https://github.com/leethomason/tinyxml2,
* and needs two files added to the project source - tinyxml2.h and tinyxml2.cpp files.
*/

#pragma once
#include <string>
#include <vector>
#include "CdDiskDetails.h"

/*
* This a class to read and parse a catalog of the CD disks in the XML format.
*/
class XmlDiskCatalogParser {
public:

	XmlDiskCatalogParser(const std::string& path) : mPath(path) {}

	// Retrieve parsing results  
	std::vector<CdDetails> getCatalog();

	// Parse an XML document  
	bool parse();

private:
	void log(const char* message);
	const std::string mPath;
	std::vector<CdDetails> mDetails;
};

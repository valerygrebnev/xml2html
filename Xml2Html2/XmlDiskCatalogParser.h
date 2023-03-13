/*
* Created by Valery Grebnev as a part of coding challenge for OpenText interview, 2023.
*
* The implementation is using TinyXML2 library https://github.com/leethomason/tinyxml2,
* and needs two files added to the project source - tinyxml2.h and tinyxml2.cpp files.
*/

#pragma once
#include <string>
#include "CdDiskDetails.h"
#include "tinyxml2.h"

/*
* This a class to read and parse a catalog of the CD disks in the XML format.
*/
class XmlDiskCatalogParser {
public:

	XmlDiskCatalogParser(const std::string& path) : mPath(path) {}

	// Parses an XML document root  
	bool parseRoot();

	// Gets a CD element at the current parsing possition in the XML file  
	CdDetails getCD();

	// Returns true if the catalog has a CD at the current possition in the XML file  
	inline bool hasCD() { return mCdPtr != nullptr; }

	// Moves the current parsing possitin to the next elexment
	bool moveToTheNextCD();

private:

	// pointer to the curent CD
	tinyxml2::XMLElement* mCdPtr = nullptr;
	tinyxml2::XMLDocument mDoc;
	const std::string mPath;
};

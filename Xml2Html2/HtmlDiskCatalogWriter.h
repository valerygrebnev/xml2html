/*
* Created by Valery Grebnev as a part coding challenge exercise for OpenText interview, 2023
*/
#pragma once
#include <string>
#include <fstream>
#include "CdDiskDetails.h"

/*
* This a class to write a parsed catalog in an HTML file.
*/
class HtmlDiskCatalogWriter {
public:
	HtmlDiskCatalogWriter(const std::string& path) : mPath(path) {}

	// Write the HTML document title and headers.  
	void writeHeaders();
	
	// Write the HTML document details table.  
	void writeDeatils(const CdDetails& details);

#ifdef PARSE_BY_CHUNKS
	// Write the HTML document details table data chunk. 
	void writeBuffer(const CdDetailsBuffer& details);
#endif

	// Write the HTML document details table ending.  
	void writeEnding();

private:
	const std::string mPath;
	std::ofstream mFile;

};
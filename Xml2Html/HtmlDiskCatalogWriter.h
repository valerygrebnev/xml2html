/*
* Created by Valery Grebnev as a part coding challenge exercise for OpenText interview, 2023
*/
#pragma once
#include <string>
#include <vector>
#include "CdDiskDetails.h"

/*
* This a class to write a parsed catalog in an HTML file.
*/
class HtmlDiskCatalogWriter {
public:

	HtmlDiskCatalogWriter(const std::string& path) : mPath(path) {}

	// Write an HTML document  
	void write(const std::vector<CdDetails>& details);

private:
	const std::string mPath;
};
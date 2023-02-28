/*
* Created by Valery Grebnev as a coding challenge for OpenText interview, 2023.
*/
#pragma once
#include <string>

/*
* The XML nodes and HTML captions.
*/
constexpr char CATALOG[] = "CATALOG";
constexpr char CD[] = "CD";
constexpr char TITLE[] = "TITLE";
constexpr char ARTIST[] = "ARTIST";
constexpr char COMPANY[] = "COMPANY";
constexpr char COUNTRY[] = "COUNTRY";
constexpr char PRICE[] = "PRICE";
constexpr char YEAR[] = "YEAR";


/*
* This a utility data structure to read a catalog of the CD disks in the XML format and convert the content to HTML.
*/
struct CdDetails
{
	std::string title;
	std::string artist;
	std::string company;
	std::string country;
	std::string price;
	std::string year;
};

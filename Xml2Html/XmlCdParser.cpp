#include <iostream>
#include "tinyxml2.h"
#include "XmlCdParser.h"

using namespace tinyxml2;

/*
* Note that instead of XmlDiskCatalogParser::log method, see at the end of this file,
* we could use a static one below in order to not expose in the header minor/utility functionality like logging.
* If we do so, we might want to add the function to a namespace.
*
* It depends on the team. There are different opinions about this.
*
* static void log(const char* message) {
*    std::cout << message << std::endl;
*    // We could call additionally loggers here if needed ...
* }
*
*/


/*
* Return parsed CD catalog details.
* @return vector of CdDetails 
*/
std::vector<CdDetails> XmlDiskCatalogParser::getCatalog() {
	return mDetails;
}

/*
* Parse XML file.
* @return true is succeeded, otherwise false.
*/
bool XmlDiskCatalogParser::parse() {
    
    log("Parsing CD catalog ...");

    XMLDocument doc;
    // Load the XML file into the Doc instance
    XMLError err = doc.LoadFile(mPath.c_str());

    if (err == XMLError::XML_ERROR_FILE_NOT_FOUND) {
        log("Failed to parse CD catalog. XML file not found.");
        return false;
    }
    else if (err != XMLError::XML_SUCCESS) {
        log("Failed to parse CD catalog.");
        return false;
    }

    // Get root Element
    XMLElement* pRootElement = doc.RootElement();
    bool isValidCatalog = (nullptr != pRootElement && 0 == std::string(CATALOG).compare(pRootElement->Name()));

    if (!isValidCatalog) {
        log("Failed to parse CD catalog. Expect to have catalog root");
        return false;
    }

    //Get 'CD' Child (pRoot is already checked above for nullptr)
    XMLElement* pCd = pRootElement->FirstChildElement(CD);
    XMLElement* pDetailsItem = nullptr;

    // Clean up results
    mDetails.clear();
    CdDetails details;
    while (pCd) {
        pDetailsItem = pCd->FirstChildElement(TITLE);
        if (nullptr != pDetailsItem) {
            details.title = pDetailsItem->GetText();
        }

        pDetailsItem = pCd->FirstChildElement(ARTIST);
        if (nullptr != pDetailsItem) {
            details.artist = pDetailsItem->GetText();
        }

        pDetailsItem = pCd->FirstChildElement(COMPANY);
        if (nullptr != pDetailsItem) {
            details.company = pDetailsItem->GetText();
        }

        pDetailsItem = pCd->FirstChildElement(PRICE);
        if (nullptr != pDetailsItem) {
            details.price = pDetailsItem->GetText();
        }

        pDetailsItem = pCd->FirstChildElement(YEAR);
        if (nullptr != pDetailsItem) {
            details.price = pDetailsItem->GetText();
        }

        pDetailsItem = pCd->FirstChildElement(COUNTRY);
        if (nullptr != pDetailsItem) {
            details.country = pDetailsItem->GetText();
        }
        mDetails.push_back(details);
        pCd = pCd->NextSiblingElement(CD);
    }

    log("Completed parsing CD catalog ...");

	return true;
}

/*
* Log info/error messages, see comments at the beginning of the file regarding using a static
* function log() instead of this method.
*/
void XmlDiskCatalogParser::log(const char* message) {
    std::cout << message << std::endl;
    // We could call more loggers here if needed ... 
}


/*
* Created by Valery Grebnev as a part coding challenge exercise for OpenText interview, 2023
*/
#include <iostream>
#include "tinyxml2.h"
#include "ConverterLogger.h"
#include "XmlDiskCatalogParser.h"

using namespace tinyxml2;

/*
* Gets a CD element at the current parsing possition in the XML file.
* @return true is succeeded, otherwise false.
*/
CdDetails XmlDiskCatalogParser::getCD() {
    CdDetails details;
    XMLElement* pDetailsItem = nullptr;
    if (mCdPtr  != nullptr) {
        pDetailsItem = mCdPtr->FirstChildElement(TITLE);
        if (nullptr != pDetailsItem) {
            details.title = pDetailsItem->GetText();
        }

        pDetailsItem = mCdPtr->FirstChildElement(ARTIST);
        if (nullptr != pDetailsItem) {
            details.artist = pDetailsItem->GetText();
        }

        pDetailsItem = mCdPtr->FirstChildElement(COMPANY);
        if (nullptr != pDetailsItem) {
            details.company = pDetailsItem->GetText();
        }

        pDetailsItem = mCdPtr->FirstChildElement(PRICE);
        if (nullptr != pDetailsItem) {
            details.price = pDetailsItem->GetText();
        }

        pDetailsItem = mCdPtr->FirstChildElement(YEAR);
        if (nullptr != pDetailsItem) {
            details.price = pDetailsItem->GetText();
        }

        pDetailsItem = mCdPtr->FirstChildElement(COUNTRY);
        if (nullptr != pDetailsItem) {
            details.country = pDetailsItem->GetText();
        }
    }
    return details;
}

/*
* Moves the current parsing possitin to the next elexment.
* @return true is succeeded, otherwise false.
*/
bool XmlDiskCatalogParser::moveToTheNextCD() {
    if (mCdPtr != nullptr) {
        mCdPtr = mCdPtr->NextSiblingElement(CD);
    }
    return mCdPtr != nullptr;
}

/*
* Parses and validates XML file root element.
* @return true is succeeded, otherwise false.
*/
bool XmlDiskCatalogParser::parseRoot() {

   ConverterLogger::log("Parsing CD catalog root.");

    // Load the XML file into the Doc instance
    XMLError err = mDoc.LoadFile(mPath.c_str());

    if (err == XMLError::XML_ERROR_FILE_NOT_FOUND) {
        ConverterLogger::log("Failed to parse CD catalog. XML file not found.");
        return false;
    }
    else if (err != XMLError::XML_SUCCESS) {
        ConverterLogger::log("Failed to parse CD catalog.");
        return false;
    }

    // Get root Element
    XMLElement*  rootElement = mDoc.RootElement();
    bool isValidCatalog = (nullptr != rootElement && 0 == std::string(CATALOG).compare(rootElement->Name()));

    if (!isValidCatalog) {
        ConverterLogger::log("Failed to parse CD catalog. Expected catalog root not found.");
        return false;
    }

    // Read first CD element
    mCdPtr = rootElement->FirstChildElement(CD);

    return true;
}
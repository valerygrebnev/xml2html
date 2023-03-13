/*
* Created by Valery Grebnev as a part coding challenge exercise for OpenText interview, 2023
*/

#include <sstream>

#include "HtmlDiskCatalogWriter.h"

/*
* Write the HTML document title and headers.
*/
void HtmlDiskCatalogWriter::writeHeaders() {

    mFile.open(mPath);

    // starting html
    mFile << "<!DOCTYPE html><html><head></head><body>";
    
    // starting catalog table
    mFile << "<h2>" << CATALOG << "</h2>";
    mFile << "<table>";
    
    // adding headers
    mFile << "<tr><th>" << TITLE << "</th><th>" << ARTIST << "</th><th>" << COUNTRY
        << "</th><th>" << COMPANY << "</th><th>" << PRICE << "</th><th>" << YEAR << "</th></tr>";

}

/*
* Write the HTML document details table
*/
void HtmlDiskCatalogWriter::writeDeatils(const CdDetails& details) {

    mFile << "<tr><td>"  << details.title << "</td><td>" << details.artist
          << "</td><td>" << details.country << "</td><td>" << details.company
          << "</td><td>" << details.price << "</td><td>" << details.year << "</td></tr>";
}

#ifdef PARSE_BY_CHUNKS
/*
* Write the HTML document details table
*/
void HtmlDiskCatalogWriter::writeBuffer(const CdDetailsBuffer& detailsBuffer) {

    std::ostringstream buffer;
    for (int i = 0; i < detailsBuffer.getNumberOfElements(); i++) {
        const CdDetails& details = detailsBuffer.get(i);
        buffer << "<tr><td>" << details.title << "</td><td>" << details.artist
            << "</td><td>" << details.country << "</td><td>" << details.company
            << "</td><td>" << details.price << "</td><td>" << details.year << "</td></tr>";
    }

    mFile.write(buffer.str().c_str(), buffer.str().length());
}
#endif

/*
* Write the HTML document details table ending.
*/
void HtmlDiskCatalogWriter::writeEnding() {
    mFile << "</table>";
    //ending html
    mFile << "</body></html>";
    mFile.close();
}
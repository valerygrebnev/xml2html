#include <fstream>
#include "HtmlDiskCatalogWriter.h"

void HtmlDiskCatalogWriter::write(const std::vector<CdDetails>& details) {

    std::ofstream myfile;
    myfile.open(mPath);

    // starting html
    myfile << "<!DOCTYPE html><html><head></head><body>";
    
    // starting catalog table
    myfile << "<h2>" << CATALOG << "</h2>";
    myfile << "<table>";
    
    // adding headers
    myfile << "<tr><th>" << TITLE << "</th><th>" << ARTIST << "</th><th>" << COUNTRY 
        << "</th><th>" << COMPANY << "</th><th>" << PRICE << "</th><th>" << YEAR << "</th></tr>";

    for (CdDetails details : details) {
        myfile << "<tr><th>" << details.title << "</th><th>" << details.artist << "</th><th>" << details.country
            << "</th><th>" << details.company << "</th><th>" << details.price << "</th><th>" << details.year << "</th></tr>";
    }

    myfile << "</table>";

    //ending html
    myfile << "</body></html>";
    myfile.close();

}

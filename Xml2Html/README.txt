PROJECT Xml2Http

SUMMARY
   
“Xml2Http.exe” is a simple C++ console program that takes cd_catalog.xml (attached) as input and converts it to an HTML file. The project is completed by Valery Grebnev as a part of coding challenge exercise for OpenText interview.

BUILD AND RUN THE APPLICATION

Add the source files listed in the “Implementation” section below to a solution and build. No specific configuration is needed. The solution could be opened and built as is in Visual Studio 2022. The program expects an XML file name as an input, for example:

                Xml2Http.exe cd_catalog.xml

The source XML file should use the same syntax/schema as the “cd_catalog.xml” (included in the project). For convenience, the source XML file is added to the project debug arguments configuration.    

Run nmake to build the program using MSVC CLI. On Linux, run make -f makefile4make.


IMPLEMENTATION

The implementation uses TinyXML2 library https://github.com/leethomason/tinyxml2, and needs two library files, tinyxml2.h and tinyxml2.cpp, added to the project sources. The project is built in Microsoft Visual Studio 2022 with C++ 14. The sources include the following files:

        Xml2Html.cpp -  contains the 'main' function.
        CdDiskDetails.h - constants for parsing an XML file and converting to an HTML file. 
        HtmlDiskCatalogWriter.cpp - HTML writer implementation.
        HtmlDiskCatalogWriter.h - HTML writer header file.

        Tinyxml2.cpp - TinyXML library file. 
        tinyxml2.h - TinyXML library file.

        XmlCdParser.cpp - XML parser implementation
        XmlCdParser.h - XML parser header

The project directory includes the documentation input/output examples and nmake makefile 

        cd_catalog.html
        cd_catalog.xml
        README.txt
        makefile - for MSVC nmake
        makefile4make - for Linux-like make utility

DESIGN NOTES

Parsing an XML file and creating an HTML file functionality is separated into two classes XmlDiskCatalogParser, HtmlDiskCatalogWriter following SRP S.O.L.I.D OOP principles.

Constructors accept the file names. The API does not provide functionality to configure file names after instantiation as it is not required by the exercise requirements to parse multiple files in runtime. This could be extended to parse multiple files if needed.

OPTIMIZATION NOTES

The current API is not optimized. As a further performance optimization, the XmlCdParser and HtmlDiskCatalogWriter could be injected to (or created in) a wrapper class “Converter” using a shared parsing results’ container, which is not implemented in the scope of this exercise. 

Reading large data will not cause the stack overflow in the current solution because the vector elements are always created on the heap and not on the stack unless the standard allocator is overridden. 

Reading large data and the related performance issues are not optimized in the current implementation, but could be addressed in the future by data chunking. The chunking data flow would require using/implementing a different XML reader library. 

Note that a simple (“obvious” at the first glance) performance “optimization” of the current solution, for example, by returning a reference instead of copying the result vector is not considered. As it is mentioned above, the performance could be improved by creating a wrapper handling both HtmlDiskCatalogWriter and XmlCdParser and controlling objects’ lifetime. In the current design, returning a reference instead of copying the result data could cause the following issues:

1) When calling the API, a caller should not make any assumption about the API object's lifetime. For example, when calling the  HtmlDiskCatalogWriter, the caller should not assume that the XmlCdParser object is still alive. Returning a reference could be unsafe leading to access violation. Consider the  “optimization” returning a reference: 

	class XmlDiskCatalogParser {
	...
		// Return a reference instead of a copy of objects
		//  std::vector<CdDetails> getCatalog();
		const std::vector<CdDetails>& getCatalog();
      };

	const std::vector<CdDetails>& getCatalog(std::string path) {
		// Create XML parser
		XmlDiskCatalogParser catalogParser(path);
		// Parse
		catalogParser.parse();
		// return a reference instead of a copy
		return catalogParser.getCatalog();
	}

In the code above, the XmlCdParser will be destroyed at the time when reading the result in the HtmlDiskCatalogWriter, which will lead to access violation.

2) API design should not assume that the caller could not call cosnt_case<type>(expression) operator:

	std::vector<CdDetails>& parsingResult = const_cast<std::vector<CdDetails>&>(catalogParser.getCatalog());

The API should prevent changing the state of the XmlCdParser after parsing.

LICENSING

The project uses  TinyXML2 library https://github.com/leethomason/tinyxml2, which is using the zlib license.

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software. Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely.

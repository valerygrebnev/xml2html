PROJECT Xml2Http

SUMMARY
   
“Xml2Http.exe” is a simple C++ console program that takes cd_catalog.xml (attached) as input and converts it to an HTML file. The project is completed by Valery Grebnev as a part of coding challenge exercise for OpenText interview.

BUILD AND RUN THE APPLICATION

Add the source files listed in the “Implementation” section below to a solution and build. No specific configuration is needed. The solution could be opened and built as is in Visual Studio 2022. The program expects an XML file name as an input, for example:

                Xml2Http.exe cd_catalog.xml

The source XML file should use the same syntax/schema as the “cd_catalog.xml” (included in the project). For convenience, the source XML file is added to the project debug arguments configuration.    

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

The project directory includes the documentation and input/output examples 

        cd_catalog.html
        cd_catalog.xml
        README.txt

DESIGN NOTES

Parsing an XML file and creating an HTML file functionality is separated into two classes XmlDiskCatalogParser, HtmlDiskCatalogWriter following SRP S.O.L.I.D OOP principles.

Constructors accept the file names. The API does not provide functionality to configure file names after instantiation as it is not required by the exercise requirements to parse multiple files in runtime. This could be extended to parse multiple files if needed.

LICENSING

The project uses  TinyXML2 library https://github.com/leethomason/tinyxml2, which is using the zlib license.

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software. Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely.

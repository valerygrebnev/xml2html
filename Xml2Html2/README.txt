ROJECT Xml2Http2


SUMMARY
   
'Xml2Http2.exe' is a simple C++ console program that takes cd_catalog.xml (attached) as input and converts it to an HTML file. The project is completed by Valery Grebnev as a part of coding challenge exercise for OpenText interview.

BUILD AND RUN THE APPLICATION

Add the source files listed in the “Implementation” section below to a solution and build. No specific configuration is needed. The solution could be opened and built as is in Visual Studio 2022. The program expects an XML file name as an input, for example:

                Xml2Http2.exe cd_catalog.xml

The source XML file should use the same syntax/schema as the “cd_catalog.xml” (included in the project). For convenience, the source XML file is added to the project debug arguments configuration.    

Run nmake to build the program using MSVC CLI. On Linux, run make -f makefile4make.


IMPLEMENTATION

The implementation uses TinyXML2 library https://github.com/leethomason/tinyxml2, and needs two library files, tinyxml2.h and tinyxml2.cpp, added to the project sources. The project is built in Microsoft Visual Studio 2022 with C++ 14. The sources include the following files:

        Xml2Html2.cpp -  contains the 'main' function.

        CdDiskDetails.h - constants for parsing an XML file and converting to an HTML file.
        ConverterLogger.h - logger implementation. 
        HtmlDiskCatalogWriter.cpp - HTML writer implementation.
        HtmlDiskCatalogWriter.h - HTML writer header file.

        tinyxml2.cpp - TinyXML library file. 
        tinyxml2.h - TinyXML library file.

        Xml2HtmlConverter.cpp - XML parser implementation
        Xml2HtmlConverter.h - XML parser header

        XmlDiskCatalogParser.cpp - XML parser implementation
        XmlDiskCatalogParser.h - XML parser header

The project directory includes the documentation input/output examples and nmake makefile 

        cd_catalog.html
        cd_catalog.xml
        README.txt
        makefile - for MSVC nmake
        makefile4make - for Linux-like make utility


DESIGN NOTES

Parsing an XML file and creating an HTML file functionality is separated into two classes XmlDiskCatalogParser, HtmlDiskCatalogWriter following SRP S.O.L.I.D OOP principles, and is orchestrated by the Xml2HtmlConverter and Xml2HtmlConverterWrapper classes:

       Xml2HtmlConverterWrapper converter(path);
       converter.convert();

Constructors accept the file names. The API does not provide functionality to configure file names after instantiation as it is not required by the exercise requirements to parse multiple files in runtime. This could be extended to parse multiple files if needed.

In order to parse large files, the application provides chunking I/O data flow. Xml2HtmlConverter calls XmlDiskCatalogParser to read a small portion of data, and then call the HtmlDiskCatalogWriter to write the converted data, for example:

        CdDetails details = mXmlParser.getCD();
        mHtmlWriter.writeDeatils(details);

The application supports three types of chunking flow, see the preprocessor directives in the CdDiskDetails.h:
 
	USE_BUFFERING 0 - application level buffering is not used.
		The CD entries are parsed one by one.
		The parser reads one XML entry and writes one HTML entry.

	USE_BUFFERING 1 - parsing by CdDetails chunks is used.
		The CD entries are parsed by data chunks.
		The parser reads one XML chunk and writes the whole HTML chunk at once.

	USE_BUFFERING 2 - parsing by CdDetails queued entries is used.
		The XML parser reads and adds the CD entries to a I/O queue till
		the queue is not full. If the queue is full, the XML reader waits for
		the HTML writer to consume some data. If the queue is empty,
		the HTML writer waits for the XML reader to produce some data.
 
The compilation will stop if the buffing type is not specified.


LICENSING

The project uses  TinyXML2 library https://github.com/leethomason/tinyxml2, which is using the zlib license.

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software. Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely.

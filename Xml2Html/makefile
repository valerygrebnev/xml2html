Xml2Html.exe: Xml2Html.obj HtmlDiskCatalogWriter.obj  XmlCdParser.obj tinyxml2.obj
      link Xml2Html.obj HtmlDiskCatalogWriter.obj  XmlCdParser.obj tinyxml2.obj

Xml2Html.obj: Xml2Html.cpp XmlCdParser.h HtmlDiskCatalogWriter.h
      cl -c Xml2Html.cpp

HtmlDiskCatalogWriter.obj: HtmlDiskCatalogWriter.cpp HtmlDiskCatalogWriter.h
      cl -c HtmlDiskCatalogWriter.cpp

XmlCdParser.obj: XmlCdParser.cpp XmlCdParser.h
      cl -c XmlCdParser.cpp

tinyxml2.obj: tinyxml2.cpp tinyxml2.h
      cl -c tinyxml2.cpp
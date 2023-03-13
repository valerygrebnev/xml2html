program: Xml2Html2.obj Xml2HtmlConverter.obj HtmlDiskCatalogWriter.obj XmlDiskCatalogParser.obj tinyxml2.obj
      link Xml2Html2.obj Xml2HtmlConverter.obj HtmlDiskCatalogWriter.obj  XmlDiskCatalogParser.obj tinyxml2.obj /out:Xml2Html2.exe

Xml2Html2.obj: Xml2Html2.cpp Xml2HtmlConverter.h
      cl -c Xml2Html2.cpp

Xml2HtmlConverter.obj: Xml2HtmlConverter.cpp Xml2HtmlConverter.h ConverterLogger.h
      cl -c Xml2HtmlConverter.cpp

HtmlDiskCatalogWriter.obj: HtmlDiskCatalogWriter.cpp HtmlDiskCatalogWriter.h
      cl -c HtmlDiskCatalogWriter.cpp

XmlDiskCatalogParser.obj: XmlDiskCatalogParser.cpp XmlDiskCatalogParser.h ConverterLogger.h
      cl -c XmlDiskCatalogParser.cpp

tinyxml2.obj: tinyxml2.cpp tinyxml2.h
      cl -c tinyxml2.cpp

clean:
	del *.obj *.exe
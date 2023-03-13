/*
* Created by Valery Grebnev as a part coding challenge exercise for OpenText interview, 2023
*/
#pragma once

#include <string>

#include "CdDiskDetails.h"
#include "XmlDiskCatalogParser.h"
#include "HtmlDiskCatalogWriter.h"

#ifdef PARSE_CONCURRENT_QUEUE
#include <atomic>
#include <condition_variable>
#include <queue>
#include <mutex>
#include <thread>
#endif

/*
* This is a class converting an XML file to an HTML file. Xml2HtmlConverter orchestrates
* XmlDiskCatalogParser and HtmlDiskCatalogWriter converting files.
* 
*/
class Xml2HtmlConverter
{
public:
	Xml2HtmlConverter(const std::string& path) : mPath(path), mXmlParser(path), mHtmlWriter(buildHtmlFilePath(path)) {}

	/*
	* Orchestrates XmlDiskCatalogParserand HtmlDiskCatalogWriter classes to read an XML document
	* and convert it to an HTML document.
	*/
	bool convert();

private:
	std::string buildHtmlFilePath(const std::string& fileName);
	XmlDiskCatalogParser mXmlParser;
	HtmlDiskCatalogWriter mHtmlWriter;
	const std::string mPath;

#ifdef PARSE_CONCURRENT_QUEUE

	bool isBufferingProcessingDone();
	void readXmlToBuffer();
	void writeBufferToHtml();
	/*
	* Queue provides buffering XML reads. If the queue size reaches MAX_ELEMENTS, then
	* the XML reader will wait for the HTML writer to consume some data before reading/producing another
	* portion of new data.  
	*/
	std::queue<CdDetails> mDetails;
	static constexpr size_t MAX_ELEMENTS = 1024;

	/*
	* Buffering synchronization objects. 
	*/
	std::condition_variable mCondition;
	std::mutex mStateMutex;
	std::atomic_bool mFinished = { false };
#endif

#ifdef PARSE_BY_CHUNKS
	CdDetailsBuffer mDetailsBuffer;
#endif
};

/*
* Created by Valery Grebnev as a part coding challenge exercise for OpenText interview, 2023
*/
#include "ConverterLogger.h"
#include "Xml2HtmlConverter.h"

/*
* Converts an XML file to an HTML file.
* @return true is succeeded, otherwise false.
*/
bool Xml2HtmlConverter::convert() {

    ConverterLogger::log("Parsing CD catalog ...");

    // Start reading the XML file.
    if (!mXmlParser.parseRoot()) {
        ConverterLogger::log("Failed to read XML file " + mPath);
        return false;
    }

    // Add the catalog title and headers to the output HTML file.
    mHtmlWriter.writeHeaders();

#ifdef PARSE_BY_ONE_ENTRY
    // Read the XML file and write the output HTML file by one CD. 
    while (mXmlParser.hasCD()) {
        CdDetails details = mXmlParser.getCD();
        mHtmlWriter.writeDeatils(details);
        mXmlParser.moveToTheNextCD();
    }
#endif

#ifdef PARSE_BY_CHUNKS
    // Read the XML file and write the output HTML file by chunks. 
    while (mXmlParser.hasCD()) {

        // Read a chunk of data into the buffer
        mDetailsBuffer.clear();
        while (mXmlParser.hasCD() && !mDetailsBuffer.isFull()) {
            CdDetails details = mXmlParser.getCD();
            mDetailsBuffer.puch_back(details);
            mXmlParser.moveToTheNextCD();
        }
        //Write the chunk of the data
        mHtmlWriter.writeBuffer(mDetailsBuffer);
    }
#endif

#ifdef PARSE_CONCURRENT_QUEUE

    /*
    * Read the XML file and write the HTML using the CD queue.
    * The queue is limited in size providing chunking reads/writes.
    * This scenario could be used when reads are faster than writes, for example,
    * if writes require sorting, formating, any blocking requests to get additional information and so on.
    */
    if (mXmlParser.hasCD()) {
        std::thread xmlReader(&Xml2HtmlConverter::readXmlToBuffer, this);
        std::thread htmlWriter(&Xml2HtmlConverter::writeBufferToHtml, this);
        xmlReader.join();
        htmlWriter.join();
    }
#endif

    // Fnalize the output HTML file.
    mHtmlWriter.writeEnding();

    ConverterLogger::log("Finished parsing CD catalog ...");

    return true;
}

/*
* Construct html file name from the program input (xml file name)
*/
std::string Xml2HtmlConverter::buildHtmlFilePath(const std::string& fileName) {
    std::string::size_type const p(fileName.find_last_of('.'));
    std::string result = fileName.substr(0, p);
    return result + ".html";
}

#ifdef PARSE_CONCURRENT_QUEUE

/*
* Reads the XML file using buffering with a queue.
*/
void Xml2HtmlConverter::readXmlToBuffer() {

    ConverterLogger::log("Start reading CD details.");

    while (mXmlParser.hasCD()) {

        {
            std::unique_lock<std::mutex> lock(mStateMutex);

            if (mDetails.size() >= MAX_ELEMENTS) {
                // Wait till the HTML writer consumes some CD details entries.   
                mCondition.wait(lock, [&]() {return mDetails.size() < MAX_ELEMENTS;});
            }

            CdDetails details = mXmlParser.getCD();
            mDetails.push(details);
            
            mXmlParser.moveToTheNextCD();
            if (!mXmlParser.hasCD()) {
                mFinished = true;
            }
        }

        mCondition.notify_one();
        std::this_thread::yield();
    }

    mCondition.notify_one();

    ConverterLogger::log("Done reading CD details.");
}

/*
* Writes the HTML file using buffering with a queue.
*/
void Xml2HtmlConverter::writeBufferToHtml() {

    ConverterLogger::log("Start writing HTML CD details.");

    while (!isBufferingProcessingDone())
    {
        {
            std::unique_lock<std::mutex> lock(mStateMutex);

            if (!mFinished && mDetails.empty()) {
                // Wait till the XML reader produces some data and pushes the data to the queue.
                mCondition.wait(lock, [&]() { return !mDetails.empty(); });
            }

            CdDetails details = mDetails.front();
            mDetails.pop();
            mHtmlWriter.writeDeatils(details);
        }

        mCondition.notify_one();
        std::this_thread::yield();
    }
}

/*
* Returns the completion status of the reading/writing processing with buffering.
* @return true if processing is completed.
*/
bool Xml2HtmlConverter::isBufferingProcessingDone() {
    std::unique_lock<std::mutex> lock(mStateMutex);
    return mFinished && mDetails.empty();
}
#endif

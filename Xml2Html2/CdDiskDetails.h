/*
* Created by Valery Grebnev as a coding challenge for OpenText interview, 2023.
*/
#pragma once
#include <string>

/*
* Define the CdDetails buffering type:
*	
*	USE_BUFFERING 0 - application level buffering is not used.
*		The CD entries are parsed one by one.
*		The parser reads one XML entry and writes one HTML entry.
*
*	USE_BUFFERING 1 - parsing by CdDetails chunks is used.
*		The CD entries are parsed by data chunks.
*		The parser reads one XML chunk and writes the whole HTML chunk at once.
*
*	USE_BUFFERING 2 - parsing by CdDetails queued entries is used.
*		The XML parser reads and adds the CD entries to a I/O queue till
*		the queue is not full. If the queue is full, the XML reader waits for
*		the HTML writer to consume some data. If the queue is empty,
*		the HTML writer waits for the XML reader to produce some data.
* 
*   The compilation will stop if the buffing type is not specified.
*
*/
#define USE_BUFFERING 0

#if USE_BUFFERING == 0
	#define PARSE_BY_ONE_ENTRY
#elif USE_BUFFERING == 1
	#define PARSE_BY_CHUNKS
#elif USE_BUFFERING == 2
	#define PARSE_CONCURRENT_QUEUE
#else
	#error Stop compilation: data chunking flow is not defined. 
#endif


/*
* The XML nodes and HTML captions.
*/
constexpr char CATALOG[] = "CATALOG";
constexpr char CD[] = "CD";
constexpr char TITLE[] = "TITLE";
constexpr char ARTIST[] = "ARTIST";
constexpr char COMPANY[] = "COMPANY";
constexpr char COUNTRY[] = "COUNTRY";
constexpr char PRICE[] = "PRICE";
constexpr char YEAR[] = "YEAR";


/*
* This is a utility data structure to read a catalog of the CD disks in the XML format and convert the content to HTML.
*/
struct CdDetails
{
	std::string title;
	std::string artist;
	std::string company;
	std::string country;
	std::string price;
	std::string year;
};

#ifdef  PARSE_BY_CHUNKS
#include <array>

/*
* This a utility class for buffering I/O.
* The template definition is used in order to facilitate std::array containers.
*/
class CdDetailsBuffer {
public:

	void clear() {
		mCount = 0;
	}
	const CdDetails& get(const int index) const {
		if (index >= mCount)
			throw std::out_of_range("CdDetails element is out of range.");

		// Will throw the standard exception.
		return mDetails.at(index);
	}

	size_t getNumberOfElements() const {
		return mCount;
	}

	bool isFull() {
		return !(mCount < MAX_ELEMENTS);
	}

	bool puch_back(const CdDetails& details) {
		if (mCount < MAX_ELEMENTS) {
			mDetails[mCount++] = details;
			return true;
		}
		return false;
	}
private:
	static constexpr int  MAX_ELEMENTS = 1024;
	std::array<CdDetails, MAX_ELEMENTS> mDetails;
	size_t mCount = 0;
};
#endif

/*
* Created by Valery Grebnev as a coding challenge for OpenText interview, 2023.
*/
#pragma once
#include <iostream>
#include <string>
#include <mutex>

namespace XML2HTML {
	static std::mutex loggerMutex;
}

/*
* Utility class to log messages
*/
class ConverterLogger {
public:

	/*
	* Log a message
	*/
	static void log(const std::string& message) {
		std::unique_lock<std::mutex> lock(XML2HTML::loggerMutex);
		std::cout << message << std::endl;
		// Call other loggers if needed ...

	}
};
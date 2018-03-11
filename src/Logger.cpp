#include <Logger.hpp>

#include <iostream>
#include <sstream>
#include <string>


namespace prx
{


	void
	Logger::Send(enum Logger::LEVEL level, std::string message...) {
		std::ostringstream output(std::ostringstream::ate);
		va_list args;
		va_start(args, message);
		for(std::string::iterator it=message.begin(); it != message.end(); it++) {
			if(*it == '%') {
				it++;
				if(*it == 's') {
					output << va_arg(args, std::string);
				} else if(*it == 'c') {
					output << static_cast<char>(va_arg(args, int));
				} else if(*it == 'd') {
					output << va_arg(args, int);
				}
				it++;
			}
			output << *it;
		}
		if(level == WARNING) {
			std::cout << "WARNING: " << output.str() << std::endl;
		} else if(level == ERROR) {
				std::cout << "ERROR: " << output.str() << std::endl;
		} else if(level == DEBUG) {
			std::cout << "DEBUG: " << output.str() << std::endl;
		} else if(level == INFO) {
			std::cout << "INFO: " << output.str() << std::endl;
		}
		va_end(args);
	}



}

#include <Logger.hpp>

#include <iostream>
#include <sstream>
#include <cstdarg>
#include <iterator>
#include <string>


namespace prx
{

	namespace Logger
	{


		void
		Send(enum Logger::LEVEL level, std::string& message...) {
			va_list args;
			va_start(args, message);
			std::ostringstream output(std::ostringstream::ate);
			for(std::string::iterator it=message.begin(); it != message.end(); it++) {
				if(*it == '%') {
					it++;
					if(*it == 's') {
						output << va_arg(args, const char*);
					} else if(*it == 'c') {
						output << static_cast<char>(va_arg(args, int));
					} else if(*it == 'd') {
						output << va_arg(args, int);
					}
					it++;
				}
				output << *it;
			}
			switch(level) {
				case WARNING:
					std::cout << "WARNING: " << output.str() << std::endl;
				break;
				case ERROR:
					std::cout << "ERROR: " << output.str() << std::endl;
				break;
				case DEBUG:
					std::cout << "DEBUG: " << output.str() << std::endl;
				break;
				case INFO:
				default:
					std::cout << "INFO: " << output.str() << std::endl;
				break;
			}
			va_end(args);
		}


	}


}

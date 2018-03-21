#include <Logger.hpp>

#include <iostream>
#include <sstream>
#include <string>

#include <SFML/System/Vector2.hpp>


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
				if(*it == 's')
					output << va_arg(args, char*);
				else if(*it == 'c')
					output << static_cast<char>(va_arg(args, int));
				else if(*it == 'd')
					output << std::to_string(va_arg(args, int));
				else if(*it == 'v') {
					sf::Vector2f v = va_arg(args, sf::Vector2f);
					output << "[" << v.x << ", " << v.y << "]";
				}
				// If the format chain type specifier is the last character in the input stream,
				// incrementing iterator leads to segmentation fault when inserting it in the
				// output stream.
				if((it + 1) == message.end())
					break;
				else
					it++;
			}
			output << *it;
		}
		va_end(args);
		if(level == WARNING)
			std::cout << "WARNING: " << output.str() << std::endl;
		else if(level == ERROR)
			std::cout << "ERROR: " << output.str() << std::endl;
		else if(level == DEBUG)
			std::cout << "DEBUG: " << output.str() << std::endl;
		else if(level == INFO)
			std::cout << "INFO: " << output.str() << std::endl;
	}


}

#ifndef LOGGER_DEFINED
#define LOGGER_DEFINED

#include <string>
#include <cstdarg>


namespace prx
{


	namespace Logger
	{


		enum LEVEL {
			INFO,
			WARNING,
			ERROR,
			DEBUG
		};

		void Send(enum LEVEL, std::string message...);


	}


}


#endif

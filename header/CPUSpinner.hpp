#ifndef CPUSPINNER_INCLUDED
#define CPUSPINNER_INCLUDED


#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>


namespace prx
{


	class CPUSpinner
	{

		public:
			CPUSpinner(const int delay);
			bool nextTickMustIterate();

		private:
			sf::Clock clock;
			sf::Time delay;
			sf::Time elapsed_time;

	};


}



#endif

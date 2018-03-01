#ifndef CPUSPINNER_INCLUDED
#define CPUSPINNER_INCLUDED

#include <SFML/Graphics.hpp>


namespace prx
{


	class CPUSpinner
	{
		public:
			CPUSpinner(sf::RenderWindow& w) : window(w)
			{ }
			void run();

		private:
			sf::RenderWindow& window;
	};


}


#endif

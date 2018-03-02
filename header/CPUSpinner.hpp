#ifndef CPUSPINNER_INCLUDED
#define CPUSPINNER_INCLUDED

#include <Signals/Signal.h>

#include <SFML/Graphics/RenderWindow.hpp>



namespace prx
{


	class CPUSpinner
	{
		public:
			CPUSpinner(sf::RenderWindow& w);
			Gallant::Signal0<void> SigTick;
			void run();

		private:
			sf::RenderWindow& window;
	};


}


#endif

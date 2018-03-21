#ifndef SCREEN_INCLUDED
#define SCREEN_INCLUDED

#include <SFML/Graphics/RenderWindow.hpp>

#include <Map.hpp>


namespace prx
{


	class Screen
	{
		public:
			Screen(sf::RenderWindow& w, Map& m) : window(w),
			                                      map(m)
			{ }
			void draw();

		private:
			sf::RenderWindow& window;
			Map& map;
	};


}


#endif

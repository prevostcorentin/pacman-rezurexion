#ifndef PATHFINDER_HEADER
#define PATHFINDER_HEADER

#include <vector>

#include <Map.hpp>


namespace prx
{


	namespace PathFinder
	{

		enum Direction GetShortestDirection(sf::Vector2f begin,
		                                    sf::Vector2f end,
		                                    Map&);

	}


}

#endif

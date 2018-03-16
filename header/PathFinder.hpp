#ifndef PATHFINDER_HEADER
#define PATHFINDER_HEADER

#include <vector>

#include <SFML/System.hpp>

#include <Map.hpp>



namespace prx
{


	namespace PathFinder
	{


		sf::Vector2f GetNearestShortestPosition(sf::Vector2f& begin, sf::Vector2f& end, Map&);


	}


}

#endif

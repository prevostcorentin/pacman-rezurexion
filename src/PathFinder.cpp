#include <PathFinder.hpp>
#include <Wall.hpp>


namespace prx
{


	enum Direction
	PathFinder::GetShortestDirection(sf::Vector2f begin, sf::Vector2f end, Map& map) {
		while(end != begin) {
			if(end.x < begin.x)
				return Left;
			else if(end.x > begin.x) 
				return Right;
			if(end.y < begin.y)
				return Up;
			else if(end.y > begin.y)
				return Down;
		}
		return Down;
	}


}

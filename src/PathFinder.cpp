#include <PathFinder.hpp>

#include <Wall.hpp>


namespace prx
{


	sf::Vector2f
	PathFinder::GetNearestShortestPosition(sf::Vector2f& begin, sf::Vector2f& end, Map& map) {
		sf::Vector2f position;
		position.x = begin.x, position.y = begin.y;
		if(end.y < begin.y)
			position.y = position.y - 1;
		else if(end.x < begin.x)
			position.x = position.x - 1;
		else if(end.x > begin.x)
			position.x = position.x + 1;
		else if(end.y > begin.y)
			position.y = position.y + 1;
		return position;
	}


}

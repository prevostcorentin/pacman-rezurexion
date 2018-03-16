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
		ObjectCollection cell = map.getCell(position.x, position.y);
		if(// out of bounds
		   position.x < 0 || position.x >= map.width ||
		   position.y < 0 || position.y >= map.height ||
		   // cell unreachable
		   cell.hasObjectOfType(object_type<Wall>::name()))
		{
			return begin;
		}
		return position;
	}


}

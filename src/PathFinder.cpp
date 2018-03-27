#include <PathFinder.hpp>

#include <Wall.hpp>


namespace prx
{


	const enum DIRECTION
	PathFinder::GetNearestShortestDirection(Object* begin, Object* end, Map& map) {
		sf::Vector2f begin_position = begin->getPosition();
		sf::Vector2f end_position = end->getPosition();
		if(end_position.y > begin_position.y)
			return DIRECTION::DOWN;
		else if(end_position.x < begin_position.x)
			return DIRECTION::LEFT;
		else if(end_position.x > begin_position.x)
			return DIRECTION::RIGHT;
		else if(end_position.y < begin_position.y)
			return DIRECTION::UP;
		return DIRECTION::RIGHT;
	}


}

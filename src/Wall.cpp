#include <Wall.hpp>

namespace prx
{


	Wall::Wall(sf::Vector2f position) : Object(position, "resources/sprites/wall.bmp")
	{ }

	const std::string Wall::getType() {
		return object_type<Wall>::name();
	}


}

#include <Ghost.hpp>


namespace prx
{


	Ghost::Ghost(sf::Vector2f position) : Object(position, "resources/sprites/ghost.bmp")
	{ }

	const std::string Ghost::getType() const {
		return object_type<Ghost>::name();
	}


}

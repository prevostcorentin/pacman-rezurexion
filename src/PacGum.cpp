#include <PacGum.hpp>


namespace prx
{


	PacGum::PacGum(sf::Vector2f position) : Object(position, "resources/sprites/pac-gum.bmp")
	{ }

	const std::string
	PacGum::getType() {
		return object_type<PacGum>::name();
	}


}

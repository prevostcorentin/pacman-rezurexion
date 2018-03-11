#include <Pacman.hpp>


namespace prx
{


	Pacman::Pacman(sf::Vector2f position) : Object(position, "resources/sprites/pacman.bmp")
	{ }

	const std::string
	Pacman::getType() {
		return object_type<Pacman>::name();
	}


}

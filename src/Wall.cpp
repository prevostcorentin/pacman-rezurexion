#include <Wall.hpp>


namespace prx
{


	template<> struct object_type<Wall> {
		static const std::string name() {
			return std::string("wall");
		}
	};


	Wall::Wall(sf::Vector2f position, const enum DIRECTION direction) : Object(position, "resources/sprites/wall.bmp") {
		this->setFrame(direction, 0);
	}

	const
	std::string Wall::getType() {
		return object_type<Wall>::name();
	}


}

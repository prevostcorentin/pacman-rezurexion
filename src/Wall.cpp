#include <Wall.hpp>


namespace prx
{


	template<> struct object_type<Wall> {
		static const std::string name() {
			return std::string("wall");
		}
	};


	Wall::Wall(sf::Vector2f position, const enum DIRECTION direction) : Object(position, "resources/sprites/wall.bmp") {
		this->direction = direction;
		this->setTextureRect(sf::IntRect(0, direction * 32, 32, 32));
	}

	const
	std::string Wall::getType() const {
		return object_type<Wall>::name();
	}


}

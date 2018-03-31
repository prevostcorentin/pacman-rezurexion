#include <Wall.hpp>

#include <Logger.hpp>


namespace prx
{


	Wall::Wall(sf::Vector2f position) : Object("resources/textures/wall.bmp"),
	                                    RectangleShape(sf::Vector2f(32, 32))
	{
		this->setFillColor(sf::Color::Magenta);
		((Object*)(this))->setPosition(position.x * 32, position.y * 32);
		((sf::RectangleShape*)(this))->setPosition(position.x * 32, position.y * 32);
		((sf::RectangleShape*)(this))->setTexture(&this->texture);
	}

	const std::string
	Wall::getType() const {
		return object_type<Wall>::name();
	}


}

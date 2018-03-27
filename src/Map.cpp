#include <Map.hpp>

#include <Logger.hpp>

#include <Wall.hpp>


namespace prx
{


	Map::Map(sf::Vector2f dimensions) : width(dimensions.x),
	                                    height(dimensions.y)
	{ }

	void
	Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		for(auto& object: this->objects->getAllObjects())
			target.draw(*object, states);
	}

	void
	Map::moveObject(Object *object, const enum DIRECTION direction) {
		sf::Vector2f new_position = sf::Vector2f(object->getPosition().x, object->getPosition().y);
		if(direction == DOWN)
			new_position.y = 32 + new_position.y;
		else if(direction == LEFT)
			new_position.x = new_position.x - 32;
		else if(direction == RIGHT)
			new_position.x = 32 + new_position.x;
		else if(direction == UP)
			new_position.y = new_position.y - 32;
		if((new_position.x >= 0 and new_position.y >= 0) and
		   (new_position.x < (this->width * 32) and new_position.y < (this->height * 32)) and
		   (not this->getCell(new_position).hasObjectOfType(object_type<Wall>::name())))
		{
			object->setPosition(new_position.x, new_position.y);
			object->setDirection(direction);
			object->nextFrame();
		}
	}

	ObjectCollection
	Map::getCell(sf::Vector2f position) {
		ObjectCollection objects_at_position;
		for(auto& object: this->objects->getAllObjects()) {
			sf::Vector2f object_position = object->getPosition();
			if(object_position.x == position.x and object_position.y == position.y)
				objects_at_position.add(object);
		}
		return objects_at_position;
	}

	const int
	Map::getHeight() const {
		return this->height;
	}

	const int
	Map::getWidth() const {
		return this->width;
	}

	void
	Map::setObjects(ObjectCollection *objects) {
		this->objects = objects;
	}


}


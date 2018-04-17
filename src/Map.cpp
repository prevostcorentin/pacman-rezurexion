#include <Map.hpp>

#include <Logger.hpp>

#include <Ghost.hpp>
#include <PacGum.hpp>
#include <Pacman.hpp>
#include <Wall.hpp>

#include <fstream>


namespace prx
{


	Map::Map() : objects(new ObjectCollection())
	{ }

	void
	Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		sf::RectangleShape *wall;
		for(auto& object: this->objects->getAllObjects()) {
			if(object->getType() == object_type<Wall>::name()) {
				wall = (sf::RectangleShape*)(Wall*)object;
				target.draw(*wall);
			} else {
				target.draw(*object, states);
			}
		}
	}

	void
	Map::loadFromFile(const char *filepath) {
		std::ifstream fstream(filepath);
		std::string str;
		std::getline(fstream, str);
		// Get dimensions of the map
		const std::size_t separator_position = str.find_last_of(",");
		this->width  = std::atoi(str.substr(0, separator_position).c_str());
		this->height = std::atoi(str.substr(separator_position + 1).c_str());
		// Get needed score to play the map
		std::getline(fstream, str);
		this->score = std::atoi(str.c_str());
		// Place objects on the map
		for(int y=0; y < this->height; y++) {
			std::getline(fstream, str);
			for(int x=0; x < this->width; x++) {
				if(str[x] == '*' or str[x] == 'G')
					this->objects->add(new PacGum(sf::Vector2f(x, y)));
				else if(str[x] == '-' or str[x] == '|' or str[x] == '+') 
					this->objects->add(new Wall(sf::Vector2f(x, y)));
				if(str[x] == 'G')
					this->objects->add(new Ghost(sf::Vector2f(x, y)));
			}
		}
	}

	void
	Map::moveObject(Object *object, const enum DIRECTION direction) {
		sf::Vector2f new_position = object->getPosition();
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
	Map::getCell(sf::Vector2f position) const {
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

	ObjectCollection*
	Map::getObjects() {
		return this->objects;
	}

	const int
	Map::getNeededScore() {
		return this->score;
	}

	const int
	Map::getWidth() const {
		return this->width;
	}


}

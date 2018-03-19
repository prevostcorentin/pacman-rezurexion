#include <Map.hpp>


namespace prx
{


	Map::Map(sf::Vector2f dimensions, ObjectCollection *oc)  : objects(oc),
	                                                           width(dimensions.x),
	                                                           height(dimensions.y)
	{ }

	ObjectCollection
	Map::getCell(int x, int y) {
		ObjectCollection objects_at_position;
		for(auto o: this->objects->getAllObjects()) {
			if(x == o->map_position.x and y == o->map_position.y)
				objects_at_position.add(o);
		}
		return objects_at_position;
	}

	std::vector<Object*>
	Map::getAllCells() {
		return this->objects->getAllObjects();
	}


}

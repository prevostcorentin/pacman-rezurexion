#include <CollisionTracker.hpp>

#include <Logger.hpp>
#include <Object.hpp>


namespace prx
{


	CollisionTracker::CollisionTracker(Map& m) : map(m)
	{ }

	void
	CollisionTracker::dispatchLastCollisions() {
		for(int x=0; x < this->map.width; x++) {
			for(int y=0; y < this->map.height; y++) {
				ObjectCollection objects_at_xy = this->map.getCell(x, y);
				if(objects_at_xy.count() > 1)
					this->SigCollision.Emit(objects_at_xy);
			}
		}
	}

	bool
	CollisionTracker::objectCanMoveTo(Object *o,
	                                  const enum DIRECTION direction)
	{
		if(direction == UP)
			return this->objectCanMoveTo(o, sf::Vector2f(o->map_position.x, o->map_position.y - 1));
		else if(direction == DOWN)
			return this->objectCanMoveTo(o, sf::Vector2f(o->map_position.x, o->map_position.y + 1));
		else if(direction == LEFT)
			return this->objectCanMoveTo(o, sf::Vector2f(o->map_position.x - 1, o->map_position.y));
		else if(direction == RIGHT)
			return this->objectCanMoveTo(o, sf::Vector2f(o->map_position.x + 1, o->map_position.y));
		return false;
	}

	bool
	CollisionTracker::objectCanMoveTo(Object *o,
	                                  const sf::Vector2f& position)
	{
		ObjectCollection objects_on_cell = this->map.getCell(position.x, position.y);
		if((position.x < 0 or position.y < 0) or
		   (position.x >= this->map.width or position.y >= this->map.height) or
		   (objects_on_cell.hasObjectOfType("wall")))
		{
			Logger::Send(Logger::LEVEL::DEBUG, "%s can not move from %v to %v", o->getType().c_str(), o->map_position, position);
			return false;
		} else {
			return true;
		}
	}


}

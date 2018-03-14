#include <CollisionTracker.hpp>

#include <iostream>


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
	                                  const sf::Vector2f& position)
	{
		ObjectCollection objects_on_cell = this->map.getCell(position.x,
		                                                     position.y);
		if((position.x < 0 or position.y < 0) or
		   (position.x >= this->map.width or position.y >= this->map.height) or
		   (objects_on_cell.hasObjectOfType("wall")))
		{
			#ifdef DEBUG
			std::cout << o->getType() << " can not move from [" <<
			             o->map_position.x << ", " << o->map_position.y << "] to [" <<
			             position.x << ", " << position.y << "]" << std::endl;
			#endif
			return false;
		} else {
			return true;
		}
	}


}

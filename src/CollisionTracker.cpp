#include <CollisionTracker.hpp>

#include <Signals.hpp>


namespace prx
{


	void
	CollisionTracker::dispatchLastCollisions() {
		for(int x=0; x < this->map.width; x++) {
			for(int y=0; y < this->map.height; y++) {
				ObjectCollection objects_at_xy = this->map.getCell(x, y);
				if(objects_at_xy.count() > 1)
					Sig::Collision.Emit(objects_at_xy);
			}
		}
	}

	bool
	CollisionTracker::objectCanMoveTo(Object *o, const sf::Vector2f& position) {
		ObjectCollection objects_on_cell = this->map.getCell(position.x, position.y);
		if(objects_on_cell.hasObjectOfType("wall"))
			return false;
		else
			return true;
	}


}

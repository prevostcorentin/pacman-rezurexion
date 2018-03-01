#ifndef COLLISIONTRACKER_INCLUDED
#define COLLISIONTRACKER_INCLUDED

#include <SFML/System/Vector2.hpp>

#include <Map.hpp>


namespace prx
{


	class CollisionTracker
	{
		public:
			CollisionTracker(Map& m) : map(m)
			{ }
			void dispatchLastCollisions();
			bool objectCanMoveTo(Object *o, const sf::Vector2f& position);

		private:
			Map& map;
	};


}


#endif

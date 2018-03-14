#ifndef COLLISIONTRACKER_INCLUDED
#define COLLISIONTRACKER_INCLUDED

#include <Signals/Signal.h>

#include <SFML/System/Vector2.hpp>

#include <Map.hpp>
#include <ObjectCollection.hpp>



namespace prx
{


	class CollisionTracker
	{
		public:
			CollisionTracker(Map& m);
			Gallant::Signal1<ObjectCollection&> SigCollision;
			void dispatchLastCollisions();
			bool objectCanMoveTo(Object *o, const enum Direction);
			bool objectCanMoveTo(Object *o, const sf::Vector2f& position);

		private:
			Map& map;
	};


}


#endif

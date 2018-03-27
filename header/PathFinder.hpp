#ifndef PATHFINDER_HEADER
#define PATHFINDER_HEADER

#include <vector>

#include <SFML/System/Vector2.hpp>

#include <Map.hpp>
#include <Object.hpp>



namespace prx
{


	namespace PathFinder
	{


		const enum DIRECTION GetNearestShortestDirection(Object *begin, Object *end, Map&);


	}


}

#endif

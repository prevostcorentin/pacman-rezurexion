#ifndef WALL_INCLUDED
#define WALL_INCLUDED

#include <Object.hpp>

#include <SFML/System/Vector2.hpp>


namespace prx
{


	class Wall : public Object
	{

		public:
			Wall(sf::Vector2f position, enum DIRECTION);
			const std::string getType();
	};



}


#endif

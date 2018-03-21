#ifndef WALL_INCLUDED
#define WALL_INCLUDED

#include <Object.hpp>

#include <SFML/System/Vector2.hpp>


namespace prx
{


	class Wall : public Object
	{
		public:
			Wall(sf::Vector2f position);
			const std::string getType();
	};

	template<> struct object_type<Wall> {
		static const std::string name() {
			return std::string("wall");
		}
	};


}


#endif

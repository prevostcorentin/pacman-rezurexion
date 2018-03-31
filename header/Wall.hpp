#ifndef WALL_INCLUDED
#define WALL_INCLUDED

#include <Object.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


namespace prx
{

	class Wall : public Object, public sf::RectangleShape
	{

		public:
			Wall(sf::Vector2f position);
			virtual const std::string getType() const;

	};

	template<> struct object_type<Wall> {
		static const std::string name() { return std::string("wall"); }
	};


}


#endif

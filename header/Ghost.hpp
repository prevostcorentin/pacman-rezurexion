#ifndef GHOST_INCLUDED
#define GHOST_INCLUDED

#include <Object.hpp>

#include <string>

#include <SFML/System.hpp>


namespace prx
{


	class Ghost : public Object
	{
		public:
			Ghost(sf::Vector2f position);
			const std::string getType();
	};

	template<> struct object_type<Ghost> {
		static const std::string name() { return std::string("ghost"); }
	};


}


#endif

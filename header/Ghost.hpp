#ifndef GHOST_INCLUDED
#define GHOST_INCLUDED

#include <Object.hpp>

#include <string>

#include <SFML/System/Vector2.hpp>


namespace prx
{


	class Ghost : public Object
	{
		public:
			Ghost(sf::Vector2f position);
			virtual const std::string getType() const;
	};

	template<> struct object_type<Ghost> {
		static const std::string name() { return std::string("ghost"); }
	};


}


#endif

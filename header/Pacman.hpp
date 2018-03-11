#ifndef PACMAN_INCLUDED
#define PACMAN_INCLUDED

#include <Object.hpp>

#include <string>

#include <SFML/System.hpp>


namespace prx
{


	class Pacman : public Object
	{
		public:
			Pacman(sf::Vector2f position);
			const std::string getType();
	};

	template<> struct object_type<Pacman> {
		static const std::string name() { return std::string("pacman"); }
	};


}


#endif

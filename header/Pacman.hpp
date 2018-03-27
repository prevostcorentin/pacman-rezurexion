#ifndef PACMAN_INCLUDED
#define PACMAN_INCLUDED

#include <Object.hpp>

#include <string>

#include <SFML/System/Vector2.hpp>


namespace prx
{


	class Pacman : public Object
	{
		public:
			Pacman(sf::Vector2f position);
			virtual const std::string getType() const;
	};

	template<> struct object_type<Pacman> {
		static const std::string name() { return std::string("pacman"); }
	};


}


#endif

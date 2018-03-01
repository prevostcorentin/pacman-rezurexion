#ifndef PACMAN_INCLUDED
#define PACMAN_INCLUDED

#include <string>

#include <Object.hpp>


namespace prx
{


	class Pacman : public Object
	{
		public:
			Pacman() : Object("resources/sprites/pacman.bmp") { }
			const std::string getType();
	};

	template<> struct object_type<Pacman> {
		static const std::string name() { return std::string("pacman"); }
	};


}


#endif

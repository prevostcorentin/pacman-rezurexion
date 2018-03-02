#ifndef GHOST_INCLUDED
#define GHOST_INCLUDED

#include <string>

#include <Object.hpp>


namespace prx
{


	class Ghost : public Object
	{
		public:
			Ghost() : Object("resources/sprites/ghost.bmp") { }
			const std::string getType();
	};

	template<> struct object_type<Ghost> {
		static const std::string name() { return std::string("ghost"); }
	};


}


#endif

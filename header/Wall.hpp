#ifndef WALL_INCLUDED
#define WALL_INCLUDED

#include <Object.hpp>


namespace prx
{


	class Wall : public Object
	{
		public:
			Wall() : Object("resources/sprites/wall.bmp") { }
			const std::string getType();
	};

	template<> struct object_type<Wall> {
		static const std::string name() {
			return std::string("wall");
		}
	};


}


#endif

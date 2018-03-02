#ifndef PACGUM_INCLUDED
#define PACGUM_INCLUDED

#include <Object.hpp>


namespace prx
{


	class PacGum : public Object
	{
		public:
			PacGum() : Object("resources/sprites/pac-gum.bmp") { }
			const std::string getType();
	};

	template<> struct object_type<PacGum> {
		static const std::string name() { return std::string("pac_gum"); }
	};


}


#endif

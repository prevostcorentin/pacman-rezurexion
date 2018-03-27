#ifndef PACGUM_INCLUDED
#define PACGUM_INCLUDED

#include <Object.hpp>

#include <SFML/System/Vector2.hpp>


namespace prx
{


	class PacGum : public Object
	{
		public:
			PacGum(sf::Vector2f position);
			virtual const std::string getType() const;
	};

	template<> struct object_type<PacGum> {
		static const std::string name() { return std::string("pac_gum"); }
	};


}


#endif

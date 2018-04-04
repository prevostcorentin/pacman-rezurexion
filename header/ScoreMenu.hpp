#ifndef SCOREMENU_INCLUDED
#define SCOREMENU_INCLUDED


#include <Menu.hpp>


namespace prx
{


	namespace GUI
	{


		class ScoreMenu : public GUI::Menu<enum GAME_STATE>
		{

			public:
				ScoreMenu(sf::Font&);

		};


	}


}


#endif

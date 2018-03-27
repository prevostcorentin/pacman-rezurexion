#ifndef MENU_INCLUDED
#define MENU_INCLUDED


#include <GameState.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


namespace prx
{


	namespace GUI
	{


		struct MenuEntry {
			MenuEntry(sf::String text, const enum GAME_STATE _resulting_state) : resulting_state(_resulting_state) {
				this->label.setString(text);
			}
			enum GAME_STATE resulting_state;
			sf::Text label;
		};

		class Menu : public sf::Drawable
		{

			public:
				Menu(sf::Font&);
				virtual ~Menu();
				virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;
				void addEntry(sf::String, const enum GAME_STATE);
				const enum GAME_STATE giveState(sf::RenderWindow&);

			private:
				unsigned int cursor=0;
				sf::Font& font;
				std::vector<struct MenuEntry*> entries;

		};


	}


}


#endif

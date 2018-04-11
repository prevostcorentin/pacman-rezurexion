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

		template<typename RESULT_TYPE>
		struct MenuEntry {
			MenuEntry<RESULT_TYPE>(sf::String text, const RESULT_TYPE result) : result(result) {
				this->label.setString(text);
			}
			RESULT_TYPE result;
			sf::Text label;
		};

		template<typename RESULT_TYPE>
		class Menu : public sf::Drawable
		{

			public:
				Menu<RESULT_TYPE>(sf::Font&);
				virtual ~Menu();
				virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;
				void addEntry(sf::String, const RESULT_TYPE);
				const RESULT_TYPE giveResult(sf::RenderWindow&);

			private:
				unsigned int cursor=0;
				sf::Font& font;
				std::vector<struct MenuEntry<RESULT_TYPE>*> entries;

		};


	}


}


#include "../src/Menu.cpp.tpl"


#endif

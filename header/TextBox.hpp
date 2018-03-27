#ifndef TEXTBOX_INCLUDED
#define TEXTBOX_INCLUDED

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>


namespace prx
{


	namespace GUI
	{


		class InputTextBox : public sf::Drawable
		{

			public:
				InputTextBox(sf::Vector2f position, const char *text, const char *font_filename, sf::Color color);
				~InputTextBox();

				virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
				std::string giveAnswer(sf::RenderWindow&);
				void handleEvent(sf::Event&);
				const bool hasFinished();

				std::string getAnswer();

			private:
				bool finished=false;
				sf::Font font;
				sf::String label;
				sf::Text text;
				std::string answer;

		};


	}


}


#endif

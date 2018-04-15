#ifndef LABEL_DEFINED
#define LABEL_DEFINED

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

#include <sstream>


namespace prx
{


	namespace GUI
	{


		class Label : public sf::Drawable
		{

			public:
				Label(sf::Vector2f position, const std::string text, sf::Font& font);
				virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

			private:
				sf::Vector2f position;
				sf::String string;
				sf::Text text;

		};


	}


}


#endif

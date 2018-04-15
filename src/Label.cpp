#include <Label.hpp>


namespace prx
{


	GUI::Label::Label(sf::Vector2f position, const std::string text, sf::Font& font)
	{
		this->text.setCharacterSize(32);
		this->text.setFillColor(sf::Color::Yellow);
		this->text.setFont(font);
		this->text.setPosition(position);
		this->text.setString(text);
	}

	void
	GUI::Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(this->text);
	}


}

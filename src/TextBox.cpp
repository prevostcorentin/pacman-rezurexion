#include <TextBox.hpp>

#include <Logger.hpp>
#include <iostream>



namespace prx
{


	GUI::InputTextBox::InputTextBox(sf::Vector2f position, const char *text,
	                                const char *font_filename, sf::Color color) : label(text)
	{
		if(not this->font.loadFromFile(font_filename))
			Logger::Send(Logger::LEVEL::ERROR, "Can not open font: pac-font.ttf");

		this->text.setFont(this->font);

		this->text.setCharacterSize(24);
		this->text.setFillColor(color);
		this->text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		this->text.setPosition(0, 0);

		this->label = this->label + " : ";
		this->text.setString(this->label);
	}

	GUI::InputTextBox::~InputTextBox()
	{ }

	void
	GUI::InputTextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(this->text, states);
	}

	std::string
	GUI::InputTextBox::giveAnswer(sf::RenderWindow& window) {
		sf::Event event;
		while(not this->finished)
			while(window.pollEvent(event)) {
				this->handleEvent(event);
				window.clear();
				window.draw(this->text);
				window.display();
			}
		return this->answer;
	}

	const bool
	GUI::InputTextBox::hasFinished() {
		return this->finished;
	}

	void
	GUI::InputTextBox::handleEvent(sf::Event& event) {
		if(event.type == sf::Event::TextEntered) {
			if(event.key.code == 13 && this->answer.size() > 0)     // Return pressed
				this->finished = true;
			else if(event.key.code == 8 && this->answer.size() > 0) // Backspace pressed
				this->answer.pop_back();
			else                                                    // Other characters
				this->answer.push_back((char)event.text.unicode);
			this->text.setString(this->label + sf::String(this->answer));
		}
	}

	std::string
	GUI::InputTextBox::getAnswer() {
		return this->answer;
	}


}

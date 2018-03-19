#include <TextBox.hpp>

#include <Logger.hpp>

#include <SFML/Window/Event.hpp>


namespace prx
{


	GUI::InputTextBox::InputTextBox(sf::Vector2f position, const char *_label,
	                  const char *font_filepath, 
	                  sf::RenderWindow& _window) : label(_label),
	                                               window(_window)
	{
		Logger::Send(Logger::LEVEL::DEBUG, "Loading font %s", font_filepath);
		if(!this->font.loadFromFile(font_filepath))
			Logger::Send(Logger::LEVEL::ERROR, "Can not load font");
		this->text.setFont(this->font);
		this->text.setCharacterSize(24);
		this->text.setColor(sf::Color::Yellow);
		this->text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		this->text.setString(this->text.getString() + " : ");
		this->label = this->label + " : ";
		this->text.setString(this->label);
	}

	void
	GUI::InputTextBox::draw() {
		this->window.clear();
		this->window.draw(this->text);
		this->window.display();
	}

	std::string
	GUI::InputTextBox::getAnswer() {
		sf::Event event;
		bool done = false;
		while(!done)
			while(window.pollEvent(event)) {
				this->draw();
				if(event.type == sf::Event::TextEntered) {
					if(event.key.code == 13 && this->answer.size() > 0)     // Return pressed
						done = true;
					else if(event.key.code == 8 && this->answer.size() > 0) // Backspace pressed
						this->answer.pop_back();
					else                                                    // Other characters
						this->answer.push_back((char)event.text.unicode);
					this->text.setString(this->label + sf::String(this->answer));
					Logger::Send(Logger::LEVEL::DEBUG, "%s", this->text.getString().toAnsiString().c_str());
				}
			}
		return this->answer;
	}


}

#include <Menu.hpp>

#include <Logger.hpp>

#include <SFML/Window/Event.hpp>


namespace prx
{


	GUI::Menu::Menu(sf::Font& _font) : font(_font)
	{ }

	GUI::Menu::~Menu() {
		this->entries.clear();
	}

	void
	GUI::Menu::addEntry(sf::String text, const enum GAME_STATE state) {
		MenuEntry *entry = new MenuEntry(text, state);
		entry->label.setCharacterSize(32);
		entry->label.setFillColor(sf::Color::Yellow);
		entry->label.setFont(this->font);
		entry->label.setOrigin(0, 0);
		entry->label.setPosition(0, entry->label.getCharacterSize() * this->entries.size());
		this->entries.push_back(entry);
	}

	void
	GUI::Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		for(auto& entry: this->entries)
			entry->label.setStyle(sf::Text::Bold);
		this->entries[this->cursor]->label.setStyle(sf::Text::Underlined);
		for(auto& entry: this->entries)
			target.draw(entry->label, states);
	}

	const enum GAME_STATE
	GUI::Menu::giveState(sf::RenderWindow& window) {
		bool done=false;
		sf::Event event;
		enum GAME_STATE new_state;
		while(not done) {
			window.clear();
			window.draw(*this);
			while(window.pollEvent(event)) {
				if(event.type == sf::Event::KeyPressed) {
					if(event.key.code == sf::Keyboard::Z and this->cursor > 0)
						this->cursor = cursor - 1;
					else if(event.key.code == sf::Keyboard::S)
						this->cursor = (1 + this->cursor) % this->entries.size();
					else if(event.key.code == sf::Keyboard::Return)
						done = true, new_state = this->entries[this->cursor]->resulting_state;
				}
			}
			window.display();
		}
		return new_state;
	}


}

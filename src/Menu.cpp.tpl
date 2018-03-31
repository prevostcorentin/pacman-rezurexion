#include <Menu.hpp>

#include <Logger.hpp>

#include <SFML/Window/Event.hpp>


namespace prx
{


	template<typename RESULT_TYPE>
	GUI::Menu<RESULT_TYPE>::Menu(sf::Font& _font) : font(_font)
	{ }

	template<typename RESULT_TYPE>
	GUI::Menu<RESULT_TYPE>::~Menu() {
		this->entries.clear();
	}

	template<typename RESULT_TYPE>
	void
	GUI::Menu<RESULT_TYPE>::addEntry(sf::String text, const RESULT_TYPE state) {
		MenuEntry<RESULT_TYPE> *entry = new MenuEntry<RESULT_TYPE>(text, state);
		entry->label.setCharacterSize(32);
		entry->label.setFillColor(sf::Color::Yellow);
		entry->label.setFont(this->font);
		entry->label.setOrigin(0, 0);
		entry->label.setPosition(0, entry->label.getCharacterSize() * this->entries.size());
		this->entries.push_back(entry);
	}

	template<typename RESULT_TYPE>
	void
	GUI::Menu<RESULT_TYPE>::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		for(auto& entry: this->entries)
			entry->label.setStyle(sf::Text::Bold);
		this->entries[this->cursor]->label.setStyle(sf::Text::Underlined);
		for(auto& entry: this->entries)
			target.draw(entry->label, states);
	}

	template<typename RESULT_TYPE>
	const RESULT_TYPE
	GUI::Menu<RESULT_TYPE>::giveResult(sf::RenderWindow& window) {
		bool done=false;
		sf::Event event;
		RESULT_TYPE result;
		while(not done) {
			window.clear();
			window.draw(*this);
			while(window.pollEvent(event)) {
				if(event.type == sf::Event::KeyPressed) {
					if(event.key.code == sf::Keyboard::Up and this->cursor > 0)
						this->cursor = cursor - 1;
					else if(event.key.code == sf::Keyboard::Down)
						this->cursor = (1 + this->cursor) % this->entries.size();
					else if(event.key.code == sf::Keyboard::Return)
						done = true, result = this->entries[this->cursor]->result;
				}
			}
			window.display();
		}
		return result;
	}


}

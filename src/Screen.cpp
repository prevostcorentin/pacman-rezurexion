#include <Screen.hpp>


namespace prx
{


	void
	Screen::draw() {
		this->window.clear();
		for(auto& o: this->map.getAllCells())
		{
			sf::Sprite *s = o->getSprite();
			s->setPosition(32 * o->map_position.x,
			               32 * o->map_position.y);
			this->window.draw(*s);
		}
		this->window.display();
	}


}

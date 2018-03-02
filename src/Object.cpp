#include <iostream>

#include <Object.hpp>


namespace prx
{


	Object::Object(const char *sprite_sheet_filepath) {
		sf::Color color(255, 255, 255, 255);
		if(!this->image.loadFromFile(sprite_sheet_filepath))
			std::cout << "Unable to load sprite sheet: " << sprite_sheet_filepath << std::endl;
		this->image.createMaskFromColor(color, 0);
		if(!this->texture.loadFromImage(this->image))
			std::cout << "Unable to create texture from " << sprite_sheet_filepath << std::endl;
		this->sprite.setTexture(this->texture);
		this->sprite.setPosition(0, 0);
		// Resizing by half
		this->sprite.setScale(sf::Vector2f(0.5, 0.5));
		this->setFrame(Direction::Right, 0);
	}

	void
	Object::setFrame(enum Direction direction, int n) {
		this->sprite.setTextureRect(sf::IntRect(n * 32, direction * 32,
		                                        32, 32));
	}

	sf::Sprite*
	Object::getSprite() {
		return &this->sprite;
	}


}

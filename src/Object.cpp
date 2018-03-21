#include <Object.hpp>

#include <Logger.hpp>


namespace prx
{


	Object::Object(sf::Vector2f position, const char *sprite_sheet_filepath) {
		this->map_position = position;
		sf::Color color(255, 255, 255, 255);
		if(!this->image.loadFromFile(sprite_sheet_filepath))
			Logger::Send(Logger::LEVEL::ERROR, "Unable to load sprite sheet (%s)", sprite_sheet_filepath);
		this->image.createMaskFromColor(color, 0);
		if(!this->texture.loadFromImage(this->image))
			Logger::Send(Logger::LEVEL::ERROR, "Unable to create texture (%s)", sprite_sheet_filepath);
		this->sprite.setTexture(this->texture);
		this->sprite.setPosition(0, 0);
		this->sprite.setScale(sf::Vector2f(0.5, 0.5)); // Resizing by half
		this->setFrame(DIRECTION::RIGHT, 0);
	}

	void
	Object::move(enum DIRECTION direction) {
		switch(direction) {
			case UP:
				this->map_position.y--;
				break;
			case DOWN:
				this->map_position.y++;
				break;
			case LEFT:
				this->map_position.x--;
				break;
			case RIGHT:
				this->map_position.x++;
				break;
		}
	}

	void
	Object::setFrame(enum DIRECTION direction, int n) {
		this->sprite.setTextureRect(sf::IntRect(n * 32, direction * 32,
		                                        32, 32));
	}

	sf::Sprite*
	Object::getSprite() {
		return &this->sprite;
	}


}

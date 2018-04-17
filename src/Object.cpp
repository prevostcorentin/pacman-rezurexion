#include <Object.hpp>

#include <Logger.hpp>

#include <SFML/System/Vector2.hpp>


namespace prx
{


	Object::Object(const char *texture_filepath)
	{
		sf::Color color(255, 255, 255, 255);
		if(not this->image.loadFromFile(texture_filepath))
			Logger::Send(Logger::LEVEL::ERROR, "Unable to load texture image (%s)", texture_filepath);
		this->image.createMaskFromColor(color, 0);
		if(not this->texture.loadFromImage(this->image))
			Logger::Send(Logger::LEVEL::ERROR, "Unable to create texture (%s)", texture_filepath);
	}

	Object::Object(sf::Vector2f position, const char *sprite_sheet_filepath) {
		sf::Color color(255, 255, 255, 255);
		if(!this->image.loadFromFile(sprite_sheet_filepath))
			Logger::Send(Logger::LEVEL::ERROR, "Unable to load sprite sheet (%s)", sprite_sheet_filepath);
		this->image.createMaskFromColor(color, 0);
		if(!this->texture.loadFromImage(this->image))
			Logger::Send(Logger::LEVEL::ERROR, "Unable to create texture (%s)", sprite_sheet_filepath);
		sf::Vector2u image_size = this->image.getSize();
		this->frames_count = image_size.x / 32;
		this->setPosition(sf::Vector2f(position.x * 32, position.y * 32));
		this->setTexture(this->texture);
		this->setTextureRect(sf::IntRect(0, 0, 32, 32));
	}

	void
	Object::nextFrame() {
		static int frame_index=0;
		if(this->frames_count > 1) {
			this->setTextureRect(sf::IntRect(frame_index * 32, this->direction * 32, 32, 32));
			frame_index = (1 + frame_index) % this->frames_count;
		}
	}

	const enum DIRECTION
	Object::getDirection() {
		return this->direction;
	}

	const std::string 
	Object::getType() const {
		return object_type<Object>::name();
	}

	void
	Object::setDirection(const enum DIRECTION direction) {
		this->direction = direction;
	}


}

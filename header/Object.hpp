#ifndef OBJECT_INCLUDED
#define OBJECT_INCLUDED

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


namespace prx
{

	enum DIRECTION { RIGHT=0, LEFT=1, DOWN=2, UP=3 };

	template<typename T> struct object_type {
		static const char* name() { return "undefined"; }
	};

	class Object
	{

		public:
			Object(sf::Vector2f position, const char *sprite_sheet_filepath);
			void setFrame(const enum DIRECTION direction, int n);
			void move(enum DIRECTION);
			virtual const std::string getType() {
				return object_type<Object>::name();
			}
			sf::Sprite* getSprite();

			sf::Vector2f map_position;

		protected:
			sf::Image image;
			sf::Texture texture;
			sf::Sprite sprite;

	};


}


#endif

#ifndef OBJECT_INCLUDED
#define OBJECT_INCLUDED

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


namespace prx
{


	enum Direction { Right=0, Left=1, Down=2, Up=3 };

	template<typename T> struct object_type {
		const char* name() { return "undefined"; }
	};

	class Object
	{
		public:
			Object(const char *sprite_sheet_filepath);
			void setFrame(enum Direction direction, int n);
			void move(enum Direction);
			virtual const std::string getType() {
				return std::string("undefined"); // object_type<Object>::name();
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

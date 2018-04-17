#ifndef OBJECT_INCLUDED
#define OBJECT_INCLUDED

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


namespace prx
{


	enum DIRECTION { RIGHT=0, LEFT=1, DOWN=2, UP=3 };

	template<typename T> struct object_type {
		static const std::string name() { return std::string("undefined"); }
	};

	class Object : public sf::Sprite
	{

		public:
			Object(const char *texture_filepath);
			Object(sf::Vector2f position, const char *sprite_sheet_filepath);
			void nextFrame();
			const enum DIRECTION getDirection();
			virtual const std::string getType() const;
			void setDirection(const enum DIRECTION);

		protected:
			enum DIRECTION direction=RIGHT;
			sf::Image image;
			sf::Texture texture;
			unsigned int frames_count;

	};


}


#endif

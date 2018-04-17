#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include <Object.hpp>
#include <ObjectCollection.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>


namespace prx
{


	class Map : public sf::Drawable
	{

		public:
			Map();
			virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;
			void loadFromFile(const char *filepath);
			void moveObject(Object*, const enum DIRECTION direction);

			ObjectCollection getCell(sf::Vector2f) const;
			const int getHeight() const;
			ObjectCollection* getObjects();
			const int getNeededScore();
			const int getWidth() const;

		private:
			ObjectCollection *objects;
			int width;
			int height;
			int score;

	};


}


#endif

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
			const int getWidth() const;
			ObjectCollection* getObjects();

		private:
			void placeCorners(std::vector<sf::Vector2f>&);
			ObjectCollection *objects;
			int width;
			int height;
			std::vector<sf::Vector2f> corners;

	};


}


#endif

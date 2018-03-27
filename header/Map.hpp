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
			Map(sf::Vector2f dimensions);
			virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;
			void moveObject(Object*, const enum DIRECTION direction);

			ObjectCollection getCell(sf::Vector2f);
			const int getHeight() const;
			const int getWidth() const;
			void setObjects(ObjectCollection*);

		private:
			ObjectCollection *objects;
			int width;
			int height;

	};


}


#endif

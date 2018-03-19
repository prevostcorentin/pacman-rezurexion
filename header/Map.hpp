#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include <ObjectCollection.hpp>


namespace prx
{


	class Map
	{
		public:
			Map(sf::Vector2f dimensions, ObjectCollection* oc);
			std::vector<Object*> getAllCells();
			ObjectCollection getCell(int x, int y);
			int width;
			int height;

		private:
			ObjectCollection* objects;
	};


}


#endif

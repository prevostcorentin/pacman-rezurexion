#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include <ObjectCollection.hpp>


namespace prx
{


	class Map
	{
		public:
			Map(ObjectCollection* oc);
			std::vector<Object*> getAllCells();
			ObjectCollection getCell(int x, int y);
			const int width = 8;
			const int height = 5;

		private:
			ObjectCollection* objects;
	};


}


#endif

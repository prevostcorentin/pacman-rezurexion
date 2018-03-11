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
			const int width = 16;
			const int height = 16;

		private:
			ObjectCollection* objects;
	};


}


#endif

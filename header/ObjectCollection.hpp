#ifndef OBJECTCOLLECTION_INCLUDED
#define OBJECTCOLLECTION_INCLUDED

#include <string>

#include <Object.hpp>


namespace prx
{


	class ObjectCollection
	{
		public:
			ObjectCollection() { }
			void add(Object *o);
			Object* get(int n);
			std::vector<Object*> getAllObjects();
			const size_t count();
			bool hasObjectOfType(std::string _typename);
			std::vector<Object*> getObjectsOfType(std::string _typename);
			void erase(Object *o);
			void clear();

		private:
			std::vector<Object*> objects;
	};


}


#endif

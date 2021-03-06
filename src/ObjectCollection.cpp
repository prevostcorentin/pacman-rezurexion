#include <ObjectCollection.hpp>

#include <Logger.hpp>


namespace prx
{


	void
	ObjectCollection::add(Object* o) {
		objects.push_back(o);
	}

	Object*
	ObjectCollection::get(int n) {
		return this->objects[n];
	}

	std::vector<Object*>
	ObjectCollection::getAllObjects() {
		return this->objects;
	}

	const size_t
	ObjectCollection::count() {
		return this->objects.size();
	}

	bool
	ObjectCollection::hasObjectOfType(std::string _typename) {
		return std::find_if(this->objects.begin(), this->objects.end(),
		                    [_typename](Object *o) {
		                        return o->getType() == _typename;
		                    }) != this->objects.end();
	}

	std::vector<Object*>
	ObjectCollection::getObjectsOfType(std::string _typename) {
		std::vector<Object*> objects_of_type;
		std::vector<Object*>::iterator object_iterator_position = this->objects.begin();
		while((object_iterator_position = std::find_if(object_iterator_position, this->objects.end(),
		      [_typename](Object *o) {
		          return o->getType() == _typename;
		      })) != this->objects.end())
		{
			objects_of_type.push_back(*object_iterator_position);
			object_iterator_position++;
		}
		return objects_of_type;
	}

	void
	ObjectCollection::erase(Object *o) {
		const std::vector<Object*>::iterator object_iterator_position = std::find(this->objects.begin(), this->objects.end(), o);
		if(object_iterator_position != this->objects.end())
			this->objects.erase(object_iterator_position);
		else
			Logger::Send(Logger::LEVEL::ERROR, "Can not erase: %s@%p does not exist", o->getType().c_str(), o);
	}

	void
	ObjectCollection::clear() {
		this->objects.clear();
	}


}

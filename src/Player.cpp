#include <iostream>

#include <Player.hpp>


namespace prx
{


	Player::Player() : id(-1),
	                   name("undefined")
	{ }

	Player::Player(const char *_name) : id(-1),
	                                    name(_name)
	{ }

	Player::Player(const int _id, const char *_name) : id(_id),
	                                                   name(_name)
	{ }

	int
	Player::getScore() {
		return this->score;
	}

	void
	Player::setScore(const int score) {
		this->score = score;
	}

	const char *
	Player::getName() {
		return this->name.c_str();
	}

	const int
	Player::getId() {
		return this->id;
	}

	void
	Player::setId(const int id) {
		if(this->id > -1)
			return;
		this->id = id;
	}

	void
	Player::setName(const char *name) {
		this->name = name;
	}


}

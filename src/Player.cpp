#include <Player.hpp>


namespace prx
{


	Player::Player() : pacman(new Pacman(sf::Vector2f(0, 0))),
	                   id(-1),
	                   name("undefined")
	{ }

	Player::~Player() {
		delete this->pacman;
	}

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

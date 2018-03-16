#include <iostream>

#include <Game.hpp>
#include <PathFinder.hpp>
#include <Logger.hpp>
#include <MapLoader.hpp>


namespace prx
{


	void _makeTmpMap(ObjectCollection& objects) {
		/* Temporary map must be this (width:8, height:5):
		 *    01234567
		 *   0P*******
		 *   1*------*
		 *   2******|*
		 *   3*----*|G
		 *   4********
		 */
		// Place walls
		Wall *wall = nullptr;
		for(int x=1; x < 7; x++) {
			wall = new Wall();
			wall->map_position = sf::Vector2f(x, 1);
			objects.add(wall);
		}
		wall = new Wall();
		wall->map_position = sf::Vector2f(6, 2);
		objects.add(wall);
		wall = new Wall();
		wall->map_position = sf::Vector2f(6, 3);
		objects.add(wall);
		for(int x=1; x < 5; x++) {
			wall = new Wall();
			wall->map_position = sf::Vector2f(x, 3);
			objects.add(wall);
		}
		// Place pac-gums
		PacGum *gum = nullptr;
		for(int x=1; x < 8; x++) {
			gum = new PacGum();
			gum->map_position = sf::Vector2f(x, 0);
			objects.add(gum);
		}
		for(int x=0; x < 8; x++) {
			gum = new PacGum();
			gum->map_position = sf::Vector2f(x, 4);
			objects.add(gum);
		}
		for(int y=1; y < 5; y++) {
			gum = new PacGum();
			gum->map_position = sf::Vector2f(0, y);
			objects.add(gum);
		}
		for(int x=0; x < 6; x++) {
			gum = new PacGum();
			gum->map_position = sf::Vector2f(x, 2);
			objects.add(gum);
		}
		gum = new PacGum();
		gum->map_position = sf::Vector2f(5, 3);
		objects.add(gum);
		gum = new PacGum();
		gum->map_position = sf::Vector2f(7, 0);
		objects.add(gum);
		gum = new PacGum();
		gum->map_position = sf::Vector2f(7, 1);
		objects.add(gum);
		gum = new PacGum();
		gum->map_position = sf::Vector2f(7, 2);
		objects.add(gum);
		gum = new PacGum();
		gum->map_position = sf::Vector2f(7, 4);
		objects.add(gum);
		// Place ghost
		Ghost *ghost = new Ghost();
		ghost->map_position = sf::Vector2f(7, 3);
		objects.add(ghost);
	}

	Game::Game(sf::ContextSettings context) : window(sf::VideoMode(640, 480),
	                                                 GAME_TITLE,
	                                                 sf::Style::Default,
	                                                 context),
	                                          objects(GetGameObjectsFromFilename("resources/map/simple.map")),
	                                          map(objects),
	                                          screen(window, map),
	                                          spinner(window),
	                                          collision_tracker(map)
	{
		this->state = Init;
		// Connect signals to handlers
		this->collision_tracker.SigCollision.Connect(this, &Game::handleCollision);
		this->keyboard.SigPlayerMove.Connect(this, &Game::handlePlayerMove);
		this->keyboard.SigQuit.Connect(this, &Game::handleQuit);
		this->SigQuit.Connect(this, &Game::handleQuit);
		this->spinner.SigTick.Connect(this, &Game::handleUpdate);
		this->player.pacman.map_position = sf::Vector2f(0, 0);
		// Adding player to game
		this->objects->add(this->player.pacman);
		this->window.setActive();
	}

	void
	Game::launch() {
		this->initPlayer();
		this->state = Running;
		while(this->window.isOpen())
			spinner.run();
		std::exit(EXIT_FAILURE);
	}

	void
	Game::initPlayer() {
		std::string choosen_name;
		std::cout << "Player name:";
		std::cin >> choosen_name;
		this->player.setName(choosen_name.c_str());
		if(not this->database.playerExists(this->player))
			this->database.createPlayer(this->player);
		else
			this->database.refreshPlayer(this->player);
	}

	void
	Game::handleCollision(ObjectCollection& objects) {
		for(auto& o: objects.getAllObjects()) {
			Logger::Send(Logger::LEVEL::DEBUG, "%s has collided at (%d, %d)", o->getType(),
			                                                                  o->map_position.x,
			                                                                  o->map_position.y);
		}
		if(objects.hasObjectOfType("pacman")) {
			if(objects.hasObjectOfType("pac_gum")) {
				for(auto& gum: objects.getObjectsOfType("pac_gum")) {
					this->player.setScore(1 + this->player.getScore());
					this->objects->erase(gum);
				}
			} else if(objects.hasObjectOfType("ghost")) {
				Logger::Send(Logger::LEVEL::INFO, "%s dies with %d pac-gum(s) eaten", this->player.getName(),
				                                                         this->player.getScore());
				Logger::Send(Logger::LEVEL::INFO, "%s has now %d", this->player.getName(),
				                                                   this->database.getTotalScore(this->player));
				this->objects->erase(this->player.pacman);
				this->SigQuit.Emit();
			}
		}
	}

	void
	Game::handleUpdate() {
		this->keyboard.dispatchLastMoves();
		for(auto& ghost: this->objects.getObjectsOfType(object_type<Ghost>::name()))
			ghost->map_position =
				PathFinder::GetNearestShortestPosition(
					ghost->map_position,
					this->player.pacman.map_position,
					this->map
				);
		this->collision_tracker.dispatchLastCollisions();
		this->screen.draw();
	}

	void
	Game::handleQuit() {
		this->database.insertScore(this->player);
		std::cout << "Quitting game" << std::endl;
		window.close();
		std::exit(EXIT_SUCCESS);
	}

	void
	Game::handlePlayerMove(enum Direction direction)
	{
		sf::Vector2f new_position;
		switch(direction) {
			case Right:
				new_position = sf::Vector2f(this->player.pacman->map_position.x + 1,
				                            this->player.pacman->map_position.y);
			break;
			case Left:
				new_position = sf::Vector2f(this->player.pacman->map_position.x - 1,
				                            this->player.pacman->map_position.y);
			break;
			case Down:
				new_position = sf::Vector2f(this->player.pacman->map_position.x,
				                            this->player.pacman->map_position.y + 1);
			break;
			case Up:
				new_position = sf::Vector2f(this->player.pacman->map_position.x,
				                            this->player.pacman->map_position.y - 1);
			break;
		}
		if(this->collision_tracker.objectCanMoveTo(this->player.pacman,
		                                           new_position))
		{
			this->player.pacman->map_position = new_position;
		}
	}


}

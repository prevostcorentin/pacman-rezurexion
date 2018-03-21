#include <Game.hpp>

#include <Ghost.hpp>
#include <Logger.hpp>
#include <MapLoader.hpp>
#include <PathFinder.hpp>
#include <TextBox.hpp>


#define MAP_FILENAME "resources/map/simple.map"


namespace prx
{


	Game::Game(sf::ContextSettings context) : window(sf::VideoMode(640, 480),
	                                                 GAME_TITLE,
	                                                 sf::Style::Default,
	                                                 context),
	                                          objects(GetGameObjectsFromFilename(MAP_FILENAME)),
	                                          map(GetDimensionsFromFilename(MAP_FILENAME), objects),
	                                          screen(window, map),
	                                          spinner(window),
	                                          collision_tracker(map)
	{
		this->state = INIT;

		this->collision_tracker.SigCollision.Connect(this, &Game::handleCollision);
		this->keyboard.SigPlayerMove.Connect(this, &Game::handlePlayerDirectionUpdate);
		this->keyboard.SigQuit.Connect(this, &Game::handleQuit);
		this->SigQuit.Connect(this, &Game::handleQuit);
		this->spinner.SigTick.Connect(this, &Game::handlePlayerMove);
		this->spinner.SigTick.Connect(this, &Game::handleUpdate);
		this->player.pacman->map_position = sf::Vector2f(0, 0);

		this->player.direction = RIGHT;
		this->objects->add(this->player.pacman);
		this->window.setActive();
	}

	void
	Game::launch() {
		this->initPlayer();
		this->state = RUNNING;
		while(this->window.isOpen())
			spinner.run();
		std::exit(EXIT_FAILURE);
	}

	void
	Game::handlePlayerMove() {
		sf::Vector2f new_position;
		if(this->player.direction == RIGHT)
			new_position = sf::Vector2f(this->player.pacman->map_position.x + 1, this->player.pacman->map_position.y);
		else if(this->player.direction == LEFT)
			new_position = sf::Vector2f(this->player.pacman->map_position.x - 1, this->player.pacman->map_position.y);
		else if(this->player.direction == DOWN)
			new_position = sf::Vector2f(this->player.pacman->map_position.x, this->player.pacman->map_position.y + 1);
		else if(this->player.direction == UP)
			new_position = sf::Vector2f(this->player.pacman->map_position.x, this->player.pacman->map_position.y - 1);
		this->player.nextFrame();
		if(this->collision_tracker.objectCanMoveTo(this->player.pacman, new_position))
			this->player.pacman->map_position = new_position;
	}

	void
	Game::initPlayer() {
		GUI::InputTextBox name_box(sf::Vector2f(0, 0), "Player name",
		                           "resources/font/pac-font.ttf", this->window);
		std::string name(name_box.getAnswer());
		this->player.setName(name.c_str());
		if(not this->database.playerExists(this->player))
			this->database.createPlayer(this->player);
		else
			this->database.refreshPlayer(this->player);
	}

	void
	Game::handleCollision(ObjectCollection& objects) {
		if(objects.hasObjectOfType("pacman")) {
			if(objects.hasObjectOfType("pac_gum")) {
				for(auto& gum: objects.getObjectsOfType("pac_gum")) {
					this->player.setScore(1 + this->player.getScore());
					this->objects->erase(gum);
				}
			}
			if(objects.hasObjectOfType("ghost")) {
				this->objects->erase(this->player.pacman);
				this->SigQuit.Emit();
			}
		}
	}

	void
	Game::handleUpdate() {
		sf::Vector2f new_position;
		this->keyboard.dispatchLastMoves();
		this->updateGhostsPaths();
		this->collision_tracker.dispatchLastCollisions();
		this->screen.draw();
	}

	void
	Game::updateGhostsPaths() {
		sf::Vector2f new_position;
		for(auto& ghost: this->objects->getObjectsOfType(object_type<Ghost>::name())) {
			new_position = PathFinder::GetNearestShortestPosition(ghost->map_position, this->player.pacman->map_position, this->map);
			if(this->collision_tracker.objectCanMoveTo(ghost, new_position))
				ghost->map_position = new_position;
		}
	}

	void
	Game::handleQuit() {
		this->database.insertScore(this->player);
		Logger::Send(Logger::LEVEL::INFO, "%s has now %d pac-gums eaten",
		                                  this->player.getName(),
		                                  this->database.getTotalScore(this->player));
		Logger::Send(Logger::LEVEL::INFO, "Quitting game ...");
		window.close();
		std::exit(EXIT_SUCCESS);
	}

	void
	Game::handlePlayerDirectionUpdate(const enum DIRECTION direction) {
		sf::Vector2f new_position;
		this->player.direction = direction;
	}


}

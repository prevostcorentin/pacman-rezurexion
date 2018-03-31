#include <Game.hpp>
#include <Wall.hpp>

#include <Ghost.hpp>
#include <Logger.hpp>
#include <MapLoader.hpp>
#include <PathFinder.hpp>
#include <TextBox.hpp>
#include <iostream>

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <iostream>


#define MAP_FILENAME "resources/map/corner_test.map"


namespace prx
{


	Game::Game(sf::ContextSettings context, sf::Font& font) : window(sf::VideoMode(640, 480),
	                                                             GAME_TITLE,
	                                                             sf::Style::Default,
	                                                             context),
	                                                         map(MAP_FILENAME),
	                                                         start_menu(font)
	{
		this->state = INIT;

		this->objects = this->map.getObjects();
		this->objects->add(this->player.pacman);

		this->start_menu.addEntry(sf::String("Play"), RUNNING);
		this->start_menu.addEntry(sf::String("Scores"), ERROR);
		this->start_menu.addEntry(sf::String("Quit"), STOPPED);
	}

	void
	Game::launch() {
		this->window.setActive();
		this->state = STARTING;
		while(this->state != STOPPED and this->window.isOpen()) {
			this->updateGame();
			sf::sleep(sf::milliseconds(120));
		}
	}

	void
	Game::updateGame() {
		if(this->state == RUNNING) {
			this->turn();
			this->window.clear();
			this->window.draw(this->map);
			this->window.display();
		} else if(this->state == STARTING) {
			this->state = this->start_menu.giveState(this->window);
			if(this->state == RUNNING)
				this->initPlayer();
		}
	}

	void
	Game::turn() {
		static enum DIRECTION pacman_direction=RIGHT;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			pacman_direction = DIRECTION::DOWN;
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			pacman_direction = DIRECTION::LEFT;
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			pacman_direction = DIRECTION::RIGHT;
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			pacman_direction = DIRECTION::UP;
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->state = GAME_STATE::STOPPED;

		this->map.moveObject(this->player.pacman, pacman_direction);
		for(auto& ghost: this->objects->getObjectsOfType(object_type<Ghost>::name()))
			this->map.moveObject(ghost, PathFinder::GetNearestShortestDirection(ghost, this->player.pacman, this->map));

		ObjectCollection objects_at_pacman_position = this->map.getCell(this->player.pacman->getPosition());
		if(objects_at_pacman_position.hasObjectOfType(object_type<PacGum>::name())) {
			for(auto& pac_gum: objects_at_pacman_position.getObjectsOfType(object_type<PacGum>::name())) {
				this->player.setScore(this->player.getScore() + 1);
				this->objects->erase(pac_gum);
			}
		}
		if(objects_at_pacman_position.hasObjectOfType(object_type<Ghost>::name()))
			this->state = STOPPED;
	}

	void
	Game::initPlayer() {
		GUI::InputTextBox name_box(sf::Vector2f(0, 0), "Player name", "resources/font/pac-font.ttf", sf::Color::Yellow);
		std::string name = name_box.giveAnswer(this->window);

		this->player.setName(name.c_str());
		if(not this->database.playerExists(this->player))
			this->database.createPlayer(this->player);
		else
			this->database.refreshPlayer(this->player);
	}

	void
	Game::quit() {
		if(this->window.isOpen())
			window.close();
		this->database.insertScore(this->player);
		delete this->objects;
		Logger::Send(Logger::LEVEL::INFO, "%s has now %d pac-gums eaten",
		                                  this->player.getName(),
		                                  this->database.getTotalScore(this->player));
		Logger::Send(Logger::LEVEL::INFO, "Quitting game ...");
		this->state = STOPPED;
	}


}

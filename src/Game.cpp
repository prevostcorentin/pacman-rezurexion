#include <Game.hpp>
#include <Wall.hpp>

#include <Ghost.hpp>
#include <Label.hpp>
#include <Logger.hpp>
#include <PathFinder.hpp>
#include <TextBox.hpp>
#include <iostream>

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <iostream>
#include <sstream>


namespace prx
{


	Game::Game(sf::ContextSettings context, sf::Font& _font) : font(_font),
	                                                           spinner(SPIN_DELAY),
	                                                           window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
	                                                                  GAME_TITLE,
	                                                                  sf::Style::Default,
	                                                                  context),
	                                                           map_choosing_menu(font),
	                                                           score_menu(font),
	                                                           start_menu(font)
	{
		this->state = INIT;

		this->objects = this->map.getObjects();

		this->start_menu.addEntry(sf::String("Play"), RUNNING);
		this->start_menu.addEntry(sf::String("Scores"), SHOW_SCORES);
		this->start_menu.addEntry(sf::String("Quit"), STOPPED);

		std::ostringstream string_stream;
		for(auto& player_score: this->database.getAllScores()) {
			string_stream.str(std::string());
			string_stream << player_score.first << "\t" << player_score.second;
			this->score_menu.addEntry(string_stream.str(), GAME_STATE::SHOW_SCORES);
		}
		this->score_menu.addEntry("Return", GAME_STATE::STARTING);
	}

	void
	Game::launch() {
		this->window.setActive();
		this->state = STARTING;
		while(this->state != STOPPED and this->window.isOpen())
			this->updateGame();
		this->quit();
	}

	void
	Game::updateGame() {
		if(this->state == RUNNING) {
			this->turn();
			if(not this->objects->hasObjectOfType(object_type<PacGum>::name()))
				this->state = GAME_ENDED;
			this->window.clear();
			this->window.draw(this->map);
			this->window.display();
		} else if(this->state == STARTING) {
			this->objects->clear();
			this->objects->add(this->player.pacman);
			this->handleMainMenu();
		} else if(this->state == SHOW_SCORES) {
			this->state = this->score_menu.giveResult(this->window);
		} else if(this->state == GAME_ENDED) {
			this->handleEnd();
		}
	}

	void
	Game::turn() {
		enum DIRECTION pacman_direction=this->player.pacman->getDirection();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			pacman_direction = DIRECTION::DOWN;
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			pacman_direction = DIRECTION::LEFT;
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			pacman_direction = DIRECTION::RIGHT;
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			pacman_direction = DIRECTION::UP;
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->state = GAME_STATE::STOPPED;
		if(this->spinner.nextTickMustIterate()) {
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
				this->state = GAME_ENDED;
		}
	}

	void
	Game::handleMainMenu() {
		this->state = this->start_menu.giveResult(this->window);
		if(this->state == RUNNING) {
			this->initPlayer();
			const std::string filepath = this->map_choosing_menu.giveResult(this->window);
			if(filepath.size() > 0) {
				this->map.loadFromFile(filepath.c_str());
				this->objects = this->map.getObjects();
				if(this->database.getTotalScore(this->player) >= map.getNeededScore())
					this->state = RUNNING;
				else
					this->state = STARTING;
			} else {
				this->state = STARTING;
			}
		}
	}

	void
	Game::initPlayer() {
		GUI::InputTextBox name_box(sf::Vector2f(0, 0), "Player name", "resources/font/arcade-classic.ttf", sf::Color::Yellow);
		std::string name = name_box.giveAnswer(this->window);

		this->player.setName(name.c_str());
		if(not this->database.playerExists(this->player))
			this->database.createPlayer(this->player);
		else
			this->database.refreshPlayer(this->player);
	}

	void
	Game::handleEnd() {
		std::ostringstream text;
		text << this->player.getName() << " has died with " << this->player.getScore() << std::endl <<
		       "Press Return to quit";
		GUI::Label label(sf::Vector2f(0, 0), text.str(), this->font);
		this->window.clear();
		this->window.draw(label);
		this->window.display();
		while(not sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		; // block execution
		this->state = STOPPED;
	}

	void
	Game::quit() {
		if(this->window.isOpen())
			window.close();
		if(this->player.getId() != -1)
			this->database.insertScore(this->player);
		delete this->objects;
		this->state = STOPPED;
		this->database.close();
	}


}

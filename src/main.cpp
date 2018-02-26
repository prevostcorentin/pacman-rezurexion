#include <cstdlib>
#include <exception>
#include <iostream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <Signals/Delegate.h>
#include <Signals/Signal.h>


#define GAME_TITLE "Pacman Rezurexion"


namespace prx
{
	
	
	enum Direction { Down, Left, Right, Up };
	namespace Sig
	{
		
		
		Gallant::Signal0<void> Tick;
		Gallant::Signal0<void> Quit;
		Gallant::Signal1<enum Direction> PlayerMove;
		
		
	}
	
	struct Player
	{
		Player() {
			this->texture.loadFromFile("resources/pacman_sprite.bmp");
			sprite.setTexture(texture);
		}
		sf::Texture texture;
		sf::Sprite sprite;
	};
	
	struct Keyboard
	{
		Keyboard() { }
		void dispatchLastMoves() {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				Sig::Quit.Emit();
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				Sig::PlayerMove.Emit(Direction::Down);
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				Sig::PlayerMove.Emit(Direction::Left);
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				Sig::PlayerMove.Emit(Direction::Right);
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				Sig::PlayerMove.Emit(Direction::Up);
		}
	};
	
	struct CPUSpinner
	{
		CPUSpinner(sf::RenderWindow& w) : window(w)
		{ }
		void run() {
			sf::Event event;
			while(window.pollEvent(event))
				Sig::Tick.Emit();
		}
		sf::Clock clock;
		sf::RenderWindow& window;
	};
	
	struct Screen
	{
		Screen(sf::RenderWindow& w) : window(w) { }
		void draw() {
			this->window.clear();
			//this->window.draw();
			this->window.display();
		}
		sf::RenderWindow& window;
	};
	
	enum GameState { Init, Running, Error, Stopped };
	
	struct Game
	{
		Game(sf::ContextSettings context) : window(sf::VideoMode(640, 480),
		                                           GAME_TITLE,
		                                           sf::Style::Default,
		                                           context),
		                                    screen(window),
		                                    spinner(window)
		{
			this->state = Init;
			Sig::PlayerMove.Connect(this, &Game::move);
			Sig::Quit.Connect(this, &Game::quit);
			Sig::Tick.Connect(this, &Game::update);
			this->window.setActive();
		}
		void launch() {
			this->state = Running;
			while(this->window.isOpen())
				spinner.run();
		}
		void update() {
			this->keyboard.dispatchLastMoves();
			this->screen.draw();
		}
		void quit() {
			std::cout << "Quitting game" << std::endl;
			window.close();
			std::exit(EXIT_SUCCESS);
		}
		void move(enum Direction direction)
		{
			std::cout << "player has moved" << std::endl;
		}
		enum GameState state;
		Keyboard keyboard;
		sf::RenderWindow window;
		Screen screen;
		CPUSpinner spinner;
		Player player;
	};
	
	
}


int main()
{
	sf::ContextSettings context;
	context.depthBits = 24;
	try {
		prx::Game game(context);
		game.launch();
	} catch (std::exception e) {
		std::cout << "Unexpected exception" << std::endl;
	}
	
	return EXIT_SUCCESS;
}

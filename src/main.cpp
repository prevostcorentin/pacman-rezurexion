#include <exception>
#include <iostream>

#include <SFML/Window.hpp>
#include <Signals/Delegate.h>
#include <Signals/Signal.h>


namespace pr
{


	namespace Sig 
	{


		Gallant::Signal0<void> Quit;


	}

	struct Spinner
	{
		void run(sf::Event& event) {
			if(event.type == sf::Event::KeyPressed) {
				switch(event.key.code) {
					case sf::Keyboard::Escape:
						std::cout << "Quitting game" << std::endl;
						Sig::Quit.Emit();
					break;
					default:
						std::cout << "No behaviour for touch " << event.key.code << std::endl;
					break;
				}
			}
		}
	};

	struct Game
	{
		Game(sf::ContextSettings context) : window(sf::VideoMode(640, 480),
		                                           "Pacman Rezurexion", 
		                                           sf::Style::Default,
		                                           context)
		{
			Sig::Quit.Connect(this, &Game::quit);
			window.setActive();
		}
		void launch() {
			while(window.isOpen()) {
				sf::Event event;
				while(window.pollEvent(event)) {
					if(event.type == sf::Event::Closed)
						Sig::Quit.Emit();
					else
						spinner.run(event);
				}
			}
		}
		void quit() {
			window.close();
		}
		Spinner spinner;
		sf::Window window;
	};


}


int main()
{
	sf::ContextSettings context;
	context.depthBits = 32;
	try {
		pr::Game game(context);
		game.launch();
	} catch (std::exception e) {
		std::cout << "Unexpected exception" << std::endl;
	}

	return EXIT_SUCCESS;
}

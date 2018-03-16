#include <exception>
#include <iostream>

#include <SFML/Window.hpp>

#include <Signals/Delegate.h>

#include <Game.hpp>



int main(int argc, char *argv[])
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


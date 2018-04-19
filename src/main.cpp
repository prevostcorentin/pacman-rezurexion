#include <Game.hpp>

#include <Logger.hpp>

#include <exception>
#include <iostream>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/ContextSettings.hpp>


int main(int argc, char *argv[])
{
	sf::Font font;
	sf::ContextSettings context;
	if(not font.loadFromFile("resources/font/pac-font.ttf"))
		prx::Logger::Send(prx::Logger::LEVEL::ERROR, "Can not load font");
	context.depthBits = 24;
	try {
		prx::Game game(context, font);
		game.launch();
	} catch (std::exception e) {
		std::cout << "Unexpected exception" << std::endl;
	}
	return EXIT_SUCCESS;
}


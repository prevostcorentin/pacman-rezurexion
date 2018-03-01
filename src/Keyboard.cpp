#include <SFML/Window/Keyboard.hpp>

#include <Keyboard.hpp>
#include <Signals.hpp>


namespace prx
{


	void
	Keyboard::dispatchLastMoves()
	{
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


}

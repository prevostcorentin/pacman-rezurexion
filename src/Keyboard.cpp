#include <SFML/Window/Keyboard.hpp>

#include <Keyboard.hpp>
#include <Signals.hpp>


namespace prx
{


	void
	Keyboard::dispatchLastMoves()
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->SigQuit.Emit();
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			this->SigPlayerMove.Emit(Direction::Down);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			this->SigPlayerMove.Emit(Direction::Left);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			this->SigPlayerMove.Emit(Direction::Right);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			this->SigPlayerMove.Emit(Direction::Up);
	}


}

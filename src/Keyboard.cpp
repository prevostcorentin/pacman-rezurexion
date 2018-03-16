#include <SFML/Window/Keyboard.hpp>

#include <Keyboard.hpp>


namespace prx
{


	void
	Keyboard::dispatchLastMoves() {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->SigQuit.Emit();
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			this->SigPlayerMove.Emit(DIRECTION::DOWN);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			this->SigPlayerMove.Emit(DIRECTION::LEFT);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			this->SigPlayerMove.Emit(DIRECTION::RIGHT);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			this->SigPlayerMove.Emit(DIRECTION::UP);
	}


}

#include <SFML/System/Sleep.hpp>
#include <SFML/Window/Event.hpp>

#include <CPUSpinner.hpp>


namespace prx
{

	CPUSpinner::CPUSpinner(sf::RenderWindow& w) : window(w)
	{ }

	void
	CPUSpinner::run() {
		sf::Event event;
		while(this->window.pollEvent(event)) {
			this->SigTick.Emit();
			sf::sleep(sf::milliseconds(60));
		}
	}


}

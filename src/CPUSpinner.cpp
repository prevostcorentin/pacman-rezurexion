#include <CPUSpinner.hpp>

#include <Signals.hpp>


namespace prx
{


	void
	CPUSpinner::run() {
		sf::Event event;
		while(this->window.pollEvent(event)) {
			Sig::Tick.Emit();
			sf::sleep(sf::milliseconds(60));
		}
	}


}

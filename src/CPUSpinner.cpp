#include <SFML/System/Sleep.hpp>
#include <SFML/Window/Event.hpp>

#include <CPUSpinner.hpp>


namespace prx
{


	CPUSpinner::CPUSpinner(sf::RenderWindow& w) : window(w)
	{ }

	void
	CPUSpinner::run() {
		this->SigTick.Emit();
		sf::sleep(sf::milliseconds(120));
	}


}

#include <CPUSpinner.hpp>


namespace prx
{


	CPUSpinner::CPUSpinner(const int delay) {
		this->delay = sf::milliseconds(delay);
	}

	bool
	CPUSpinner::nextTickMustIterate() {
		this->elapsed_time = this->clock.getElapsedTime();
		if(this->elapsed_time >= this->delay) {
			this->elapsed_time = sf::milliseconds(0);
			this->clock.restart();
			return true;
		}
		return false;
	}


}

#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include <string>

#include <Pacman.hpp>


namespace prx
{


	class Player
	{
		public:
			Player() : name("unknown") { }
			int getScore();
			void setScore(const int score);
			Pacman pacman;
		private:
			int score = 0;
			std::string name;
	};


}



#endif

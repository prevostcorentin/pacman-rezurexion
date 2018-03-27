#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include <string>

#include <Pacman.hpp>


namespace prx
{


	class Player
	{
		public:
			Player();
			const int getId();
			const char* getName();
			int getScore();
			void setId(const int);
			void setName(const char*);
			void setScore(const int score);

			Pacman* pacman;

		private:
			int id;
			int score = 0;
			std::string name;
	};


}



#endif

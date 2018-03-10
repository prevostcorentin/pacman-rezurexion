#ifndef DATABASE_INCLUDED
#define DATABASE_INCLUDED

#include <sqlite3/sqlite3.h>

#include <Player.hpp>


namespace prx
{


	class Database
	{
		public:
			Database();
			~Database();
			void createPlayer(Player&);
			bool playerExists(Player&);
			void insertScore(Player&);
			Player getPlayer(const char *name);
			int getTotalScore(Player&);

		private:
			void execute(const char *sql_request);
			sqlite3 *database;
			char *error_message = nullptr;
	};


}

#endif

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include <Database.hpp>


namespace prx
{


	Database::Database() {
		sqlite3_initialize();
		if(sqlite3_open("score.db", &this->database)) {
			std::cout << "Cannot open score database: " << sqlite3_errmsg(this->database) << std::endl;
		}
		this->execute("CREATE TABLE IF NOT EXISTS PLAYER(" \
		                 "PLAYER_ID INTEGER PRIMARY KEY AUTOINCREMENT," \
		                 "NAME      TEXT                NOT NULL);");
		this->execute("CREATE TABLE IF NOT EXISTS SCORE(" \
		                 "SCORE_ID  INTEGER PRIMARY KEY AUTOINCREMENT," \
		                 "AMOUNT    INTEGER             NOT NULL," \
		                 "PLAYER_ID INTEGER            NOT NULL," \
		                 "FOREIGN KEY (PLAYER_ID) REFERENCES PLAYER(PLAYER_ID));");
	}

	void
	Database::execute(const char *sql_request) {
		if(sqlite3_exec(this->database, sql_request,
		                NULL, 0, &this->error_message) != SQLITE_OK)
		{
			std::cout << "SQL Error: " << this->error_message << std::endl;
			sqlite3_free(this->error_message);
		}
	}

	Database::~Database() {
		sqlite3_close(this->database);
	}

	void
	Database::createPlayer(Player& player) {
		sqlite3_stmt *statement;
		if(sqlite3_prepare(this->database, "INSERT INTO " \
		                                   "PLAYER(NAME) " \
		                                   "VALUES(?);",
		                   -1, &statement, NULL) == SQLITE_OK) {
			sqlite3_bind_text(statement, 1, player.getName(), strlen(player.getName()), NULL);
			sqlite3_step(statement);
			sqlite3_finalize(statement);
			if(sqlite3_prepare(this->database, "SELECT PLAYER_ID FROM PLAYER " \
			                                   "ORDER BY PLAYER_ID DESC " \
			                                   "LIMIT 1",
			                   -1, &statement, NULL) == SQLITE_OK)
			{
				sqlite3_step(statement);
				player.setId(sqlite3_column_int(statement, 0));
				sqlite3_finalize(statement);
			}
		}
	}

	bool
	Database::playerExists(Player& player) {
		sqlite3_stmt *statement;
		if(sqlite3_prepare(this->database, "SELECT * FROM PLAYER " \
		                                   "WHERE PLAYER_ID = ? OR NAME = ?;",
		                   -1, &statement, NULL) == SQLITE_OK) {
			sqlite3_bind_int(statement, 1, player.getId());
			sqlite3_bind_text(statement, 2, player.getName(), strlen(player.getName()), NULL);
			if(sqlite3_step(statement) == SQLITE_ROW) {
				sqlite3_finalize(statement);
				return true;
			}
		}
		return false;
	}

	void
	Database::insertScore(Player& player) {
		sqlite3_stmt *statement;
		if(sqlite3_prepare(this->database, "INSERT INTO " \
		                                   "SCORE(PLAYER_ID, AMOUNT) " \
		                                   "VALUES(?, ?);",
		                   -1, &statement, NULL) == SQLITE_OK) {
			sqlite3_bind_int(statement, 1, player.getId());
			sqlite3_bind_int(statement, 2, player.getScore());
			sqlite3_step(statement);
			sqlite3_finalize(statement);
		}
	}

	Player
	Database::getPlayer(const char *name) {
		sqlite3_stmt *statement;
		Player player;
		if(sqlite3_prepare(this->database, "SELECT PLAYER_ID, NAME FROM PLAYER " \
		                                   "WHERE NAME = ?;",
		                   -1, &statement, NULL) == SQLITE_OK)
		{
			sqlite3_bind_text(statement, 1, name, strlen(name), NULL);
			if(sqlite3_step(statement) == SQLITE_ROW) {
				player.setId(sqlite3_column_int(statement, 0));
				player.setName((const char*) sqlite3_column_text(statement, 1));
				#ifdef DEBUG
				std::cout << "Name: " << player.getName() <<
				             "\tId: " << player.getId() << std::endl;
				#endif
			}
			sqlite3_finalize(statement);
		}
		return player;
	}

	int
	Database::getTotalScore(Player& player) {
		sqlite3_stmt *statement;
		int total_score=-1;
		if(sqlite3_prepare(this->database, "SELECT SUM(AMOUNT) FROM SCORE " \
		                                   "WHERE PLAYER_ID = ?;",
		                   -1, &statement, NULL) == SQLITE_OK) {
			sqlite3_bind_int(statement, 1, player.getId());
			sqlite3_step(statement);
			total_score = sqlite3_column_int(statement, 0);
			std::cout << total_score << std::endl;
			sqlite3_finalize(statement);
		}
		return total_score;
	}


}

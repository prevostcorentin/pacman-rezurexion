#include <ScoreMenu.hpp>

#include <Database.hpp>
#include <GameState.hpp>

#include <iostream>
#include <sstream>



namespace prx
{


	GUI::ScoreMenu::ScoreMenu(sf::Font& font) : GUI::Menu<enum GAME_STATE>(font) {
		Database database;
		std::ostringstream string_stream;
		for(auto& player_score: database.getAllScores()) {
			string_stream.clear();
			string_stream << player_score.first << "\t" << player_score.second;
			this->addEntry(string_stream.str(), GAME_STATE::SHOW_SCORES);
		}
		this->addEntry("Return", GAME_STATE::STARTING);
	}


}

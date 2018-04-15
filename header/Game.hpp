#ifndef GAME_INCLUDED
#define GAME_INCLUDED


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>

#include <CPUSpinner.hpp>
#include <Database.hpp>
#include <GameState.hpp>
#include <Map.hpp>
#include <MapChoosingMenu.hpp>
#include <Menu.hpp>
#include <ObjectCollection.hpp>
#include <PacGum.hpp>
#include <Player.hpp>
#include <Wall.hpp>


#define GAME_TITLE "Pacman Rezurexion"


namespace prx
{


	class Game
	{

		public:
			Game(sf::ContextSettings, sf::Font&);
			void launch();

		private:
			void initPlayer();
			void moveObject(Object*);
			void moveGhosts();
			void quit();
			void turn();
			void updateCollisions();
			void updateGame();
			void updateState(const enum GAME_STATE);

			sf::Font& font;
			CPUSpinner spinner;
			enum GAME_STATE state;
			sf::RenderWindow window;
			ObjectCollection* objects;
			Map map;
			Database database;
			Player player;
			GUI::MapChoosingMenu map_choosing_menu;
			GUI::Menu<enum GAME_STATE> score_menu;
			GUI::Menu<enum GAME_STATE> start_menu;

	};


}


#endif

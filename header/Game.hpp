#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <Signals/Delegate.h>
#include <Signals/Signal.h>

#include <SFML/Window.hpp>

#include <CollisionTracker.hpp>
#include <CPUSpinner.hpp>
#include <Database.hpp>
#include <Keyboard.hpp>
#include <Map.hpp>
#include <ObjectCollection.hpp>
#include <PacGum.hpp>
#include <Player.hpp>
#include <Screen.hpp>
#include <Wall.hpp>

#define GAME_TITLE "Pacman Rezurexion"


namespace prx
{


	enum GameState { Init, Running, Error, Stopped };
	class Game
	{
		public:
			Game(sf::ContextSettings context);
			void launch();
			Gallant::Signal0<void> SigQuit;

		private:
			void initPlayer();
			void handleCollision(ObjectCollection& objects);
			void handleUpdate();
			void handleQuit();
			void handlePlayerMove(enum Direction direction);

			enum GameState state;
			Keyboard keyboard;
			sf::RenderWindow window;
			ObjectCollection* objects;
			Map map;
			Screen screen;
			CPUSpinner spinner;
			CollisionTracker collision_tracker;
			Database database;
			Player player;
	};


}


#endif

#include <cstdlib>
#include <exception>
#include <iostream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <Signals/Delegate.h>
#include <Signals/Signal.h>


#define GAME_TITLE "Pacman Rezurexion"


namespace prx
{
	
	
	enum Direction { Right=0, Left=1, Down=2, Up=3 };
	
	namespace Sig
	{
		
		
		Gallant::Signal0<void> Tick;
		Gallant::Signal0<void> Quit;
		Gallant::Signal1<enum Direction> PlayerMove;
		
		
	}
	
	struct Point { int x, y; };
	struct Object 
	{
		Object(const char *sprite_sheet_filepath) {
			sf::Color color(255, 255, 255, 255);
			if(!this->image.loadFromFile(sprite_sheet_filepath))
				Sig::Quit.Emit();
			this->image.createMaskFromColor(color, 0);
			if(!this->texture.loadFromImage(this->image))
				Sig::Quit.Emit();
			this->sprite.setTexture(this->texture);
			this->sprite.setPosition(0, 0);
			this->setFrame(Direction::Right, 0);
		}
		void setFrame(enum Direction direction, int n) {
			this->sprite.setTextureRect(sf::IntRect(n * 32, direction * 32,
			                                        32, 32));
		}
		sf::Vector2f map_position;
		sf::Image image;
		sf::Texture texture;
		sf::Sprite sprite;
	};

	struct ObjectCollection
	{
		ObjectCollection() { }
		void add(Object* o) {
			objects.push_back(o);
		}
		Object* get(int n) {
			return this->objects[n];
		}
		std::vector<Object*> getAllObjects() {
			return this->objects;
		}
		std::vector<Object*> objects;
	};
	
	struct Map {
		Map(ObjectCollection& oc) : objects(oc)
		{ }
		std::vector<Object*> getCell(sf::Vector2f position) {
			std::vector<Object*> objects_at_position;
			for(auto o: this->objects.getAllObjects())
			{
				if(position == o->map_position)
					objects_at_position.push_back(o);
			}
			return objects_at_position;
		}
		ObjectCollection& objects;
	};
	
	struct Player : Object
	{
		Player() : Object("resources/sprites/pacman.bmp") {}
	};
	
	struct Keyboard
	{
		Keyboard() { }
		void dispatchLastMoves() {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				Sig::Quit.Emit();
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				Sig::PlayerMove.Emit(Direction::Down);
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				Sig::PlayerMove.Emit(Direction::Left);
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				Sig::PlayerMove.Emit(Direction::Right);
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				Sig::PlayerMove.Emit(Direction::Up);
		}
	};
	
	struct CPUSpinner
	{
		CPUSpinner(sf::RenderWindow& w) : window(w)
		{ }
		void run() {
			sf::Event event;
			while(window.pollEvent(event))
				Sig::Tick.Emit();
		}
		sf::Clock clock;
		sf::RenderWindow& window;
	};
	
	struct Screen
	{
		Screen(sf::RenderWindow& w, Map& m) : window(w),
		                                      map(m)
		{ }
		void draw() {
			this->window.clear();
			for(auto& o: this->map.objects.getAllObjects())
			{
				o->sprite.setPosition(32 * o->map_position.x, 
				                      32 * o->map_position.y);
				this->window.draw(o->sprite);
			}
			this->window.display();
		}
		sf::RenderWindow& window;
		Map& map;
	};
	
	enum GameState { Init, Running, Error, Stopped };
	struct Game
	{
		Game(sf::ContextSettings context) : window(sf::VideoMode(640, 480),
		                                           GAME_TITLE,
		                                           sf::Style::Default,
		                                           context),
		                                    map(objects),
		                                    screen(window, map),
		                                    spinner(window)
		{
			this->state = Init;
			Sig::PlayerMove.Connect(this, &Game::move);
			Sig::Quit.Connect(this, &Game::quit);
			Sig::Tick.Connect(this, &Game::update);
			this->player.map_position = sf::Vector2f(1, 1);
			this->objects.add(&this->player);
			this->window.setActive();
		}
		void launch() {
			this->state = Running;
			while(this->window.isOpen())
				spinner.run();
		}
		void update() {
			this->keyboard.dispatchLastMoves();
			this->screen.draw();
		}
		void quit() {
			std::cout << "Quitting game" << std::endl;
			window.close();
			std::exit(EXIT_SUCCESS);
		}
		void move(enum Direction direction)
		{
			std::cout << "player has moved" << std::endl;
		}
		enum GameState state;
		Keyboard keyboard;
		sf::RenderWindow window;
		ObjectCollection objects;
		Map map;
		Screen screen;
		CPUSpinner spinner;
		Player player;
	};
	
	
}


int main()
{
	sf::ContextSettings context;
	context.depthBits = 24;
	try {
		prx::Game game(context);
		game.launch();
	} catch (std::exception e) {
		std::cout << "Unexpected exception" << std::endl;
	}
	
	return EXIT_SUCCESS;
}

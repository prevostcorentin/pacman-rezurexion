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
	
	namespace Sig {
		Gallant::Signal0<void> Quit;
	}
	
	enum Direction { Right=0, Left=1, Down=2, Up=3 };
	
	struct Point { int x, y; };
	template<typename T> struct object_type {
		const char* name() { return "undefined"; }
	};
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
			// Resizing by half
			this->sprite.setScale(sf::Vector2f(0.5, 0.5));
			this->setFrame(Direction::Right, 0);
		}
		void setFrame(enum Direction direction, int n) {
			this->sprite.setTextureRect(sf::IntRect(n * 32, direction * 32,
			                                        32, 32));
		}
		virtual const std::string getType() {
			return std::string("undefined"); // object_type<Object>::name();
		}

		sf::Vector2f map_position;
		sf::Image image;
		sf::Texture texture;
		sf::Sprite sprite;
	};
	
	namespace Sig
	{
		
		
		Gallant::Signal0<void> Tick;
		Gallant::Signal1<enum Direction> PlayerMove;
		
		
	}
	
	struct Pacman : Object
	{
		Pacman() : Object("resources/sprites/pacman.bmp") { }
		const std::string getType() {
			return std::string("pacman");
		}
	};
	template<> struct object_type<Pacman> {
		const std::string name() { return std::string("pacman"); }
	};
	
	struct Ghost : Object
	{
		Ghost() : Object("resources/sprites/ghost.bmp") { }
		const std::string getType() {
			return std::string("ghost");
		}
	};
	template<> struct object_type<Ghost> {
		const std::string name() { return std::string("ghost"); }
	};
	
	struct Wall : Object
	{
		Wall() : Object("resources/sprites/wall.bmp") { }
		const std::string getType() {
			return std::string("wall");
		}
	};
	template<> struct object_type<Wall> {
		const std::string name() {
			return std::string("wall");
		}
	};

	struct PacGum : Object
	{
		PacGum() : Object("resources/sprites/pac-gum.bmp") { }
		const std::string getType() {
			return std::string("pac_gum");
		}
	};
	template<> struct object_type<PacGum> {
		const std::string name() { return std::string("pac_gum"); }
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
		const size_t count() {
			return this->objects.size();
		}
		bool hasObjectOfType(std::string _typename) {
			return std::find_if(this->objects.begin(), this->objects.end(),
			                    [_typename](Object *o) {
			                       return o->getType() == _typename;
			                    }) != this->objects.end();
		}
		std::vector<Object*> getObjectsOfType(std::string _typename) {
			std::vector<Object*> objects_of_type;
			std::vector<Object*>::iterator object_position = this->objects.begin();
			while((object_position = std::find_if(object_position, this->objects.end(),
			       [_typename](Object *o) {
			          return o->getType() == _typename;
			       })) != this->objects.end())
			{
				objects_of_type.push_back(*object_position);
				object_position++;
			}
			return objects_of_type;
		}
		void erase(Object *o) {
			const std::vector<Object*>::iterator object_position =
			   std::find(this->objects.begin(), this->objects.end(), o);
			if(object_position != this->objects.end())
				this->objects.erase(object_position);
			else
				std::cout << "Object does not exist" << std::endl;
		}
		std::vector<Object*> objects;
	};
	
	namespace Sig
	{
		
		
		Gallant::Signal1<ObjectCollection&> Collision;
		
		
	}
	
	struct Map {
		Map(ObjectCollection& oc) : objects(oc)
		{ }
		ObjectCollection getCell(int x, int y) {
			ObjectCollection objects_at_position;
			for(auto o: this->objects.getAllObjects()) {
				if(x == o->map_position.x and y == o->map_position.y)
					objects_at_position.add(o);
			}
			return objects_at_position;
		}
		ObjectCollection& objects;
		const int width = 16;
		const int height = 16;
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
			while(window.pollEvent(event)) {
				Sig::Tick.Emit();
				sf::sleep(sf::milliseconds(60));
			}
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
				o->sprite.setPosition(16 * o->map_position.x,
				                      16 * o->map_position.y);
				this->window.draw(o->sprite);
			}
			this->window.display();
		}
		sf::RenderWindow& window;
		Map& map;
	};

	struct Player
	{
		Player() : name("unknown") 
		{ }
		Pacman pacman;
		int score = 0;
		std::string name;
	};
	
	struct CollisionTracker
	{
		CollisionTracker(Map& m) : map(m)
		{ }
		void dispatchLastCollisions() {
			for(int x=0; x < this->map.width; x++) {
				for(int y=0; y < this->map.height; y++) {
					ObjectCollection objects_at_xy = this->map.getCell(x, y);
					if(objects_at_xy.count() > 1)
						Sig::Collision.Emit(objects_at_xy);
				}
			}
		}
		bool objectCanMoveTo(Object *o, const sf::Vector2f& position) {
			ObjectCollection objects_on_cell = this->map.getCell(position.x, position.y);
			if(objects_on_cell.hasObjectOfType("wall"))
				return false;
			else
				return true;
		}
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
		                                    spinner(window),
		                                    collision_tracker(map)
		{
			this->state = Init;
			// Connect signals to handlers
			Sig::Collision.Connect(this, &Game::handleCollision);
			Sig::PlayerMove.Connect(this, &Game::handlePlayerMove);
			Sig::Quit.Connect(this, &Game::handleQuit);
			Sig::Tick.Connect(this, &Game::handleUpdate);
			// Place objects
			this->player.pacman.map_position = sf::Vector2f(0, 0);
			this->pac_gum.map_position = sf::Vector2f(2, 5);
			this->ghost.map_position = sf::Vector2f(3, 5);
			this->wall.map_position = sf::Vector2f(4, 5);
			// Adding it to the collection
			this->objects.add(&this->player.pacman);
			this->objects.add(&this->ghost);
			this->objects.add(&this->wall);
			this->objects.add(&this->pac_gum);
			this->window.setActive();
		}
		void launch() {
			this->state = Running;
			while(this->window.isOpen())
				spinner.run();
			std::exit(EXIT_FAILURE);
		}
		void handleCollision(ObjectCollection& objects) {
			#ifdef DEBUG
			std::cout << "Collision: " << std::endl;
			for(auto& o: objects.getAllObjects())
				std::cout << "\t" << o->getType();
			std::cout << std::endl;
			#endif
			if(objects.hasObjectOfType("pacman")) {
				if(objects.hasObjectOfType("pac_gum")) {
					for(auto& gum: objects.getObjectsOfType("pac_gum")) {
						this->player.score++;
						this->objects.erase(gum);
					}
				} else if(objects.hasObjectOfType("ghost")) {
					std::cout << "Player dies with score of " << this->player.score << std::endl;
					this->objects.erase(&this->player.pacman);
					Sig::Quit.Emit();
				}
			}
		}
		void handleUpdate() {
			this->keyboard.dispatchLastMoves();
			this->collision_tracker.dispatchLastCollisions();
			this->screen.draw();
		}
		void handleQuit() {
			std::cout << "Quitting game" << std::endl;
			window.close();
			std::exit(EXIT_SUCCESS);
		}
		void handlePlayerMove(enum Direction direction)
		{
			sf::Vector2f new_position;
			switch(direction) {
				case Right:
					new_position = sf::Vector2f(this->player.pacman.map_position.x + 1,
					                            this->player.pacman.map_position.y);
				break;
				case Left:
					new_position = sf::Vector2f(this->player.pacman.map_position.x - 1,
					                            this->player.pacman.map_position.y);
				break;
				case Down:
					new_position = sf::Vector2f(this->player.pacman.map_position.x,
					                            this->player.pacman.map_position.y + 1);
				break;
				case Up:
					new_position = sf::Vector2f(this->player.pacman.map_position.x,
					                            this->player.pacman.map_position.y - 1);
				break;
			}
			if(this->collision_tracker.objectCanMoveTo(&this->player.pacman,
			                                           new_position))
			{
				this->player.pacman.map_position = new_position;
			}
		}
		enum GameState state;
		Keyboard keyboard;
		sf::RenderWindow window;
		ObjectCollection objects;
		Map map;
		Screen screen;
		CPUSpinner spinner;
		CollisionTracker collision_tracker;
		Player player;
		PacGum pac_gum;
		Wall wall;
		Ghost ghost;
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

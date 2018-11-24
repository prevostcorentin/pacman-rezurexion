#include <MapChoosingMenu.hpp>

#include <Logger.hpp>

#include <dirent.h>
#include <sstream>



namespace prx
{


	GUI::MapChoosingMenu::MapChoosingMenu(sf::Font& font) : GUI::Menu<std::string>(font) {
		DIR *dir;
		struct dirent *ent;
		if ((dir = opendir("resources/map")) != NULL) {
			while ((ent = readdir(dir)) != NULL)
				if(ent->d_name[0] != '.') {
					std::ostringstream path;
					path << "resources/map/" << ent->d_name;
					this->addEntry(ent->d_name, path.str());
				}
			closedir(dir);
		} else {
			Logger::Send(Logger::LEVEL::DEBUG, "Can not open \"resources/map\"");
		}
		this->addEntry("RETURN", std::string(""));
	}


}

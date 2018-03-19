#include <MapLoader.hpp>

#include <Ghost.hpp>
#include <Logger.hpp>
#include <Pacman.hpp>
#include <PacGum.hpp>
#include <Wall.hpp>

#include <cctype>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include <SFML/System.hpp>





namespace prx
{

	sf::Vector2f 
	GetDimensionsFromFilename(const char *filename) {
		std::ifstream fstream(filename);
		MapFile::header_t header = MapFile::_extract_header(fstream);
		return sf::Vector2f(header.map_width, header.map_height);
	}

	ObjectCollection*
	GetGameObjectsFromFilename(const char *filename) {
		Logger::Send(Logger::LEVEL::INFO, "Loading map from file %s", filename);
		ObjectCollection *objects = new ObjectCollection();
		std::ifstream fstream(filename);
		/*
		if(MapFile::get_last_error(fstream)) {
			Logger::Send(Logger::LEVEL::ERROR, "%s -> Can not load %s\n", MapFile::strerror(MapFile::get_last_error(fstream)), filename);
			return nullptr;
		}
		*/
		MapFile::header_t header = MapFile::_extract_header(fstream);
		// skip header
		std::string line;
		std::getline(fstream, line);
		for(int y=0; y < header.map_height; y++) {
			std::getline(fstream, line);
			for(int x=0; x < header.map_width; x++) {
				if(line[x] == '*') {
					objects->add(new PacGum(sf::Vector2f(x, y)));
				} else if(line[x] == '-' or line[x] == '|') {
					objects->add(new Wall(sf::Vector2f(x, y)));
				} else if(line[x] == 'G') {
					objects->add(new PacGum(sf::Vector2f(x, y)));
					objects->add(new Ghost(sf::Vector2f(x, y)));
				}
			}
		}
		return objects;
	}


	enum MapFile::ERROR MapFile::get_last_error(std::ifstream& fstream) {
		MapFile::header_t header = MapFile::_extract_header(fstream);
		int width_count=0, height_count=0;
		std::string line;
		// skip header
		std::getline(fstream, line);
		while(std::getline(fstream, line)) {
			while(line[width_count++] != '\n') {
				if(width_count > header.map_width)
					break;
			}
			if(width_count != header.map_width - 1)
				return MapFile::ERROR::WrongWidth;
			height_count++;
			width_count=0;
		}
		if(height_count != header.map_height)
			return MapFile::ERROR::WrongHeight;
		return MapFile::ERROR::NoError;
	}

	MapFile::header_t
	MapFile::_extract_header(std::ifstream& fstream) {
		MapFile::header_t header;
		std::string dimensions;
		std::getline(fstream, dimensions);
		const std::size_t separator_position = dimensions.find_last_of(",");
		header.map_width = std::atoi(dimensions.substr(0, separator_position).c_str());
		header.map_height = std::atoi(dimensions.substr(separator_position + 1).c_str());
		fstream.seekg(0, std::ios::beg);
		return header;
	}

	const char*
	MapFile::strerror(ERROR errcode) {
		std::string errstr;
		if(errcode == WrongHeader)
			errstr = std::string("Wrong header format");
		if(errcode == WrongHeight)
			errstr = std::string("Wrong height");
		if(errcode == WrongWidth)
			errstr = std::string("Wrong width");
		else
			errstr = std::string("No error");
		return errstr.c_str();
	}


}



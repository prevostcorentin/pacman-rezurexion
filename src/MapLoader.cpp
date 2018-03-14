#include <MapLoader.hpp>

#include <cctype>
#include <iostream>
#include <iterator>
#include <fstream>
#include <cstdlib>

#include <SFML/System.hpp>

#define MAX_HEADER_SIZE 32
#define MAX_WIDTH 120
#define MAX_HEIGHT 120

#define MAPFILE_LINE_SEPARATOR 'L'
#define END_OF_MAPFILE 'E'
#define GHOST 'G'
#define HWALL '-'
#define PAC_GUM '*'
#define PLAYER 'P'
#define VWALL '|'



namespace MapFile 
{


	typedef struct HEADER {
		int map_width;
		int map_height;
	} header_t;

	enum ERROR {
		NoError = 0,
		WrongHeader = 100, 
		WrongHeight,
		WrongWidth,
		NoPlayer
	};

	enum ERROR get_last_error(std::istream&);
	header_t _extract_header(std::istream&);


}



namespace prx
{


	void
	LoadGameObjectsFromFilename(ObjectCollection& objects, const char *filename) {
		std::ifstream file(filename);
		if(::MapFile::get_last_error(file)) {
			std::cout << "Can not load " << filename << std::endl;
			return;
		}
	}


}


enum MapFile::ERROR
MapFile::get_last_error(std::istream& stream) {
	MapFile::header_t header = MapFile::_extract_header(stream);
	std::istream_iterator<char> stream_it(stream);
	int width_count=0, height_count=0;
	bool has_player = false;
	bool headers_skipped = false;
	for(; *stream_it != END_OF_MAPFILE; stream_it++) {
		if(not headers_skipped) {
			for(; *stream_it != MAPFILE_LINE_SEPARATOR; stream_it++) {
				if(*stream_it == END_OF_MAPFILE)
					return WrongHeader;
			};
			headers_skipped = true;
			stream_it++;
		}
		if(width_count > header.map_width) {
			return MapFile::ERROR::WrongWidth;
		}
		width_count++;
		if(*stream_it == MAPFILE_LINE_SEPARATOR) {
			height_count++;
			if(width_count - 1 < header.map_width) {
				std::cout << width_count << std::endl;
				return MapFile::ERROR::WrongWidth;
			}
			width_count = 0;
		} else if(std::toupper(*stream_it) == PLAYER) {
			has_player = true;
		}
	}
	if(not has_player)
		return MapFile::ERROR::NoPlayer;
	if(height_count != header.map_height)
		return MapFile::ERROR::WrongHeight;
	return MapFile::ERROR::NoError;
}

MapFile::header_t
MapFile::_extract_header(std::istream& stream) {
	MapFile::header_t header;
	std::string dimensions;
	std::getline(stream, dimensions);
	const std::size_t separator_position = dimensions.find_last_of(",");
	header.map_width = std::atoi(dimensions.substr(0, separator_position).c_str());
	header.map_height = std::atoi(dimensions.substr(separator_position+1).c_str());
	stream.seekg(0, std::ios::beg);
	return header;
}

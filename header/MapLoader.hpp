#ifndef MAP_LOADER_DEFINED
#define MAP_LOADER_DEFINED

#include <Map.hpp>
#include <ObjectCollection.hpp>

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


namespace prx 
{


	ObjectCollection* GetGameObjectsFromFilename(const char *filename);

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


}



#endif

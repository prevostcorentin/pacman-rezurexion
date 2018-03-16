#include <UnitTest++/UnitTest++.h>

#include <MapLoader.cpp>


struct PlayableMapStreamFixture
{
	std::istringstream stream;
	PlayableMapStreamFixture() : stream("8,9\n" \
	                                    "P*******\n" \
	                                    "*------*\n" \
	                                    "*|G***|*\n" \
	                                    "*|****|*\n" \
	                                    "*|****|*\n" \
	                                    "*|****|*\n" \
	                                    "*|--*-|*\n" \
	                                    "*|*|*|-*\n" \
	                                    "********\n")
	{ }
};

SUITE(FormatErrors) {
	TEST(ExtractHeader) {
		std::istringstream stream("2,1E");
		const MapFile::header_t header = MapFile::_extract_header(stream);
		CHECK_EQUAL(2, header.map_width);
		CHECK_EQUAL(1, header.map_height);
	}

	TEST(GreaterHeight) {
		std::istringstream stream("2,1LP*L**LE");
		CHECK_EQUAL(MapFile::ERROR::WrongHeight, MapFile::get_last_error(stream));
	}

	TEST(GreaterWidth) {
		std::istringstream stream("2,1LP**LE");
		CHECK_EQUAL(MapFile::ERROR::WrongWidth, MapFile::get_last_error(stream));
	}

	TEST(LesserHeight) {
		std::istringstream stream("2,2LP*LE");
		CHECK_EQUAL(MapFile::ERROR::WrongHeight, MapFile::get_last_error(stream));
	}

	TEST(LesserWidth) {
		std::istringstream stream("2,1LPLE");
		CHECK_EQUAL(MapFile::ERROR::WrongWidth, MapFile::get_last_error(stream));
	}

	TEST(NoError) {
		std::istringstream stream("1,1LPLE");
		CHECK_EQUAL(MapFile::ERROR::NoError, MapFile::get_last_error(stream));
	}

	TEST(NoPlayer) {
		std::istringstream stream("1,1L*LE");
		CHECK_EQUAL(MapFile::ERROR::NoPlayer, MapFile::get_last_error(stream));
	}
}

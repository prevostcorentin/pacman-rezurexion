ifeq ($(OS), Windows_NT)
	CMAKE_MAKEFILE_TYPE = "MinGW Makefiles"
	LIBS = -lsfml-main
	RELEASE_LDFLAGS = -mwindows
	DYNAMIC_LIBS = extlibs/SFML/lib/sfml-*.dll
else
	CMAKE_MAKEFILE_TYPE = "Unix Makefiles"
	LIBS = -lpthread -ldl
	RELEASE_LDFLAGS =
	DYNAMIC_LIBS = extlibs/SFML/lib/libsfml-*.so
endif


CC = gcc
CXX_FLAGS = -Wall -std=c++0x
DEFINES = -DSFML_STATIC -DSPIN_DELAY=120 -DSCREEN_WIDTH=640 -DSCREEN_HEIGHT=480
EXECUTABLE = PacmanRezurexion
HEADERS_PATHS = -Iextlibs -Iextlibs/SFML/include -Iheader
STATIC_LIBS_SEARCH_PATHS = -Lextlibs/SFML/lib -Lextlibs/sqlite3/lib -Llib
LIBS += -lprx -lsfml-system -lsfml-graphics -lsfml-window -lsqlite3
OBJS = $(filter-out obj/main.o, $(subst src/, obj/, $(patsubst %.cpp, %.o, $(wildcard src/*.cpp))))


init: debug-target release-target

all: SFML extlibs/sqlite3/lib/libsqlite3.a debug-target release-target

debug-target: lib/libprx.a bin/Debug/$(EXECUTABLE)
	cp -R resources bin/Debug/resources
	cp $(DYNAMIC_LIBS) bin/Debug

release-target: lib/libprx.a bin/Release/$(EXECUTABLE)
	cp -R resources bin/Release/resources
	cp $(DYNAMIC_LIBS) bin/Release

lib/libprx.a: obj $(OBJS) lib
	ar rvs -o $@ $(OBJS)

obj:
	mkdir $@

obj/%.o: src/%.cpp
	$(CXX) $(CXX_FLAGS) $(DEFINES) -c $< -o $@ \
		-Iextlibs/ -Iextlibs/SFML/include -Iheader

lib:
	mkdir $@

bin/Debug/$(EXECUTABLE): | bin/Debug
	$(CXX) $(CXX_FLAGS) -g src/main.cpp -o $@ \
		$(HEADERS_PATHS) \
		$(STATIC_LIBS_SEARCH_PATHS) $(LIBS)

bin/Debug:
	mkdir -p $@

bin/Release/$(EXECUTABLE): | bin/Release
	$(CXX) $(CXX_FLAGS) src/main.cpp -o $@ \
		$(HEADERS_PATHS) \
		$(RELEASE_LDFLAGS) $(STATIC_LIBS_SEARCH_PATHS) $(LIBS)

bin/Release:
	mkdir -p $@

dependencies: SFML lib/libsqlite3.a

extlibs/sqlite3/lib/libsqlite3.a: extlibs/sqlite3/obj extlibs/sqlite3/lib
	$(CC) -c extlibs/sqlite3/sqlite3.c -o extlibs/sqlite3/obj/sqlite3.o
	ar rvs -o $@ extlibs/sqlite3/obj/sqlite3.o

extlibs/sqlite3/obj:
	mkdir $@

extlibs/sqlite3/lib:
	mkdir $@

obj/extlibs/sqlite3/sqlite3.o:

SFML:
	cd extlibs/SFML; cmake -G$(CMAKE_MAKEFILE_TYPE); $(MAKE)

clean:
	rm obj/*.o

ifeq ($(OS), Windows_NT)
	CMAKE_MAKEFILE_TYPE = "MinGW Makefiles"
	LIBS = -lsfml-main
else
	CMAKE_MAKEFILE_TYPE = "Unix Makefiles"
	LIBS = -lpthread -ldl
endif
LIBS += -lsfml-system -lsfml-graphics -lsfml-window
CXX_FLAGS = -DDEBUG -g -Wall -Wno-unused-local-typedefs -std=c++0x
EXECUTABLE = PacmanRezurexion

$(EXECUTABLE): $(subst src/, obj/, $(patsubst %.cpp, %.o, $(wildcard src/*.cpp)))
	@echo Compiling $@
	$(CXX) $(CXX_FLAGS) obj/*.o -o $@ \
		-Lextlibs/SFML/lib -Llib $(LIBS)

obj/%.o: src/%.cpp
	@echo Compiling object file $@
	$(CXX) $(CXX_FLAGS) -c $< -o $@ \
		-Iextlibs/ -Iextlibs/SFML/include -Iheader

dependencies: SFML obj/sqlite3.o

SFML: lib
	cd extlibs/SFML; cmake -G$(CMAKE_MAKEFILE_TYPE); make
	cp extlibs/SFML/lib/* lib

lib:
	mkdir lib

obj/sqlite3.o: extlibs/sqlite3/sqlite3.c
	$(CC) -c $< -o $@

install:
	cp lib/libsfml-*.so.2.4 /usr/lib

clean:
	@rm obj/*.

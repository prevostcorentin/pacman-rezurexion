CC = mingw32-gcc.exe
CXX = mingw32-g++.exe
CXX_FLAGS = -DDEBUG -g -Wall -Wno-unused-local-typedefs -std=c++0x
LIB = lib/libprx.a
OBJS = $(subst src/, obj/, $(patsubst %.cpp, %.o, $(wildcard src/*.cpp)))
EXECUTABLE = PacmanRezurexion.exe

.SILENT:

all: obj/sqlite3.o $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	@echo Compiling $@
	$(CXX) $(CXX_FLAGS) obj/*.o -o $@ \
		-Lextlibs/SFML/lib -lsfml-system -lsfml-main -lsfml-graphics -lsfml-window

obj/%.o: src/%.cpp
	@echo Compiling object file $@
	$(CXX) $(CXX_FLAGS) -c $< -o $@ \
		-Iextlibs/ -Iextlibs/SFML/include -Iheader

obj/sqlite3.o: extlibs/sqlite3/sqlite3.c
	$(CC) -c $< -o $@

clean:
	@rm obj/*.

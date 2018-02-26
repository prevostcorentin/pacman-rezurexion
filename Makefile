CXX = mingw32-g++.exe
CXX_FLAGS = -Wall -Wno-unused-local-typedefs -std=c++0x
OBJS = $(subst src/, obj/, $(patsubst %.cpp, %.o, $(wildcard src/*.cpp)))
EXECUTABLE = PacmanRezurexion.exe

.SILENT:

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	@echo Compiling $@
	$(CXX) $(CXX_FLAGS) obj/*.o -o $@ \
		-Lextlibs/SFML/lib -lsfml-system -lsfml-main -lsfml-graphics -lsfml-window

obj/%.o: src/%.cpp
	@echo Compiling object file $@
	$(CXX) $(CXX_FLAGS) -c $< -o $@ \
		-Iextlibs/ -Iextlibs/SFML/include -Iheader

clean:
	@rm obj/*.o

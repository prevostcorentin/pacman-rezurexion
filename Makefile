ifeq ($(OS), Windows_NT)
	CMAKE_MAKEFILE_TYPE = "MinGW Makefiles"
	LIBS = -lsfml-main
else
	CMAKE_MAKEFILE_TYPE = "Unix Makefiles"
	LIBS = -lpthread -ldl
endif
OBJS = $(filter-out obj/main.o, $(subst src/, obj/, $(patsubst %.cpp, %.o, $(wildcard src/*.cpp))))
LIBS += -lsfml-system -lsfml-graphics -lsfml-window
CXX_FLAGS = -g -Wall -Wno-unused-local-typedefs -std=c++0x
EXECUTABLE = PacmanRezurexion


.SILENT: $(OBJS) $(EXECUTABLE) prx-static-lib exe-without-lib


init: obj $(OBJS) prx-static-lib $(EXECUTABLE)

obj:
	mkdir $@

$(EXECUTABLE): $(OBJS) prx-static-lib lib/libsqlite3.a
	@echo Compiling statically linked version of $(EXECUTABLE)
	$(CXX) $(CXX_FLAGS) src/main.cpp -o $(EXECUTABLE) \
		-Iextlibs -Iextlibs/SFML/include -Iheader \
		-Lextlibs/SFML/lib -Llib -Llib/extlibs/ $(LIBS) -lprx

prx-static-lib: $(OBJS) lib
	@echo Linking game static library ...
	ar rvs -o lib/libprx.a $(OBJS)

exe-without-lib: $(OBJS) lib/libsqlite3.a
	@echo Compiling $(EXECUTABLE) by linking game objects ...
	$(CXX) $(CXX_FLAGS) obj/*.o -o $(EXECUTABLE) \
		-Lextlibs/SFML/lib -Llib $(LIBS)

obj/%.o: src/%.cpp
	@echo Compiling object file $@ ...
	$(CXX) $(CXX_FLAGS) -c $< -o $@ \
		-Iextlibs/ -Iextlibs/SFML/include -Iheader


dependencies: SFML lib/libsqlite3.a

lib/libsqlite3.a: obj/extlibs/sqlite3 obj/extlibs/sqlite3/sqlite3.o lib
	@echo Linking $@ ...
	ar rvs -o lib/libsqlite3.a obj/extlibs/sqlite3/*.o

obj/extlibs/sqlite3:
	mkdir $@

obj/extlibs/sqlite3/sqlite3.o:
	$(CC) -c extlibs/sqlite3/sqlite3.c -o $@


SFML: lib
	cd extlibs/SFML; cmake -G$(CMAKE_MAKEFILE_TYPE); make
	cp extlibs/SFML/lib/* $<

lib:
	mkdir $@

install:
	cp lib/libsfml-*.so.2.4 /usr/lib

clean:
	@rm obj/*.o

debug:
	@echo Object files: $(OBJS)

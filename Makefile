ifeq ($(OS), Windows_NT)
	CMAKE_MAKEFILE_TYPE = "MinGW Makefiles"
	LIBS = -lsfml-main
else
	CMAKE_MAKEFILE_TYPE = "Unix Makefiles"
	LIBS = -lpthread -ldl
endif
OBJS = $(filter-out obj/main.o, $(subst src/, obj/, $(patsubst %.cpp, %.o, $(wildcard src/*.cpp))))
LIBS += -lsfml-system -lsfml-graphics -lsfml-window
CXX_FLAGS = -DSFML_STATIC -g -Wall -Wno-unused-local-typedefs -std=c++0x
EXECUTABLE = PacmanRezurexion


.SILENT: $(OBJS) $(EXECUTABLE) debug-exe lib/libprx.a exe-without-lib


init: obj $(EXECUTABLE)

obj:
	mkdir $@

debug-exe: $(OBJS) lib/libprx.a lib/libsqlite3.a
	@echo Compiling debug version of $(EXECUTABLE)
	$(CXX) $(CXX_FLAGS) src/main.cpp -o $(EXECUTABLE) \
		-Iextlibs -Iextlibs/SFML/include -Iheader \
		-Lextlibs/SFML/lib -Llib -Llib/extlibs/ -lprx $(LIBS) -lsqlite3

$(EXECUTABLE): $(OBJS) lib/libprx.a lib/libsqlite3.a
	@echo Compiling statically linked version of $(EXECUTABLE)
	$(CXX) $(CXX_FLAGS) src/main.cpp -o $(EXECUTABLE) \
		-Iextlibs -Iextlibs/SFML/include -Iheader \
		-Lextlibs/SFML/lib -Llib -Llib/extlibs/ -lprx $(LIBS) -lsqlite3 -mwindows

lib/libprx.a: $(OBJS) lib
	@echo Linking game static library ...
	@ar rvs -o $@ $(OBJS)

exe-without-lib: $(OBJS) obj/main.o lib/libsqlite3.a
	@echo Compiling $(EXECUTABLE) by linking game objects ...
	$(CXX) $(CXX_FLAGS) obj/*.o -o $(EXECUTABLE) \
		-Lextlibs/SFML/lib -Llib $(LIBS) -lsqlite3

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
	cp extlibs/SFML/lib/*.dll .
	cp extlibs/SFML/lib/*.a $<

lib:
	mkdir $@

install:
	cp lib/libsfml-*.so.2.4 /usr/lib

clean:
	@rm obj/*.o

debug:
	@echo Object files: $(OBJS)

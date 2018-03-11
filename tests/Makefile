ifeq ($(OS), Windows_NT)
	CMAKE_MAKEFILE_TYPE = "MinGW Makefiles"
else
	CMAKE_MAKEFILE_TYPE = "Unix Makefiles"
endif

.PHONY: clean

init: dependencies TestPacmanRezurexion

test: TestPacmanRezurexion
	./TestPacmanRezurexion

TestPacmanRezurexion: obj $(patsubst %.cpp, obj/%.o, $(wildcard *.cpp))
	$(CXX) -o $@ obj/*.o \
		-L../lib -Llib -lUnitTest++ -lsqlite3

obj:
	mkdir obj

obj/%.o: %.cpp
	$(CXX) -c $< -o $@ \
		-I../header -I../../extlibs -I../src  \
		-I../extlibs/SFML/include -Iextlibs/unittest-cpp


dependencies: ../lib/libprx.a ../lib/libsqlite3.a lib/libUnitTest++.a

../lib/libprx.a:
	cd ../; make prx-static-lib

../lib/libsqlite3.a:
	cd ..; make lib/libsqlite3.a

lib/libUnitTest++.a:
	cd extlibs/unittest-cpp; cmake -G$(CMAKE_MAKEFILE_TYPE); make
	cp extlibs/unittest-cpp/libUnitTest++.a lib

clean:
	rm obj/*.o
	rm lib/*.a

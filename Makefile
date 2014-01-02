JAILCUR_OBJECTS= obj/basic_win.o obj/colour.o obj/data.o obj/render.o obj/standard.o obj/util.o
JAILCUR_TEST_OBJECTS= obj/jailcur_test.o

default: jailcur_test

jailcur_test: $(JAILCUR_OBJECTS) $(JAILCUR_TEST_OBJECTS)
	g++ $(JAILCUR_OBJECTS) $(JAILCUR_TEST_OBJECTS) -o bin/jailcur_test -lcurses

obj/basic_win.o: basic_win.cpp
	g++ basic_win.cpp -c -std=c++11 -o obj/basic_win.o

obj/colour.o: colour.cpp
	g++ colour.cpp -c -std=c++11 -o obj/colour.o

obj/data.o: data.cpp
	g++ data.cpp -c -std=c++11 -o obj/data.o

obj/jailcur_test.o: jailcur_test.cpp
	g++ jailcur_test.cpp -c -std=c++11 -o obj/jailcur_test.o

obj/render.o: render.cpp
	g++ render.cpp -c -std=c++11 -o obj/render.o

obj/standard.o: standard.cpp
	g++ standard.cpp -c -std=c++11 -o obj/standard.o

obj/util.o: util.cpp
	g++ util.cpp -c -std=c++11 -o obj/util.o

clean:
	-rm -f obj/*.o
	-rm -f bin/*


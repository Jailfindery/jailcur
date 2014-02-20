JAILCUR_OBJECTS= obj/basic_cwindow.o obj/basic_message_window.o obj/basic_window.o \
                 obj/colour.o obj/jailcur_except.o obj/menu_window.o obj/message_window.o \
                 obj/progress_window.o obj/render.o obj/standard.o obj/util.o
JAILCUR_TEST_OBJECTS= obj/jailcur_test.o
LD_OPTS=-lmenu -lcurses
COMPILER_OPTS=-Wall -Werror -Wno-sign-compare

default: jailcur_test

jailcur_test: $(JAILCUR_OBJECTS) $(JAILCUR_TEST_OBJECTS)
	g++ $(COMPILER_OPTS) $(JAILCUR_OBJECTS) $(JAILCUR_TEST_OBJECTS) -o bin/jailcur_test $(LD_OPTS)

obj/basic_cwindow.o: basic_cwindow.cpp
	g++ $(COMPILER_OPTS) basic_cwindow.cpp -c -std=c++11 -o obj/basic_cwindow.o

obj/basic_message_window.o: basic_message_window.cpp
	g++ $(COMPILER_OPTS) basic_message_window.cpp -c -std=c++11 -o obj/basic_message_window.o

obj/basic_window.o: basic_window.cpp
	g++ $(COMPILER_OPTS) basic_window.cpp -c -std=c++11 -o obj/basic_window.o

obj/colour.o: colour.cpp
	g++ $(COMPILER_OPTS) colour.cpp -c -std=c++11 -o obj/colour.o

obj/jailcur_except.o: jailcur_except.cpp
	g++ $(COMPILER_OPTS) jailcur_except.cpp -c -std=c++11 -o obj/jailcur_except.o

obj/menu_window.o: menu_window.cpp
	g++ $(COMPILER_OPTS) menu_window.cpp -c -std=c++11 -o obj/menu_window.o

obj/jailcur_test.o: jailcur_test.cpp
	g++ $(COMPILER_OPTS) jailcur_test.cpp -c -std=c++11 -o obj/jailcur_test.o

obj/message_window.o: message_window.cpp
	g++ $(COMPILER_OPTS) message_window.cpp -c -std=c++11 -o obj/message_window.o

obj/progress_window.o: progress_window.cpp
	g++ $(COMPILER_OPTS) progress_window.cpp -c -std=c++11 -o obj/progress_window.o

obj/render.o: render.cpp
	g++ $(COMPILER_OPTS) render.cpp -c -std=c++11 -o obj/render.o

obj/standard.o: standard.cpp
	g++ $(COMPILER_OPTS) standard.cpp -c -std=c++11 -o obj/standard.o

obj/util.o: util.cpp
	g++ $(COMPILER_OPTS) util.cpp -c -std=c++11 -o obj/util.o

clean:
	-rm -f obj/*.o
	-rm -f bin/*


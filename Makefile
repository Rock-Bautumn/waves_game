# -*- MakeFile -*-

all: waves

waves: objs/main.o objs/map.o
	g++ objs/main.o objs/map.o -lncursesw -o waves

objs/main.o: src/main.cpp
	g++ -c src/main.cpp -lncursesw -o objs/main.o

objs/map.o: src/map.cpp
	g++ -c src/map.cpp -lncursesw -o objs/map.o

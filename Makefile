CC=g++
FLAGS=-g -Wall -std=c++17 -I./include -I./lib
LIBS=-lGL -lGLEW -lSDL2 -lm
NAME=HelloWorld

build:
	make objs

objs: $(wildcard src/*.cpp) lib/lodepng.cpp
	$(CC) $(FLAGS) -c $^ $(LIBS)
	make link

link:
	$(CC) $(FLAGS) $(wildcard *.o) $(LIBS) -o $(NAME).out

clean:
	rm -f *.o

install:
	sudo bash install-depends.sh

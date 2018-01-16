CC=g++
FLAGS=-g -Wall -std=c++17 -I./include -I./lib
LIBS=-lGL -lGLEW -lSDL2
NAME=HelloWorld

build: 
	make objs

objs: $(wildcard */*.cpp)
	$(CC) $(FLAGS) -c $^ $(LIBS)
	make link

link:
	$(CC) $(FLAGS) $(wildcard *.o) $(LIBS) -o $(NAME).out
	make clean

clean:
	rm -f *.o

install:
	sudo bash install-depends.sh

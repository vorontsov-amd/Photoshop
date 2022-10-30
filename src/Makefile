all: main

main: main.o
	g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -O2 -std=c++20

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -rf *.o main


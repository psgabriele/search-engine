CC = c++ -I include -std=c++17

main:	build/main.o build/searchengine.o
	$(CC) build/main.o build/searchengine.o -o main

build/main.o:	main.cpp
	$(CC) -c main.cpp -o build/main.o

build/searchengine.o:	include/searchengine.hpp src/entidades/searchengine.cpp
	$(CC) -c src/entidades/searchengine.cpp -o build/searchengine.o

clean:
	rm build/*.o
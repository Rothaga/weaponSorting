CC=g++
CFLAGS=-Wall -std=c++11 -g

csgo: csgo.o 
	$(CC) -o $@ $< $(CFLAGS) 

csgo.o: main.cpp
	$(CC) -c -o $@ $< $(CFLAGS) 
	
PHONY: clean

clean:
	rm -f ./*.o 

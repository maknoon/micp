CC=g++
CFLAGS=-Wall -std=c++11

ts: main.cc
	$(CC) $(CFLAGS) -g -c twosum.cc -o twosum.o
	$(CC) $(CFLAGS) -g main.cc twosum.o -o ts

clean:
	rm -rf ts twosum.o ts.dSYM/

CC=g++
CFLAGS=-Wall -std=c++11

ts: threesum.cc
	$(CC) $(CFLAGS) -g -c twosum.cc -o twosum.o
	$(CC) $(CFLAGS) -g threesum.cc twosum.o -o ts

clean:
	rm -rf ts twosum.o ts.dSYM/

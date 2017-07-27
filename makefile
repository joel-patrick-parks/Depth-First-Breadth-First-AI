CC = g++
CFLAGS = -O0

default: hw1

hw1: Main.o
	$(CC) -std=c++0x $(CFLAGS) -o hw1 Main.o

Main.o: Main.cpp
	$(CC) -std=c++0x $(CFLAGS) -c Main.cpp

clean:
	$(RM) count *.o *~

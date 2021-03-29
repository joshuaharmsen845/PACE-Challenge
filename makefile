CC = g++
CFLAGS = -Wall -g

pace: code.o graph.o
	$(CC)	$(CFLAGS)	-o	pace	code.o	graph.o

	$(CC)	$(CFLAGS)	-c	code.cpp	graph.cpp

graph.o: graph.cpp graph.h
	$(CC)	$(CFLAGS)	-c	graph.cpp

#
#  Joshua Harmsen and AJ Zuckerman
#
#  PACE  Challenge 2021 - Cluster Editing
#  May 2021
#
#  A nuanced approach to cluster editing which utilizes existing cliques in the
#  formation of "complete" clusters by considering whether to add or cut
#  a vertex from the cluster piece-wise.
#

CC = g++
CFLAGS = -Wall -g

pace: code.o graph.o
	$(CC)	$(CFLAGS)	-o	pace	code.o	graph.o

	$(CC)	$(CFLAGS)	-c	code.cpp	graph.cpp

graph.o: graph.cpp graph.h
	$(CC)	$(CFLAGS)	-c	graph.cpp

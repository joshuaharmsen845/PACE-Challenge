#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>
#include <queue>
#include <csignal>
#include <cstring>
#include <unistd.h>
#include "graph.h"


/*
  Joshua Harmsen and AJ Zuckerman

  PACE  Challenge 2021 - Cluster Editing
  May 2021

  A nuanced approach to cluster editing which utilizes existing cliques in the
  formation of "complete" clusters by considering whether to add or cut
  a vertex from the cluster piece-wise.
*/


// Globsal graph and set of unhandled vertices
Graph graph = Graph();
std::unordered_set<int> toHandle;
volatile sig_atomic_t tle = 0;

// Non-functioning signal handler to cut all remaining edges
//
void term( int signum ) {
   graph.cutAll(toHandle);
   tle = 1;
   exit(signum);
}


int main(int argc,  char* argv[]) {
  // Set up signal handling of SIGTERM
  struct sigaction action;
  memset(&action, 0, sizeof(struct sigaction));
  action.sa_handler = term;
  action.sa_flags = 0;
  sigaction(SIGTERM, &action, NULL);


  // Form a queue of vertices so we can cover all vertices
  std::queue<int> q;
  for (int i = 1; i <= graph.vertices; i++){
    q.push(i);
    toHandle.insert(i);
  }


  while (!q.empty()) { // While we have vertices to consider
    int elm = q.front();
    q.pop();
    if (toHandle.find(elm) != toHandle.end()){  // If we have not handled yet
      std::unordered_set<int> clique = graph.findClique(elm); //Find clique
      graph.formCluster(clique); // Transform the clique into a cluster

    for (auto elm: clique)
      toHandle.erase(elm); // Remove handled vertices
    }
  }
  return 0;
}
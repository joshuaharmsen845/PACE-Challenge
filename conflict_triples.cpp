// Conflict Triples
// A.J. Zuckerman and Josh Harmsen
// Checks for conflict triples in a passed cluster and decides what to do with them

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>
#include "graph.h"

void add_edges(size_t i, size_t j, size_t k, std::unordered_set <std::tuple> & moves, map & graph) {
  bool j_nei = false;
  bool k_nei = false;
  for (size_t p = 0; p < graph[i]; p++) {
    if (graph[i][p] == j)
      j_nei = true;
    if (graph[i][p] == k)
      k_nei = true;
  if (!j_nei) {
    graph[i] += [j];
    moves += [(i, j)]; // need to mark these as adds or deletes
  }
  if (!k_nei) {
    graph[i] += [k];
    moves += [(i, k)]; // need to mark these as adds or deletes
  }
}

void delete_edges(size_t i, size_t j, size_t k, std::unordered_set <std::tuple> & moves, map & graph) {
  for (size_t p = 0; p < graph[i]; p++) {
    if (graph[i][p] == j) {
      graph[i].remove(j); // I don't know if this is legal
      moves += [(i, j)]; // need to mark these as adds or deletes
    }
    if (graph[i][p] == k){
      graph[i].remove(k); // I don't know if this is legal
      moves += [(i, k)]; // need to mark these as adds or deletes
    }
  }
}


void conflict_triples(std::unordered_set <int> & cluster, std::unordered_set <int> & connectedness, map & graph, std::unordered_set <std::tuple> & moves) {
  // takes a cluster and checks every conflict triple and handles it
  float con_max = connectedness.length() * (connectedness.length() - 1);
  float con = 0;
  for (size_t i = 0; i < connectedness.length(); i++)
    con += connectedness[i];

  float con_per = con/con_max;
  // use this to make most decisions for the most part follow this unless obvious cuts or adds are available

  // loop through all the vertices in the cluster three times for each possible triple
  // THERE MUST BE A BETTER WAY TO IDENTIFY CONFLICT TRIPLES
  for (size_t i = 0; i < connectedness.length(); i++) {
    for (size_t j = 0; j < connectedness.length(); j++) {
      for (size_t k = 0; k < connectedness.length(); k++) {
        for (size_t p = 0; p < graph[i]; p++) {
          size_t trip = 0;
          if (graph[i][p] == j || graph[i][p] == k)
            trip++;
        }
        if ((trip == 1 || trip == 2) && con_per > .5)
          add_edges(i, j, k, moves, graph);
        else delete_edges(i, j, k, moves, graph);
      }
    }
  }
}

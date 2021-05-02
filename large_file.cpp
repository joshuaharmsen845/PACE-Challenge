#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>
#include "graph.h"

void clique_it(graph graph, unordered_set cluster) {
  for (size_t i = 0; i < cluster.size(); i++) {
    unordered_set neighbors = graph[i];
    unordered_set not_nei = cluster;
    for (size_t j = i + 1; j < neighbors.size(); j++) {
      for (size_t k = 0; k < cluster.size(); k++) {
        if (cluster[k] == neighbors[j])
          not_nei.remove(cluster[k]);
      }
    }
    for (size_t l = 0; l < not_nei.size(); l++)
      graph.addEdge(i, l);
  }
}

void break_it(graph graph, unordered_set cluster) {
  for (size_t i = 0; i < cluster.size(); i++) {
    unordered_set neighbors = graph[i];
    for (size_t j = i + 1; j < neighbors.size(); j++) {
      for (size_t k = 0; k < cluster.size(); k++) {       //Does this cut E/2 edges or all of them? We can get away with E/2.
        if (cluster[k] == neighbors[j])
          graph.cutEdge(i, j);              
      }
    }
}


void large_file(graph graph) {
  for (size_t i = 0; i < graph.size(); i++) {
    float con = 0;
    unordered_set cluster = graph.findCluster(i);
    int max_con = cluster.size() * (cluster.size() - 1) //If we calculate this, why use connectedness?
    for (size_t j = 0; j < cluster.size(); j++)         //We know the number of edges, its an attribute of the Graph class. 
      con += graph.connectedness(j)
    float con_per = con / con_max
    if (con_per < .5)
      clique_it(graph, cluster);
    else
      break_it(graph, cluster);
  }
}

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>
#include "graph.h"


int main(int argc,  char* argv[]) {

  Graph graph = Graph();
  //  graph.printGraph();

  int var = 10;
//  std::cout << "Largest clique containing "<< var <<  ":" << std::endl;
//  for (auto elm: graph.findClique(var))
//    std::cout << elm << " ";
//  std::cout << std::endl;

//  std::cout << "Cluster containing " << var << ":" << std::endl;
//  for (auto elm: graph.findCluster(var))
//    std::cout << elm << " ";
//  std::cout << std::endl;

  std::cout << "Connectedness of " << var << ":" << std::endl;
  std::cout << graph.connectedness(var) << std::endl;
}

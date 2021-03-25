#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>
#include "graph.h"


int main(int argc,  char* argv[]) {

  if (argc > 1){
    Graph graph = Graph(argv[1]);
  //  graph.printGraph();

  int var = 10;
  std::cout << "Largest clique containing "<< var <<  ":" << std::endl;
  for (auto elm: graph.findClique(var))
    std::cout << elm << " ";
  std::cout << std::endl;

  } else {
    std::cout << "No file given." << std::endl;
  }
}

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>
#include "graph.h"

int main(int argc,  char* argv[]) {

  if (argc > 1){
    Graph graph = Graph(argv[1]);

    graph.printGraph();
  } else {
    std::cout << "No file given." << std::endl;
  }
}

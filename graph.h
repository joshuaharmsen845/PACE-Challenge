#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>

class Graph {
 
  public:
    std::map<unsigned int,std::unordered_set<unsigned int>>  graph;

    Graph(std::string fileName);

    void printGraph();
};

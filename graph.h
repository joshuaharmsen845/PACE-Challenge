#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>

class Graph {

  public:
    std::map<unsigned int,std::unordered_set<unsigned int>>  graph;
    unsigned int vertices;
    unsigned int edges;

    Graph(std::string fileName);

    std::unordered_set<unsigned int> operator [](int i);

    void printGraph();

    void addEdge(unsigned int u, unsigned int v);

    void cutEdge(unsigned int u, unsigned int v);

};

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>

class Graph {

  public:
    std::map<int,std::unordered_set<int>>  graph;
    int vertices;
    int edges;

    Graph();

    std::unordered_set<int> operator [](int i);

    void printGraph();

    void addEdge(int u, int v);

    void cutEdge(int u, int v);

    bool hasEdge(int u, int v);

    bool cliqueCheck(std::unordered_set<int> clique);

    std::unordered_set<int> findClique(int startNode);

};

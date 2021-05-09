#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>


/*
  Joshua Harmsen and AJ Zuckerman

  PACE  Challenge 2021 - Cluster Editing
  May 2021

  A nuanced approach to cluster editing which utilizes existing cliques in the
  formation of "complete" clusters by considering whether to add or cut
  a vertex from the cluster piece-wise.
*/


class Graph {

  public:
    std::map<int,std::unordered_set<int>> graph;
    int vertices;
    int edges;

    Graph();

    std::unordered_set<int> operator [](int i);

    void printGraph();

    void cutAll(std::unordered_set<int> unHandled);

    void addEdge(int u, int v);

    void cutEdge(int u, int v);

    bool hasEdge(int u, int v);

    bool cliqueCheck(std::unordered_set<int>& clique);

    std::unordered_set<int> findClique(int startNode);

    std::unordered_set<int> findCluster(int startNode);

    float connectedness(int startNode);

    int formCluster(std::unordered_set<int>& clique);

    //void clique_it(std::unordered_set<int> cluster);

    //void break_it(std::unordered_set<int> cluster);

    //void large_file();
};

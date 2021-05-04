#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>
#include <queue>
#include <csignal>
#include "graph.h"

Graph graph = Graph();

void signalHandler( int signum ) {
   //std::cout << "Interrupt signal (" << signum << ") received.\n";
   graph.cutAll();

   exit(signum);
}

int main(int argc,  char* argv[]) {
  signal(SIGTERM, signalHandler);


  std::queue<int> q;
  std::unordered_set<int> toHandle;
  for (int i = 1; i <= graph.vertices; i++){
    q.push(i);
    toHandle.insert(i);
  }


  while (!q.empty()) {
    int elm = q.front();
    q.pop();
    if (toHandle.find(elm) != toHandle.end()){
      //std::cout << "Finding for " << elm << std::endl;
      std::unordered_set<int> clique = graph.findClique(elm);
      int cost = graph.cliqueCost(clique);
      //std::cout << "Costed: " << cost << std::endl;

    for (auto elm: clique)
      toHandle.erase(elm);

    //graph.printGraph();
    }
  }



//  std::cout << "Cluster containing " << var << ":" << std::endl;
//  for (auto elm: graph.findCluster(var))
//    std::cout << elm << " ";
//  std::cout << std::endl;

//  std::cout << "Connectedness of " << var << ":" << std::endl;
//  std::cout << graph.connectedness(var) << std::endl;

}

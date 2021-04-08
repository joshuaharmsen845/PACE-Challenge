#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>
#include <queue>
#include "graph.h"

Graph::Graph() {
    std::string line;

    std::getline(std::cin, line); // Get the first line
    line = line.substr(6);
    int sep = line.find(' ');
    vertices = stoi(line.substr(0, sep)); //Get the vertex count
    edges = stoi(line.substr(sep));       //Get the edge count

    while (std::getline(std::cin, line)) {
    // if (!(line[0] == 'p' || line[0] == 'c')) { REMOVED FOR EFFICIEnCY
    // WILL BE AN ISSUE IF WE HAVE A COMMENT LINE IN THE .GR INPUT

        int sep = line.find(' ');
        int u = stoi(line.substr(0, sep)); //Separate by the space
        int v = stoi(line.substr(sep));    //to get the vertices
        // ISSUES IF COMMENT ON END OF LINE

        bool uInGraph = (graph.find(u) != graph.end());
        bool vInGraph = (graph.find(v) != graph.end());

        if (!uInGraph) {    // If u is not yet in the graoh
          if (!vInGraph) {  // If v is not yet in the Graph
            //Create entries for both
            std::unordered_set <int> setU;
            setU.insert(v);
            graph.insert(
              std::pair <int,std::unordered_set<int>>(u, setU));

            std::unordered_set <int> setV;
            setV.insert(u);
            graph.insert(
              std::pair <int,std::unordered_set<int>>(v, setV));

          } else {            //If v is in graph, but u isn't
            std::unordered_set <int> setV;
            setV.insert(v);
            graph.insert(
              std::pair <int,std::unordered_set<int>>(u, setV));

            graph.find(v)->second.insert(u);  //Insert u into v's set
          }
        } else if (!vInGraph) { //If u is in the graph, but v isn't
            std::unordered_set <int> setU;
            setU.insert(u);
            graph.insert(
              std::pair <int,std::unordered_set<int>>(v, setU));

            graph.find(u)->second.insert(v);  //Insert v into u's set
          } else { //If u and v are both in the graph, just insert
            graph.find(v)->second.insert(u);
            graph.find(u)->second.insert(v);
          }
      //}
    }
}

void Graph::printGraph() {
  std::cout  << "Vertices: " << vertices << std::endl;
  std::cout << "Edges: " << edges << std::endl;
  for (auto key: graph) {     //For every vertex in the graph
    std::cout << key.first << " -> ";
    for (auto i: key.second) //For every vertex in key's unordered_set
      std::cout << i << " ";
    std::cout << std::endl;
  }
}

std::unordered_set<int> Graph::operator [](int i) {
  return graph[i];
}

//Requires both u and v to exist already
void Graph::addEdge(int u, int v) {
  graph.find(v)->second.insert(u);
  graph.find(u)->second.insert(v);
}

//Requires both u and v to exist already
void Graph::cutEdge(int u, int v) {
  graph.find(v)->second.erase(u);
  graph.find(u)->second.erase(v);
}

bool Graph::hasEdge(int u, int v) {
return (graph[u].find(v) != graph[u].end());
}

//Simply makes sure all elements in the clique have edges to one another
bool Graph::cliqueCheck(std::unordered_set<int> clique) {
  for (auto u: clique)
    for (auto v: clique)
      if (u != v)
        if (!hasEdge(u, v))
          return false;
  return true;
}

std::unordered_set<int> Graph::findClique(int startNode) {
  std::unordered_set<int> clique;
  std::unordered_set<int> bestClique;
  bestClique.insert(startNode);
  int edges = 0;
  int bestEdges = 5000000;
  std::unordered_set<int> startSet = graph[startNode]; //Get all neighbors
  clique.insert(startNode);
  edges += graph[startNode].size();

  for (auto u: startSet) {
    clique.insert(u);             //TRY EVERY POSSIBLE CLIQUE COMBINATION
    edges += graph[u].size();
    for (auto v: graph[u]) {
      if (v != startNode) {
        clique.insert(v);           //TRY TO INSERT U'S NEIGHBOR
        edges += graph[v].size();
      }
      if (!cliqueCheck(clique)){
        clique.erase(v);          //UNDO IF WE DON'T HAVE A CLIQUE
        edges -= graph[v].size();
      } else {
        startSet.erase(v);        //If it worked, remove it so we don't duplicate
      }
    }
    //edges = edges / 2;
    //std::cout << "edges: " << edges << " and size: " << clique.size() << std::endl;
    //for (auto elm: clique)
    //  std::cout << elm << " ";
    //std::cout << std::endl;
    if (edges -(clique.size()*(clique.size()-1)) < //MINIMIZE EXTRA EDGES IN CLIQUE
        bestEdges - (bestClique.size()*(bestClique.size())-1)) {
      bestClique = clique;
      bestEdges = edges;
    }
    //for (auto elm: clique)
    //  std::cout << elm << " ";
    //std::cout << std::endl;
    clique.clear();               //CLEAR AND TRY AGAIN
    clique.insert(startNode);
    edges = graph[startNode].size();
  }

  std::cout << "Choose clique of size: " << bestClique.size() <<
    " with " << bestEdges << " edges." << std::endl;
  return bestClique;
}

//Uses BFS to check whole cluster, returns as unordered_set
std::unordered_set<int> Graph::findCluster(int startNode) {
    std::unordered_set<int> cluster;
    std::queue<int> q;

    q.push(startNode);
    cluster.insert(startNode);
    while (!q.empty()) {
      int v = q.front();    //Get the popped node
      q.pop();

      for (auto neighbor: graph[v]) {   //Insert popped node's neighbors
        if (cluster.find(neighbor) == cluster.end()) {
          q.push(neighbor);
          cluster.insert(neighbor);
        }
      }
    }

    return cluster;
}

float Graph::connectedness(int startNode) {
  float edges = (float)graph[startNode].size();
  float clusterSize = (float)findCluster(startNode).size();

  std::cout << "Edges: " << edges << " /// Cluster Size: " << clusterSize << std::endl;
  return edges/clusterSize;
}

//Computes the cost of deleting all edges from the clique to the outside graph
int Graph::cliqueCost(std::unordered_set<int> clique) {
  int count = 0;
  int adds = 0;
  int cuts = 0;
  std::unordered_set<int> handled;

  for (auto node: clique) { //For every node in the clique
    for (auto neighbor: graph[node]) { //For every neighbor of said node
      if (handled.find(neighbor) == handled.end()) {//If we have not yet handled neighbor
        handled.insert(neighbor);
        if (clique.find(neighbor) == clique.end()) {//If the neighbor is not in clique
          for (auto v: clique) { //Check all possible clique connections
            if (hasEdge(neighbor, v)) //Check if we should cut or add to clique
              cuts ++; //Store cuts somewhere later
            else
              adds ++; //Store additions somewhere later
          }
        //  std::cout << "Current node is: " << neighbor << std::endl;
        //  std::cout << "Adds: " << adds << std::endl;
        //  std::cout << "Cuts: " << cuts << std::endl << std:: endl;
        }

      if (cuts <= adds){
        count += cuts;
      }
      else {
        clique.insert(neighbor);
        count += adds;
      }
      adds = 0;
      cuts = 0;
      }
    }
  }

  int size = 0;
  std::cout << "Formed the cluster: " << std::endl;
  for (auto elm: clique){
    std::cout << elm << " ";
    size ++;
  }
  std::cout << std::endl;
  std::cout << "New size: " << size << std::endl;
  return count;
}

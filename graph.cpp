#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>
#include <queue>
#include "graph.h"


/*
  Joshua Harmsen and AJ Zuckerman

  PACE  Challenge 2021 - Cluster Editing
  May 2021

  A nuanced approach to cluster editing which utilizes existing cliques in the
  formation of "complete" clusters by considering whether to add or cut
  a vertex from the cluster piece-wise.
*/

// Graph Constructor - reads from stdin and accepts .gr graph format.
// Forms a map data structure of ints to unordered_sets to represent
// a vertex and its edge connections.
Graph::Graph() {
    std::string line;

    std::getline(std::cin, line); // Get the first line
    line = line.substr(6);
    int sep = line.find(' ');
    vertices = stoi(line.substr(0, sep)); //Get the vertex count
    edges = stoi(line.substr(sep));       //Get the edge count

    while (std::getline(std::cin, line)) {

        int sep = line.find(' ');
        int u = stoi(line.substr(0, sep)); //Separate by the space
        int v = stoi(line.substr(sep));    //to get the vertices

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
    }
}

// printGraph - For debugging purposes, prints out the number of vertices and
// edges in the graph, followed by all entries in the map.
void Graph::printGraph() {
  std::cout  << "Vertices: " << vertices << std::endl;
  std::cout << "Edges: " << edges << std::endl;
  for (auto key: graph) {     // For every vertex in the graph
    std::cout << key.first << " -> ";
    for (auto i: key.second) // For every vertex in key's unordered_set
      std::cout << i << " ";
    std::cout << std::endl;
  }
}

// cutAll - Cuts all remaining, unhandled vertices from the eachother.
// Useful to avoid running out of time.
// Non-functioning since this is not async-safe.
void Graph::cutAll(std::unordered_set<int> unHandled) {
  for (auto key: graph) {     // For every vertex in the graph
    if (unHandled.find(key.first) != unHandled.end()){ //If we have not handled
      for (auto i: key.second) { // For every vertex in key's unordered_set
          std::cout << key.first << " " << i << std::endl;
          cutEdge(i, key.first); // Cut the edge
      }
    }
  }
  return;
}

// [] operator - Return the unordered_set related to a certain key
std::unordered_set<int> Graph::operator [](int key) {
  return graph[key];
}

// addEdge - adds the edge (u, v) to the graph
// Requires both u and v to exist already
void Graph::addEdge(int u, int v) {
  graph.find(v)->second.insert(u);
  graph.find(u)->second.insert(v);
}

// cutEdge - cuts the edge (u, v) from the graph
// Requires both u and v to exist already
void Graph::cutEdge(int u, int v) {
  graph.find(v)->second.erase(u);
  graph.find(u)->second.erase(v);
}


// hasEdge - Return a bool relating to whether the graph has the edge (u, v)
bool Graph::hasEdge(int u, int v) {
return (graph[u].find(v) != graph[u].end());
}

// cliqueCheck - returns a bool reating to whether the given set of vertices
// is a clique or not.
// Simply makes sure all elements in the clique have edges to one another
bool Graph::cliqueCheck(std::unordered_set<int>& clique) {
  for (auto u: clique)
    for (auto v: clique)
      if (u != v)
        if (!hasEdge(u, v))
          return false;
  return true;
}


// findClique - Given a starting node, finds the least connected clique it is a
// part of. This clique is subsequently turned into a cluster
std::unordered_set<int> Graph::findClique(int startNode) {
  std::unordered_set<int> clique;
  std::unordered_set<int> bestClique;
  bestClique.insert(startNode); // The clique must include startNode
  int edges = 0;
  int bestEdges = 5000000;
  std::unordered_set<int> startSet = graph[startNode]; // Get all neighbors
  clique.insert(startNode);
  edges += graph[startNode].size();

  for (auto u: startSet) { // For every neighbor of startNode
    clique.insert(u);             // Try every possible clique combination
    edges += graph[u].size();
    for (auto v: graph[u]) {
      if (v != startNode) {
        clique.insert(v);           // Try to insert u's neighbor
        edges += graph[v].size();
      }
      if (!cliqueCheck(clique)){
        clique.erase(v);          // Undo if this does not form a clique
        edges -= graph[v].size();
      } else {
        startSet.erase(v);        // If it worked, remove it so we don't duplicate
      }
    }

    if (edges - (clique.size()*(clique.size()-1)) < //Minimize edges in clique
        bestEdges - (bestClique.size()*(bestClique.size())-1)) {
      bestClique = clique; // If this is a new best, update
      bestEdges = edges;
    }

    clique.clear();               // Clear and try again
    clique.insert(startNode);
    edges = graph[startNode].size();
  }

  return bestClique;
}

// findCluster - Returns the cluster to which startNode is a member of
// Uses a BFS to check all connections.
std::unordered_set<int> Graph::findCluster(int startNode) {
    std::unordered_set<int> cluster;
    std::queue<int> q;

    q.push(startNode);
    cluster.insert(startNode);
    while (!q.empty()) {
      int v = q.front();    // Get the popped node
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


// connectetedness - Returns a float relating the number of edges a node has
// to the number of vertices in its cluster.
float Graph::connectedness(int startNode) {
  float edges = (float)graph[startNode].size();
  float clusterSize = (float)findCluster(startNode).size();

  return edges/clusterSize;
}

// formCluster - Forms a cluster from a given clique. For all connected
// vertices, decides piece-wise whether to add it to the clique via adding
// edges or to remove it from the cluster by cutting all edges to the clique
// Computes the cost of deleting all edges from the clique to the outside graph
int Graph::formCluster(std::unordered_set<int>& clique) {
  int count = 0;
  int adds = 0;
  int cuts = 0;
  std::unordered_set<std::string> addStrings;
  std::unordered_set<std::string> cutStrings;
  std::unordered_set<int> handled;
  std::unordered_set<int> addList;
  std::unordered_set<int> cutList;
  std::queue<int> q;

  for (auto elm: clique)
    q.push(elm);

  while (!q.empty()) { // For every node in the clique, even if we add
    int node = q.front();
    q.pop();

    std::queue<int> neighbors; // Initialize queue to hold neighbors
    for (auto elm: graph[node])
      neighbors.push(elm);

    while  (!neighbors.empty()) {
    int neighbor = neighbors.front(); // Get popped neighbor
    neighbors.pop();
    if (cutList.find(neighbor) == cutList.end()) {
      // If we haven't cut this already
       if (handled.find(neighbor) == handled.end()) {
         // If we have not yet handled neighbor
        handled.insert(neighbor);
        if (clique.find(neighbor) == clique.end()) {
          // If the neighbor is not in clique
          for (auto v: clique) { // Check all possible clique connections
            if (hasEdge(neighbor, v)) {
              // Check if we should cut or add to clique
              cuts ++; // Store cut and increment
              cutStrings.insert(std::to_string(neighbor) + " " + std::to_string(v));
            } else {
              adds ++; // Store addition and increment
              addStrings.insert(std::to_string(neighbor) + " " + std::to_string(v));
            }
          }
        }

        if (cuts <= adds){
          count += cuts; // Complete the cuts
          for (std::string edge: cutStrings) {
            int sep = edge.find(' ');
            int u = stoi(edge.substr(0, sep)); // Separate by the space
            int v = stoi(edge.substr(sep));    // to get the vertices
            cutList.insert(u);
            std::cout << edge << std::endl;
            cutEdge(u, v);

          }
        }
        else {
          clique.insert(neighbor); // Complete the additions
          q.push(neighbor);
          count += adds;
          for (std::string edge: addStrings) {
            int sep = edge.find(' ');
            int u = stoi(edge.substr(0, sep)); // Separate by the space
            int v = stoi(edge.substr(sep));    // to get the vertices
            addList.insert(u);
            std::cout << edge << std::endl;
            addEdge(u, v);
          }
        }

        adds = 0;
        addStrings.clear();
        cuts = 0;
        cutStrings.clear(); // Reset for subsequent run
        }
      }
    }
  }

  for (auto u: addList) // Complete the final cuts between those vertices we cut
    for (auto v: cutList) // and those we decided to add
      if (hasEdge(u,v)) {
        std::cout << u << " " << v << std::endl;
        cutEdge(u, v);
      }
  return count;
}

/*
void Graph::clique_it(std::unordered_set<int> cluster) {
  for (auto i: cluster) {
    std::unordered_set<int> neighbors = graph[i];
    std::unordered_set<int> not_nei = cluster;
    for (auto j: neighbors) {
      for (auto k: cluster) {
        if (k == j)
          not_nei.erase(k);
      }
    }
    for (auto l: not_nei) {
      if (l != i) {
        addEdge(i, l);
        std::cout << i << " " << l << std::endl;
      }
    }
  }
}

void Graph::break_it(std::unordered_set<int> cluster) {
  for (auto i: cluster) {
    std::unordered_set<int> neighbors = graph[i];
    for (auto j: neighbors) {
      for (auto k: cluster)        //Does this cut E/2 edges or all of them? We can get away with E/2.
        if (k == j) {//Cannot iterate
          if (i != j) {
            cutEdge(i, j);
            std::cout << i << " " << j << std::endl;
          }
        }
    }
  }
}

void Graph::large_file() {
  std:: unordered_set<int> used;
  for (auto i: graph) {
    float con = 0;
    bool iter = false;
    std::unordered_set<int> cluster = findCluster(i.first);
    int max_con = cluster.size() * (cluster.size() - 1);
    for (auto j: cluster)
      con += connectedness(j);
    float con_per = con / max_con;
    for (auto j: cluster) {
      for (auto k: used) {
        if (j == k)
          iter = true;
      }
    }
    if (!iter) {
      if (con_per < .5)
        clique_it(cluster);
      else
        break_it(cluster);
      }
  }
}
*/

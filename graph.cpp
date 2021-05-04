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

void Graph::cutAll() {
  for (auto key: graph) {     //For every vertex in the graph
    for (auto i: key.second) //For every vertex in key's unordered_set
      std::cout << i << " " << key.first << std::endl;
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
  //printGraph();
  //std::cout << "CUTTING" << std::endl;
  graph.find(v)->second.erase(u);
  graph.find(u)->second.erase(v);
//  printGraph();
}

bool Graph::hasEdge(int u, int v) {
return (graph[u].find(v) != graph[u].end());
}

//Simply makes sure all elements in the clique have edges to one another
bool Graph::cliqueCheck(std::unordered_set<int>& clique) {
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

  // std::cout << "Choose clique of size: " << bestClique.size() <<
  //   " with " << bestEdges << " edges." << std::endl;
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

  //std::cout << "Edges: " << edges << " /// Cluster Size: " << clusterSize << std::endl;
  return edges/clusterSize;
}

//Computes the cost of deleting all edges from the clique to the outside graph
int Graph::cliqueCost(std::unordered_set<int>& clique) {
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

  while (!q.empty()) { //For every node in the clique, even if we add
    int node = q.front();
    q.pop();

    std::queue<int> neighbors; //Initialize queue to hold neighbors
    for (auto elm: graph[node])
      neighbors.push(elm);

    while  (!neighbors.empty()) {
    int neighbor = neighbors.front(); //Get popped neighbor
    neighbors.pop();
    if (cutList.find(neighbor) == cutList.end()) { //If we haven't cut this already
       if (handled.find(neighbor) == handled.end()) {//If we have not yet handled neighbor
        handled.insert(neighbor);
        if (clique.find(neighbor) == clique.end()) {//If the neighbor is not in clique
          for (auto v: clique) { //Check all possible clique connections
            if (hasEdge(neighbor, v)) { //Check if we should cut or add to clique
              cuts ++; //Store cuts somewhere later
              cutStrings.insert(std::to_string(neighbor) + " " + std::to_string(v));
            } else {
              adds ++; //Store added somewhere later
              addStrings.insert(std::to_string(neighbor) + " " + std::to_string(v));
            }
          }
        }

        if (cuts <= adds){
          //std::cout << "Cutting" << std::endl;
          count += cuts;
          for (std::string edge: cutStrings) {
            //std::cout << "EDGE: " << edge << std::endl;
            int sep = edge.find(' ');
            int u = stoi(edge.substr(0, sep)); //Separate by the space
            int v = stoi(edge.substr(sep));    //to get the vertices
            cutList.insert(u);
            std::cout << edge << std::endl;
            cutEdge(u, v); //causing seg fault somewhere?

          }
        }
        else {
          //std::cout << "Adding" << std::endl;
          clique.insert(neighbor);
          q.push(neighbor);
          count += adds;
          for (std::string edge: addStrings) {
            //std::cout << "EDGE:" << edge << std::endl;
            int sep = edge.find(' ');
            int u = stoi(edge.substr(0, sep)); //Separate by the space
            int v = stoi(edge.substr(sep));    //to get the vertices
            addList.insert(u);
            std::cout << edge << std::endl;
            addEdge(u, v);
          }
        }
        adds = 0;
        addStrings.clear();
        cuts = 0;
        cutStrings.clear();
        }
      }
    }
  }


  // int size = 0;
  // std::cout << "Formed the cluster: " << std::endl;
  // for (auto elm: clique){
  //   std::cout << elm << " ";
  //   size ++;
  // }
  // std::cout << std::endl;
  // std::cout << "New size: " << size << std::endl;
  // //printGraph();

  for (auto u: addList)
    for (auto v: cutList)
      if (hasEdge(u,v)) {
        std::cout << u << " " << v << std::endl;
        cutEdge(u, v);
      }
  return count;
}

// void Graph::clique_it(std::unordered_set<int> cluster) {
//   for (size_t i = 0; i < cluster.size(); i++) { //These are not the elements of the cluster
//     std::unordered_set<int> neighbors = graph[i];
//     std::unordered_set<int> not_nei = cluster;
//     for (size_t j = i + 1; j < neighbors.size(); j++) {
//       for (size_t k = 0; k < cluster.size(); k++) {
//         if (cluster[k] == neighbors[j]) //Cannot iterate
//           not_nei.erase(cluster[k]); //Cannot iterate
//       }
//     }
//     for (size_t l = 0; l < not_nei.size(); l++) //These are not the elements of not_nei
//       addEdge(i, l);
//   }
// }
//
// void Graph::break_it(std::unordered_set<int> cluster) {
//   for (size_t i = 0; i < cluster.size(); i++) { //These are not the elements of the cluster
//     std::unordered_set<int> neighbors = graph[i];
//     for (size_t j = i + 1; j < neighbors.size(); j++) {
//       for (size_t k = 0; k < cluster.size(); k++)        //Does this cut E/2 edges or all of them? We can get away with E/2.
//         if (cluster[k] == neighbors[j]) //Cannot iterate
//           cutEdge(i, j);
//     }
//   }
// }
//
// void Graph::large_file() {
//   for (size_t i = 0; i < graph.size(); i++) { //Deal with some cluster, but then deal with it again.
//     float con = 0;                            //Consider the cluster {1, 2, 3}, we do 3x the work
//     std::unordered_set<int> cluster = findCluster(i);
//     int max_con = cluster.size() * (cluster.size() - 1);
//     for (size_t j = 0; j < cluster.size(); j++) //These are not the elements of the cluster
//       con += connectedness(j);
//     float con_per = con / max_con;
//     if (con_per < .5)
//       clique_it(cluster);
//     else
//       break_it(cluster);
//   }
// }

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
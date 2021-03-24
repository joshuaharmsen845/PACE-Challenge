#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>
#include "graph.h"

Graph::Graph(std::string fileName) {
    std::string line;
    std::ifstream file(fileName);

    if (file.is_open()) {
      std::getline(file, line); // Get the first line
      line = line.substr(6);
      int sep = line.find(' ');
      vertices = stoi(line.substr(0, sep)); //Get the vertex count
      edges = stoi(line.substr(sep));       //Get the edge count

      while (std::getline(file, line)) {
      // if (!(line[0] == 'p' || line[0] == 'c')) { REMOVED FOR EFFICIEnCY
      // WILL BE AN ISSUE IF WE HAVE A COMMENT LINE IN THE .GR INPUT

          int sep = line.find(' ');
          unsigned int u = stoi(line.substr(0, sep)); //Separate by the space
          unsigned int v = stoi(line.substr(sep));    //to get the vertices
          // ISSUES IF COMMENT ON END OF LINE

          bool uInGraph = (graph.find(u) != graph.end());
          bool vInGraph = (graph.find(v) != graph.end());

          if (!uInGraph) {    // If u is not yet in the graoh
            if (!vInGraph) {  // If v is not yet in the Graph
              //Create entries for both
              std::unordered_set <unsigned int> setU;
              setU.insert(v);
              graph.insert(
                std::pair <unsigned int,std::unordered_set<unsigned int>>(u, setU));

              std::unordered_set <unsigned int> setV;
              setV.insert(u);
              graph.insert(
                std::pair <unsigned int,std::unordered_set<unsigned int>>(v, setV));

            } else {            //If v is in graph, but u isn't
              std::unordered_set <unsigned int> setV;
              setV.insert(v);
              graph.insert(
                std::pair <unsigned int,std::unordered_set<unsigned int>>(u, setV));

              graph.find(v)->second.insert(u);  //Insert u into v's set
            }
          } else if (!vInGraph) { //If u is in the graph, but v isn't
              std::unordered_set <unsigned int> setU;
              setU.insert(u);
              graph.insert(
                std::pair <unsigned int,std::unordered_set<unsigned int>>(v, setU));

              graph.find(u)->second.insert(v);  //Insert v into u's set
            } else { //If u and v are both in the graph, just insert
              graph.find(v)->second.insert(u);
              graph.find(u)->second.insert(v);
            }
        //}
      }
    } else {
      std::cout << "Error. File not found." << std::endl;
    }
    file.close();
  }

void Graph::printGraph() {
    for (auto key: graph) {     //For every vertex in the graph
      std::cout << key.first << " -> ";
      for (auto i: key.second) //For every vertex in key's unordered_set
        std::cout << i << " ";
      std::cout << std::endl;
    }
}

std::unordered_set<unsigned int> Graph::operator [](int i) {
  return graph[i];
}

//Requires both u and v to exist already
void Graph::addEdge(unsigned int u, unsigned int v) {
  graph.find(v)->second.insert(u);
  graph.find(u)->second.insert(v);
}

//Requires both u and v to exist already
void Graph::cutEdge(unsigned int u, unsigned int v) {
  graph.find(v)->second.erase(u);
  graph.find(u)->second.erase(v);
}

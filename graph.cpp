#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>
#include "graph.h"

Graph::Graph(std::string fileName) {
    //std::map<unsigned int,std::unordered_set<unsigned int>>  graph;
    std::string line;
    std::ifstream file(fileName);

    if (file.is_open()) {
      std::getline(file, line);
      while (std::getline(file, line)) {
      //  std::cout << line << std::endl;

      //  if (!(line[0] == 'p' || line[0] == 'c')) { TO IMPROVE EFFICIENCY - UNSAFE
          int sep = line.find(' ');
          unsigned int key = stoi(line.substr(0, sep));
          unsigned int val = stoi(line.substr(sep)); // ISSUES IF COMMENT ON LINE
        //  std::cout << key << std::endl;
        //  std::cout << val << std::endl;
          bool keyInGraph = (graph.find(key) != graph.end());
          bool valInGraph = (graph.find(val) != graph.end());

          if (!keyInGraph) {// if no entry exists
            if (!valInGraph) { // neither has entry, make both
              std::unordered_set <unsigned int> usK;
              usK.insert(val);
              graph.insert(
                std::pair <unsigned int,std::unordered_set<unsigned int>>(key, usK));

              std::unordered_set <unsigned int> usV;
              usV.insert(key);
              graph.insert(
                std::pair <unsigned int,std::unordered_set<unsigned int>>(val, usV));

            } else { //val is in graph, key isn't
              std::unordered_set <unsigned int> usV;
              usV.insert(val);
              graph.insert(
                std::pair <unsigned int,std::unordered_set<unsigned int>>(key, usV));
              graph.find(val)->second.insert(key);
            }
          } else if (!valInGraph) { //key is in graph, val isn't
              std::unordered_set <unsigned int> usK;
              usK.insert(key);
              graph.insert(
                std::pair <unsigned int,std::unordered_set<unsigned int>>(val, usK));
              graph.find(key)->second.insert(val);

            } else {
              graph.find(val)->second.insert(key);
              graph.find(key)->second.insert(val);
            }
        //}
      }
    } else {
      std::cout << "Error. File not found." << std::endl;
    }
    file.close();
  }

void Graph::printGraph() {
    std::cout << "printing" << std::endl;
    for (auto entry: graph) {
      std::cout << entry.first << " -> ";
      for (auto i: entry.second)
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

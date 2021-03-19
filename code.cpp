#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>

std::map<unsigned int,std::unordered_set<unsigned int>> fileIn(std::string fileName) {
  std::map<unsigned int,std::unordered_set<unsigned int>>  graph;
  std::string line;
  std::ifstream file(fileName);

  if (file.is_open()) {
    while (std::getline(file, line)) {
      std::cout << line << std::endl;

      if (!(line[0] == 'p' || line[0] == 'c')) {
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
      }
    }
  } else {
    std::cout << "Error. File not found." << std::endl;
  }
  file.close();
  return graph;
}


int main(int argc,  char* argv[]) {

  std::map<unsigned int,std::unordered_set<unsigned int>>  graph;
  if (argc > 1)
    graph = fileIn(argv[1]);

  for (auto entry: graph) {
    std::cout << entry.first << " -> ";
    for (auto i: entry.second)
      std::cout << i << " ";
    std::cout << std::endl;
  }

  return 0;
}

#include <iostream>
#include <fstream>
#include <map>

void fileIn(std::string fileName) {
  std::string line;
  std::ifstream file(fileName);
  if (file.is_open()) {
    while (std::getline(file, line)) {
      std::cout << line << std::endl;
      }
  } else {
    std::cout << "Error. File not found." << std::endl;
  }
  file.close();
  return;
}


int main(int argc,  char* argv[]) {
  fileIn(argv[1]);
  return 0;
}

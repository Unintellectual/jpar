#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "token.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return EXIT_FAILURE;
  }

  std::ifstream file(argv[1]);

  if (!file) {
    std::cerr << "Error: Could not open file " << argv[1] << std::endl;
    return EXIT_FAILURE;
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string json_input = buffer.str();

  return 0;
}

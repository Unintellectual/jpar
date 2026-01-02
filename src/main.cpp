/*
 * Copyright (c) 2026 Noah Victoriano official.noah.victoriano@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <fstream>
#include <iostream>
#include <vector>

#include "includes/common.h"
#include "includes/lexer.h"
#include "includes/parser.h"
#include "includes/token.h"

int main(int argc, char* argv[]) {
  if (argc < 2 || argc > 3) {
    std::cerr << "Usage: " << argv[0] << " <fileName> [displayData]\n";
    return 1;
  }

  std::ifstream inputFile(argv[1]);

  if (!inputFile.is_open()) {
    std::cerr << "Error in opening file " << argv[1] << "\n";
    return 1;
  }

  // For displaying the tokens and parsing phase
  if (argc == 3) displayData = argv[2];

  std::vector<Token> tokens;

  // Perform lexical analysis
  lexer(inputFile, tokens);

  inputFile.close();

  tokenSize = tokens.size();

  displayTokens(tokens);

  // Check if invalid JSON found in lexical analysis
  if (tokenSize > 0 && tokens[tokenSize - 1].type == UNKNOWN) {
    std::cout << "INVALID JSON\n";
  } else {
    // perform parsing
    if (!parser(tokens))
      std::cout << "INVALID JSON\n";
    else
      std::cout << "VALID JSON\n";
  }

  return 0;
}

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
#pragma once

#include <vector>

#include "token.h"

namespace jpar {

class Parser
{
public:
  static bool parseLeftCurlyBracket(std::vector<TokenType> token);
  static bool parseLeftSquareBracket(std::vector<TokenType> &tokens);
  static void displayParsingStart();
  static void displayParsingEnd();
  static void displayParsing(std::vector<TokenType> &tokens);
  static void eat(std::vector<TokenType> &tokens);
  static bool isClosingToken(TokenType type);
  static bool isValidDataType(TokenType type);
  static bool parser(std::vector<TokenType> &tokens);
};

}// namespace jpar

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

#include "includes/parser.h"

#include <iostream>
#include <vector>

#include "includes/common.h"
#include "includes/token.h"

void displayParsingStart() {
  if (!displayData) return;

  std::cout << "Parsing:\n";
  std::cout << "-------------------------------\n";
}

void displayParsingEnd() {
  if (!displayData) return;

  std::cout << "-------------------------------\n\n";
}

void displayParsing(std::vector<Token> &tokens) {
  if (!displayData) return;
  std::cout << tokens[parseIndex].value << "\n";
}

void eat(std::vector<Token> &tokens) {
  displayParsing(tokens);
  parseIndex++;
}

bool isClosingToken(tokenTypes type) { return type == RIGHTCURLYBRACKET || type == RIGHTSQUAREBRACKET; }

bool isValidDataType(tokenTypes type) {
  if (type == STRINGVALUE || type == NUMBER || type == BOOLEAN || type == NULLVALUE) return true;

  return false;
}

/*  Parse the left curly bracket.
    Format: {}

            { "key" : value }

            { "key1" : value, "key2" : value }

            { "key1" : [...JSON...] }

            { "key1" : {...JSON...} }


                {
               / \
              /   \
            Key     }
             |
             |
             :
             |
             |
       ---------------
       |     |       |
       |     |       |
       {     [    DataType
                    / \
                   /   \
                  ,     }
                 / \
                /   \
               [     {
*/

bool parseLeftCurlyBracket(std::vector<Token> &tokens) {
  eat(tokens);

  if (isInvalidIndex(parseIndex, tokenSize)) return false;

  if (tokens[parseIndex].type == STRINGVALUE) {
    eat(tokens);

    if (isInvalidIndex(parseIndex, tokenSize)) return false;

    if (tokens[parseIndex].type != COLON) return false;

    eat(tokens);

    if (isInvalidIndex(parseIndex, tokenSize)) return false;

    // eat value
    if (tokens[parseIndex].type == LEFTCURLYBRACKET) {
      if (!parseLeftCurlyBracket(tokens)) return false;
    } else if (tokens[parseIndex].type == LEFTSQUAREBRACKET) {
      if (!parseLeftSquareBracket(tokens)) return false;
    } else if (isValidDataType(tokens[parseIndex].type)) {
      eat(tokens);
    } else {
      return false;
    }

    if (isInvalidIndex(parseIndex, tokenSize)) return false;

    if (tokens[parseIndex].type == COMMA) {
      if (parseIndex + 1 >= tokenSize) return false;

      if (isClosingToken(tokens[parseIndex + 1].type)) return false;

      if (!parseLeftCurlyBracket(tokens)) return false;
    } else if (tokens[parseIndex].type == RIGHTCURLYBRACKET) {
      eat(tokens);
    } else {
      return false;
    }
  } else if (tokens[parseIndex].type == RIGHTCURLYBRACKET) {
    eat(tokens);
  } else {
    return false;
  }

  return true;
}

/*  Parse the left square bracket.
    Format: []

            [ value ]

            [value1, value2]

            [[...JSON...]]

            [{...JSON...}]


                [
                |
                |
       ----------------------
       |     |       |      |
       |     |       |      |
       [     {     Value    ]
                    / \
                   /   \
                  ,     }
                 / \
                /   \
               [     {

*/

bool parseLeftSquareBracket(std::vector<Token> &tokens) {
  eat(tokens);
  if (isInvalidIndex(parseIndex, tokenSize)) return false;

  if (tokens[parseIndex].type == LEFTSQUAREBRACKET || tokens[parseIndex].type == LEFTCURLYBRACKET
      || isValidDataType(tokens[parseIndex].type)) {
    if (tokens[parseIndex].type == LEFTSQUAREBRACKET) {
      if (!parseLeftSquareBracket(tokens)) return false;
    } else if (tokens[parseIndex].type == LEFTCURLYBRACKET) {
      if (!parseLeftCurlyBracket(tokens)) return false;
    } else if (isValidDataType(tokens[parseIndex].type)) {
      eat(tokens);
    }

    if (isInvalidIndex(parseIndex, tokenSize)) return false;

    if (tokens[parseIndex].type == COMMA) {
      if (parseIndex + 1 >= tokenSize) return false;

      if (isClosingToken(tokens[parseIndex + 1].type)) return false;

      if (!parseLeftSquareBracket(tokens)) return false;
    } else if (tokens[parseIndex].type == RIGHTSQUAREBRACKET) {
      eat(tokens);
    } else {
      return false;
    }

  } else if (tokens[parseIndex].type == RIGHTSQUAREBRACKET) {
    eat(tokens);
  } else {
    return false;
  }
  return true;
}

bool parser(std::vector<Token> &tokens) {
  displayParsingStart();

  if (isInvalidIndex(parseIndex, tokenSize)) return false;

  switch (tokens[parseIndex].type) {
  case LEFTCURLYBRACKET:
    if (!parseLeftCurlyBracket(tokens)) return false;

    if (!isInvalidIndex(parseIndex, tokenSize)) {
      displayParsing(tokens);
      return false;
    }
    break;

  case LEFTSQUAREBRACKET:
    if (!parseLeftSquareBracket(tokens)) return false;
    if (!isInvalidIndex(parseIndex, tokenSize)) {
      displayParsing(tokens);
      return false;
    }
    break;

  default:
    displayParsing(tokens);
    return false;
  }

  displayParsingEnd();
  return true;
}

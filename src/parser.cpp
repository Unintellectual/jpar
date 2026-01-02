#include "parser.h"  // wtf is this formatting from clang

#include <iostream>
#include <vector>

#include "common.h"
#include "token.h"

void displayParsingStart() {
  if (!displayData) return;

  std::cout << "Parsing:\n";
  std::cout << "-------------------------------\n";
}

void displayParsingEnd() {
  if (!displayData) return;

  std::cout << "-------------------------------\n\n";
}

void displayParsing(std::vector<Token>& tokens) {
  if (!displayData) return;

  std::cout << tokens[parseIndex].value << "\n";
}

void eat(std::vector<Token>& tokens) {
  displayParsing(tokens);
  parseIndex++;
}

bool isClosingToken(tokenTypes type) {
  return type == RIGHTCURLYBRACKET || type == RIGHTSQUAREBRACKET;
}

bool isValidDataType(tokenTypes type) {
  if (type == STRINGVALUE || type == NUMBER || type == BOOLEAN ||
      type == NULLVALUE)
    return true;

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

bool parseLeftCurlyBracket(std::vector<Token>& tokens) {
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
    } else if (isValidDataType(tokens[parseIndex].type))
      eat(tokens);
    else
      return false;

    if (isInvalidIndex(parseIndex, tokenSize)) return false;

    if (tokens[parseIndex].type == COMMA) {
      if (parseIndex + 1 >= tokenSize) return false;

      if (isClosingToken(tokens[parseIndex + 1].type)) return false;

      if (!parseLeftCurlyBracket(tokens)) return false;
    } else if (tokens[parseIndex].type == RIGHTCURLYBRACKET)
      eat(tokens);
    else
      return false;
  } else if (tokens[parseIndex].type == RIGHTCURLYBRACKET)
    eat(tokens);
  else
    return false;

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

bool parseLeftSquareBracket(std::vector<Token>& tokens) {
  eat(tokens);
  if (isInvalidIndex(parseIndex, tokenSize)) return false;

  if (tokens[parseIndex].type == LEFTSQUAREBRACKET ||
      tokens[parseIndex].type == LEFTCURLYBRACKET ||
      isValidDataType(tokens[parseIndex].type)) {
    if (tokens[parseIndex].type == LEFTSQUAREBRACKET) {
      if (!parseLeftSquareBracket(tokens)) return false;
    } else if (tokens[parseIndex].type == LEFTCURLYBRACKET) {
      if (!parseLeftCurlyBracket(tokens)) return false;
    } else if (isValidDataType(tokens[parseIndex].type))
      eat(tokens);

    if (isInvalidIndex(parseIndex, tokenSize)) return false;

    if (tokens[parseIndex].type == COMMA) {
      if (parseIndex + 1 >= tokenSize) return false;

      if (isClosingToken(tokens[parseIndex + 1].type)) return false;

      if (!parseLeftSquareBracket(tokens)) return false;
    } else if (tokens[parseIndex].type == RIGHTSQUAREBRACKET)
      eat(tokens);
    else
      return false;
  } else if (tokens[parseIndex].type == RIGHTSQUAREBRACKET)
    eat(tokens);
  else
    return false;

  return true;
}

bool parser(std::vector<Token>& tokens) {
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
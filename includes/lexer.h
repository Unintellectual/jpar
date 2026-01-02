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

#include <string>
#include <vector>

#include "token.h"

std::string getTokenType(tokenTypes option);

void AddToken(std::vector<Token>& tokens, tokenTypes type, std::string value);

bool isNumber(std::string input);

tokenTypes getValueType(std::string str);

bool isClosingBracketOrComma(char ch);

bool isValidEscapeCharacterForJSON(char ch);

bool isControlCharacter(char ch);

void displayTokens(std::vector<Token>& tokens);

bool isValidString(std::string& str);

void lexer(std::ifstream& file, std::vector<Token>& tokens);
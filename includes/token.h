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
#include <variant>

namespace jpar {
enum class TokenType {
  LEFTCURLYBRACKET,// {
  RIGHTCURLYBRACKET,// }
  LEFTSQUAREBRACKET,// [
  RIGHTSQUAREBRACKET,// ]
  LEFTROUNDBRACKET,// (
  RIGHTROUNDBRACKET,// )
  DOT,// .
  COLON,// :
  COMMA,// ,
  DOUBLEQUOTE,// "
  STRINGVALUE,// string
  BOOLEAN,// true, false
  NUMBER,// number
  NULLVALUE,// null
  UNKNOWN
};

class Token
{
public:
  Token(TokenType type, std::string value);

private:
  TokenType type;
  std::string value;
};
}// namespace jpar

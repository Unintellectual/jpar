#pragma once

#include <string>

enum TokenType {
    LBRACE,
    RBRACE,
    STRING,
    COLON,
    END_OF_INPUT
};

struct Token {
    TokenType type;
    std::string value;
};
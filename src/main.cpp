#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

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

class JSONLexer {
private:
    std::string input;
    size_t current = 0;

public:
    JSONLexer(const std::string& json_str)
        : input(json_str)
    {
    }

    Token getNextToken()
    {
        while (current < input.length()) {
            char ch = input[current];

            switch (ch) {
            case '{':
                current++;
                return { LBRACE, "{" };
            case '}':
                current++;
                return { RBRACE, "}" };
            case ':':
                current++;
                return { COLON, ":" };
            case '"':
                return parseString();
            case ' ':
            case '\t':
            case '\n':
            case '\r':
                current++;
                continue;
            default:
                std::cerr << "Unexpected character: " << ch << std::endl;
                current++;
            }
        }
        return { END_OF_INPUT, "" };
    }

private:
    Token parseString()
    {
        current++; // Skip opening quote
        size_t start = current;

        while (current < input.length() && input[current] != '"') {
            current++;
        }

        std::string str_value = input.substr(start, current - start);

        if (current < input.length()) {
            current++; // Skip closing quote
        }

        return { STRING, str_value };
    }
};

int main(int argc, char* argv[])
{
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

    JSONLexer lexer(json_input);

    Token token;
    while ((token = lexer.getNextToken()).type != END_OF_INPUT) {
        std::string type_str;
        switch (token.type) {
        case LBRACE:
            type_str = "LBRACE";
            break;
        case RBRACE:
            type_str = "RBRACE";
            break;
        case STRING:
            type_str = "STRING";
            break;
        case COLON:
            type_str = "COLON";
            break;
        default:
            type_str = "UNKNOWN";
        }

        std::cout << "TokenType: " << type_str
                  << ", Value: \"" << token.value << "\"" << std::endl;
    }

    return 0;
}

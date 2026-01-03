# JPAR

This is a JSON parser to check valid and invalid json output and input in the command line. The executable is dynamically linked but all you really need to build this project is base-devel and the most latest gcc or clang available in your repos.

### Usage: 
```
chmod +x setup.sh
./setup.sh
```

### Parsing Stages

| Stage         | Function     | Description                                        | Key Operations                                        |
|---------------|--------------|----------------------------------------------------|------------------------------------------------------|
| <b>Tokenizer</b> | `tokenizer()` | Breaks input into individual tokens                | - Reads input character by character<br>- Identifies JSON elements<br>- Converts raw input into a token stream |
| <b>Lexer</b>    | `lexer()`    | Analyzes and categorizes tokens                     | - Validates token types<br>- Checks token syntax<br>- Prepares tokens for final parsing |
| <b>Parser</b>   | `parser()`   | Checks the validity of the JSON structure           | - Validates hierarchical relationships<br>- Ensures all syntax rules are followed |
| <b>Validation</b>| Final Check  | Determines validity of the JSON                     | - Confirms complete parsing<br>- Returns valid/invalid status based on checks |


## References

For those interested in diving deeper into parsing techniques, I recommend exploring the following references:

- https://codingchallenges.fyi/challenges/challenge-json-parser
- https://cplusplus.com/reference/fstream/ifstream/
- https://craftinginterpreters.com/scanning.html
- https://www.rapidtables.com/convert/number/hex-to-ascii.html
- https://cmake.org/documentation/
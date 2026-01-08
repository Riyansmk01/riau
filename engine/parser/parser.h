#ifndef RIAU_PARSER_H
#define RIAU_PARSER_H

#include "../lexer/lexer.h"
#include "../ast/ast.h"
#include <stdbool.h>

typedef struct {
    Lexer* lexer;
    Token current;
    Token previous;
    bool had_error;
    bool panic_mode;
    char error_message[512];
} Parser;

// Parser initialization
void parser_init(Parser* parser, Lexer* lexer);

// Main parsing function
ASTNode* parser_parse(Parser* parser);

// Error handling
void parser_print_errors(Parser* parser);
bool parser_had_error(Parser* parser);

#endif // RIAU_PARSER_H

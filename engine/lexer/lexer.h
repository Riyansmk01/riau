#ifndef RIAU_LEXER_H
#define RIAU_LEXER_H

#include <stddef.h>
#include <stdbool.h>

// Token types for Riau language
typedef enum {
    // Literals
    TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_TRUE,
    TOKEN_FALSE,
    
    // Keywords
    TOKEN_LET,
    TOKEN_FN,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_FOR,
    TOKEN_IN,
    TOKEN_RETURN,
    TOKEN_TRY,
    TOKEN_CATCH,
    TOKEN_AS,
    TOKEN_ENTITY,
    TOKEN_USE,
    TOKEN_SPAWN,
    
    // Operators
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCENT,
    TOKEN_ASSIGN,
    TOKEN_EQUAL,
    TOKEN_NOT_EQUAL,
    TOKEN_LESS,
    TOKEN_LESS_EQUAL,
    TOKEN_GREATER,
    TOKEN_GREATER_EQUAL,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,
    TOKEN_QUESTION,
    TOKEN_ARROW,
    
    // Delimiters
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_COMMA,
    TOKEN_DOT,
    TOKEN_COLON,
    TOKEN_SEMICOLON,
    
    // Special
    TOKEN_NEWLINE,
    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    const char* start;
    size_t length;
    int line;
    int column;
} Token;

typedef struct {
    const char* source;
    const char* start;
    const char* current;
    int line;
    int column;
    bool had_error;
    char error_message[256];
} Lexer;

// Lexer functions
void lexer_init(Lexer* lexer, const char* source);
Token lexer_next_token(Lexer* lexer);
const char* token_type_to_string(TokenType type);
void lexer_print_error(Lexer* lexer);

#endif // RIAU_LEXER_H

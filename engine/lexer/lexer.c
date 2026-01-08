#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>


void lexer_init(Lexer *lexer, const char *source) {
  lexer->source = source;
  lexer->start = source;
  lexer->current = source;
  lexer->line = 1;
  lexer->column = 1;
  lexer->had_error = false;
  lexer->error_message[0] = '\0';

  // Skip shebang line if present (#!/usr/bin/env riau)
  if (lexer->current[0] == '#' && lexer->current[1] == '!') {
    // Skip entire first line
    while (*lexer->current != '\n' && *lexer->current != '\0') {
      lexer->current++;
    }
    if (*lexer->current == '\n') {
      lexer->current++; // Skip newline
      lexer->line++;
      lexer->column = 1;
    }
    lexer->start = lexer->current;
  }
}

static bool is_at_end(Lexer *lexer) { return *lexer->current == '\0'; }

static char advance(Lexer *lexer) {
  lexer->current++;
  lexer->column++;
  return lexer->current[-1];
}

static char peek(Lexer *lexer) { return *lexer->current; }

static char peek_next(Lexer *lexer) {
  if (is_at_end(lexer))
    return '\0';
  return lexer->current[1];
}

static bool match(Lexer *lexer, char expected) {
  if (is_at_end(lexer))
    return false;
  if (*lexer->current != expected)
    return false;
  lexer->current++;
  lexer->column++;
  return true;
}

static Token make_token(Lexer *lexer, TokenType type) {
  Token token;
  token.type = type;
  token.start = lexer->start;
  token.length = (size_t)(lexer->current - lexer->start);
  token.line = lexer->line;
  token.column = lexer->column - token.length;
  return token;
}

static Token error_token(Lexer *lexer, const char *message) {
  lexer->had_error = true;
  snprintf(lexer->error_message, sizeof(lexer->error_message), "%s", message);

  Token token;
  token.type = TOKEN_ERROR;
  token.start = message;
  token.length = strlen(message);
  token.line = lexer->line;
  token.column = lexer->column;
  return token;
}

static void skip_whitespace(Lexer *lexer) {
  for (;;) {
    char c = peek(lexer);
    switch (c) {
    case ' ':
    case '\r':
    case '\t':
      advance(lexer);
      break;
    case '\n':
      lexer->line++;
      lexer->column = 0;
      advance(lexer);
      break;
    case '/':
      if (peek_next(lexer) == '/') {
        // Comment until end of line
        while (peek(lexer) != '\n' && !is_at_end(lexer)) {
          advance(lexer);
        }
      } else {
        return;
      }
      break;
    default:
      return;
    }
  }
}

static Token string(Lexer *lexer) {
  while (peek(lexer) != '"' && !is_at_end(lexer)) {
    if (peek(lexer) == '\n') {
      lexer->line++;
      lexer->column = 0;
    }
    advance(lexer);
  }

  if (is_at_end(lexer)) {
    return error_token(lexer, "Unterminated string");
  }

  advance(lexer); // Closing quote
  return make_token(lexer, TOKEN_STRING);
}

static Token number(Lexer *lexer) {
  while (isdigit(peek(lexer))) {
    advance(lexer);
  }

  // Look for decimal part
  if (peek(lexer) == '.' && isdigit(peek_next(lexer))) {
    advance(lexer); // Consume '.'
    while (isdigit(peek(lexer))) {
      advance(lexer);
    }
  }

  return make_token(lexer, TOKEN_NUMBER);
}

static TokenType check_keyword(const char *start, size_t length,
                               const char *rest, TokenType type) {
  if (strlen(rest) == length && memcmp(start, rest, length) == 0) {
    return type;
  }
  return TOKEN_IDENTIFIER;
}

static TokenType identifier_type(Lexer *lexer) {
  size_t length = lexer->current - lexer->start;
  const char *start = lexer->start;

  switch (start[0]) {
  case 'a':
    if (length > 1 && start[1] == 's')
      return check_keyword(start + 2, length - 2, "", TOKEN_AS);
    break;
  case 'c':
    if (length > 1 && start[1] == 'a')
      return check_keyword(start + 2, length - 2, "tch", TOKEN_CATCH);
    break;
  case 'e':
    if (length > 1) {
      switch (start[1]) {
      case 'l':
        return check_keyword(start + 2, length - 2, "se", TOKEN_ELSE);
      case 'n':
        return check_keyword(start + 2, length - 2, "tity", TOKEN_ENTITY);
      }
    }
    break;
  case 'f':
    if (length > 1) {
      switch (start[1]) {
      case 'a':
        return check_keyword(start + 2, length - 2, "lse", TOKEN_FALSE);
      case 'n':
        return check_keyword(start + 2, length - 2, "", TOKEN_FN);
      case 'o':
        return check_keyword(start + 2, length - 2, "r", TOKEN_FOR);
      }
    }
    break;
  case 'i':
    if (length > 1) {
      switch (start[1]) {
      case 'f':
        return check_keyword(start + 2, length - 2, "", TOKEN_IF);
      case 'n':
        return check_keyword(start + 2, length - 2, "", TOKEN_IN);
      }
    }
    break;
  case 'l':
    if (length > 1 && start[1] == 'e')
      return check_keyword(start + 2, length - 2, "t", TOKEN_LET);
    break;
  case 'r':
    if (length > 1 && start[1] == 'e')
      return check_keyword(start + 2, length - 2, "turn", TOKEN_RETURN);
    break;
  case 's':
    if (length > 1 && start[1] == 'p')
      return check_keyword(start + 2, length - 2, "awn", TOKEN_SPAWN);
    break;
  case 't':
    if (length > 1) {
      switch (start[1]) {
      case 'r':
        if (length > 2) {
          switch (start[2]) {
          case 'u':
            return check_keyword(start + 3, length - 3, "e", TOKEN_TRUE);
          case 'y':
            return check_keyword(start + 3, length - 3, "", TOKEN_TRY);
          }
        }
        break;
      }
    }
    break;
  case 'u':
    if (length > 1 && start[1] == 's')
      return check_keyword(start + 2, length - 2, "e", TOKEN_USE);
    break;
  }

  return TOKEN_IDENTIFIER;
}

static Token identifier(Lexer *lexer) {
  while (isalnum(peek(lexer)) || peek(lexer) == '_') {
    advance(lexer);
  }
  return make_token(lexer, identifier_type(lexer));
}

Token lexer_next_token(Lexer *lexer) {
  skip_whitespace(lexer);

  lexer->start = lexer->current;

  if (is_at_end(lexer)) {
    return make_token(lexer, TOKEN_EOF);
  }

  char c = advance(lexer);

  if (isalpha(c) || c == '_')
    return identifier(lexer);
  if (isdigit(c))
    return number(lexer);

  switch (c) {
  case '(':
    return make_token(lexer, TOKEN_LPAREN);
  case ')':
    return make_token(lexer, TOKEN_RPAREN);
  case '{':
    return make_token(lexer, TOKEN_LBRACE);
  case '}':
    return make_token(lexer, TOKEN_RBRACE);
  case '[':
    return make_token(lexer, TOKEN_LBRACKET);
  case ']':
    return make_token(lexer, TOKEN_RBRACKET);
  case ',':
    return make_token(lexer, TOKEN_COMMA);
  case '.':
    return make_token(lexer, TOKEN_DOT);
  case ':':
    return make_token(lexer, TOKEN_COLON);
  case ';':
    return make_token(lexer, TOKEN_SEMICOLON);
  case '?':
    return make_token(lexer, TOKEN_QUESTION);
  case '+':
    return make_token(lexer, TOKEN_PLUS);
  case '-':
    return make_token(lexer, TOKEN_MINUS);
  case '*':
    return make_token(lexer, TOKEN_STAR);
  case '/':
    return make_token(lexer, TOKEN_SLASH);
  case '%':
    return make_token(lexer, TOKEN_PERCENT);
  case '!':
    return make_token(lexer, match(lexer, '=') ? TOKEN_NOT_EQUAL : TOKEN_NOT);
  case '=':
    if (match(lexer, '=')) {
      return make_token(lexer, TOKEN_EQUAL);
    } else if (match(lexer, '>')) {
      return make_token(lexer, TOKEN_ARROW);
    } else {
      return make_token(lexer, TOKEN_ASSIGN);
    }
  case '<':
    return make_token(lexer, match(lexer, '=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
  case '>':
    return make_token(lexer,
                      match(lexer, '=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
  case '&':
    if (match(lexer, '&'))
      return make_token(lexer, TOKEN_AND);
    break;
  case '|':
    if (match(lexer, '|'))
      return make_token(lexer, TOKEN_OR);
    break;
  case '"':
    return string(lexer);
  }

  return error_token(lexer, "Unexpected character");
}

const char *token_type_to_string(TokenType type) {
  switch (type) {
  case TOKEN_IDENTIFIER:
    return "IDENTIFIER";
  case TOKEN_STRING:
    return "STRING";
  case TOKEN_NUMBER:
    return "NUMBER";
  case TOKEN_TRUE:
    return "TRUE";
  case TOKEN_FALSE:
    return "FALSE";
  case TOKEN_LET:
    return "LET";
  case TOKEN_FN:
    return "FN";
  case TOKEN_IF:
    return "IF";
  case TOKEN_ELSE:
    return "ELSE";
  case TOKEN_FOR:
    return "FOR";
  case TOKEN_IN:
    return "IN";
  case TOKEN_RETURN:
    return "RETURN";
  case TOKEN_TRY:
    return "TRY";
  case TOKEN_CATCH:
    return "CATCH";
  case TOKEN_AS:
    return "AS";
  case TOKEN_ENTITY:
    return "ENTITY";
  case TOKEN_USE:
    return "USE";
  case TOKEN_SPAWN:
    return "SPAWN";
  case TOKEN_PLUS:
    return "PLUS";
  case TOKEN_MINUS:
    return "MINUS";
  case TOKEN_STAR:
    return "STAR";
  case TOKEN_SLASH:
    return "SLASH";
  case TOKEN_PERCENT:
    return "PERCENT";
  case TOKEN_ASSIGN:
    return "ASSIGN";
  case TOKEN_EQUAL:
    return "EQUAL";
  case TOKEN_NOT_EQUAL:
    return "NOT_EQUAL";
  case TOKEN_LESS:
    return "LESS";
  case TOKEN_LESS_EQUAL:
    return "LESS_EQUAL";
  case TOKEN_GREATER:
    return "GREATER";
  case TOKEN_GREATER_EQUAL:
    return "GREATER_EQUAL";
  case TOKEN_AND:
    return "AND";
  case TOKEN_OR:
    return "OR";
  case TOKEN_NOT:
    return "NOT";
  case TOKEN_QUESTION:
    return "QUESTION";
  case TOKEN_ARROW:
    return "ARROW";
  case TOKEN_LPAREN:
    return "LPAREN";
  case TOKEN_RPAREN:
    return "RPAREN";
  case TOKEN_LBRACE:
    return "LBRACE";
  case TOKEN_RBRACE:
    return "RBRACE";
  case TOKEN_LBRACKET:
    return "LBRACKET";
  case TOKEN_RBRACKET:
    return "RBRACKET";
  case TOKEN_COMMA:
    return "COMMA";
  case TOKEN_DOT:
    return "DOT";
  case TOKEN_COLON:
    return "COLON";
  case TOKEN_SEMICOLON:
    return "SEMICOLON";
  case TOKEN_NEWLINE:
    return "NEWLINE";
  case TOKEN_EOF:
    return "EOF";
  case TOKEN_ERROR:
    return "ERROR";
  default:
    return "UNKNOWN";
  }
}

void lexer_print_error(Lexer *lexer) {
  if (lexer->had_error) {
    fprintf(stderr, "Lexer error at line %d, column %d: %s\n", lexer->line,
            lexer->column, lexer->error_message);
  }
}

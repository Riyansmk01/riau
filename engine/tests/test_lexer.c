// Test: Lexer functionality
#include "../lexer/lexer.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>


void test_lexer_keywords() {
  printf("Testing lexer keywords...\n");

  const char *source = "let fn if else for in return try catch";
  Lexer lexer;
  lexer_init(&lexer, source);

  Token token;

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_LET);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_FN);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_IF);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_ELSE);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_FOR);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_IN);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_RETURN);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_TRY);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_CATCH);

  printf("✓ Keyword tests passed\n");
}

void test_lexer_literals() {
  printf("Testing lexer literals...\n");

  const char *source = "123 45.67 \"hello\" true false";
  Lexer lexer;
  lexer_init(&lexer, source);

  Token token;

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_NUMBER);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_NUMBER);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_STRING);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_TRUE);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_FALSE);

  printf("✓ Literal tests passed\n");
}

void test_lexer_operators() {
  printf("Testing lexer operators...\n");

  const char *source = "+ - * / == != < > <= >= && ||";
  Lexer lexer;
  lexer_init(&lexer, source);

  Token token;

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_PLUS);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_MINUS);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_STAR);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_SLASH);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_EQUAL);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_NOT_EQUAL);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_LESS);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_GREATER);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_LESS_EQUAL);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_GREATER_EQUAL);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_AND);

  token = lexer_next_token(&lexer);
  assert(token.type == TOKEN_OR);

  printf("✓ Operator tests passed\n");
}

int main() {
  printf("=== Riau Lexer Tests ===\n\n");

  test_lexer_keywords();
  test_lexer_literals();
  test_lexer_operators();

  printf("\n=== All lexer tests passed! ===\n");
  return 0;
}

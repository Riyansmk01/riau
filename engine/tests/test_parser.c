// Test: Parser functionality
#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include <assert.h>
#include <stdio.h>


void test_parser_variable_decl() {
  printf("Testing variable declarations...\n");

  const char *source = "let x = 10";
  Lexer lexer;
  lexer_init(&lexer, source);

  Parser parser;
  parser_init(&parser, &lexer);

  ASTNode *ast = parser_parse(&parser);

  assert(ast != NULL);
  assert(ast->type == AST_PROGRAM);
  assert(!parser_had_error(&parser));

  ast_free(ast);
  printf("✓ Variable declaration test passed\n");
}

void test_parser_function_decl() {
  printf("Testing function declarations...\n");

  const char *source = "fn add(a, b) { return a + b }";
  Lexer lexer;
  lexer_init(&lexer, source);

  Parser parser;
  parser_init(&parser, &lexer);

  ASTNode *ast = parser_parse(&parser);

  assert(ast != NULL);
  assert(ast->type == AST_PROGRAM);
  assert(!parser_had_error(&parser));

  ast_free(ast);
  printf("✓ Function declaration test passed\n");
}

void test_parser_expressions() {
  printf("Testing expressions...\n");

  const char *source = "1 + 2 * 3";
  Lexer lexer;
  lexer_init(&lexer, source);

  Parser parser;
  parser_init(&parser, &lexer);

  ASTNode *ast = parser_parse(&parser);

  assert(ast != NULL);
  assert(ast->type == AST_PROGRAM);
  assert(!parser_had_error(&parser));

  ast_free(ast);
  printf("✓ Expression test passed\n");
}

void test_parser_if_statement() {
  printf("Testing if statements...\n");

  const char *source = "if x { y }";
  Lexer lexer;
  lexer_init(&lexer, source);

  Parser parser;
  parser_init(&parser, &lexer);

  ASTNode *ast = parser_parse(&parser);

  assert(ast != NULL);
  assert(ast->type == AST_PROGRAM);
  assert(!parser_had_error(&parser));

  ast_free(ast);
  printf("✓ If statement test passed\n");
}

int main() {
  printf("=== Riau Parser Tests ===\n\n");

  test_parser_variable_decl();
  test_parser_function_decl();
  test_parser_expressions();
  test_parser_if_statement();

  printf("\n=== All parser tests passed! ===\n");
  return 0;
}

#include "../bytecode/bytecode.h"
#include "../bytecode/compiler.h"
#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "../semantic/semantic.h"
#include "../vm/vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define VERSION "0.1.0"

static void print_banner() {
  printf("Riau Programming Language v%s\n", VERSION);
  printf("Type 'exit' to quit\n\n");
}

static char *read_file(const char *path) {
  FILE *file = fopen(path, "rb");
  if (!file) {
    fprintf(stderr, "Could not open file \"%s\"\n", path);
    return NULL;
  }

  fseek(file, 0L, SEEK_END);
  size_t file_size = ftell(file);
  rewind(file);

  char *buffer = malloc(file_size + 1);
  if (!buffer) {
    fprintf(stderr, "Not enough memory to read \"%s\"\n", path);
    fclose(file);
    return NULL;
  }

  size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
  if (bytes_read < file_size) {
    fprintf(stderr, "Could not read file \"%s\"\n", path);
    free(buffer);
    fclose(file);
    return NULL;
  }

  buffer[bytes_read] = '\0';
  fclose(file);
  return buffer;
}

static void run_file(const char *path) {
  char *source = read_file(path);
  if (!source) {
    exit(74);
  }

  // Lexer
  Lexer lexer;
  lexer_init(&lexer, source);

  // Parser
  Parser parser;
  parser_init(&parser, &lexer);
  ASTNode *ast = parser_parse(&parser);

  if (parser_had_error(&parser)) {
    parser_print_errors(&parser);
    ast_free(ast);
    free(source);
    exit(65);
  }

  printf("✓ Parsing successful\n");

  // Semantic analysis
  SemanticAnalyzer analyzer;
  semantic_init(&analyzer);

  if (!semantic_analyze(&analyzer, ast)) {
    semantic_print_errors(&analyzer);
    semantic_free(&analyzer);
    ast_free(ast);
    free(source);
    exit(65);
  }

  printf("✓ Semantic analysis passed\n");
  semantic_free(&analyzer);

  // Compile to bytecode
  Chunk chunk;
  chunk_init(&chunk);

  Compiler compiler;
  compiler_init(&compiler, &chunk);

  if (!compiler_compile(&compiler, ast)) {
    compiler_print_error(&compiler);
    chunk_free(&chunk);
    ast_free(ast);
    free(source);
    exit(65);
  }

  printf("✓ Compilation successful\n");

  // Execute bytecode
  VM vm;
  vm_init(&vm);

  printf("\n--- Execution Output ---\n");
  bool result = vm_execute(&vm, &chunk);
  printf("--- End Output ---\n\n");

  if (!result) {
    vm_print_error(&vm);
    vm_free(&vm);
    chunk_free(&chunk);
    ast_free(ast);
    free(source);
    exit(70);
  }

  printf("✓ Execution successful\n");

  vm_free(&vm);
  chunk_free(&chunk);
  ast_free(ast);
  free(source);
}

static void repl() {
  print_banner();

  char line[1024];

  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    // Remove newline
    line[strcspn(line, "\n")] = 0;

    if (strcmp(line, "exit") == 0 || strcmp(line, "quit") == 0) {
      break;
    }

    if (strlen(line) == 0) {
      continue;
    }

    // Lexer
    Lexer lexer;
    lexer_init(&lexer, line);

    // Parser
    Parser parser;
    parser_init(&parser, &lexer);
    ASTNode *ast = parser_parse(&parser);

    if (parser_had_error(&parser)) {
      parser_print_errors(&parser);
    } else {
      printf("✓ Valid syntax\n");
    }

    ast_free(ast);
  }
}

static void print_usage() {
  printf("Usage: riau [options] [file]\n");
  printf("Options:\n");
  printf("  -h, --help     Show this help message\n");
  printf("  -v, --version  Show version information\n");
  printf("  -d, --debug    Enable debug output\n");
  printf("\n");
  printf("If no file is specified, starts REPL mode\n");
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    repl();
    return 0;
  }

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      print_usage();
      return 0;
    } else if (strcmp(argv[i], "-v") == 0 ||
               strcmp(argv[i], "--version") == 0) {
      printf("Riau v%s\n", VERSION);
      return 0;
    } else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) {
      // Enable debug mode
      continue;
    } else {
      run_file(argv[i]);
      return 0;
    }
  }

  return 0;
}

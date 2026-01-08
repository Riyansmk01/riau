#ifndef RIAU_COMPILER_H
#define RIAU_COMPILER_H

#include "../ast/ast.h"
#include "../bytecode/bytecode.h"
#include <stdbool.h>

// Compiler state
typedef struct {
  Chunk *chunk;
  bool had_error;
  char error_message[512];
} Compiler;

// Compiler functions
void compiler_init(Compiler *compiler, Chunk *chunk);
bool compiler_compile(Compiler *compiler, ASTNode *ast);
void compiler_print_error(Compiler *compiler);

#endif // RIAU_COMPILER_H

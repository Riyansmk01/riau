#include "compiler.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARIABLES 256

// Simple variable table
static char *variables[MAX_VARIABLES];
static int variable_count = 0;

static int find_variable(const char *name) {
  for (int i = 0; i < variable_count; i++) {
    if (strcmp(variables[i], name) == 0) {
      return i;
    }
  }
  return -1;
}

static int add_variable(const char *name) {
  if (variable_count >= MAX_VARIABLES) {
    return -1;
  }
  variables[variable_count] = strdup(name);
  return variable_count++;
}

static void compiler_error(Compiler *compiler, const char *format, ...) {
  va_list args;
  va_start(args, format);
  vsnprintf(compiler->error_message, sizeof(compiler->error_message), format,
            args);
  va_end(args);
  compiler->had_error = true;
}

void compiler_init(Compiler *compiler, Chunk *chunk) {
  compiler->chunk = chunk;
  compiler->had_error = false;
  compiler->error_message[0] = '\0';

  // Reset variable table
  for (int i = 0; i < variable_count; i++) {
    free(variables[i]);
  }
  variable_count = 0;
}

// Forward declarations
static void compile_statement(Compiler *compiler, ASTNode *node);
static void compile_expression(Compiler *compiler, ASTNode *node);

static void compile_expression(Compiler *compiler, ASTNode *node) {
  if (!node)
    return;

  switch (node->type) {
  case AST_LITERAL_NUMBER: {
    size_t constant = chunk_add_constant(
        compiler->chunk, constant_number(node->data.number.value));
    chunk_write(compiler->chunk, OP_PUSH_CONST, node->line);
    chunk_write(compiler->chunk, (uint8_t)constant, node->line);
    break;
  }

  case AST_LITERAL_STRING: {
    size_t constant = chunk_add_constant(
        compiler->chunk, constant_string(node->data.string.value));
    chunk_write(compiler->chunk, OP_PUSH_CONST, node->line);
    chunk_write(compiler->chunk, (uint8_t)constant, node->line);
    break;
  }

  case AST_LITERAL_BOOL: {
    chunk_write(compiler->chunk,
                node->data.boolean.value ? OP_PUSH_TRUE : OP_PUSH_FALSE,
                node->line);
    break;
  }

  case AST_LITERAL_NULL: {
    chunk_write(compiler->chunk, OP_PUSH_NULL, node->line);
    break;
  }

  case AST_IDENTIFIER: {
    int slot = find_variable(node->data.identifier.name);
    if (slot == -1) {
      compiler_error(compiler, "Undefined variable '%s'",
                     node->data.identifier.name);
      chunk_write(compiler->chunk, OP_PUSH_NULL, node->line);
    } else {
      chunk_write(compiler->chunk, OP_LOAD_VAR, node->line);
      chunk_write(compiler->chunk, (uint8_t)slot, node->line);
    }
    break;
  }

  case AST_BINARY_EXPR: {
    // Compile left and right operands
    compile_expression(compiler, node->data.binary.left);
    compile_expression(compiler, node->data.binary.right);

    // Emit operator instruction
    const char *op = node->data.binary.operator;
    if (strcmp(op, "+") == 0) {
      chunk_write(compiler->chunk, OP_ADD, node->line);
    } else if (strcmp(op, "-") == 0) {
      chunk_write(compiler->chunk, OP_SUB, node->line);
    } else if (strcmp(op, "*") == 0) {
      chunk_write(compiler->chunk, OP_MUL, node->line);
    } else if (strcmp(op, "/") == 0) {
      chunk_write(compiler->chunk, OP_DIV, node->line);
    } else if (strcmp(op, "%") == 0) {
      chunk_write(compiler->chunk, OP_MOD, node->line);
    } else if (strcmp(op, "==") == 0) {
      chunk_write(compiler->chunk, OP_EQUAL, node->line);
    } else if (strcmp(op, "!=") == 0) {
      chunk_write(compiler->chunk, OP_NOT_EQUAL, node->line);
    } else if (strcmp(op, "<") == 0) {
      chunk_write(compiler->chunk, OP_LESS, node->line);
    } else if (strcmp(op, "<=") == 0) {
      chunk_write(compiler->chunk, OP_LESS_EQUAL, node->line);
    } else if (strcmp(op, ">") == 0) {
      chunk_write(compiler->chunk, OP_GREATER, node->line);
    } else if (strcmp(op, ">=") == 0) {
      chunk_write(compiler->chunk, OP_GREATER_EQUAL, node->line);
    } else if (strcmp(op, "&&") == 0) {
      chunk_write(compiler->chunk, OP_AND, node->line);
    } else if (strcmp(op, "||") == 0) {
      chunk_write(compiler->chunk, OP_OR, node->line);
    }
    break;
  }

  case AST_UNARY_EXPR: {
    compile_expression(compiler, node->data.unary.operand);

    const char *op = node->data.unary.operator;
    if (strcmp(op, "-") == 0) {
      chunk_write(compiler->chunk, OP_NEGATE, node->line);
    } else if (strcmp(op, "!") == 0) {
      chunk_write(compiler->chunk, OP_NOT, node->line);
    }
    break;
  }

  case AST_CALL_EXPR: {
    // Check if this is a built-in function
    if (node->data.call.callee->type == AST_IDENTIFIER) {
      const char *func_name = node->data.call.callee->data.identifier.name;

      // Handle print() built-in
      if (strcmp(func_name, "print") == 0) {
        ASTNodeList *args = node->data.call.arguments;
        if (!args || !args->node) {
          compiler_error(compiler, "print() requires at least one argument");
          return;
        }
        // Compile the argument
        compile_expression(compiler, args->node);
        // Emit PRINT opcode
        chunk_write(compiler->chunk, OP_PRINT, node->line);
        return;
      }

      // Handle env() built-in
      if (strcmp(func_name, "env") == 0) {
        ASTNodeList *args = node->data.call.arguments;
        if (!args || !args->node) {
          compiler_error(compiler, "env() requires one argument");
          return;
        }
        // Compile the argument (should be a string)
        compile_expression(compiler, args->node);
        // Emit ENV opcode
        chunk_write(compiler->chunk, OP_ENV, node->line);
        return;
      }
    }

    // Regular function call (not implemented yet)
    // Compile arguments
    ASTNodeList *args = node->data.call.arguments;
    int arg_count = 0;
    while (args) {
      compile_expression(compiler, args->node);
      arg_count++;
      args = args->next;
    }

    // Compile callee
    compile_expression(compiler, node->data.call.callee);

    // Emit call instruction
    chunk_write(compiler->chunk, OP_CALL, node->line);
    chunk_write(compiler->chunk, (uint8_t)arg_count, node->line);
    break;
  }

  default:
    compiler_error(compiler, "Unknown expression type");
    break;
  }
}

static void compile_statement(Compiler *compiler, ASTNode *node) {
  if (!node)
    return;

  switch (node->type) {
  case AST_EXPR_STMT: {
    compile_expression(compiler, node->data.expr_stmt.expression);
    chunk_write(compiler->chunk, OP_POP, node->line);
    break;
  }

  case AST_VARIABLE_DECL: {
    if (node->data.var_decl.initializer) {
      compile_expression(compiler, node->data.var_decl.initializer);
    } else {
      chunk_write(compiler->chunk, OP_PUSH_NULL, node->line);
    }
    // Add variable and store it
    int slot = add_variable(node->data.var_decl.name);
    if (slot == -1) {
      compiler_error(compiler, "Too many variables");
      return;
    }
    chunk_write(compiler->chunk, OP_STORE_VAR, node->line);
    chunk_write(compiler->chunk, (uint8_t)slot, node->line);
    break;
  }

  case AST_RETURN_STMT: {
    if (node->data.return_stmt.value) {
      compile_expression(compiler, node->data.return_stmt.value);
    } else {
      chunk_write(compiler->chunk, OP_PUSH_NULL, node->line);
    }
    chunk_write(compiler->chunk, OP_RETURN, node->line);
    break;
  }

  case AST_BLOCK: {
    ASTNodeList *stmts = node->data.block.statements;
    while (stmts) {
      compile_statement(compiler, stmts->node);
      stmts = stmts->next;
    }
    break;
  }

  default:
    // For now, skip unsupported statements
    break;
  }
}

bool compiler_compile(Compiler *compiler, ASTNode *ast) {
  if (!ast)
    return false;

  if (ast->type == AST_PROGRAM) {
    ASTNodeList *stmts = ast->data.program.statements;
    while (stmts) {
      compile_statement(compiler, stmts->node);
      stmts = stmts->next;
    }
  }

  // Add halt instruction at the end
  chunk_write(compiler->chunk, OP_HALT, 0);

  return !compiler->had_error;
}

void compiler_print_error(Compiler *compiler) {
  if (compiler->had_error) {
    fprintf(stderr, "Compilation error: %s\n", compiler->error_message);
  }
}

#include "semantic.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Symbol table implementation
void symbol_table_init(SymbolTable *table) {
  table->count = 0;
  table->scope_depth = 0;
  memset(table->symbols, 0, sizeof(table->symbols));
}

void symbol_table_free(SymbolTable *table) {
  for (int i = 0; i < table->count; i++) {
    free(table->symbols[i].name);
    type_free(table->symbols[i].type);
  }
  table->count = 0;
}

bool symbol_table_define(SymbolTable *table, const char *name, TypeInfo *type,
                         bool is_optional) {
  if (table->count >= MAX_SYMBOLS) {
    return false;
  }

  // Check for redefinition in current scope
  for (int i = table->count - 1; i >= 0; i--) {
    if (table->symbols[i].scope_depth < table->scope_depth) {
      break;
    }
    if (strcmp(table->symbols[i].name, name) == 0) {
      return false; // Already defined in this scope
    }
  }

  Symbol *symbol = &table->symbols[table->count++];
  symbol->name = strdup(name);
  symbol->type = type;
  symbol->is_initialized = false;
  symbol->is_optional = is_optional;
  symbol->scope_depth = table->scope_depth;

  return true;
}

Symbol *symbol_table_resolve(SymbolTable *table, const char *name) {
  for (int i = table->count - 1; i >= 0; i--) {
    if (strcmp(table->symbols[i].name, name) == 0) {
      return &table->symbols[i];
    }
  }
  return NULL;
}

void symbol_table_begin_scope(SymbolTable *table) { table->scope_depth++; }

void symbol_table_end_scope(SymbolTable *table) {
  table->scope_depth--;

  // Remove symbols from ended scope
  while (table->count > 0 &&
         table->symbols[table->count - 1].scope_depth > table->scope_depth) {
    table->count--;
    free(table->symbols[table->count].name);
    type_free(table->symbols[table->count].type);
  }
}

// Semantic analyzer implementation
static void semantic_error(SemanticAnalyzer *analyzer, int line,
                           const char *format, ...) {
  va_list args;
  va_start(args, format);
  char buffer[512];
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);

  snprintf(analyzer->error_message, sizeof(analyzer->error_message),
           "[line %d] Semantic error: %s", line, buffer);
  analyzer->had_error = true;
}

void semantic_init(SemanticAnalyzer *analyzer) {
  analyzer->symbols = malloc(sizeof(SymbolTable));
  symbol_table_init(analyzer->symbols);
  analyzer->had_error = false;
  analyzer->error_message[0] = '\0';
}

void semantic_free(SemanticAnalyzer *analyzer) {
  if (analyzer->symbols) {
    symbol_table_free(analyzer->symbols);
    free(analyzer->symbols);
  }
}

// Forward declarations
static void analyze_statement(SemanticAnalyzer *analyzer, ASTNode *node);
static TypeInfo *analyze_expression(SemanticAnalyzer *analyzer, ASTNode *node);

static TypeInfo *analyze_expression(SemanticAnalyzer *analyzer, ASTNode *node) {
  if (!node)
    return type_create(TYPE_UNKNOWN, false, NULL);

  switch (node->type) {
  case AST_LITERAL_NUMBER:
    return type_create(TYPE_INT, false, "int");

  case AST_LITERAL_STRING:
    return type_create(TYPE_STRING, false, "string");

  case AST_LITERAL_BOOL:
    return type_create(TYPE_BOOL, false, "bool");

  case AST_LITERAL_NULL:
    return type_create(TYPE_NULL, true, "null");

  case AST_IDENTIFIER: {
    Symbol *symbol =
        symbol_table_resolve(analyzer->symbols, node->data.identifier.name);
    if (!symbol) {
      semantic_error(analyzer, node->line, "Undefined variable '%s'",
                     node->data.identifier.name);
      return type_create(TYPE_UNKNOWN, false, NULL);
    }

    // Check null safety
    if (symbol->is_optional && !symbol->is_initialized) {
      semantic_error(analyzer, node->line, "Variable '%s' may be null",
                     node->data.identifier.name);
    }

    return type_create(symbol->type->kind, symbol->is_optional,
                       symbol->type->name);
  }

  case AST_BINARY_EXPR: {
    TypeInfo *left_type = analyze_expression(analyzer, node->data.binary.left);
    TypeInfo *right_type =
        analyze_expression(analyzer, node->data.binary.right);

    // Type checking for binary operations
    const char *op = node->data.binary.operator;
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 || strcmp(op, "*") == 0 ||
        strcmp(op, "/") == 0) {
      if (left_type->kind != TYPE_INT && left_type->kind != TYPE_FLOAT) {
        semantic_error(analyzer, node->line,
                       "Arithmetic operation requires numeric types");
      }
    }

    type_free(left_type);
    type_free(right_type);
    return type_create(TYPE_INT, false, "int");
  }

  default:
    return type_create(TYPE_UNKNOWN, false, NULL);
  }
}

static void analyze_statement(SemanticAnalyzer *analyzer, ASTNode *node) {
  if (!node)
    return;

  switch (node->type) {
  case AST_VARIABLE_DECL: {
    TypeInfo *init_type = NULL;
    if (node->data.var_decl.initializer) {
      init_type = analyze_expression(analyzer, node->data.var_decl.initializer);
    }

    TypeInfo *var_type = node->data.var_decl.type_info;
    if (!var_type && init_type) {
      var_type = init_type; // Type inference
    }

    bool is_optional = var_type && var_type->is_optional;

    if (!symbol_table_define(analyzer->symbols, node->data.var_decl.name,
                             var_type, is_optional)) {
      semantic_error(analyzer, node->line, "Variable '%s' already defined",
                     node->data.var_decl.name);
    }

    if (init_type && init_type != var_type) {
      type_free(init_type);
    }
    break;
  }

  case AST_BLOCK: {
    symbol_table_begin_scope(analyzer->symbols);
    ASTNodeList *stmts = node->data.block.statements;
    while (stmts) {
      analyze_statement(analyzer, stmts->node);
      stmts = stmts->next;
    }
    symbol_table_end_scope(analyzer->symbols);
    break;
  }

  case AST_EXPR_STMT: {
    TypeInfo *type =
        analyze_expression(analyzer, node->data.expr_stmt.expression);
    type_free(type);
    break;
  }

  case AST_IF_STMT: {
    TypeInfo *cond_type =
        analyze_expression(analyzer, node->data.if_stmt.condition);
    type_free(cond_type);

    analyze_statement(analyzer, node->data.if_stmt.then_branch);
    if (node->data.if_stmt.else_branch) {
      analyze_statement(analyzer, node->data.if_stmt.else_branch);
    }
    break;
  }

  default:
    break;
  }
}

bool semantic_analyze(SemanticAnalyzer *analyzer, ASTNode *ast) {
  if (!ast)
    return false;

  if (ast->type == AST_PROGRAM) {
    ASTNodeList *stmts = ast->data.program.statements;
    while (stmts) {
      analyze_statement(analyzer, stmts->node);
      stmts = stmts->next;
    }
  }

  return !analyzer->had_error;
}

void semantic_print_errors(SemanticAnalyzer *analyzer) {
  if (analyzer->had_error) {
    fprintf(stderr, "%s\n", analyzer->error_message);
  }
}

#ifndef RIAU_SEMANTIC_H
#define RIAU_SEMANTIC_H

#include "../ast/ast.h"
#include <stdbool.h>

#define MAX_SYMBOLS 256

// Symbol table entry
typedef struct {
  char *name;
  TypeInfo *type;
  bool is_initialized;
  bool is_optional;
  int scope_depth;
} Symbol;

// Symbol table
typedef struct {
  Symbol symbols[MAX_SYMBOLS];
  int count;
  int scope_depth;
} SymbolTable;

// Semantic analyzer
typedef struct {
  SymbolTable *symbols;
  bool had_error;
  char error_message[512];
} SemanticAnalyzer;

// Semantic analyzer functions
void semantic_init(SemanticAnalyzer *analyzer);
void semantic_free(SemanticAnalyzer *analyzer);
bool semantic_analyze(SemanticAnalyzer *analyzer, ASTNode *ast);
void semantic_print_errors(SemanticAnalyzer *analyzer);

// Symbol table functions
void symbol_table_init(SymbolTable *table);
void symbol_table_free(SymbolTable *table);
bool symbol_table_define(SymbolTable *table, const char *name, TypeInfo *type,
                         bool is_optional);
Symbol *symbol_table_resolve(SymbolTable *table, const char *name);
void symbol_table_begin_scope(SymbolTable *table);
void symbol_table_end_scope(SymbolTable *table);

#endif // RIAU_SEMANTIC_H

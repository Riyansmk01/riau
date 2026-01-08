#ifndef RIAU_BYTECODE_H
#define RIAU_BYTECODE_H

#include <stddef.h>
#include <stdint.h>

// Bytecode instruction set
typedef enum {
  OP_HALT,          // Stop execution
  OP_PUSH_CONST,    // Push constant onto stack
  OP_PUSH_NULL,     // Push null onto stack
  OP_PUSH_TRUE,     // Push true onto stack
  OP_PUSH_FALSE,    // Push false onto stack
  OP_POP,           // Pop value from stack
  OP_LOAD_VAR,      // Load variable onto stack
  OP_STORE_VAR,     // Store top of stack into variable
  OP_LOAD_GLOBAL,   // Load global variable
  OP_STORE_GLOBAL,  // Store global variable
  OP_LOAD_FIELD,    // Load object field
  OP_STORE_FIELD,   // Store object field
  OP_ADD,           // Addition
  OP_SUB,           // Subtraction
  OP_MUL,           // Multiplication
  OP_DIV,           // Division
  OP_MOD,           // Modulo
  OP_NEGATE,        // Unary negation
  OP_NOT,           // Logical NOT
  OP_EQUAL,         // Equality
  OP_NOT_EQUAL,     // Inequality
  OP_GREATER,       // Greater than
  OP_GREATER_EQUAL, // Greater or equal
  OP_LESS,          // Less than
  OP_LESS_EQUAL,    // Less or equal
  OP_AND,           // Logical AND
  OP_OR,            // Logical OR
  OP_JUMP,          // Unconditional jump
  OP_JUMP_IF_FALSE, // Jump if top of stack is false
  OP_JUMP_IF_TRUE,  // Jump if top of stack is true
  OP_CALL,          // Call function
  OP_RETURN,        // Return from function
  OP_ARRAY_NEW,     // Create new array
  OP_ARRAY_GET,     // Get array element
  OP_ARRAY_SET,     // Set array element
  OP_OBJECT_NEW,    // Create new object
  OP_OBJECT_GET,    // Get object property
  OP_OBJECT_SET,    // Set object property
  OP_TRY,           // Begin try block
  OP_CATCH,         // Begin catch block
  OP_THROW,         // Throw error
  OP_CHECK_NULL,    // Check if value is null (for null safety)
  OP_ENV,           // Get environment variable
  OP_INPUT,         // Read from stdin
  OP_PRINT,         // Debug print
} OpCode;

// Constant value types
typedef enum {
  CONST_NUMBER,
  CONST_STRING,
} ConstantType;

typedef struct {
  ConstantType type;
  union {
    double number;
    char *string;
  } as;
} Constant;

// Bytecode chunk
typedef struct {
  uint8_t *code;
  size_t count;
  size_t capacity;
  int *lines;
  Constant *constants;
  size_t constant_count;
  size_t constant_capacity;
} Chunk;

// Chunk operations
void chunk_init(Chunk *chunk);
void chunk_free(Chunk *chunk);
void chunk_write(Chunk *chunk, uint8_t byte, int line);
size_t chunk_add_constant(Chunk *chunk, Constant constant);
void chunk_disassemble(Chunk *chunk, const char *name);
int chunk_disassemble_instruction(Chunk *chunk, int offset);

// Constant operations
Constant constant_number(double value);
Constant constant_string(const char *str);
void constant_free(Constant *constant);

#endif // RIAU_BYTECODE_H

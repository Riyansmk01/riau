#ifndef RIAU_VM_H
#define RIAU_VM_H

#include "../bytecode/bytecode.h"
#include <stdbool.h>

#define STACK_MAX 256
#define FRAMES_MAX 64
#define GLOBALS_MAX 256

// Runtime value types
typedef enum {
  VAL_NULL,
  VAL_BOOL,
  VAL_NUMBER,
  VAL_STRING,
  VAL_ARRAY,
  VAL_OBJECT,
  VAL_FUNCTION,
} ValueType;

// Forward declarations
typedef struct Value Value;
typedef struct RiauArray RiauArray;
typedef struct RiauObject RiauObject;
typedef struct RiauFunction RiauFunction;

// Runtime value
struct Value {
  ValueType type;
  union {
    bool boolean;
    double number;
    char *string;
    RiauArray *array;
    RiauObject *object;
    RiauFunction *function;
  } as;
};

// Array type
struct RiauArray {
  Value *elements;
  size_t count;
  size_t capacity;
  int ref_count;
};

// Object type (hash map)
typedef struct {
  char *key;
  Value value;
} ObjectEntry;

struct RiauObject {
  ObjectEntry *entries;
  size_t count;
  size_t capacity;
  int ref_count;
};

// Function type
struct RiauFunction {
  Chunk *chunk;
  int arity;
  char *name;
  int ref_count;
};

// Call frame
typedef struct {
  RiauFunction *function;
  uint8_t *ip;
  Value *slots;
} CallFrame;

// Virtual Machine
typedef struct {
  Chunk *chunk;
  uint8_t *ip;
  Value stack[STACK_MAX];
  Value *stack_top;
  CallFrame frames[FRAMES_MAX];
  int frame_count;
  Value globals[GLOBALS_MAX];
  int global_count;
  bool had_error;
  char error_message[512];
} VM;

// VM operations
void vm_init(VM *vm);
void vm_free(VM *vm);
bool vm_execute(VM *vm, Chunk *chunk);
void vm_print_error(VM *vm);

// Value operations
Value value_null();
Value value_bool(bool b);
Value value_number(double n);
Value value_string(const char *str);
Value value_array();
Value value_object();
Value value_function(Chunk *chunk, int arity, const char *name);

bool value_is_null(Value v);
bool value_is_bool(Value v);
bool value_is_number(Value v);
bool value_is_string(Value v);
bool value_is_truthy(Value v);
bool value_equals(Value a, Value b);

void value_print(Value v);
void value_free(Value *v);

// Array operations
void array_push(RiauArray *arr, Value value);
Value array_get(RiauArray *arr, size_t index);
void array_set(RiauArray *arr, size_t index, Value value);

// Object operations
void object_set(RiauObject *obj, const char *key, Value value);
Value object_get(RiauObject *obj, const char *key);
bool object_has(RiauObject *obj, const char *key);

#endif // RIAU_VM_H

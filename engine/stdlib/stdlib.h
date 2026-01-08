#ifndef RIAU_STDLIB_H
#define RIAU_STDLIB_H

#include "../vm/vm.h"

// Built-in function signatures
typedef Value (*NativeFunction)(int arg_count, Value *args);

// Core functions
Value builtin_print(int arg_count, Value *args);
Value builtin_log(int arg_count, Value *args);
Value builtin_type_of(int arg_count, Value *args);
Value builtin_len(int arg_count, Value *args);

// String functions
Value builtin_str_concat(int arg_count, Value *args);
Value builtin_str_length(int arg_count, Value *args);
Value builtin_str_upper(int arg_count, Value *args);
Value builtin_str_lower(int arg_count, Value *args);

// Array functions
Value builtin_array_push(int arg_count, Value *args);
Value builtin_array_pop(int arg_count, Value *args);
Value builtin_array_length(int arg_count, Value *args);

// Math functions
Value builtin_math_abs(int arg_count, Value *args);
Value builtin_math_floor(int arg_count, Value *args);
Value builtin_math_ceil(int arg_count, Value *args);
Value builtin_math_round(int arg_count, Value *args);

// Utility functions
void stdlib_register_builtins(VM *vm);

#endif // RIAU_STDLIB_H

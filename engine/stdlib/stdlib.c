#include "stdlib.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Core functions
Value builtin_print(int arg_count, Value *args) {
  for (int i = 0; i < arg_count; i++) {
    value_print(args[i]);
    if (i < arg_count - 1) {
      printf(" ");
    }
  }
  printf("\n");
  return value_null();
}

Value builtin_log(int arg_count, Value *args) {
  printf("[LOG] ");
  for (int i = 0; i < arg_count; i++) {
    value_print(args[i]);
    if (i < arg_count - 1) {
      printf(" ");
    }
  }
  printf("\n");
  return value_null();
}

Value builtin_type_of(int arg_count, Value *args) {
  if (arg_count != 1) {
    return value_string("error: type_of expects 1 argument");
  }

  const char *type_name;
  switch (args[0].type) {
  case VAL_NULL:
    type_name = "null";
    break;
  case VAL_BOOL:
    type_name = "bool";
    break;
  case VAL_NUMBER:
    type_name = "number";
    break;
  case VAL_STRING:
    type_name = "string";
    break;
  case VAL_ARRAY:
    type_name = "array";
    break;
  case VAL_OBJECT:
    type_name = "object";
    break;
  case VAL_FUNCTION:
    type_name = "function";
    break;
  default:
    type_name = "unknown";
    break;
  }

  return value_string(type_name);
}

Value builtin_len(int arg_count, Value *args) {
  if (arg_count != 1) {
    return value_number(-1);
  }

  if (args[0].type == VAL_STRING) {
    return value_number((double)strlen(args[0].as.string));
  } else if (args[0].type == VAL_ARRAY) {
    return value_number((double)args[0].as.array->count);
  }

  return value_number(-1);
}

// String functions
Value builtin_str_concat(int arg_count, Value *args) {
  if (arg_count < 2) {
    return value_string("");
  }

  size_t total_len = 0;
  for (int i = 0; i < arg_count; i++) {
    if (args[i].type == VAL_STRING) {
      total_len += strlen(args[i].as.string);
    }
  }

  char *result = malloc(total_len + 1);
  result[0] = '\0';

  for (int i = 0; i < arg_count; i++) {
    if (args[i].type == VAL_STRING) {
      strcat(result, args[i].as.string);
    }
  }

  Value v = value_string(result);
  free(result);
  return v;
}

Value builtin_str_length(int arg_count, Value *args) {
  if (arg_count != 1 || args[0].type != VAL_STRING) {
    return value_number(0);
  }
  return value_number((double)strlen(args[0].as.string));
}

Value builtin_str_upper(int arg_count, Value *args) {
  if (arg_count != 1 || args[0].type != VAL_STRING) {
    return value_string("");
  }

  char *str = strdup(args[0].as.string);
  for (size_t i = 0; i < strlen(str); i++) {
    str[i] = toupper(str[i]);
  }

  Value v = value_string(str);
  free(str);
  return v;
}

Value builtin_str_lower(int arg_count, Value *args) {
  if (arg_count != 1 || args[0].type != VAL_STRING) {
    return value_string("");
  }

  char *str = strdup(args[0].as.string);
  for (size_t i = 0; i < strlen(str); i++) {
    str[i] = tolower(str[i]);
  }

  Value v = value_string(str);
  free(str);
  return v;
}

// Array functions
Value builtin_array_push(int arg_count, Value *args) {
  if (arg_count != 2 || args[0].type != VAL_ARRAY) {
    return value_null();
  }

  array_push(args[0].as.array, args[1]);
  return args[0];
}

Value builtin_array_pop(int arg_count, Value *args) {
  if (arg_count != 1 || args[0].type != VAL_ARRAY) {
    return value_null();
  }

  RiauArray *arr = args[0].as.array;
  if (arr->count == 0) {
    return value_null();
  }

  Value last = arr->elements[arr->count - 1];
  arr->count--;
  return last;
}

Value builtin_array_length(int arg_count, Value *args) {
  if (arg_count != 1 || args[0].type != VAL_ARRAY) {
    return value_number(0);
  }
  return value_number((double)args[0].as.array->count);
}

// Math functions
Value builtin_math_abs(int arg_count, Value *args) {
  if (arg_count != 1 || args[0].type != VAL_NUMBER) {
    return value_number(0);
  }
  return value_number(fabs(args[0].as.number));
}

Value builtin_math_floor(int arg_count, Value *args) {
  if (arg_count != 1 || args[0].type != VAL_NUMBER) {
    return value_number(0);
  }
  return value_number(floor(args[0].as.number));
}

Value builtin_math_ceil(int arg_count, Value *args) {
  if (arg_count != 1 || args[0].type != VAL_NUMBER) {
    return value_number(0);
  }
  return value_number(ceil(args[0].as.number));
}

Value builtin_math_round(int arg_count, Value *args) {
  if (arg_count != 1 || args[0].type != VAL_NUMBER) {
    return value_number(0);
  }
  return value_number(round(args[0].as.number));
}

// Register all built-in functions (placeholder for now)
void stdlib_register_builtins(VM *vm) {
  // This would register built-in functions in the VM's global scope
  // For now, this is a placeholder
  (void)vm; // Suppress unused parameter warning
}

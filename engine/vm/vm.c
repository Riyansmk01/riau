#include "vm.h"
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Stack operations
static void reset_stack(VM *vm) {
  vm->stack_top = vm->stack;
  vm->frame_count = 0;
}

static void push(VM *vm, Value value) {
  *vm->stack_top = value;
  vm->stack_top++;
}

static Value pop(VM *vm) {
  vm->stack_top--;
  return *vm->stack_top;
}

static Value peek(VM *vm, int distance) { return vm->stack_top[-1 - distance]; }

// Error handling
static void runtime_error(VM *vm, const char *format, ...) {
  va_list args;
  va_start(args, format);
  vsnprintf(vm->error_message, sizeof(vm->error_message), format, args);
  va_end(args);

  vm->had_error = true;

  // Print stack trace
  for (int i = vm->frame_count - 1; i >= 0; i--) {
    CallFrame *frame = &vm->frames[i];
    RiauFunction *function = frame->function;
    size_t instruction = frame->ip - function->chunk->code - 1;
    fprintf(stderr, "[line %d] in %s()\n", function->chunk->lines[instruction],
            function->name ? function->name : "script");
  }

  reset_stack(vm);
}

// Value operations
Value value_null() {
  Value v;
  v.type = VAL_NULL;
  return v;
}

Value value_bool(bool b) {
  Value v;
  v.type = VAL_BOOL;
  v.as.boolean = b;
  return v;
}

Value value_number(double n) {
  Value v;
  v.type = VAL_NUMBER;
  v.as.number = n;
  return v;
}

Value value_string(const char *str) {
  Value v;
  v.type = VAL_STRING;
  v.as.string = malloc(strlen(str) + 1);
  strcpy(v.as.string, str);
  return v;
}

Value value_array() {
  Value v;
  v.type = VAL_ARRAY;
  v.as.array = malloc(sizeof(RiauArray));
  v.as.array->elements = NULL;
  v.as.array->count = 0;
  v.as.array->capacity = 0;
  v.as.array->ref_count = 1;
  return v;
}

Value value_object() {
  Value v;
  v.type = VAL_OBJECT;
  v.as.object = malloc(sizeof(RiauObject));
  v.as.object->entries = NULL;
  v.as.object->count = 0;
  v.as.object->capacity = 0;
  v.as.object->ref_count = 1;
  return v;
}

Value value_function(Chunk *chunk, int arity, const char *name) {
  Value v;
  v.type = VAL_FUNCTION;
  v.as.function = malloc(sizeof(RiauFunction));
  v.as.function->chunk = chunk;
  v.as.function->arity = arity;
  v.as.function->name = name ? strdup(name) : NULL;
  v.as.function->ref_count = 1;
  return v;
}

bool value_is_null(Value v) { return v.type == VAL_NULL; }
bool value_is_bool(Value v) { return v.type == VAL_BOOL; }
bool value_is_number(Value v) { return v.type == VAL_NUMBER; }
bool value_is_string(Value v) { return v.type == VAL_STRING; }

bool value_is_truthy(Value v) {
  if (v.type == VAL_NULL)
    return false;
  if (v.type == VAL_BOOL)
    return v.as.boolean;
  return true;
}

bool value_equals(Value a, Value b) {
  if (a.type != b.type)
    return false;

  switch (a.type) {
  case VAL_NULL:
    return true;
  case VAL_BOOL:
    return a.as.boolean == b.as.boolean;
  case VAL_NUMBER:
    return fabs(a.as.number - b.as.number) < 1e-10;
  case VAL_STRING:
    return strcmp(a.as.string, b.as.string) == 0;
  default:
    return false;
  }
}

void value_print(Value v) {
  switch (v.type) {
  case VAL_NULL:
    printf("null");
    break;
  case VAL_BOOL:
    printf(v.as.boolean ? "true" : "false");
    break;
  case VAL_NUMBER:
    printf("%g", v.as.number);
    break;
  case VAL_STRING:
    printf("%s", v.as.string);
    break;
  case VAL_ARRAY:
    printf("[Array]");
    break;
  case VAL_OBJECT:
    printf("[Object]");
    break;
  case VAL_FUNCTION:
    printf("[Function %s]",
           v.as.function->name ? v.as.function->name : "anonymous");
    break;
  }
}

void value_free(Value *v) {
  switch (v->type) {
  case VAL_STRING:
    free(v->as.string);
    break;
  case VAL_ARRAY:
    if (--v->as.array->ref_count == 0) {
      for (size_t i = 0; i < v->as.array->count; i++) {
        value_free(&v->as.array->elements[i]);
      }
      free(v->as.array->elements);
      free(v->as.array);
    }
    break;
  case VAL_OBJECT:
    if (--v->as.object->ref_count == 0) {
      for (size_t i = 0; i < v->as.object->count; i++) {
        free(v->as.object->entries[i].key);
        value_free(&v->as.object->entries[i].value);
      }
      free(v->as.object->entries);
      free(v->as.object);
    }
    break;
  case VAL_FUNCTION:
    if (--v->as.function->ref_count == 0) {
      free(v->as.function->name);
      free(v->as.function);
    }
    break;
  default:
    break;
  }
}

// Array operations
void array_push(RiauArray *arr, Value value) {
  if (arr->capacity < arr->count + 1) {
    size_t old_capacity = arr->capacity;
    arr->capacity = old_capacity < 8 ? 8 : old_capacity * 2;
    arr->elements = realloc(arr->elements, arr->capacity * sizeof(Value));
  }
  arr->elements[arr->count++] = value;
}

Value array_get(RiauArray *arr, size_t index) {
  if (index >= arr->count) {
    return value_null();
  }
  return arr->elements[index];
}

void array_set(RiauArray *arr, size_t index, Value value) {
  if (index >= arr->count) {
    // Expand array
    while (arr->count <= index) {
      array_push(arr, value_null());
    }
  }
  arr->elements[index] = value;
}

// Object operations
void object_set(RiauObject *obj, const char *key, Value value) {
  // Simple linear search (could be optimized with hash table)
  for (size_t i = 0; i < obj->count; i++) {
    if (strcmp(obj->entries[i].key, key) == 0) {
      value_free(&obj->entries[i].value);
      obj->entries[i].value = value;
      return;
    }
  }

  // Add new entry
  if (obj->capacity < obj->count + 1) {
    size_t old_capacity = obj->capacity;
    obj->capacity = old_capacity < 8 ? 8 : old_capacity * 2;
    obj->entries = realloc(obj->entries, obj->capacity * sizeof(ObjectEntry));
  }

  obj->entries[obj->count].key = strdup(key);
  obj->entries[obj->count].value = value;
  obj->count++;
}

Value object_get(RiauObject *obj, const char *key) {
  for (size_t i = 0; i < obj->count; i++) {
    if (strcmp(obj->entries[i].key, key) == 0) {
      return obj->entries[i].value;
    }
  }
  return value_null();
}

bool object_has(RiauObject *obj, const char *key) {
  for (size_t i = 0; i < obj->count; i++) {
    if (strcmp(obj->entries[i].key, key) == 0) {
      return true;
    }
  }
  return false;
}

// VM operations
void vm_init(VM *vm) {
  reset_stack(vm);
  vm->chunk = NULL;
  vm->ip = NULL;
  vm->global_count = 0;
  vm->had_error = false;
  vm->error_message[0] = '\0';
}

void vm_free(VM *vm) {
  // Free stack values
  while (vm->stack_top > vm->stack) {
    vm->stack_top--;
    value_free(vm->stack_top);
  }

  // Free globals
  for (int i = 0; i < vm->global_count; i++) {
    value_free(&vm->globals[i]);
  }
}

static uint8_t read_byte(VM *vm) { return *vm->ip++; }

static uint16_t read_short(VM *vm) {
  vm->ip += 2;
  return (uint16_t)((vm->ip[-2] << 8) | vm->ip[-1]);
}

static Constant read_constant(VM *vm) {
  return vm->chunk->constants[read_byte(vm)];
}

bool vm_execute(VM *vm, Chunk *chunk) {
  vm->chunk = chunk;
  vm->ip = chunk->code;

  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("          ");
    for (Value *slot = vm->stack; slot < vm->stack_top; slot++) {
      printf("[ ");
      value_print(*slot);
      printf(" ]");
    }
    printf("\n");
    chunk_disassemble_instruction(vm->chunk, (int)(vm->ip - vm->chunk->code));
#endif

    uint8_t instruction = read_byte(vm);

    switch (instruction) {
    case OP_HALT:
      return !vm->had_error;

    case OP_PUSH_CONST: {
      Constant constant = read_constant(vm);
      if (constant.type == CONST_NUMBER) {
        push(vm, value_number(constant.as.number));
      } else if (constant.type == CONST_STRING) {
        push(vm, value_string(constant.as.string));
      }
      break;
    }

    case OP_PUSH_NULL:
      push(vm, value_null());
      break;

    case OP_PUSH_TRUE:
      push(vm, value_bool(true));
      break;

    case OP_PUSH_FALSE:
      push(vm, value_bool(false));
      break;

    case OP_POP: {
      Value v = pop(vm);
      value_free(&v);
      break;
    }

    case OP_ADD: {
      Value b = pop(vm);
      Value a = pop(vm);
      if (value_is_number(a) && value_is_number(b)) {
        push(vm, value_number(a.as.number + b.as.number));
      } else if (value_is_string(a) && value_is_string(b)) {
        char *result = malloc(strlen(a.as.string) + strlen(b.as.string) + 1);
        strcpy(result, a.as.string);
        strcat(result, b.as.string);
        push(vm, value_string(result));
        free(result);
      } else {
        runtime_error(vm, "Operands must be two numbers or two strings");
        return false;
      }
      value_free(&a);
      value_free(&b);
      break;
    }

    case OP_SUB: {
      Value b = pop(vm);
      Value a = pop(vm);
      if (!value_is_number(a) || !value_is_number(b)) {
        runtime_error(vm, "Operands must be numbers");
        return false;
      }
      push(vm, value_number(a.as.number - b.as.number));
      value_free(&a);
      value_free(&b);
      break;
    }

    case OP_MUL: {
      Value b = pop(vm);
      Value a = pop(vm);
      if (!value_is_number(a) || !value_is_number(b)) {
        runtime_error(vm, "Operands must be numbers");
        return false;
      }
      push(vm, value_number(a.as.number * b.as.number));
      value_free(&a);
      value_free(&b);
      break;
    }

    case OP_DIV: {
      Value b = pop(vm);
      Value a = pop(vm);
      if (!value_is_number(a) || !value_is_number(b)) {
        runtime_error(vm, "Operands must be numbers");
        return false;
      }
      if (b.as.number == 0) {
        runtime_error(vm, "Division by zero");
        return false;
      }
      push(vm, value_number(a.as.number / b.as.number));
      value_free(&a);
      value_free(&b);
      break;
    }

    case OP_NEGATE: {
      Value v = pop(vm);
      if (!value_is_number(v)) {
        runtime_error(vm, "Operand must be a number");
        return false;
      }
      push(vm, value_number(-v.as.number));
      value_free(&v);
      break;
    }

    case OP_NOT: {
      Value v = pop(vm);
      push(vm, value_bool(!value_is_truthy(v)));
      value_free(&v);
      break;
    }

    case OP_EQUAL: {
      Value b = pop(vm);
      Value a = pop(vm);
      push(vm, value_bool(value_equals(a, b)));
      value_free(&a);
      value_free(&b);
      break;
    }

    case OP_GREATER: {
      Value b = pop(vm);
      Value a = pop(vm);
      if (!value_is_number(a) || !value_is_number(b)) {
        runtime_error(vm, "Operands must be numbers");
        return false;
      }
      push(vm, value_bool(a.as.number > b.as.number));
      value_free(&a);
      value_free(&b);
      break;
    }

    case OP_LESS: {
      Value b = pop(vm);
      Value a = pop(vm);
      if (!value_is_number(a) || !value_is_number(b)) {
        runtime_error(vm, "Operands must be numbers");
        return false;
      }
      push(vm, value_bool(a.as.number < b.as.number));
      value_free(&a);
      value_free(&b);
      break;
    }

    case OP_MOD: {
      Value b = pop(vm);
      Value a = pop(vm);
      if (!value_is_number(a) || !value_is_number(b)) {
        runtime_error(vm, "Operands must be numbers");
        return false;
      }
      if (b.as.number == 0) {
        runtime_error(vm, "Modulo by zero");
        return false;
      }
      push(vm, value_number(fmod(a.as.number, b.as.number)));
      value_free(&a);
      value_free(&b);
      break;
    }

    case OP_NOT_EQUAL: {
      Value b = pop(vm);
      Value a = pop(vm);
      push(vm, value_bool(!value_equals(a, b)));
      value_free(&a);
      value_free(&b);
      break;
    }

    case OP_LESS_EQUAL: {
      Value b = pop(vm);
      Value a = pop(vm);
      if (!value_is_number(a) || !value_is_number(b)) {
        runtime_error(vm, "Operands must be numbers");
        return false;
      }
      push(vm, value_bool(a.as.number <= b.as.number));
      value_free(&a);
      value_free(&b);
      break;
    }

    case OP_GREATER_EQUAL: {
      Value b = pop(vm);
      Value a = pop(vm);
      if (!value_is_number(a) || !value_is_number(b)) {
        runtime_error(vm, "Operands must be numbers");
        return false;
      }
      push(vm, value_bool(a.as.number >= b.as.number));
      value_free(&a);
      value_free(&b);
      break;
    }

    case OP_AND: {
      Value b = pop(vm);
      Value a = pop(vm);
      push(vm, value_bool(value_is_truthy(a) && value_is_truthy(b)));
      value_free(&a);
      value_free(&b);
      break;
    }

    case OP_OR: {
      Value b = pop(vm);
      Value a = pop(vm);
      push(vm, value_bool(value_is_truthy(a) || value_is_truthy(b)));
      value_free(&a);
      value_free(&b);
      break;
    }

    case OP_STORE_VAR: {
      uint8_t slot = read_byte(vm);
      if (slot >= GLOBALS_MAX) {
        runtime_error(vm, "Too many global variables");
        return false;
      }
      vm->globals[slot] = peek(vm, 0);
      if (slot >= vm->global_count) {
        vm->global_count = slot + 1;
      }
      break;
    }

    case OP_LOAD_VAR: {
      uint8_t slot = read_byte(vm);
      if (slot >= vm->global_count) {
        runtime_error(vm, "Undefined variable");
        return false;
      }
      push(vm, vm->globals[slot]);
      break;
    }

    case OP_CHECK_NULL: {
      Value v = peek(vm, 0);
      if (value_is_null(v)) {
        runtime_error(vm, "Variable may be null");
        return false;
      }
      break;
    }

    case OP_ENV: {
      Value v = pop(vm);
      if (!value_is_string(v)) {
        runtime_error(vm, "env() requires a string argument");
        value_free(&v);
        return false;
      }

      char *env_value = getenv(v.as.string);
      if (env_value) {
        push(vm, value_string(env_value));
      } else {
        push(vm, value_null());
      }
      value_free(&v);
      break;
    }

    case OP_INPUT: {
      // Read from stdin (for POST data)
      char *content_length_str = getenv("CONTENT_LENGTH");
      size_t content_length = 0;

      if (content_length_str) {
        content_length = (size_t)atoi(content_length_str);
      }

      if (content_length > 0 && content_length < 1048576) { // Max 1MB
        // Read exactly content_length bytes from stdin
        char *buffer = malloc(content_length + 1);
        if (buffer) {
          size_t bytes_read = fread(buffer, 1, content_length, stdin);
          buffer[bytes_read] = '\0';
          push(vm, value_string(buffer));
          free(buffer);
        } else {
          push(vm, value_string(""));
        }
      } else {
        // No content or too large, return empty string
        push(vm, value_string(""));
      }
      break;
    }

    case OP_PRINT: {
      Value v = pop(vm);
      value_print(v);
      printf("\n");
      value_free(&v);
      break;
    }

    default:
      runtime_error(vm, "Unknown opcode %d", instruction);
      return false;
    }
  }

  return !vm->had_error;
}

void vm_print_error(VM *vm) {
  if (vm->had_error) {
    fprintf(stderr, "Runtime error: %s\n", vm->error_message);
  }
}

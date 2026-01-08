#include "bytecode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void chunk_init(Chunk *chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lines = NULL;
  chunk->constants = NULL;
  chunk->constant_count = 0;
  chunk->constant_capacity = 0;
}

void chunk_free(Chunk *chunk) {
  free(chunk->code);
  free(chunk->lines);

  for (size_t i = 0; i < chunk->constant_count; i++) {
    constant_free(&chunk->constants[i]);
  }
  free(chunk->constants);

  chunk_init(chunk);
}

void chunk_write(Chunk *chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    size_t old_capacity = chunk->capacity;
    chunk->capacity = old_capacity < 8 ? 8 : old_capacity * 2;
    chunk->code = realloc(chunk->code, chunk->capacity);
    chunk->lines = realloc(chunk->lines, chunk->capacity * sizeof(int));
  }

  chunk->code[chunk->count] = byte;
  chunk->lines[chunk->count] = line;
  chunk->count++;
}

size_t chunk_add_constant(Chunk *chunk, Constant constant) {
  if (chunk->constant_capacity < chunk->constant_count + 1) {
    size_t old_capacity = chunk->constant_capacity;
    chunk->constant_capacity = old_capacity < 8 ? 8 : old_capacity * 2;
    chunk->constants =
        realloc(chunk->constants, chunk->constant_capacity * sizeof(Constant));
  }

  chunk->constants[chunk->constant_count] = constant;
  return chunk->constant_count++;
}

Constant constant_number(double value) {
  Constant c;
  c.type = CONST_NUMBER;
  c.as.number = value;
  return c;
}

Constant constant_string(const char *str) {
  Constant c;
  c.type = CONST_STRING;
  c.as.string = malloc(strlen(str) + 1);
  strcpy(c.as.string, str);
  return c;
}

void constant_free(Constant *constant) {
  if (constant->type == CONST_STRING) {
    free(constant->as.string);
  }
}

static const char *opcode_name(OpCode op) {
  switch (op) {
  case OP_HALT:
    return "HALT";
  case OP_PUSH_CONST:
    return "PUSH_CONST";
  case OP_PUSH_NULL:
    return "PUSH_NULL";
  case OP_PUSH_TRUE:
    return "PUSH_TRUE";
  case OP_PUSH_FALSE:
    return "PUSH_FALSE";
  case OP_POP:
    return "POP";
  case OP_LOAD_VAR:
    return "LOAD_VAR";
  case OP_STORE_VAR:
    return "STORE_VAR";
  case OP_LOAD_GLOBAL:
    return "LOAD_GLOBAL";
  case OP_STORE_GLOBAL:
    return "STORE_GLOBAL";
  case OP_LOAD_FIELD:
    return "LOAD_FIELD";
  case OP_STORE_FIELD:
    return "STORE_FIELD";
  case OP_ADD:
    return "ADD";
  case OP_SUB:
    return "SUB";
  case OP_MUL:
    return "MUL";
  case OP_DIV:
    return "DIV";
  case OP_MOD:
    return "MOD";
  case OP_NEGATE:
    return "NEGATE";
  case OP_NOT:
    return "NOT";
  case OP_EQUAL:
    return "EQUAL";
  case OP_NOT_EQUAL:
    return "NOT_EQUAL";
  case OP_GREATER:
    return "GREATER";
  case OP_GREATER_EQUAL:
    return "GREATER_EQUAL";
  case OP_LESS:
    return "LESS";
  case OP_LESS_EQUAL:
    return "LESS_EQUAL";
  case OP_AND:
    return "AND";
  case OP_OR:
    return "OR";
  case OP_JUMP:
    return "JUMP";
  case OP_JUMP_IF_FALSE:
    return "JUMP_IF_FALSE";
  case OP_JUMP_IF_TRUE:
    return "JUMP_IF_TRUE";
  case OP_CALL:
    return "CALL";
  case OP_RETURN:
    return "RETURN";
  case OP_ARRAY_NEW:
    return "ARRAY_NEW";
  case OP_ARRAY_GET:
    return "ARRAY_GET";
  case OP_ARRAY_SET:
    return "ARRAY_SET";
  case OP_OBJECT_NEW:
    return "OBJECT_NEW";
  case OP_OBJECT_GET:
    return "OBJECT_GET";
  case OP_OBJECT_SET:
    return "OBJECT_SET";
  case OP_TRY:
    return "TRY";
  case OP_CATCH:
    return "CATCH";
  case OP_THROW:
    return "THROW";
  case OP_CHECK_NULL:
    return "CHECK_NULL";
  case OP_PRINT:
    return "PRINT";
  default:
    return "UNKNOWN";
  }
}

static int simple_instruction(const char *name, int offset) {
  printf("%s\n", name);
  return offset + 1;
}

static int constant_instruction(const char *name, Chunk *chunk, int offset) {
  uint8_t constant_idx = chunk->code[offset + 1];
  printf("%-16s %4d '", name, constant_idx);

  Constant *c = &chunk->constants[constant_idx];
  if (c->type == CONST_NUMBER) {
    printf("%g", c->as.number);
  } else if (c->type == CONST_STRING) {
    printf("%s", c->as.string);
  }
  printf("'\n");

  return offset + 2;
}

static int byte_instruction(const char *name, Chunk *chunk, int offset) {
  uint8_t slot = chunk->code[offset + 1];
  printf("%-16s %4d\n", name, slot);
  return offset + 2;
}

static int jump_instruction(const char *name, int sign, Chunk *chunk,
                            int offset) {
  uint16_t jump = (uint16_t)(chunk->code[offset + 1] << 8);
  jump |= chunk->code[offset + 2];
  printf("%-16s %4d -> %d\n", name, offset, offset + 3 + sign * jump);
  return offset + 3;
}

int chunk_disassemble_instruction(Chunk *chunk, int offset) {
  printf("%04d ", offset);

  if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
    printf("   | ");
  } else {
    printf("%4d ", chunk->lines[offset]);
  }

  uint8_t instruction = chunk->code[offset];
  switch (instruction) {
  case OP_PUSH_CONST:
    return constant_instruction("PUSH_CONST", chunk, offset);
  case OP_LOAD_VAR:
  case OP_STORE_VAR:
  case OP_LOAD_GLOBAL:
  case OP_STORE_GLOBAL:
  case OP_CALL:
    return byte_instruction(opcode_name(instruction), chunk, offset);
  case OP_JUMP:
  case OP_JUMP_IF_FALSE:
  case OP_JUMP_IF_TRUE:
    return jump_instruction(opcode_name(instruction), 1, chunk, offset);
  default:
    return simple_instruction(opcode_name(instruction), offset);
  }
}

void chunk_disassemble(Chunk *chunk, const char *name) {
  printf("== %s ==\n", name);

  for (size_t offset = 0; offset < chunk->count;) {
    offset = chunk_disassemble_instruction(chunk, offset);
  }
}

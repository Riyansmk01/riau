// Test: VM functionality
#include "../bytecode/bytecode.h"
#include "../vm/vm.h"
#include <assert.h>
#include <stdio.h>


void test_vm_arithmetic() {
  printf("Testing VM arithmetic operations...\n");

  Chunk chunk;
  chunk_init(&chunk);

  // Push 10
  size_t const1 = chunk_add_constant(&chunk, constant_number(10));
  chunk_write(&chunk, OP_PUSH_CONST, 1);
  chunk_write(&chunk, (uint8_t)const1, 1);

  // Push 20
  size_t const2 = chunk_add_constant(&chunk, constant_number(20));
  chunk_write(&chunk, OP_PUSH_CONST, 1);
  chunk_write(&chunk, (uint8_t)const2, 1);

  // Add
  chunk_write(&chunk, OP_ADD, 1);

  // Print
  chunk_write(&chunk, OP_PRINT, 1);

  // Halt
  chunk_write(&chunk, OP_HALT, 1);

  VM vm;
  vm_init(&vm);

  bool result = vm_execute(&vm, &chunk);
  assert(result == true);

  vm_free(&vm);
  chunk_free(&chunk);

  printf("✓ VM arithmetic test passed\n");
}

void test_vm_comparison() {
  printf("Testing VM comparison operations...\n");

  Chunk chunk;
  chunk_init(&chunk);

  // Push 10
  size_t const1 = chunk_add_constant(&chunk, constant_number(10));
  chunk_write(&chunk, OP_PUSH_CONST, 1);
  chunk_write(&chunk, (uint8_t)const1, 1);

  // Push 20
  size_t const2 = chunk_add_constant(&chunk, constant_number(20));
  chunk_write(&chunk, OP_PUSH_CONST, 1);
  chunk_write(&chunk, (uint8_t)const2, 1);

  // Less than
  chunk_write(&chunk, OP_LESS, 1);

  // Print
  chunk_write(&chunk, OP_PRINT, 1);

  // Halt
  chunk_write(&chunk, OP_HALT, 1);

  VM vm;
  vm_init(&vm);

  bool result = vm_execute(&vm, &chunk);
  assert(result == true);

  vm_free(&vm);
  chunk_free(&chunk);

  printf("✓ VM comparison test passed\n");
}

void test_vm_strings() {
  printf("Testing VM string operations...\n");

  Chunk chunk;
  chunk_init(&chunk);

  // Push "Hello"
  size_t const1 = chunk_add_constant(&chunk, constant_string("Hello"));
  chunk_write(&chunk, OP_PUSH_CONST, 1);
  chunk_write(&chunk, (uint8_t)const1, 1);

  // Push " World"
  size_t const2 = chunk_add_constant(&chunk, constant_string(" World"));
  chunk_write(&chunk, OP_PUSH_CONST, 1);
  chunk_write(&chunk, (uint8_t)const2, 1);

  // Concatenate
  chunk_write(&chunk, OP_ADD, 1);

  // Print
  chunk_write(&chunk, OP_PRINT, 1);

  // Halt
  chunk_write(&chunk, OP_HALT, 1);

  VM vm;
  vm_init(&vm);

  bool result = vm_execute(&vm, &chunk);
  assert(result == true);

  vm_free(&vm);
  chunk_free(&chunk);

  printf("✓ VM string test passed\n");
}

int main() {
  printf("=== Riau VM Tests ===\n\n");

  test_vm_arithmetic();
  test_vm_comparison();
  test_vm_strings();

  printf("\n=== All VM tests passed! ===\n");
  return 0;
}

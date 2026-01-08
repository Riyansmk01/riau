#ifndef RIAU_AST_H
#define RIAU_AST_H

#include <stddef.h>
#include <stdbool.h>

// Forward declarations
typedef struct ASTNode ASTNode;
typedef struct ASTNodeList ASTNodeList;

// AST Node Types
typedef enum {
    AST_PROGRAM,
    AST_VARIABLE_DECL,
    AST_FUNCTION_DECL,
    AST_ENTITY_DECL,
    AST_PARAMETER,
    AST_BLOCK,
    AST_IF_STMT,
    AST_FOR_STMT,
    AST_RETURN_STMT,
    AST_TRY_CATCH_STMT,
    AST_EXPR_STMT,
    AST_USE_STMT,
    AST_SPAWN_STMT,
    AST_BINARY_EXPR,
    AST_UNARY_EXPR,
    AST_CALL_EXPR,
    AST_MEMBER_EXPR,
    AST_INDEX_EXPR,
    AST_IDENTIFIER,
    AST_LITERAL_NUMBER,
    AST_LITERAL_STRING,
    AST_LITERAL_BOOL,
    AST_LITERAL_NULL,
    AST_ARRAY_LITERAL,
    AST_OBJECT_LITERAL
} ASTNodeType;

// Type information
typedef enum {
    TYPE_UNKNOWN,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_BOOL,
    TYPE_NULL,
    TYPE_ARRAY,
    TYPE_OBJECT,
    TYPE_FUNCTION,
    TYPE_OPTIONAL
} TypeKind;

typedef struct {
    TypeKind kind;
    bool is_optional;
    char* name;
} TypeInfo;

// Linked list for AST nodes
struct ASTNodeList {
    ASTNode* node;
    ASTNodeList* next;
};

// AST Node structure
struct ASTNode {
    ASTNodeType type;
    int line;
    int column;
    
    union {
        // Program
        struct {
            ASTNodeList* statements;
        } program;
        
        // Variable declaration: let name: type? = value
        struct {
            char* name;
            TypeInfo* type_info;
            ASTNode* initializer;
        } var_decl;
        
        // Function declaration: fn name(params) { body } or fn name(params) => expr
        struct {
            char* name;
            ASTNodeList* parameters;
            TypeInfo* return_type;
            ASTNode* body;
            bool is_arrow;
        } func_decl;
        
        // Entity declaration: entity Name { fields }
        struct {
            char* name;
            ASTNodeList* fields;
        } entity_decl;
        
        // Parameter: name: type
        struct {
            char* name;
            TypeInfo* type_info;
        } parameter;
        
        // Block: { statements }
        struct {
            ASTNodeList* statements;
        } block;
        
        // If statement: if condition { then_branch } else { else_branch }
        struct {
            ASTNode* condition;
            ASTNode* then_branch;
            ASTNode* else_branch;
        } if_stmt;
        
        // For loop: for item in iterable { body }
        struct {
            char* iterator;
            ASTNode* iterable;
            ASTNode* body;
        } for_stmt;
        
        // Return statement: return value
        struct {
            ASTNode* value;
        } return_stmt;
        
        // Try-catch: try { try_block } catch ErrorType as name { catch_block }
        struct {
            ASTNode* try_block;
            char* error_type;
            char* error_name;
            ASTNode* catch_block;
        } try_catch;
        
        // Use statement: use module.submodule
        struct {
            char* module_path;
        } use_stmt;
        
        // Spawn statement: spawn { body }
        struct {
            ASTNode* body;
        } spawn_stmt;
        
        // Expression statement
        struct {
            ASTNode* expression;
        } expr_stmt;
        
        // Binary expression: left op right
        struct {
            char* operator;
            ASTNode* left;
            ASTNode* right;
        } binary;
        
        // Unary expression: op operand
        struct {
            char* operator;
            ASTNode* operand;
        } unary;
        
        // Call expression: callee(arguments)
        struct {
            ASTNode* callee;
            ASTNodeList* arguments;
        } call;
        
        // Member expression: object.property
        struct {
            ASTNode* object;
            char* property;
        } member;
        
        // Index expression: array[index]
        struct {
            ASTNode* array;
            ASTNode* index;
        } index;
        
        // Identifier
        struct {
            char* name;
        } identifier;
        
        // Literals
        struct {
            double value;
        } number;
        
        struct {
            char* value;
        } string;
        
        struct {
            bool value;
        } boolean;
        
        // Array literal: [elements]
        struct {
            ASTNodeList* elements;
        } array;
        
        // Object literal: { key: value, ... }
        struct {
            ASTNodeList* pairs; // Each pair is a binary node with key and value
        } object;
    } data;
};

// AST creation functions
ASTNode* ast_create_program(ASTNodeList* statements);
ASTNode* ast_create_var_decl(char* name, TypeInfo* type_info, ASTNode* initializer, int line, int column);
ASTNode* ast_create_func_decl(char* name, ASTNodeList* parameters, TypeInfo* return_type, ASTNode* body, bool is_arrow, int line, int column);
ASTNode* ast_create_entity_decl(char* name, ASTNodeList* fields, int line, int column);
ASTNode* ast_create_parameter(char* name, TypeInfo* type_info, int line, int column);
ASTNode* ast_create_block(ASTNodeList* statements, int line, int column);
ASTNode* ast_create_if_stmt(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch, int line, int column);
ASTNode* ast_create_for_stmt(char* iterator, ASTNode* iterable, ASTNode* body, int line, int column);
ASTNode* ast_create_return_stmt(ASTNode* value, int line, int column);
ASTNode* ast_create_try_catch(ASTNode* try_block, char* error_type, char* error_name, ASTNode* catch_block, int line, int column);
ASTNode* ast_create_use_stmt(char* module_path, int line, int column);
ASTNode* ast_create_spawn_stmt(ASTNode* body, int line, int column);
ASTNode* ast_create_expr_stmt(ASTNode* expression, int line, int column);
ASTNode* ast_create_binary(char* operator, ASTNode* left, ASTNode* right, int line, int column);
ASTNode* ast_create_unary(char* operator, ASTNode* operand, int line, int column);
ASTNode* ast_create_call(ASTNode* callee, ASTNodeList* arguments, int line, int column);
ASTNode* ast_create_member(ASTNode* object, char* property, int line, int column);
ASTNode* ast_create_index(ASTNode* array, ASTNode* index, int line, int column);
ASTNode* ast_create_identifier(char* name, int line, int column);
ASTNode* ast_create_number(double value, int line, int column);
ASTNode* ast_create_string(char* value, int line, int column);
ASTNode* ast_create_bool(bool value, int line, int column);
ASTNode* ast_create_null(int line, int column);
ASTNode* ast_create_array(ASTNodeList* elements, int line, int column);
ASTNode* ast_create_object(ASTNodeList* pairs, int line, int column);

// List operations
ASTNodeList* ast_list_create(ASTNode* node);
ASTNodeList* ast_list_append(ASTNodeList* list, ASTNode* node);
size_t ast_list_length(ASTNodeList* list);

// Type operations
TypeInfo* type_create(TypeKind kind, bool is_optional, char* name);
TypeInfo* type_parse(const char* type_string);

// Memory management
void ast_free(ASTNode* node);
void ast_list_free(ASTNodeList* list);
void type_free(TypeInfo* type);

// Debugging
void ast_print(ASTNode* node, int indent);
const char* ast_type_to_string(ASTNodeType type);

#endif // RIAU_AST_H

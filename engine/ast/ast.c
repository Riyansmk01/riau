#include "ast.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Helper to allocate and copy strings
static char* str_dup(const char* str) {
    if (!str) return NULL;
    size_t len = strlen(str);
    char* copy = malloc(len + 1);
    if (copy) {
        memcpy(copy, str, len + 1);
    }
    return copy;
}

// AST Node creation
static ASTNode* ast_create_node(ASTNodeType type, int line, int column) {
    ASTNode* node = calloc(1, sizeof(ASTNode));
    node->type = type;
    node->line = line;
    node->column = column;
    return node;
}

ASTNode* ast_create_program(ASTNodeList* statements) {
    ASTNode* node = ast_create_node(AST_PROGRAM, 0, 0);
    node->data.program.statements = statements;
    return node;
}

ASTNode* ast_create_var_decl(char* name, TypeInfo* type_info, ASTNode* initializer, int line, int column) {
    ASTNode* node = ast_create_node(AST_VARIABLE_DECL, line, column);
    node->data.var_decl.name = str_dup(name);
    node->data.var_decl.type_info = type_info;
    node->data.var_decl.initializer = initializer;
    return node;
}

ASTNode* ast_create_func_decl(char* name, ASTNodeList* parameters, TypeInfo* return_type, ASTNode* body, bool is_arrow, int line, int column) {
    ASTNode* node = ast_create_node(AST_FUNCTION_DECL, line, column);
    node->data.func_decl.name = str_dup(name);
    node->data.func_decl.parameters = parameters;
    node->data.func_decl.return_type = return_type;
    node->data.func_decl.body = body;
    node->data.func_decl.is_arrow = is_arrow;
    return node;
}

ASTNode* ast_create_entity_decl(char* name, ASTNodeList* fields, int line, int column) {
    ASTNode* node = ast_create_node(AST_ENTITY_DECL, line, column);
    node->data.entity_decl.name = str_dup(name);
    node->data.entity_decl.fields = fields;
    return node;
}

ASTNode* ast_create_parameter(char* name, TypeInfo* type_info, int line, int column) {
    ASTNode* node = ast_create_node(AST_PARAMETER, line, column);
    node->data.parameter.name = str_dup(name);
    node->data.parameter.type_info = type_info;
    return node;
}

ASTNode* ast_create_block(ASTNodeList* statements, int line, int column) {
    ASTNode* node = ast_create_node(AST_BLOCK, line, column);
    node->data.block.statements = statements;
    return node;
}

ASTNode* ast_create_if_stmt(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch, int line, int column) {
    ASTNode* node = ast_create_node(AST_IF_STMT, line, column);
    node->data.if_stmt.condition = condition;
    node->data.if_stmt.then_branch = then_branch;
    node->data.if_stmt.else_branch = else_branch;
    return node;
}

ASTNode* ast_create_for_stmt(char* iterator, ASTNode* iterable, ASTNode* body, int line, int column) {
    ASTNode* node = ast_create_node(AST_FOR_STMT, line, column);
    node->data.for_stmt.iterator = str_dup(iterator);
    node->data.for_stmt.iterable = iterable;
    node->data.for_stmt.body = body;
    return node;
}

ASTNode* ast_create_return_stmt(ASTNode* value, int line, int column) {
    ASTNode* node = ast_create_node(AST_RETURN_STMT, line, column);
    node->data.return_stmt.value = value;
    return node;
}

ASTNode* ast_create_try_catch(ASTNode* try_block, char* error_type, char* error_name, ASTNode* catch_block, int line, int column) {
    ASTNode* node = ast_create_node(AST_TRY_CATCH_STMT, line, column);
    node->data.try_catch.try_block = try_block;
    node->data.try_catch.error_type = str_dup(error_type);
    node->data.try_catch.error_name = str_dup(error_name);
    node->data.try_catch.catch_block = catch_block;
    return node;
}

ASTNode* ast_create_use_stmt(char* module_path, int line, int column) {
    ASTNode* node = ast_create_node(AST_USE_STMT, line, column);
    node->data.use_stmt.module_path = str_dup(module_path);
    return node;
}

ASTNode* ast_create_spawn_stmt(ASTNode* body, int line, int column) {
    ASTNode* node = ast_create_node(AST_SPAWN_STMT, line, column);
    node->data.spawn_stmt.body = body;
    return node;
}

ASTNode* ast_create_expr_stmt(ASTNode* expression, int line, int column) {
    ASTNode* node = ast_create_node(AST_EXPR_STMT, line, column);
    node->data.expr_stmt.expression = expression;
    return node;
}

ASTNode* ast_create_binary(char* operator, ASTNode* left, ASTNode* right, int line, int column) {
    ASTNode* node = ast_create_node(AST_BINARY_EXPR, line, column);
    node->data.binary.operator = str_dup(operator);
    node->data.binary.left = left;
    node->data.binary.right = right;
    return node;
}

ASTNode* ast_create_unary(char* operator, ASTNode* operand, int line, int column) {
    ASTNode* node = ast_create_node(AST_UNARY_EXPR, line, column);
    node->data.unary.operator = str_dup(operator);
    node->data.unary.operand = operand;
    return node;
}

ASTNode* ast_create_call(ASTNode* callee, ASTNodeList* arguments, int line, int column) {
    ASTNode* node = ast_create_node(AST_CALL_EXPR, line, column);
    node->data.call.callee = callee;
    node->data.call.arguments = arguments;
    return node;
}

ASTNode* ast_create_member(ASTNode* object, char* property, int line, int column) {
    ASTNode* node = ast_create_node(AST_MEMBER_EXPR, line, column);
    node->data.member.object = object;
    node->data.member.property = str_dup(property);
    return node;
}

ASTNode* ast_create_index(ASTNode* array, ASTNode* index, int line, int column) {
    ASTNode* node = ast_create_node(AST_INDEX_EXPR, line, column);
    node->data.index.array = array;
    node->data.index.index = index;
    return node;
}

ASTNode* ast_create_identifier(char* name, int line, int column) {
    ASTNode* node = ast_create_node(AST_IDENTIFIER, line, column);
    node->data.identifier.name = str_dup(name);
    return node;
}

ASTNode* ast_create_number(double value, int line, int column) {
    ASTNode* node = ast_create_node(AST_LITERAL_NUMBER, line, column);
    node->data.number.value = value;
    return node;
}

ASTNode* ast_create_string(char* value, int line, int column) {
    ASTNode* node = ast_create_node(AST_LITERAL_STRING, line, column);
    node->data.string.value = str_dup(value);
    return node;
}

ASTNode* ast_create_bool(bool value, int line, int column) {
    ASTNode* node = ast_create_node(AST_LITERAL_BOOL, line, column);
    node->data.boolean.value = value;
    return node;
}

ASTNode* ast_create_null(int line, int column) {
    return ast_create_node(AST_LITERAL_NULL, line, column);
}

ASTNode* ast_create_array(ASTNodeList* elements, int line, int column) {
    ASTNode* node = ast_create_node(AST_ARRAY_LITERAL, line, column);
    node->data.array.elements = elements;
    return node;
}

ASTNode* ast_create_object(ASTNodeList* pairs, int line, int column) {
    ASTNode* node = ast_create_node(AST_OBJECT_LITERAL, line, column);
    node->data.object.pairs = pairs;
    return node;
}

// List operations
ASTNodeList* ast_list_create(ASTNode* node) {
    ASTNodeList* list = malloc(sizeof(ASTNodeList));
    list->node = node;
    list->next = NULL;
    return list;
}

ASTNodeList* ast_list_append(ASTNodeList* list, ASTNode* node) {
    if (!list) return ast_list_create(node);
    
    ASTNodeList* current = list;
    while (current->next) {
        current = current->next;
    }
    current->next = ast_list_create(node);
    return list;
}

size_t ast_list_length(ASTNodeList* list) {
    size_t count = 0;
    while (list) {
        count++;
        list = list->next;
    }
    return count;
}

// Type operations
TypeInfo* type_create(TypeKind kind, bool is_optional, char* name) {
    TypeInfo* type = malloc(sizeof(TypeInfo));
    type->kind = kind;
    type->is_optional = is_optional;
    type->name = str_dup(name);
    return type;
}

TypeInfo* type_parse(const char* type_string) {
    if (!type_string) return type_create(TYPE_UNKNOWN, false, NULL);
    
    bool is_optional = false;
    char* type_str = str_dup(type_string);
    size_t len = strlen(type_str);
    
    if (len > 0 && type_str[len - 1] == '?') {
        is_optional = true;
        type_str[len - 1] = '\0';
    }
    
    TypeKind kind = TYPE_UNKNOWN;
    if (strcmp(type_str, "int") == 0) kind = TYPE_INT;
    else if (strcmp(type_str, "float") == 0) kind = TYPE_FLOAT;
    else if (strcmp(type_str, "string") == 0) kind = TYPE_STRING;
    else if (strcmp(type_str, "bool") == 0) kind = TYPE_BOOL;
    else if (strcmp(type_str, "null") == 0) kind = TYPE_NULL;
    
    TypeInfo* type = type_create(kind, is_optional, type_str);
    free(type_str);
    return type;
}

// Memory management
void ast_free(ASTNode* node) {
    if (!node) return;
    
    switch (node->type) {
        case AST_PROGRAM:
            ast_list_free(node->data.program.statements);
            break;
        case AST_VARIABLE_DECL:
            free(node->data.var_decl.name);
            type_free(node->data.var_decl.type_info);
            ast_free(node->data.var_decl.initializer);
            break;
        case AST_FUNCTION_DECL:
            free(node->data.func_decl.name);
            ast_list_free(node->data.func_decl.parameters);
            type_free(node->data.func_decl.return_type);
            ast_free(node->data.func_decl.body);
            break;
        case AST_ENTITY_DECL:
            free(node->data.entity_decl.name);
            ast_list_free(node->data.entity_decl.fields);
            break;
        case AST_PARAMETER:
            free(node->data.parameter.name);
            type_free(node->data.parameter.type_info);
            break;
        case AST_BLOCK:
            ast_list_free(node->data.block.statements);
            break;
        case AST_IF_STMT:
            ast_free(node->data.if_stmt.condition);
            ast_free(node->data.if_stmt.then_branch);
            ast_free(node->data.if_stmt.else_branch);
            break;
        case AST_FOR_STMT:
            free(node->data.for_stmt.iterator);
            ast_free(node->data.for_stmt.iterable);
            ast_free(node->data.for_stmt.body);
            break;
        case AST_RETURN_STMT:
            ast_free(node->data.return_stmt.value);
            break;
        case AST_TRY_CATCH_STMT:
            ast_free(node->data.try_catch.try_block);
            free(node->data.try_catch.error_type);
            free(node->data.try_catch.error_name);
            ast_free(node->data.try_catch.catch_block);
            break;
        case AST_USE_STMT:
            free(node->data.use_stmt.module_path);
            break;
        case AST_SPAWN_STMT:
            ast_free(node->data.spawn_stmt.body);
            break;
        case AST_EXPR_STMT:
            ast_free(node->data.expr_stmt.expression);
            break;
        case AST_BINARY_EXPR:
            free(node->data.binary.operator);
            ast_free(node->data.binary.left);
            ast_free(node->data.binary.right);
            break;
        case AST_UNARY_EXPR:
            free(node->data.unary.operator);
            ast_free(node->data.unary.operand);
            break;
        case AST_CALL_EXPR:
            ast_free(node->data.call.callee);
            ast_list_free(node->data.call.arguments);
            break;
        case AST_MEMBER_EXPR:
            ast_free(node->data.member.object);
            free(node->data.member.property);
            break;
        case AST_INDEX_EXPR:
            ast_free(node->data.index.array);
            ast_free(node->data.index.index);
            break;
        case AST_IDENTIFIER:
            free(node->data.identifier.name);
            break;
        case AST_LITERAL_STRING:
            free(node->data.string.value);
            break;
        case AST_ARRAY_LITERAL:
            ast_list_free(node->data.array.elements);
            break;
        case AST_OBJECT_LITERAL:
            ast_list_free(node->data.object.pairs);
            break;
        default:
            break;
    }
    
    free(node);
}

void ast_list_free(ASTNodeList* list) {
    while (list) {
        ASTNodeList* next = list->next;
        ast_free(list->node);
        free(list);
        list = next;
    }
}

void type_free(TypeInfo* type) {
    if (!type) return;
    free(type->name);
    free(type);
}

// Debugging
const char* ast_type_to_string(ASTNodeType type) {
    switch (type) {
        case AST_PROGRAM: return "PROGRAM";
        case AST_VARIABLE_DECL: return "VARIABLE_DECL";
        case AST_FUNCTION_DECL: return "FUNCTION_DECL";
        case AST_ENTITY_DECL: return "ENTITY_DECL";
        case AST_PARAMETER: return "PARAMETER";
        case AST_BLOCK: return "BLOCK";
        case AST_IF_STMT: return "IF_STMT";
        case AST_FOR_STMT: return "FOR_STMT";
        case AST_RETURN_STMT: return "RETURN_STMT";
        case AST_TRY_CATCH_STMT: return "TRY_CATCH_STMT";
        case AST_EXPR_STMT: return "EXPR_STMT";
        case AST_USE_STMT: return "USE_STMT";
        case AST_SPAWN_STMT: return "SPAWN_STMT";
        case AST_BINARY_EXPR: return "BINARY_EXPR";
        case AST_UNARY_EXPR: return "UNARY_EXPR";
        case AST_CALL_EXPR: return "CALL_EXPR";
        case AST_MEMBER_EXPR: return "MEMBER_EXPR";
        case AST_INDEX_EXPR: return "INDEX_EXPR";
        case AST_IDENTIFIER: return "IDENTIFIER";
        case AST_LITERAL_NUMBER: return "LITERAL_NUMBER";
        case AST_LITERAL_STRING: return "LITERAL_STRING";
        case AST_LITERAL_BOOL: return "LITERAL_BOOL";
        case AST_LITERAL_NULL: return "LITERAL_NULL";
        case AST_ARRAY_LITERAL: return "ARRAY_LITERAL";
        case AST_OBJECT_LITERAL: return "OBJECT_LITERAL";
        default: return "UNKNOWN";
    }
}

void ast_print(ASTNode* node, int indent) {
    if (!node) return;
    
    for (int i = 0; i < indent; i++) printf("  ");
    printf("%s", ast_type_to_string(node->type));
    
    switch (node->type) {
        case AST_IDENTIFIER:
            printf(" (%s)", node->data.identifier.name);
            break;
        case AST_LITERAL_NUMBER:
            printf(" (%g)", node->data.number.value);
            break;
        case AST_LITERAL_STRING:
            printf(" (\"%s\")", node->data.string.value);
            break;
        case AST_LITERAL_BOOL:
            printf(" (%s)", node->data.boolean.value ? "true" : "false");
            break;
        case AST_VARIABLE_DECL:
            printf(" (%s)", node->data.var_decl.name);
            break;
        case AST_FUNCTION_DECL:
            printf(" (%s)", node->data.func_decl.name);
            break;
        default:
            break;
    }
    
    printf("\n");
}

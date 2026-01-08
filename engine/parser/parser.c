#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declarations
static ASTNode* parse_statement(Parser* parser);
static ASTNode* parse_expression(Parser* parser);
static ASTNode* parse_declaration(Parser* parser);

// Error handling
static void error_at(Parser* parser, Token* token, const char* message) {
    if (parser->panic_mode) return;
    parser->panic_mode = true;
    parser->had_error = true;
    
    snprintf(parser->error_message, sizeof(parser->error_message),
             "[line %d, col %d] Error at '%.*s': %s",
             token->line, token->column, (int)token->length, token->start, message);
}

static void error(Parser* parser, const char* message) {
    error_at(parser, &parser->previous, message);
}

static void error_at_current(Parser* parser, const char* message) {
    error_at(parser, &parser->current, message);
}

// Token management
static void advance(Parser* parser) {
    parser->previous = parser->current;
    
    for (;;) {
        parser->current = lexer_next_token(parser->lexer);
        if (parser->current.type != TOKEN_ERROR) break;
        
        error_at_current(parser, parser->current.start);
    }
}

static bool check(Parser* parser, TokenType type) {
    return parser->current.type == type;
}

static bool match(Parser* parser, TokenType type) {
    if (!check(parser, type)) return false;
    advance(parser);
    return true;
}

static void consume(Parser* parser, TokenType type, const char* message) {
    if (parser->current.type == type) {
        advance(parser);
        return;
    }
    error_at_current(parser, message);
}

static char* token_to_string(Token* token) {
    char* str = malloc(token->length + 1);
    memcpy(str, token->start, token->length);
    str[token->length] = '\0';
    return str;
}

// Parsing functions
static ASTNode* parse_primary(Parser* parser) {
    if (match(parser, TOKEN_TRUE)) {
        return ast_create_bool(true, parser->previous.line, parser->previous.column);
    }
    
    if (match(parser, TOKEN_FALSE)) {
        return ast_create_bool(false, parser->previous.line, parser->previous.column);
    }
    
    if (match(parser, TOKEN_NUMBER)) {
        char* str = token_to_string(&parser->previous);
        double value = atof(str);
        free(str);
        return ast_create_number(value, parser->previous.line, parser->previous.column);
    }
    
    if (match(parser, TOKEN_STRING)) {
        char* str = token_to_string(&parser->previous);
        // Remove quotes
        str[strlen(str) - 1] = '\0';
        ASTNode* node = ast_create_string(str + 1, parser->previous.line, parser->previous.column);
        free(str);
        return node;
    }
    
    if (match(parser, TOKEN_IDENTIFIER)) {
        char* name = token_to_string(&parser->previous);
        ASTNode* node = ast_create_identifier(name, parser->previous.line, parser->previous.column);
        free(name);
        return node;
    }
    
    if (match(parser, TOKEN_LPAREN)) {
        ASTNode* expr = parse_expression(parser);
        consume(parser, TOKEN_RPAREN, "Expected ')' after expression");
        return expr;
    }
    
    if (match(parser, TOKEN_LBRACKET)) {
        ASTNodeList* elements = NULL;
        if (!check(parser, TOKEN_RBRACKET)) {
            do {
                ASTNode* elem = parse_expression(parser);
                elements = ast_list_append(elements, elem);
            } while (match(parser, TOKEN_COMMA));
        }
        consume(parser, TOKEN_RBRACKET, "Expected ']' after array elements");
        return ast_create_array(elements, parser->previous.line, parser->previous.column);
    }
    
    error(parser, "Expected expression");
    return NULL;
}

static ASTNode* parse_call(Parser* parser) {
    ASTNode* expr = parse_primary(parser);
    
    while (true) {
        if (match(parser, TOKEN_LPAREN)) {
            ASTNodeList* arguments = NULL;
            if (!check(parser, TOKEN_RPAREN)) {
                do {
                    ASTNode* arg = parse_expression(parser);
                    arguments = ast_list_append(arguments, arg);
                } while (match(parser, TOKEN_COMMA));
            }
            consume(parser, TOKEN_RPAREN, "Expected ')' after arguments");
            expr = ast_create_call(expr, arguments, parser->previous.line, parser->previous.column);
        } else if (match(parser, TOKEN_DOT)) {
            consume(parser, TOKEN_IDENTIFIER, "Expected property name after '.'");
            char* property = token_to_string(&parser->previous);
            expr = ast_create_member(expr, property, parser->previous.line, parser->previous.column);
            free(property);
        } else if (match(parser, TOKEN_LBRACKET)) {
            ASTNode* index = parse_expression(parser);
            consume(parser, TOKEN_RBRACKET, "Expected ']' after index");
            expr = ast_create_index(expr, index, parser->previous.line, parser->previous.column);
        } else {
            break;
        }
    }
    
    return expr;
}

static ASTNode* parse_unary(Parser* parser) {
    if (match(parser, TOKEN_NOT) || match(parser, TOKEN_MINUS)) {
        char* op = token_to_string(&parser->previous);
        int line = parser->previous.line;
        int column = parser->previous.column;
        ASTNode* operand = parse_unary(parser);
        ASTNode* node = ast_create_unary(op, operand, line, column);
        free(op);
        return node;
    }
    
    return parse_call(parser);
}

static ASTNode* parse_factor(Parser* parser) {
    ASTNode* expr = parse_unary(parser);
    
    while (match(parser, TOKEN_STAR) || match(parser, TOKEN_SLASH) || match(parser, TOKEN_PERCENT)) {
        char* op = token_to_string(&parser->previous);
        int line = parser->previous.line;
        int column = parser->previous.column;
        ASTNode* right = parse_unary(parser);
        expr = ast_create_binary(op, expr, right, line, column);
        free(op);
    }
    
    return expr;
}

static ASTNode* parse_term(Parser* parser) {
    ASTNode* expr = parse_factor(parser);
    
    while (match(parser, TOKEN_PLUS) || match(parser, TOKEN_MINUS)) {
        char* op = token_to_string(&parser->previous);
        int line = parser->previous.line;
        int column = parser->previous.column;
        ASTNode* right = parse_factor(parser);
        expr = ast_create_binary(op, expr, right, line, column);
        free(op);
    }
    
    return expr;
}

static ASTNode* parse_comparison(Parser* parser) {
    ASTNode* expr = parse_term(parser);
    
    while (match(parser, TOKEN_GREATER) || match(parser, TOKEN_GREATER_EQUAL) ||
           match(parser, TOKEN_LESS) || match(parser, TOKEN_LESS_EQUAL)) {
        char* op = token_to_string(&parser->previous);
        int line = parser->previous.line;
        int column = parser->previous.column;
        ASTNode* right = parse_term(parser);
        expr = ast_create_binary(op, expr, right, line, column);
        free(op);
    }
    
    return expr;
}

static ASTNode* parse_equality(Parser* parser) {
    ASTNode* expr = parse_comparison(parser);
    
    while (match(parser, TOKEN_EQUAL) || match(parser, TOKEN_NOT_EQUAL)) {
        char* op = token_to_string(&parser->previous);
        int line = parser->previous.line;
        int column = parser->previous.column;
        ASTNode* right = parse_comparison(parser);
        expr = ast_create_binary(op, expr, right, line, column);
        free(op);
    }
    
    return expr;
}

static ASTNode* parse_logical_and(Parser* parser) {
    ASTNode* expr = parse_equality(parser);
    
    while (match(parser, TOKEN_AND)) {
        char* op = token_to_string(&parser->previous);
        int line = parser->previous.line;
        int column = parser->previous.column;
        ASTNode* right = parse_equality(parser);
        expr = ast_create_binary(op, expr, right, line, column);
        free(op);
    }
    
    return expr;
}

static ASTNode* parse_logical_or(Parser* parser) {
    ASTNode* expr = parse_logical_and(parser);
    
    while (match(parser, TOKEN_OR)) {
        char* op = token_to_string(&parser->previous);
        int line = parser->previous.line;
        int column = parser->previous.column;
        ASTNode* right = parse_logical_and(parser);
        expr = ast_create_binary(op, expr, right, line, column);
        free(op);
    }
    
    return expr;
}

static ASTNode* parse_expression(Parser* parser) {
    return parse_logical_or(parser);
}

static ASTNode* parse_block(Parser* parser) {
    int line = parser->previous.line;
    int column = parser->previous.column;
    ASTNodeList* statements = NULL;
    
    while (!check(parser, TOKEN_RBRACE) && !check(parser, TOKEN_EOF)) {
        ASTNode* stmt = parse_declaration(parser);
        if (stmt) {
            statements = ast_list_append(statements, stmt);
        }
    }
    
    consume(parser, TOKEN_RBRACE, "Expected '}' after block");
    return ast_create_block(statements, line, column);
}

static ASTNode* parse_if_statement(Parser* parser) {
    int line = parser->previous.line;
    int column = parser->previous.column;
    
    ASTNode* condition = parse_expression(parser);
    consume(parser, TOKEN_LBRACE, "Expected '{' after if condition");
    ASTNode* then_branch = parse_block(parser);
    
    ASTNode* else_branch = NULL;
    if (match(parser, TOKEN_ELSE)) {
        consume(parser, TOKEN_LBRACE, "Expected '{' after else");
        else_branch = parse_block(parser);
    }
    
    return ast_create_if_stmt(condition, then_branch, else_branch, line, column);
}

static ASTNode* parse_for_statement(Parser* parser) {
    int line = parser->previous.line;
    int column = parser->previous.column;
    
    consume(parser, TOKEN_IDENTIFIER, "Expected iterator variable name");
    char* iterator = token_to_string(&parser->previous);
    
    consume(parser, TOKEN_IN, "Expected 'in' after iterator");
    ASTNode* iterable = parse_expression(parser);
    
    consume(parser, TOKEN_LBRACE, "Expected '{' after for clause");
    ASTNode* body = parse_block(parser);
    
    ASTNode* node = ast_create_for_stmt(iterator, iterable, body, line, column);
    free(iterator);
    return node;
}

static ASTNode* parse_return_statement(Parser* parser) {
    int line = parser->previous.line;
    int column = parser->previous.column;
    
    ASTNode* value = NULL;
    if (!check(parser, TOKEN_RBRACE) && !check(parser, TOKEN_EOF)) {
        value = parse_expression(parser);
    }
    
    return ast_create_return_stmt(value, line, column);
}

static ASTNode* parse_try_catch(Parser* parser) {
    int line = parser->previous.line;
    int column = parser->previous.column;
    
    consume(parser, TOKEN_LBRACE, "Expected '{' after try");
    ASTNode* try_block = parse_block(parser);
    
    consume(parser, TOKEN_CATCH, "Expected 'catch' after try block");
    
    consume(parser, TOKEN_IDENTIFIER, "Expected error type");
    char* error_type = token_to_string(&parser->previous);
    
    consume(parser, TOKEN_AS, "Expected 'as' after error type");
    
    consume(parser, TOKEN_IDENTIFIER, "Expected error variable name");
    char* error_name = token_to_string(&parser->previous);
    
    consume(parser, TOKEN_LBRACE, "Expected '{' after catch clause");
    ASTNode* catch_block = parse_block(parser);
    
    ASTNode* node = ast_create_try_catch(try_block, error_type, error_name, catch_block, line, column);
    free(error_type);
    free(error_name);
    return node;
}

static ASTNode* parse_use_statement(Parser* parser) {
    int line = parser->previous.line;
    int column = parser->previous.column;
    
    consume(parser, TOKEN_IDENTIFIER, "Expected module name");
    char* module_path = token_to_string(&parser->previous);
    
    // Handle dotted paths like http.server
    while (match(parser, TOKEN_DOT)) {
        consume(parser, TOKEN_IDENTIFIER, "Expected module component after '.'");
        char* component = token_to_string(&parser->previous);
        char* new_path = malloc(strlen(module_path) + strlen(component) + 2);
        sprintf(new_path, "%s.%s", module_path, component);
        free(module_path);
        free(component);
        module_path = new_path;
    }
    
    ASTNode* node = ast_create_use_stmt(module_path, line, column);
    free(module_path);
    return node;
}

static ASTNode* parse_spawn_statement(Parser* parser) {
    int line = parser->previous.line;
    int column = parser->previous.column;
    
    consume(parser, TOKEN_LBRACE, "Expected '{' after spawn");
    ASTNode* body = parse_block(parser);
    
    return ast_create_spawn_stmt(body, line, column);
}

static ASTNode* parse_statement(Parser* parser) {
    if (match(parser, TOKEN_IF)) return parse_if_statement(parser);
    if (match(parser, TOKEN_FOR)) return parse_for_statement(parser);
    if (match(parser, TOKEN_RETURN)) return parse_return_statement(parser);
    if (match(parser, TOKEN_TRY)) return parse_try_catch(parser);
    if (match(parser, TOKEN_USE)) return parse_use_statement(parser);
    if (match(parser, TOKEN_SPAWN)) return parse_spawn_statement(parser);
    
    // Expression statement
    ASTNode* expr = parse_expression(parser);
    return ast_create_expr_stmt(expr, expr->line, expr->column);
}

static TypeInfo* parse_type_annotation(Parser* parser) {
    if (!match(parser, TOKEN_COLON)) return NULL;
    
    consume(parser, TOKEN_IDENTIFIER, "Expected type name");
    char* type_str = token_to_string(&parser->previous);
    
    bool is_optional = match(parser, TOKEN_QUESTION);
    
    TypeInfo* type = type_parse(type_str);
    type->is_optional = is_optional;
    free(type_str);
    return type;
}

static ASTNode* parse_var_declaration(Parser* parser) {
    int line = parser->previous.line;
    int column = parser->previous.column;
    
    consume(parser, TOKEN_IDENTIFIER, "Expected variable name");
    char* name = token_to_string(&parser->previous);
    
    TypeInfo* type_info = parse_type_annotation(parser);
    
    ASTNode* initializer = NULL;
    if (match(parser, TOKEN_ASSIGN)) {
        initializer = parse_expression(parser);
    }
    
    ASTNode* node = ast_create_var_decl(name, type_info, initializer, line, column);
    free(name);
    return node;
}

static ASTNode* parse_function_declaration(Parser* parser) {
    int line = parser->previous.line;
    int column = parser->previous.column;
    
    consume(parser, TOKEN_IDENTIFIER, "Expected function name");
    char* name = token_to_string(&parser->previous);
    
    consume(parser, TOKEN_LPAREN, "Expected '(' after function name");
    
    ASTNodeList* parameters = NULL;
    if (!check(parser, TOKEN_RPAREN)) {
        do {
            consume(parser, TOKEN_IDENTIFIER, "Expected parameter name");
            char* param_name = token_to_string(&parser->previous);
            TypeInfo* param_type = parse_type_annotation(parser);
            ASTNode* param = ast_create_parameter(param_name, param_type, parser->previous.line, parser->previous.column);
            parameters = ast_list_append(parameters, param);
            free(param_name);
        } while (match(parser, TOKEN_COMMA));
    }
    
    consume(parser, TOKEN_RPAREN, "Expected ')' after parameters");
    
    TypeInfo* return_type = parse_type_annotation(parser);
    
    bool is_arrow = false;
    ASTNode* body = NULL;
    
    if (match(parser, TOKEN_ARROW)) {
        is_arrow = true;
        body = parse_expression(parser);
    } else {
        consume(parser, TOKEN_LBRACE, "Expected '{' or '=>' after function signature");
        body = parse_block(parser);
    }
    
    ASTNode* node = ast_create_func_decl(name, parameters, return_type, body, is_arrow, line, column);
    free(name);
    return node;
}

static ASTNode* parse_entity_declaration(Parser* parser) {
    int line = parser->previous.line;
    int column = parser->previous.column;
    
    consume(parser, TOKEN_IDENTIFIER, "Expected entity name");
    char* name = token_to_string(&parser->previous);
    
    consume(parser, TOKEN_LBRACE, "Expected '{' after entity name");
    
    ASTNodeList* fields = NULL;
    while (!check(parser, TOKEN_RBRACE) && !check(parser, TOKEN_EOF)) {
        consume(parser, TOKEN_IDENTIFIER, "Expected field name");
        char* field_name = token_to_string(&parser->previous);
        
        TypeInfo* field_type = parse_type_annotation(parser);
        
        ASTNode* default_value = NULL;
        if (match(parser, TOKEN_ASSIGN)) {
            default_value = parse_expression(parser);
        }
        
        ASTNode* field = ast_create_var_decl(field_name, field_type, default_value, parser->previous.line, parser->previous.column);
        fields = ast_list_append(fields, field);
        free(field_name);
    }
    
    consume(parser, TOKEN_RBRACE, "Expected '}' after entity fields");
    
    ASTNode* node = ast_create_entity_decl(name, fields, line, column);
    free(name);
    return node;
}

static ASTNode* parse_declaration(Parser* parser) {
    if (match(parser, TOKEN_LET)) return parse_var_declaration(parser);
    if (match(parser, TOKEN_FN)) return parse_function_declaration(parser);
    if (match(parser, TOKEN_ENTITY)) return parse_entity_declaration(parser);
    
    return parse_statement(parser);
}

// Public API
void parser_init(Parser* parser, Lexer* lexer) {
    parser->lexer = lexer;
    parser->had_error = false;
    parser->panic_mode = false;
    parser->error_message[0] = '\0';
    advance(parser);
}

ASTNode* parser_parse(Parser* parser) {
    ASTNodeList* statements = NULL;
    
    while (!match(parser, TOKEN_EOF)) {
        ASTNode* decl = parse_declaration(parser);
        if (decl) {
            statements = ast_list_append(statements, decl);
        }
        
        if (parser->panic_mode) {
            // Synchronize on statement boundaries
            while (parser->current.type != TOKEN_EOF) {
                if (parser->previous.type == TOKEN_RBRACE) break;
                
                switch (parser->current.type) {
                    case TOKEN_LET:
                    case TOKEN_FN:
                    case TOKEN_ENTITY:
                    case TOKEN_IF:
                    case TOKEN_FOR:
                    case TOKEN_RETURN:
                    case TOKEN_TRY:
                    case TOKEN_USE:
                        parser->panic_mode = false;
                        return ast_create_program(statements);
                    default:
                        advance(parser);
                }
            }
        }
    }
    
    return ast_create_program(statements);
}

void parser_print_errors(Parser* parser) {
    if (parser->had_error) {
        fprintf(stderr, "%s\n", parser->error_message);
    }
}

bool parser_had_error(Parser* parser) {
    return parser->had_error;
}

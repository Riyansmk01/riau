#ifndef ERROR_REPORTER_H
#define ERROR_REPORTER_H

#include <stdbool.h>
#include <stddef.h>

// ANSI color codes for terminal output
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_BOLD "\033[1m"

// Error severity levels
typedef enum {
  ERROR_LEVEL_ERROR,
  ERROR_LEVEL_WARNING,
  ERROR_LEVEL_HINT
} ErrorLevel;

// Error context structure
typedef struct {
  const char *filename;
  const char *source_code;
  int line;
  int column;
  int length;
  ErrorLevel level;
  const char *message;
  const char *suggestion;
  const char *hint;
} ErrorContext;

// Initialize error reporter
void error_reporter_init(bool use_colors);

// Report error with full context
void error_report(ErrorContext *ctx);

// Report error with code snippet
void error_report_with_snippet(const char *filename, const char *source_code,
                               int line, int column, int length,
                               const char *message);

// Find similar names using Levenshtein distance
char *suggest_similar_name(const char *target, const char **candidates,
                           int count);

// Get helpful hint for common errors
const char *get_helpful_hint(const char *error_type);

// Calculate Levenshtein distance between two strings
int levenshtein_distance(const char *s1, const char *s2);

// Format error message with colors
void print_colored(const char *color, const char *format, ...);

// Get line from source code
char *get_source_line(const char *source, int line_number);

// Show code context with error pointer
void show_code_context(const char *source, int line, int column, int length,
                       const char *message);

#endif // ERROR_REPORTER_H

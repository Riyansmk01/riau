#include "error_reporter.h"
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool use_terminal_colors = true;

void error_reporter_init(bool use_colors) { use_terminal_colors = use_colors; }

// Calculate Levenshtein distance for "Did you mean?" suggestions
int levenshtein_distance(const char *s1, const char *s2) {
  int len1 = strlen(s1);
  int len2 = strlen(s2);

  // Create distance matrix
  int **matrix = malloc((len1 + 1) * sizeof(int *));
  for (int i = 0; i <= len1; i++) {
    matrix[i] = malloc((len2 + 1) * sizeof(int));
  }

  // Initialize first row and column
  for (int i = 0; i <= len1; i++)
    matrix[i][0] = i;
  for (int j = 0; j <= len2; j++)
    matrix[0][j] = j;

  // Calculate distances
  for (int i = 1; i <= len1; i++) {
    for (int j = 1; j <= len2; j++) {
      int cost = (tolower(s1[i - 1]) == tolower(s2[j - 1])) ? 0 : 1;

      int deletion = matrix[i - 1][j] + 1;
      int insertion = matrix[i][j - 1] + 1;
      int substitution = matrix[i - 1][j - 1] + cost;

      matrix[i][j] = deletion < insertion ? deletion : insertion;
      matrix[i][j] = matrix[i][j] < substitution ? matrix[i][j] : substitution;
    }
  }

  int distance = matrix[len1][len2];

  // Free matrix
  for (int i = 0; i <= len1; i++) {
    free(matrix[i]);
  }
  free(matrix);

  return distance;
}

// Find most similar name from candidates
char *suggest_similar_name(const char *target, const char **candidates,
                           int count) {
  if (count == 0)
    return NULL;

  int min_distance = 999;
  const char *best_match = NULL;

  for (int i = 0; i < count; i++) {
    int distance = levenshtein_distance(target, candidates[i]);

    // Only suggest if distance is small (likely typo)
    if (distance < min_distance && distance <= 3) {
      min_distance = distance;
      best_match = candidates[i];
    }
  }

  if (best_match) {
    return strdup(best_match);
  }

  return NULL;
}

// Get helpful hint for common error types
const char *get_helpful_hint(const char *error_type) {
  if (strstr(error_type, "undefined variable")) {
    return "Make sure the variable is declared before use with 'let'";
  } else if (strstr(error_type, "undefined function")) {
    return "Check if the function is defined or imported";
  } else if (strstr(error_type, "type mismatch")) {
    return "Ensure the types match or add explicit type conversion";
  } else if (strstr(error_type, "null")) {
    return "Use null safety operator '?' or check for null before accessing";
  } else if (strstr(error_type, "syntax")) {
    return "Check for missing semicolons, brackets, or parentheses";
  } else if (strstr(error_type, "already defined")) {
    return "Variable names must be unique within the same scope";
  }

  return NULL;
}

// Print with color support
void print_colored(const char *color, const char *format, ...) {
  va_list args;
  va_start(args, format);

  if (use_terminal_colors) {
    printf("%s", color);
  }

  vprintf(format, args);

  if (use_terminal_colors) {
    printf("%s", COLOR_RESET);
  }

  va_end(args);
}

// Get specific line from source code
char *get_source_line(const char *source, int line_number) {
  if (!source)
    return NULL;

  int current_line = 1;
  const char *line_start = source;
  const char *line_end = source;

  // Find the target line
  while (*line_end && current_line < line_number) {
    if (*line_end == '\n') {
      current_line++;
      line_start = line_end + 1;
    }
    line_end++;
  }

  if (current_line != line_number) {
    return NULL;
  }

  // Find end of line
  while (*line_end && *line_end != '\n' && *line_end != '\r') {
    line_end++;
  }

  // Copy line
  size_t length = line_end - line_start;
  char *line = malloc(length + 1);
  memcpy(line, line_start, length);
  line[length] = '\0';

  return line;
}

// Show code context with error pointer
void show_code_context(const char *source, int line, int column, int length,
                       const char *message) {
  char *source_line = get_source_line(source, line);
  if (!source_line)
    return;

  // Print line number and source code
  print_colored(COLOR_CYAN, "  %4d | ", line);
  printf("%s\n", source_line);

  // Print error pointer
  print_colored(COLOR_CYAN, "       | ");

  // Add spacing before pointer
  for (int i = 0; i < column - 1; i++) {
    printf(" ");
  }

  // Print pointer
  print_colored(COLOR_RED, "^");
  for (int i = 1; i < length; i++) {
    print_colored(COLOR_RED, "~");
  }
  printf("\n");

  free(source_line);
}

// Main error reporting function
void error_report_with_snippet(const char *filename, const char *source_code,
                               int line, int column, int length,
                               const char *message) {
  // Print error header
  print_colored(COLOR_RED, "Error");
  printf(" at ");
  print_colored(COLOR_BOLD, "%s:%d:%d\n", filename ? filename : "<input>", line,
                column);

  // Show code context
  if (source_code) {
    show_code_context(source_code, line, column, length, message);
  }

  // Print error message
  print_colored(COLOR_RED, "%s\n", message);
}

// Full error report with all context
void error_report(ErrorContext *ctx) {
  if (!ctx)
    return;

  const char *level_color = COLOR_RED;
  const char *level_name = "Error";

  switch (ctx->level) {
  case ERROR_LEVEL_WARNING:
    level_color = COLOR_YELLOW;
    level_name = "Warning";
    break;
  case ERROR_LEVEL_HINT:
    level_color = COLOR_GREEN;
    level_name = "Hint";
    break;
  default:
    break;
  }

  // Print header
  print_colored(level_color, "%s", level_name);
  printf(" at ");
  print_colored(COLOR_BOLD, "%s:%d:%d\n",
                ctx->filename ? ctx->filename : "<input>", ctx->line,
                ctx->column);

  // Show code context
  if (ctx->source_code) {
    show_code_context(ctx->source_code, ctx->line, ctx->column,
                      ctx->length > 0 ? ctx->length : 1, ctx->message);
  }

  // Print main message
  print_colored(level_color, "%s\n", ctx->message);

  // Print suggestion if available
  if (ctx->suggestion) {
    printf("\n");
    print_colored(COLOR_CYAN, "💡 Did you mean ");
    print_colored(COLOR_GREEN, "'%s'", ctx->suggestion);
    print_colored(COLOR_CYAN, "?\n");
  }

  // Print hint if available
  if (ctx->hint) {
    printf("\n");
    print_colored(COLOR_YELLOW, "Hint: ");
    printf("%s\n", ctx->hint);
  }

  printf("\n");
}

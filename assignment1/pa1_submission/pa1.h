#ifndef HEADER_FILE_H
#define HEADER_FILE_H

#define BUFFER_SIZE 1000

#include <stdbool.h>

void sanitize(char *s);
bool is_singleton(char *s);
bool is_arithmetic(char *s);
bool is_reverse_arithmetic(char *s);
bool is_balanced_tripartite(char *s);
bool is_balanced_bipartite(char *s);
bool is_palindrome(char *s);

#endif

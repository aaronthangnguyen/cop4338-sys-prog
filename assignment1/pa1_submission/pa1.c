#include "pa1.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Removes the trailing newline character from a string, if present.
void sanitize(char *s)
{
    size_t length = strlen(s);
    if (length > 0 && s[length - 1] == '\n')
        s[length - 1] = '\0';
}

// Checks if the given string is a singleton (all characters are the same).
bool is_singleton(char *s)
{
    for (int i = 0; s[i] != '\0'; i++)
        if (i > 0 && s[i] != s[i - 1])
            return false;
    return true;
}

// Checks if the given string forms an arithmetic sequence (consecutive characters have a difference of 1).
bool is_arithmetic(char *s)
{
    for (int i = 0; s[i] != '\0'; i++)
        if (i > 0 && s[i] - s[i - 1] != 1)
            return false;
    return true;
}

// Checks if the given string forms a reverse arithmetic sequence (consecutive characters have a difference of -1).
bool is_reverse_arithmetic(char *s)
{
    for (int i = 0; s[i] != '\0'; i++)
        if (i > 0 && s[i] - s[i - 1] != -1)
            return false;
    return true;
}

// Checks if the given string is balanced in a tripartite pattern.
bool is_balanced_tripartite(char *s)
{
    size_t length = strlen(s);
    if (length % 3 != 0)
        return false;
    for (int i = 0; i < length / 3; i++)
        if (s[i] != s[length / 3 + i] && s[i] != s[2 * length / 3 + i])
            return false;
    return true;
}

// Checks if the given string is balanced in a bipartite pattern.
bool is_balanced_bipartite(char *s)
{
    size_t length = strlen(s);
    if (length % 2 != 0)
        return false;
    for (int i = 0; i < length / 2; i++)
        if (s[i] != s[length / 2 + i])
            return false;
    return true;
}

// Checks if the given string is a palindrome (reads the same forwards and backwards).
bool is_palindrome(char *s)
{
    size_t length = strlen(s);
    for (int i = 0; i < length / 2; i++)
        if (s[i] != s[length - i - 1])
            return false;
    return true;
}

int main()
{
    char buffer[BUFFER_SIZE];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        sanitize(buffer);

        if (is_singleton(buffer))
            printf("singleton\n");
        if (is_arithmetic(buffer))
            printf("arithmetic\n");
        if (is_reverse_arithmetic(buffer))
            printf("reverse arithmetic\n");
        if (is_balanced_tripartite(buffer))
            printf("balanced tripartite\n");
        if (is_balanced_bipartite(buffer))
            printf("balanced bipartite\n");
        if (is_palindrome(buffer))
            printf("palindrome\n");

        printf("\n");
    }

    return 0;
}

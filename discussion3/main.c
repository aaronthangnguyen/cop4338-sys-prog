#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *helper(char *str, int left, int right)
{
    int len = right - left + 1;
    if (len == 0) // base case #1: return empty string if nothing to sort
        return "";
    if (len == 1)
    {                                 // base case #2: return string with 1 character
        char *rv = (char *)malloc(2); // malloc(2) to preserve for '\0' null terminator
        strncpy(rv, str + left, 1);   // copy 1 character to rv
        return rv;
    }
    // recursive step!
    char *first = helper(str, left, left + len / 2 - 1); // recurse left-half
    char *second = helper(str, left + len / 2, right);   // recurse right-half
    char *rv = (char *)malloc(len + 1);                  // create temp array
    strcpy(rv, second);                                  // copy second array to rv
    strcat(rv, first);                                   // concat first array to rv starting at '\0'
    // example:
    // 1. rv = "", second = "second", first = "first"
    // 2. rv = "second", first = "first"
    // 3. rv = "secondfirst"
    return rv;
}

char *unknown_operation(char *str)
{
    int len = strlen(str);
    return helper(str, 0, len - 1);
}
int main(void)
{
    char *out = unknown_operation("what does this function do?!!");
    printf("%s\n", out);
    return 0;
}
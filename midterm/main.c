#include <stdio.h>
int main() {
  char str[11] = "HelloWorld";
  printf("%d, %c", (*str > str[5]) * (int)str, *(str + 3) + 4);
  return 0;
}
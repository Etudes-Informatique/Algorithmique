#include <stdlib.h>
#include <stdio.h>

#define MAX_LENGTH 8

#define STR(s) #s
#define XSTR(s) STR(s)

int main(void) {
  char s[MAX_LENGTH + 1];
  int n = 0;
  while (scanf("%"XSTR(MAX_LENGTH)"s", s) == 1) {
    n++;
    printf("%d\t%s\n", n, s);
  }
  return EXIT_SUCCESS;
}

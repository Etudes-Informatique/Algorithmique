#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define STR(s) #s
#define XSTR(s) STR(s)

#define MAX_LENGTH 32

#define ADD "ADD"
#define MUL "MUL"
#define END "END"

int main(void) {
  char s[MAX_LENGTH + 1];
  long int n = 0;
  while (scanf("%"XSTR (MAX_LENGTH) "s", s) == 1) {
    ++n;
    char *end;
    errno = 0;
    long int x = strtol(s, &end, 10);
    if (*end == '\0') {
      if (errno != 0) {
        printf("%ld\t%s\tvalue out of range\n", n, s);
        return EXIT_FAILURE;
      }
      printf("%ld\t%s\toperand = %ld\n", n, s, x);
    } else {
      if (strcmp(s, ADD) != 0 && strcmp(s, MUL) != 0 && strcmp(s, END) != 0) {
        printf("%ld\t%s\trejected form\n", n, s);
        return EXIT_FAILURE;
      } else {
        printf("%ld\t%s\toperator\n", n, s);
      }
    }
  }
  return EXIT_SUCCESS;
}

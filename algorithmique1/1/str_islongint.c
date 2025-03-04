#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define MAX_LENGTH 32

#define STR(s) #s
#define XSTR(s) STR(s)

int main(void) {
  char s[MAX_LENGTH + 1];
  long int n = 0;
  while (scanf("%"XSTR (MAX_LENGTH) "s", s) == 1) {
    char *end;
    errno = 0;
    long int x = strtol(s, &end, 10);
    n++;
    if (*end == '\0') {
      if (errno != 0) {
        printf("%ld\t%s\tvalue out of range\n", n, s);
      } else {
        printf("%ld\t%s\tvalue = %ld\n", n, s, x);
      }
    } else {
      printf("%ld\t%s\tillegal value\n", n, s);
    }
  }
  return EXIT_SUCCESS;
}

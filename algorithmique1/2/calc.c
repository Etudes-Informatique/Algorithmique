#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define STR(s) #s
#define XSTR(s) STR(s)

#define MAX_LENGTH 32
#define SIZE_STACK 4

#define ADD "ADD"
#define MUL "MUL"
#define END "END"
#define SUB "SUB"
#define QUO "QUO"
#define REM "REM"

int main(void) {
  char s[MAX_LENGTH + 1];
  long int n = 0;
  long int p[SIZE_STACK];
  int h = 0;
  long int c;
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
      if (h == SIZE_STACK) {
        printf("Stack overflow\n");
        return EXIT_FAILURE;
      }
      p[h] = x;
      ++h;
    } else {
      if (strcmp(s, ADD) != 0 && strcmp(s, MUL) != 0
          && strcmp(s, END) != 0 && strcmp(s, SUB) != 0
          && strcmp(s, QUO) != 0 && strcmp(s, REM) != 0) {
        printf("%ld\t%s\trejected form\n", n, s);
        return EXIT_FAILURE;
      } else {
        if (strcmp(s, ADD) == 0) {
          if (h <= 1) {
            printf("Stack Underflow\n");
            return EXIT_FAILURE;
          }
          c = p[h - 2] + p[h - 1];
          --h;
          p[h - 1] = c;
        } else if (strcmp(s, MUL) == 0) {
          if (h <= 1) {
            printf("Stack Underflow\n");
            return EXIT_FAILURE;
          }
          c = p[h - 2] * p[h - 1];
          --h;
          p[h - 1] = c;
        } else if (strcmp(s, SUB) == 0) {
          if (h <= 1) {
            printf("Stack underflow\n");
            return EXIT_FAILURE;
          }
          // Soustraction du therme le moins profond au therme le plus profond
          c = p[h - 2] - p[h - 1];
          --h;
          p[h - 1] = c;
        } else if (strcmp(s, QUO) == 0) {
          if (h <= 1) {
            printf("Stack underflow\n");
            return EXIT_FAILURE;
          } else if (p[h - 1] == 0) {
            printf("Illegal Division\n");
            return EXIT_FAILURE;
          }
          // Division du therme le plus profond par le therme le moins profond
          c = p[h - 2] / p[h - 1];
          --h;
          p[h - 1] = c;
        } else if (strcmp(s, REM) == 0) {
          if (h <= 1) {
            printf("Stack underflow\n");
            return EXIT_FAILURE;
          } else if (p[h - 1] == 0) {
            printf("Illegal Division\n");
            return EXIT_FAILURE;
          }
          // Division du therme le plus profond par le therme le moins profond
          c = p[h - 2] % p[h - 1];
          --h;
          p[h - 1] = c;
        } else if (strcmp(s, END) == 0) {
          if (h != 1) {
            printf("Missplaced Operator\n");
            return EXIT_FAILURE;
          }
          printf("Result: %ld\n", p[h - 1]);
          --h;
        }
      }
    }
  }
  return EXIT_SUCCESS;
}

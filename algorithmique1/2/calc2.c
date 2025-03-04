#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void fail_if(int expr, const char *cause);


#define STR(s) #s
#define XSTR(s) STR(s)

#define MAX_LENGTH 32
#define SIZE_STACK 4

typedef struct stack {
  long int value[SIZE_STACK];
  int height;
} stack;

void stack_init(stack *s);
int stack_height(const stack * s);
void stack_push(stack * s, long int x);
long int stack_pop(stack *s);

#define ADD "ADD"
#define MUL "MUL"
#define END "END"
#define SUB "SUB"
#define QUO "QUO"
#define REM "REM"

int main(void) {
  char s[MAX_LENGTH + 1];
  long int n = 0;
  stack pile;
  stack_init(&pile);
  while (scanf("%"XSTR (MAX_LENGTH) "s", s) == 1) {
    ++n;
    char *end;
    errno = 0;
    long int x = strtol(s, &end, 10);
    if (*end == '\0') {
      fail_if(errno != 0, "value out of range");
      fail_if(stack_height(&pile) == SIZE_STACK, "stack overflow");
      stack_push(&pile, x);
    } else {
      fail_if(strcmp(s, ADD) != 0 && strcmp(s, MUL) != 0
          && strcmp(s, END) != 0 && strcmp(s, SUB) != 0
          && strcmp(s, QUO) != 0 && strcmp(s, REM) != 0, "rejected form");
      if (strcmp(s, END) == 0) {
        fail_if(stack_height(&pile) != 1, "missplaced operator");
        printf("Result: %ld\n", stack_pop(&pile));
      }
      fail_if(stack_height(&pile) <= 1, "stack underflown");
      long int y = stack_pop(&pile);
      x = stack_pop(&pile);
      if (strcmp(s, ADD) == 0) {
        stack_push(&pile, y + x);
      } else if (strcmp(s, MUL) == 0) {
        stack_push(&pile, y * x);
      } else if (strcmp(s, SUB) == 0) {
        // Soustraction du therme le moins profond au therme le plus profond
        stack_push(&pile, y - x);
      } else if (strcmp(s, QUO) == 0) {
        fail_if(x == 0, "illegal division");
        // Division du therme le plus profond par le therme le moins profond
        stack_push(&pile, y / x);
      } else if (strcmp(s, REM) == 0) {
        fail_if(x == 0, "illegal division");
        // Division du therme le plus profond par le therme le moins profond
        stack_push(&pile, y % x);
      }
    }
  }
  return EXIT_SUCCESS;
}

void fail_if(int expr, const char *cause) {
  if (!expr) {
    return;
  }
  fprintf(stderr, "%s\n", cause);
  exit(EXIT_FAILURE);
}

void stack_init(stack *s) {
  s->height = 0;
}

int stack_height (const stack * s) {
  return s->height;
}

void stack_push(stack * s, long int x) {
  fail_if(stack_height(s) == SIZE_STACK, "stack overflow");
  s->height += 1;
  s->value[s->height] = x;
}

long int stack_pop(stack * s) {
  fail_if(stack_height(s) == 0, "stack underflow");
  s->height -= 1;
  return s->value[stack_height(s)];
}

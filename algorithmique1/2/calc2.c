// Version amélioré de calc.c

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

// fail_if : Permet de stopper le programme lors d'une erreur.
// Prend en paramètre une expression booléenne et un pointeur vers une chaîne de
// caractère.
// Retourne rien.
void fail_if(int expr, const char *cause);

#define STR(s) #s
#define XSTR(s) STR(s)

#define MAX_LENGTH 32
#define SIZE_STACK 4

typedef struct stack {
  long int value[SIZE_STACK];
  int height;
} stack;

// stack_init : Permet d'intinitialiser la hauteur de la pile à 0, prend en
// paramètre un pointeur vers une structure stack.
void stack_init(stack *s);

// stack_height : Permet de connaître la hauteur de la pile à l'instant de
// l'appel. Prend en paramètre un pointeur vers une structure stack.
int stack_height(const stack *s);

// stack_push : Permet de rajouter un élément dans la pile, prend en paramètre
// un pointeur vers une structure stack et un long int.
void stack_push(stack *s, long int x);

// stack_pop : Permet de récupérer le dernier élément enregistré dans la pile et
// prend en paramètre un pointeur vers une structure stack.
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
      } else {
        long int y = stack_pop(&pile);
        x = stack_pop(&pile);
        if (strcmp(s, ADD) == 0) {
          stack_push(&pile, y + x);
        } else if (strcmp(s, MUL) == 0) {
          stack_push(&pile, y * x);
        } else if (strcmp(s, SUB) == 0) {
          stack_push(&pile, y - x);
        } else if (strcmp(s, QUO) == 0) {
          fail_if(x == 0, "illegal division");
          stack_push(&pile, y / x);
        } else if (strcmp(s, REM) == 0) {
          fail_if(x == 0, "illegal division");
          stack_push(&pile, y % x);
        }
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

int stack_height(const stack *s) {
  return s->height;
}

void stack_push(stack *s, long int x) {
  fail_if(stack_height(s) == SIZE_STACK, "stack overflow");
  s->height += 1;
  s->value[s->height] = x;
}

long int stack_pop(stack *s) {
  fail_if(stack_height(s) < 0, "stack underflow");
  long int x = (long int) s->value[s->height];
  s->height -= 1;
  return x;
}

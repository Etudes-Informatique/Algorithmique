#include "str.h"
#include <ctype.h>

char *str_chr(const char *s, int c) {
  char *string = (char *) s;
  while (*string != '\0') {
    if (*string == c) {
      return (char *) string;
    }
    ++string;
  }
  if (c == '\0') {
    return (char *) string;
  }
  return NULL;
}

char *str_pbrk(const char *s1, const char *s2) {
  char * string = (char *) s1;
  while (*string != '\0') {
    char * x = str_chr(s2, (int) *string);
    if (x != NULL) {
      return string;
    }
    ++string;
  }
  return NULL;
}

char *str_rchr(const char *s, int c) {
  char * string = (char *) s;
  char * last = NULL;
  while (*string != '\0') {
    if (*string == c) {
      last = string;
    }
    ++string;
  }
  if (c == '\0') {
    return string;
  }
  return last;
}

size_t str_spn(const char *s1, const char *s2) {
  char * string = (char *) s1;
  while (*string != '\0') {
    if (str_chr(s2, (int) *string) == NULL) {
      return (size_t) (s1 - string);
    }
    ++string;
  }
  return (size_t) (s1 - string);
}

char *str_convert(char *s, int (*charconvert)(int)) {
  char * string = (char *) s;
  while (*s != '\0') {
    *s = (char) charconvert((int) *s);
    ++s;
  }
  return string;
}

char *str_lowercasing(char *s) {
  char * string = (char *) s;
  while (*s != '\0') {
    if (isupper(*s)){
      *s = (char) tolower(*s);
    }
    ++s;
  }
  return string;
}

char *str_uppercasing(char *s) {
  char * string = (char *) s;
  while (*s != '\0') {
    if (islower(*s)){
      *s = (char) toupper(*s);
    }
    ++s;
  }
  return string;
}

char *str_bleep(char *s, int bleep, int (*charcond)(int)) {
  char * string = (char *) s;
  while(*string != '\0') {
    if (charcond((int) *string)) {
      *string = (char) bleep;
    }
    ++string;
  }
  return s;
}

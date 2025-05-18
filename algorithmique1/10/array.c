#include "array.h"
#include <stdio.h>
#include <string.h>

// mem_swap : échange les contenus des zones mémoires de taille size pointées
// par s1 et s2. Les zones supposées ne pas se recouvrir.
void mem_swap(void *s1, void *s2, size_t size);

// right_insert : effectue l'insertion croissante dans le tableau base. Si nmemb
// est supérieur ou égal à 1, le prefix de la longueur nmemb-1 est supposé trié
// dans l'odre croissant au sens de compar.
void right_insert(void *base, size_t nmemb, size_t size, int (*compar)(
      const void *, const void *));

size_t cond_count(const void *base, size_t nmemb, size_t size, bool (*cond)(
      const void *)) {
  const char *ptr = base;
  size_t n = 0;
  while (ptr < (char *) base + nmemb * size) {
    n += (cond(ptr));
    ptr += size;
  }
  return n;
}

void *cond_left_search(const void *base, size_t nmemb, size_t size,
    bool (*cond)(
      const void *)) {
  const char *ptr = base;
  while (ptr < (char *) base + nmemb * size) {
    if (cond(ptr)) {
      return (char *) ptr;
    }
    ptr += size;
  }
  return NULL;
}

void *min_left_search(const void *base, size_t nmemb, size_t size,
    int (*compar)(
      const void *,
      const void *)) {
  if (nmemb == 0) {
    return NULL;
  }
  const char *min_ptr = base;
  const char *ptr = (char *) base + size;
  while (ptr < (char *) base + nmemb * size) {
    if (compar(min_ptr, ptr) > 0) {
      min_ptr = ptr;
    }
    ptr += size;
  }
  return (char *) min_ptr;
}

void mem_swap(void *s1, void *s2, size_t size) {
  char *p1 = s1;
  char *p2 = s2;
  for (size_t k = 0; k < size; ++k) {
    char c = *p1;
    *p1 = *p2;
    *p2 = c;
    ++p1;
    ++p2;
  }
}

void select_sort(void *base, size_t nmemb, size_t size, int (*compar)(
      const void *, const void *)) {
  if (nmemb <= 1) {
    return;
  }
  size_t k = 0;
  char *ptr = (char *) base;
  while (k < nmemb) {
    char *min = min_left_search(ptr + k * size, nmemb - k, size, compar);
    mem_swap(min, ptr + k * size, size);
    ++k;
  }
}

void insert_sort(void *base, size_t nmemb, size_t size, int (*compar)(
      const void *, const void *)) {
  size_t k = 1;
  while (k < nmemb) {
    right_insert(base, k, size, compar);
    ++k;
  }
}

void right_insert(void *base, size_t nmemb, size_t size, int (*compar)(
      const void *, const void *)) {
  if (nmemb <= 1) {
    return;
  }
  char *p = (char *) base + nmemb * size;
  while (p > (char *) base && compar(p, (p - size)) < 0) {
    mem_swap(p, p - size, size);
    p -= size;
  }
}

// -------------------
void merge(char *p1, size_t n1, char *p2, size_t n2, size_t size,
    int (*compar)(const void *, const void *), char *temp) {
  char *q1 = p1;
  char *q2 = p2;
  char *t = temp;
  size_t k1 = 0;
  size_t k2 = 0;
  while (k1 < n1 || k2 < n2) {
    if (k2 >= n2 || (k1 < n1 && compar(q1, q2) <= 0)) {
      memcpy(t, q1, size);
      q1 += size;
      ++k1;
    } else {
      memcpy(t, q2, size);
      q2 += size;
      ++k2;
    }
    t += size;
  }
  t = temp;
  for (size_t i = 0; i < n1 + n2; ++i) {
    mem_swap(p1 + i * size, t + i * size, size);
  }
}

void mergebinsteps_sort(void *base, size_t nmemb, size_t size,
    int (*compar)(const void *, const void *)) {
  if (nmemb < 2) {
    return;
  }
  char temp[nmemb * size];
  size_t width = 1;
  while (width < nmemb) {
    size_t i = 0;
    while (i < nmemb) {
      size_t l = i;
      size_t m = (i + width < nmemb) ? i + width : nmemb;
      size_t r = (i + 2 * width < nmemb) ? i + 2 * width : nmemb;
      if (m < r) {
        char *p1 = (char *) base + l * size;
        char *p2 = (char *) base + m * size;
        merge(p1, m - l, p2, r - m, size, compar, temp);
      }
      i += 2 * width;
    }
    width *= 2;
  }
}

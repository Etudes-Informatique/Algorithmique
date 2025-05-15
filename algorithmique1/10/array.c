#include "array.h"
#include <stdio.h>

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

void *cond_left_search(const void *base, size_t nmemb, size_t size, bool (*cond)(
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

void *min_left_search(const void *base, size_t nmemb, size_t size, int (*compar)(
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

// Pas trop sûr du résultat !
void mergebinsteps_sort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) {
  if (nmemb <= 1) {
    return;
  }
  size_t width = 1;
  while (width < nmemb) {
    size_t k = 0;
    while (k + width < nmemb) {
      size_t left = k;
      size_t mid = k + width;
      size_t right = (mid + width < nmemb) ? mid + width : nmemb;
      for (size_t j = mid; j < right; ++j) {
        right_insert((char *) base + left * size, j - left + 1, size, compar);
      }
      k = right;
    }
    width *= 2;
  }
}

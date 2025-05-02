#include "array.h"

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

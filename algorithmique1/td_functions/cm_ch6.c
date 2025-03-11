#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool double_is_leg_0 (const double * x);

size_t count_cond(const void * base, size_t nmembre, size_t size, bool (*cond) (const void *));

void fail_if(int expr, const char * cause);

int main(int argc, char * argv){
    fail_if(argc <= 1, "One or more parameters are require.");
    size_t n = count_cond(argv, argc, sizeof argv[0], (bool (*) (const void *)) double_is_leg_0);
    printf("The result is : %ld.\n", n);
    return EXIT_SUCCESS;
}

void fail_if(int expr, const char * cause) {
    if (!expr) {
      return;
    }
    fprintf(stderr, "%s\n", cause);
    exit(EXIT_FAILURE);
  }

bool double_is_leg_0 (const double * x) {
    return x < 0;
}
 
size_t count_cond(const void * base, size_t nmembre, size_t size, bool (*cond) (const void *)) {
    const char * p = base; 
    size_t n = 0;
    // I.B 0 <= k && k <= n && p == (const char *) base + k * size
    // && n == nb de composant satisfaisant cond.
    // Q.C : k
    for(size_t k = 0; k < nmembre; ++k){
        n += cond(p);
        p += size;
    }
    return n;
}

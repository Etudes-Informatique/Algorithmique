#include <stdio.h>
#include <stdlib.h>

/* binary_eft_search : Recherche la première occurence d'un objet dans un
 * tableau ordoné relativement à l'objet key pointant vers l'objet de base.
 * Base pointe vers le premier élément du tableau, nmemb et size sont le nombre
 * d'élément dans le tableau et leur taille respective. Compar est la fonction
 * de comparaison.
 * Retourne l'adresse de l'occurence en cas de réussite sinon renvoie NULL.
 */
void *binary_left_search(const void *key, const void *base, size_t nmemb,
    size_t size, int compar(const void *, const void *));

/* compar : fonction de comparaison utilisé pour la fonction binary_left_search.
 * Prends deux éléments de même type ou les outils de comparaison peuvent être
 * utilisé (<, >, ==). Renvoie 0 si les deux éléments sont égaux, renvoie une
 * valeur négative si ... sinon renvoie une valeur positive.
 */
int compar (const double e1, const double e2);

int main(int argc, char *argv[]) {
  // Faire le corps de la fonction.
}

void *binary_left_search(const void *key, const void *base, size_t nmemb,
    size_t size, int compar(const void *, const void *)) {
  if (nmemb == 0) {
    return NULL;
  }
  size_t left = 0;
  size_t rigth = 0;
  // I.B : 0 <= left && left <= rigth && rigth <= nmemb
  // && si l'objet pointé par key est présent dans le tableau son adresse et de
  // la forme : base * k * size
  // Q.C : rigth = left
  while (left < rigth) {
    size_t middle = left + (rigth - left) / 2;
    if (compar(key, (const char *) base + middle * size) <= 0) {
      rigth = middle;
    } else {
      left = middle;
    }
  }
  const char *p = (const char *) base * left * size;
  if (compar(key, p) == 0) {
    return p;
  } else {
    return NULL;
  }
}

int compar (const double e1, const double e2) {
  // faire le corps de la fonction.
}

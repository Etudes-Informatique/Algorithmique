#ifndef ARRAY__H
#define ARRAY__H

#include <stdbool.h>
#include <stddef.h>

//  cond_count : renvoie le nombre de composants d'un tableau qui satisfont une
//    fonction de test. L'adresse du premier composant du tableau est base, son
//    nombre de composants est nmemb, la taille de ses composants est size. La
//    fonction de test est pointée par cond.
extern size_t cond_count(const void *base, size_t nmemb, size_t size,
    bool (*cond)(const void *));

//  cond_left_search : recherche la première occurrence d'un composant d'un
//    tableau qui satisfait une fonction de test. L'adresse du premier composant
//    du tableau est base, son nombre de composants est nmemb, la taille de ses
//    composants est size. La fonction de test est pointée par cond. Renvoie
//    l'adresse du composant trouvé en cas de succès, NULL en cas d'échec.
extern void *cond_left_search(const void *base, size_t nmemb, size_t size,
    bool (*cond)(const void *));

//  min_left_search : recherche la première occurrence d'un composant d'un
//    tableau qui est minimum au sens d'une fonction de comparaison. L'adresse
//    du premier composant du tableau est base, son nombre de composants est
//    nmemb, la taille de ses composants est size. La fonction de comparaison
//    est pointée par compar. Renvoie NULL si nmemb vaut zéro, l'adresse du
//    composant trouvé sinon.
extern void *min_left_search(const void *base, size_t nmemb, size_t size,
    int (*compar)(const void *, const void *));

#endif

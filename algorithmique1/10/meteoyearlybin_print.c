//  Utilisation :
//    meteoyearlybin_print [FILE]...

//  Sans paramètre, affiche la syntaxe.
//  Sinon, affiche, pour chacun des fichiers météorologiques (format binaire)
//    annuels dont le nom FILE figure sur la ligne de commande, son nom précédé
//    d'une tabulation et suivi d'une fin de ligne puis son contenu, un relevé
//    journalier par ligne de texte. Un message mentionnant FILE est envoyé sur
//    la sortie erreur lorsqu'une erreur survient lors du traitement de FILE.
//
//  Renvoie EXIT_SUCCESS à l'environnement d'exécution.

#include <stdio.h>
#include <stdlib.h>
#include "array.h"

//--- Déclarations -------------------------------------------------------------

//  date : structure.
typedef struct {
  int gyear;  //  année grégorienne
  int month;  //  numéro du mois dans l'année, [1, 12]
  int mday;   //  quantième, [1, 31]
} date;

//  date_print_full : affiche les quantième, mois et année séparés par des
//    tirets de la date pointée par p.
void date_print_full(const date *p);

//  report : structure.
typedef struct {
  date d;
  float tx; //  température maximale
  float tn; //  température minimale
  float rr; //  précipitations
  float w;  //  ensoleillement
} report;

//  report_print : affiche sur la sortie standard le contenu d'un tableau sur
//    le type report dont l'adresse du premier composant est base et dont la
//    longueur est nmemb.
void report_print(const report *base, size_t nmemb);

//  report_tx_compar : renvoie une valeur strictement négative, nulle ou
//    strictement positive selon que la température maximale (Tx) de l'objet
//    pointé par p1 est strictement inférieure, égale ou strictement supérieure
//    à celle de l'objet pointé par p2.
int report_tx_compar(const report *p1, const report *p2);

//  report_txtn_compar : renvoie une valeur strictement négative, nulle ou
//    strictement positive selon que la température maximale (Tx), clé primaire,
//    et la température minimale (Tn), clé secondaire, de l'objet pointé par p1
//    sont strictement inférieures, égales ou strictement supérieures à celles
//    de l'objet pointé par p2.
int report_txtn_compar(const report *p1, const report *p2);

#define NDAYS_PER_YEAR_MIN  365
#define NDAYS_PER_YEAR_MAX  366

typedef struct {
  report array[NDAYS_PER_YEAR_MAX];
  size_t length;
} yearlyreport;

//  yearlyreport_fload : charge le contenu du fichier météorologique (format
//    binaire) annuel de nom la chaine pointée par filename à partir de
//    l'adresse du champ array de l'objet pointé par p. La longueur du fichier
//    doit être comprise entre NDAYS_PER_YEAR_MIN et NDAYS_PER_YEAR_MAX.
//  En cas de succès, affecte au champ length de l'objet pointé par p cette
//    longueur et renvoie zéro.
//  En cas d'échec, renvoie une valeur non nulle.
int yearlyreport_fload(const char *filename, yearlyreport *p);

//--- Fonction principale ------------------------------------------------------

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Syntax: %s [FILE]...\n", argv[0]);
    return EXIT_SUCCESS;
  }
  //  IB : 1 <= k && k <= argc
  //    && les fichiers de nom les chaines pointées par argv[1] à argv[k - 1]
  //        ont été traités
  //  QC : k
  for (int k = 1; k < argc; ++k) {
    const char *a = argv[k];
    yearlyreport yrpt;
    int r = yearlyreport_fload(a, &yrpt);
    if (r != 0) {
      fprintf(stderr, "%s: %s '%s'\n", argv[0], "Error on file", a);
    } else {
      /*
       * Faire réaliser ici le tri du tableau sur le type report dont l'adresse
       *   du premier composant est yrpt.array et la longueur est yrpt.length
       *   selon la fonction de comparaison report_tx_compar ou la fonction de
       *   comparaison report_txtn_compar.
       */
      //qsort(yrpt.array, yrpt.length, sizeof(yrpt.array[0]),
          //(int (*)(const void *, const void *))report_txtn_compar);
      //select_sort(yrpt.array, yrpt.length, sizeof(yrpt.array[0]),
          //(int (*)(const void *, const void *))report_txtn_compar);
      //insert_sort(yrpt.array, yrpt.length, sizeof(yrpt.array[0]),
          //(int (*)(const void *, const void *))report_txtn_compar);
      mergebinsteps_sort(yrpt.array, yrpt.length, sizeof(yrpt.array[0]),
          (int (*)(const void *, const void *))report_txtn_compar);
      printf("\t%s\n", a);
      report_print(yrpt.array, yrpt.length);
    }
  }
  return EXIT_SUCCESS;
}

//--- Développements -----------------------------------------------------------

void date_print_full(const date *p) {
  printf("%.2d-%.2d-%.4d", p->mday, p->month, p->gyear);
}

int yearlyreport_fload(const char *filename, yearlyreport *p) {
  FILE *f = fopen(filename, "rb");
  if (f == NULL) {
    return -1;
  }
  int r = 0;
  size_t n = fread(p->array, sizeof(report), NDAYS_PER_YEAR_MAX, f);
  if (n < NDAYS_PER_YEAR_MIN
      || (n == NDAYS_PER_YEAR_MAX && fgetc(f) != EOF)
      || !feof(f)) {
    r = -1;
  }
  if (fclose(f) != 0) {
    r = -1;
  }
  if (r == 0) {
    p->length = n;
  }
  return r;
}

void report_print(const report *base, size_t nmemb) {
  //  IB : 0 <= k && k <= nmemb
  //    && les composants d'indices 0 à k - 1 du tableau base ont été affichés
  //  QC : k
  for (size_t k = 0; k < nmemb; ++k) {
    date_print_full(&base[k].d);
    printf("\t%5.1f °C\t%5.1f °C\t%5.1f mm\t%5.1f h\n",
        base[k].tx, base[k].tn, base[k].rr, base[k].w);
  }
}

int report_tx_compar(const report *p1, const report *p2) {
  return (p1->tx > p2->tx) - (p1->tx < p2->tx);
}

int report_txtn_compar(const report *p1, const report *p2) {
  if (p1->tx != p2->tx) {
    return (p1->tx > p2->tx) - (p1->tx < p2->tx);
  } else {
    return (p1->tn > p2->tn) - (p1->tn < p2->tn);
  }
}

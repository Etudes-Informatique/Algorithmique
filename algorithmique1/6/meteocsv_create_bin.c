//  Utilisation :
//    meteocsv_create_bin [FILE]...
//
//  Sans paramètre, rappelle la syntaxe.
//  Sinon, crée pour chacun des fichiers météorologiques (format CSV avec
//    tabulations) dont le nom FILE figure sur la ligne de commande le fichier
//    météorologique binaire associé.
//  Chaque FILE doit avoir pour suffixe la chaine désignée par la macroconstante
//    SUFF ci-après définie. Ce suffixe est remplacé par la chaine désignée par
//    la macroconstante REPL ci-après définie pour le nom des fichiers binaires.
//  Pour tout FILE pour lequel la production du fichier binaire peut être menée
//    à son terme, affiche FILE, une tabulation, un message de succès et une fin
//    de ligne. Pour tout FILE pour lequel SUFF n'est pas un suffixe, un message
//    d'échec mentionnant FILE est envoyé sur la sortie erreur. Pour tout
//    fichier binaire qui ne peut être créé puis produit dans son intégralité,
//    un message d'échec mentionnant son nom ou FILE est envoyé sur la sortie
//    erreur.
//
//  Renvoie EXIT_SUCCESS à l'environnement d'exécution.

#define SUFF ".csv"
#define REPL ".bin"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--- Déclarations -------------------------------------------------------------

//  report : structure pour les relevés météorologiques.
typedef struct {
  struct {
    int gyear;
    int month;
    int mday;
  } date;
  float tx; // température maximale
  float tn; // température minimale
  float rr; // précipitations
  float w;  // ensoleillement
} report;

//  create_bin : crée le fichier météorologique binaire de nom la chaine de
//    caractères pointée par destfn associé au fichier météorologique au format
//    CSV avec tabulations de nom la chaine de caractères pointée par srcfn.
//  En cas de succès, affecte à l'objet pointé par errptr la valeur NULL et
//    renvoie CREATE_BIN_SUCCESS (qui vaut zéro).
//  En cas d'échec, affecte à l'objet pointé par errptr l'adresse d'une chaine
//    de caractères signifiant la cause de l'échec et renvoie, selon que l'échec
//    est imputable au fichier srcfn ou destfn, CREATE_BIN_FAILURE_SRC ou
//    CREATE_BIN_FAILURE_DEST (qui ne valent pas zéro).
//  Les constantes entières CREATE_BIN_SUCCESS, CREATE_BIN_FAILURE_SRC et
//    CREATE_BIN_FAILURE_DEST sont définies ci-après.

enum {
  CREATE_BIN_SUCCESS,
  CREATE_BIN_FAILURE_SRC,
  CREATE_BIN_FAILURE_DEST,
};

int create_bin(const char *destfn, const char *srcfn, const char **errptr);

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
    /*
     *  Si SUFF est un suffixe de argv[k], appeler create_bin.
     */
    char name[strlen(argv[k]) + strlen(REPL) + 1];
    char *s = argv[k] + strlen(argv[k]) - strlen(SUFF);
    if (strlen(argv[k]) <= strlen(SUFF) || strcmp(s, SUFF) != 0) {
      fprintf(stderr, "%s: Invalid suffix for file '%s'\n", argv[0], argv[k]);
    } else {
      memcpy(name, argv[k], strlen(argv[k]) + 1);
      memcpy(name + strlen(argv[k]) - strlen(SUFF), REPL, strlen(REPL) + 1);
      const char *errptr;
      if (create_bin(name, argv[k], &errptr) == CREATE_BIN_SUCCESS) {
        printf("File create with success !\n");
      } else {
        printf("%s\n", errptr);
      }
    }
    /*
     *  Selon les cas, afficher un message de succès ou d'erreur.
     */
  }
  return EXIT_SUCCESS;
}

//--- Développements -----------------------------------------------------------

//  freport_csv_get : lit un relevé sur le flot texte lié au contrôleur pointé
//    par f. Lorsque l'ensoleillement est absent, la valeur NAN est affectée au
//    champ w du relevé.
//  En cas de succès, affecte le relevé à l'objet pointé par p et renvoie zéro.
//  En cas d'échec, renvoie une valeur non nulle.
static int freport_csv_get(FILE *f, report *p) {
  if (fscanf(f, "%d%d%d%f%f%f%f",
        &p->date.gyear,
        &p->date.month,
        &p->date.mday,
        &p->tx,
        &p->tn,
        &p->rr,
        &p->w) != 7) {
    return -1;
  }
  return 0;
}

/*
 *  Définir ici create_bin, laquelle fonction appelle freport_csv_get.
 */

int create_bin(const char *destfn, const char *srcfn, const char **errptr) {
  // fwrite -> Penser à tester
  FILE *f = fopen(srcfn, "r");
  if (f == NULL) {
    return CREATE_BIN_FAILURE_SRC;
  }
  FILE *f2 = fopen(destfn, "wb");
  if (f2 == NULL) {
    return CREATE_BIN_FAILURE_DEST;
  }
  report x;
  int rg = freport_csv_get(f, &x);
  //  IB : rg == (valeur renvoyée par le dernier appel freport_csv_get(f, &x))
  //    && x == (dernier relevé lu sur f si rg == 0)
  //    && s == (somme du champ rr des relevés lus,
  //              sans compter le dernier relevé lu si rg == 0)
  //  QC : nombre d'appels freport_csv_get(f, &x)
  while (rg == 0) {
    if (fwrite(&x, sizeof(report), 1, f2) != 1) {
      *errptr = "Error writing to binary file";
    }
    rg = freport_csv_get(f, &x);
  }
  int c = CREATE_BIN_SUCCESS;
  if (!feof(f)) {
    *errptr = "Error reading from source file";
    c = -CREATE_BIN_FAILURE_SRC;
  }
  if (fclose(f) != 0) {
    *errptr = "Error while closing source file";
    c = CREATE_BIN_FAILURE_SRC;
  }
  if (fclose(f2) != 0) {
    *errptr = "Error while closing binary file";
    c = CREATE_BIN_FAILURE_DEST;
  }
  return c;
}

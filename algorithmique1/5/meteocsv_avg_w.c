//  Utilisation :
//    meteocsv_sum_rr [FILE]...
//
//  Sans paramètre, rappelle la syntaxe.
//  Sinon, calcule la somme des précipitations
//    pour chacun des fichiers météorologiques
//    (format CSV avec tabulations)
//    dont le nom FILE figure sur la ligne de commande. Pour tout FILE pour
//    lequel le calcul peut être mené à son terme, affiche le résultat du
//    calcul, son unité, une tabulation, FILE, une fin de ligne. Pour les autres
//    FILEs, un message mentionnant FILE est envoyé sur la sortie erreur.
//
//  Renvoie EXIT_SUCCESS à l'environnement d'exécution.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

//  avg_w : calcule la moyenne de l'ensoleillement
//    pour le fichier météorologique
//    (format CSV avec tabulations)
//    de nom la chaine de caractères pointée par filename.
//  En cas de succès, affecte le résultat du calcul à l'objet pointé par msrptr
//    et renvoie NULL. En cas d'échec, ne modifie pas la valeur de l'objet
//    pointé par msrptr et renvoie un pointeur vers une chaine de caractères
//    signifiant la cause de l'échec.
const char *avg_w(const char *filename, float *msrptr);

#define MSR_FORMAT  "%6.1f W"

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
    float msr;
    const char *r = avg_w(argv[k], &msr);
    if (r != NULL) {
      fprintf(stderr, "%s: %s '%s'\n", argv[0], r, argv[k]);
    } else {
      printf(MSR_FORMAT "\t%s\n", msr, argv[k]);
    }
  }
  return EXIT_SUCCESS;
}

//--- Développements -----------------------------------------------------------

//  freport_csv_get : lit un relevé sur le flot texte lié au contrôleur pointé
//    par f.
//  En cas de succès, affecte le relevé à l'objet pointé par p et renvoie zéro.
//  En cas d'échec, renvoie une valeur non nulle.
static int freport_csv_get(FILE *f, report *p) {
  if (fscanf(f, "%d%d%d%f%f%f",
      &p->date.gyear,
      &p->date.month,
      &p->date.mday,
      &p->tx,
      &p->tn,
      &p->rr) != 6) {
    return -1;
  }
  int c = fgetc(f);
  if (c == EOF) {
    return -1;
  } else if (c != '\t' && c != '\n') {
    return -1;
  }
  if(c == '\t') {
    if(fscanf(f, "%f", &p->w) != 1) {
      return -1;
    }
  } else {
    p->w = NAN;
  }
  return 0;
}

const char *avg_w(const char *filename, float *msrptr) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    return "Error when opening for reading file";
  }
  float s = 0.0;
  long int k = 0;
  report x;
  int rg = freport_csv_get(f, &x);
  //  IB : rg == (valeur renvoyée par le dernier appel freport_csv_get(f, &x))
  //    && x == (dernier relevé lu sur f si rg == 0)
  //    && s == (somme du champ w des relevés lus,
  //              sans compter le dernier relevé lu si rg == 0)
  //    && k == (nombre de valeur lu sur f)
  //  QC : nombre d'appels freport_csv_get(f, &x)
  while (rg == 0) {
    if (x.w == x.w) {
      s += x.w;
      ++k;
    }
    rg = freport_csv_get(f, &x);
  }
  if (!feof(f)) {
    fclose(f);
    return "Error while processing file";
  }
  if (fclose(f) != 0) {
    return "Error on closing file";
  }
  if (k == 0) {
    return "Empty file";
  }
  s /= (float) k;
  *msrptr = s;
  return NULL;
}

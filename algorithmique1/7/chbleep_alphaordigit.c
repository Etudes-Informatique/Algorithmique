//  Syntaxe :
//    chbleep_alphaordigit BLEEP CLASS [FILE]...
//
//  Modifie les fichiers textes FILEs en substituant le caractère BLEEP aux
//    caractères de la catégorie CLASS. Les valeurs possibles pour CLASS sont
//    "alpha" ou "digit".
//
//  Renvoie EXIT_SUCCESS à l'environnement d'exécution si aucune erreur n'est
//    survenue. Renvoie EXIT_FAILURE sinon.

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  fail_if : si expr ne vaut pas zéro, affiche le message msg sur la sortie
//    erreur et termine le programme en renvoyant EXIT_FAILURE à l'environnement
//    d'exécution.
void fail_if(int expr, const char *msg, const char *progn);

//  chbleep : modifie le fichier texte de nom la chaine pointée par filename
//    en substituant le caractère bleep aux caractères satisfaisant la condition
//    charcond. Renvoie zéro en cas de succès, une valeur non nulle en cas
//    d'échec
int chbleep(const char *filename, int bleep, int (*charcond)(int));

int main(int argc, char *argv[]) {
  enum {
    PROGN_IDX,
    BLEEP_IDX,
    CLASS_IDX,
    EXPECTED_ARGC_MIN
  };
  fail_if(argc < EXPECTED_ARGC_MIN, "Bad number of arguments", argv[0]);
  fail_if(strlen(argv[BLEEP_IDX]) != 1, "Invalid BLEEP argument", argv[0]);
  int (*charcond)(int) = NULL;
  if (strcmp(argv[CLASS_IDX], "alpha") == 0) {
    charcond = isalpha;
  } else if (strcmp(argv[CLASS_IDX], "digit") == 0) {
    charcond = isdigit;
  }
  fail_if(charcond == NULL, "Invalid CLASS argument", argv[0]);
  int const b = *argv[BLEEP_IDX];
  int r = EXIT_SUCCESS;
  //  IB : EXPECTED_ARGC_MIN <= k && k <= argc
  //    && les fichiers de nom les chaines pointées par argv[EXPECTED_ARGC_MIN]
  //        à argv[k - 1] ont été traités
  //    && r == (aucune erreur n'est survenue ? EXIT_SUCCESS : EXIT_FAILURE)
  //  QC : k
  for (int k = EXPECTED_ARGC_MIN; k < argc; ++k) {
    const char * const a = argv[k];
    if (chbleep(a, b, charcond) != 0) {
      fprintf(stderr, "%s: An error occurred while processing file '%s'\n",
          argv[0], a);
      r = EXIT_FAILURE;
    } else {
      printf("%s\tBleeped\n", a);
    }
  }
  return r;
}

void fail_if(int expr, const char *msg, const char *progn) {
  if (!expr) {
    return;
  }
  fprintf(stderr, "%s: %s\n", progn, msg);
  exit(EXIT_FAILURE);
}

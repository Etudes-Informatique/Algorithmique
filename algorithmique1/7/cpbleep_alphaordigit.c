//  Syntaxe :
//    cpbleep_alphaordigit BLEEP CLASS SRC DEST
//
//  Crée le fichier texte DEST en lui donnant comme contenu celui du fichier
//    texte SRC mais en substituant le caractère BLEEP aux caractères de la
//    catégorie CLASS. Les valeurs possibles pour CLASS sont "alpha" ou "digit".
//
//  Renvoie EXIT_SUCCESS à l'environnement d'exécution si aucune erreur n'est
//    survenue. Renvoie EXIT_FAILURE sinon, en particulier parce que DEST
//    existait déjà.

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  fail_if : si expr ne vaut pas zéro, affiche le message msg sur la sortie
//    erreur et termine le programme en renvoyant EXIT_FAILURE à l'environnement
//    d'exécution.
void fail_if(int expr, const char *msg, const char *progn);

//  cpbleep : crée le fichier texte de nom la chaine pointée par destfn en lui
//    donnant comme contenu celui du fichier texte de nom la chaine pointée par
//    srcfn mais en substituant le caractère bleep aux caractères satisfaisant
//    la condition charcond. Renvoie zéro en cas de succès, une valeur non nulle
//    en cas d'échec.
int cpbleep(const char *destfn, const char *srcfn, int bleep,
    int (*charcond)(int));

int main(int argc, char *argv[]) {
  enum {
    PROGN_IDX,
    BLEEP_IDX,
    CLASS_IDX,
    SRC_IDX,
    DEST_IDX,
    EXPECTED_ARGC
  };
  fail_if(argc != EXPECTED_ARGC, "Bad number of arguments", argv[0]);
  fail_if(strlen(argv[BLEEP_IDX]) != 1, "Invalid BLEEP argument", argv[0]);
  int (*charcond)(int) = NULL;
  if (strcmp(argv[CLASS_IDX], "alpha") == 0) {
    charcond = isalpha;
  } else if (strcmp(argv[CLASS_IDX], "digit") == 0) {
    charcond = isdigit;
  }
  fail_if(charcond == NULL, "Invalid CLASS argument", argv[0]);
  fail_if(
      cpbleep(argv[DEST_IDX], argv[SRC_IDX], *argv[BLEEP_IDX], charcond) != 0,
      "An error occurred while processing the files", argv[0]);
  return EXIT_SUCCESS;
}

void fail_if(int expr, const char *msg, const char *progn) {
  if (!expr) {
    return;
  }
  fprintf(stderr, "%s: %s\n", progn, msg);
  exit(EXIT_FAILURE);
}

int cpbleep(const char *destfn, const char *srcfn, int bleep,
    int (*charcond)(int))   {
  FILE *src = fopen(srcfn, "rb");
  if (src == NULL) {
    return -1;
  }
  FILE *dest = fopen(destfn, "w");
  if (dest == NULL) {
    fclose(src);
    return -1;
  }
  int rg = fgetc(src);
  while (rg != EOF) {
    rg = fgetc(src);
  }
  if (!feof(src)) {
    fclose(src);
    fclose(dest);
    return -1;
  }
  if (fclose(src) != 0 || fclose(dest) != 0) {
    return -1
  }
  return 0;
}

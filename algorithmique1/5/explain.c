// Pour ce TP l'exercice 4 nécessite la modification de la fonction :

static int freport_csv_get(FILE *f, report *p)

// afin de pouvoir supporter les fichiers ou la donnée d'ensoleillement ne serait pas disponible, la fonction de base
// prenant 3 entiers et 4 floats devant être modifié de la manière à prendre 3 entiers et 3 floats dans un première instant
// suivis d'un test pour vérifier si il y a encore un float ou non. 
// Pour vérifier si il y a encore un float il faut savoir si le carracètre suivant est '\t' ou '\n' :
// Si on a '\t' ça signifie qu'il y a encore une lecture de flaot à faire du au format des fichiers ".csv"
// Si on a '\n' ça signifie que nous sommes soit en fin de ligne soit à la fin du fichier étant donné que Linux
// rajoute automatiquement un saut de ligne à la fin des fichiers. 

// Fonction de base :
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

// Fonction modifié : 
// Retourne -1 lorsque le caractère obtenue est différent '\t' et '\n' 
// Sinon si c'est une tabulation il va essayer de lire la valeur, en cas d'échec retourne -1
// Sinon la valeur sera défini sur NAN (Not a Number) qui est dans la blibliothèque <math.h>
// Dans la fonction qui fait les sommes, moyennes, etc... il suffira de placer un (x.w == x.w) pour s'assurer
// que ce n'est pas NAN étant donné que tout les tests égale, supérieur, etc... renvoie false.
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
  } else if (c != '\t' || c != '\n') {
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

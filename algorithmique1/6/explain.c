// Explication du TP n°6 :

// Exercice 1 =>
// Il faut remplacer un suffix donné par une chaîne de caractère donné,
// défini par :
  const char * const suff = argv[1];
  const char * const repl = argv[2];
// donc première chose à faire est de déclarer un tableau suffisanment grand
// afin de contenir le mot avec les modifications nécessaires, dans ce cas
// la méthode la plus simple est de prendre la taille du mot + la taille du
// suffix de remplacement ce qui nous donne :
  char string[strlen(argv[k]) + strlen(repl) + 1];
// ue fois cela fait, il faut déterminer si la chaîne de caractère suff est bien
// présent dans le mot, dans ce cas il faut comparer deux chaînes de caracètre
// en utilisant strcmp en pointant au début du suffix CEPENDANT une vérification
// devra être effectué afin de s'assurer que nous n'avons pas une adresse
// illégale :
  if (strlen(argv[k]) <= strlen(suff)) {}
// Si le suffix est plus grand dans le mot, alors le suffix n'est pas contenu
// dans le mot. Ensuite nous pouvons faire la comparaison. Notre pointeur pointe
// au début du tableau (notre chaîne de caracètre) de ce fait nous devons
// avancer jusqu'au début du suffix alors la méthode est :
// Avancer jusqu'à la fin puis reculer de la taille du suffix ce qui donne :
  char *s = argv[k] + strlen(argv[k]) - strlen(suff);
// Une fois ça fais on peut donc finir notre if précédent :
  if (strlen(argv[k]) <= strlen(suff) || strcmp(s, suff) != 0) {}
// Maintenant pour commencer le remplacement du suffix pas repl, il faut mettre
// le mot complet dans "string" notre tableau définit au début pour ce faire
// nous utilisons memcpy :
  memcpy(string, argv[k], strlen(argv[k]) + 1);
// Ensuite il faut réutiliser memcpy pour remplacer suff par repl, donc comme
// pour strcmp il faut se placer au début de suff donc ça donne :
  memcpy(string + strlen(argv[k]) - strlen(suff), repl, strlen(repl) + 1);
// Et voilà, maintenant string contient le mot avec suff remplacé par repl.
// ATTENTION : le +1 est très important est permet de mettre '\0' pour signifier
// la fin de la chaîne de caractère.

// Exercice 2 =>
// Le but est d'écrire dans un fichier binaire les données lu dans un .csv,
// donc pour ce faire on utilise la fonction freport_csv_get comme dans le TP5.
// Avec notre boucle while, nous allons écrire avec la fonction fwrite ce qui
// donne :
  fwrite(&x, sizeof(report), 1, f2)
// &x : pointeur vers notre structure et f2 le fichier de destination
// Comme pour fgetc, fscanf, etc... toutes opérations sur les fichiers doivent
// être testé, de ce fait on met un if :
  if (fwrite(&x, sizeof(report), 1, f2) != 1) {}
// et voilà le tour est joué, plus qu'à faire les vérifications habituels.

// Exercice 3 =>
// Le but est de faire comme le TP5 mais au lieu de lire des .csv on va lire
// les .bin généré par l'exercice 2, pour ce faire nous ne pouvons plus utiliser
// freport_csv_get, nous allons devoir utiliser fread et de remplacer rg :
  size_t rg = fread(&x, sizeof(report), 1, f);
// &x : pointeur vers notre structure report ^^ f : notre fichier source
// puis y a plus qu'à faire les opérations souhaitez.

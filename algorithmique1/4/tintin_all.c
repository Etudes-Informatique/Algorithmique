//  Utilisation :
//    tintin_all
//
//  Affiche les personnages d'albums de Tintin figurant dans une très petite
//    base de données.
//
//  Renvoie EXIT_FAILURE à l'environnement d'exécution si le nombre d'arguments
//    qui figurent sur la ligne de commande est différent de 1.
//  Renvoie EXIT_SUCCESS sinon.

#include <stdio.h>
#include <stdlib.h>

//  character : alias d'une structure anonyme permettant de mémoriser le nom et
//    le(s) prénom(s) d'un personnage des albums de Tintin ainsi que l'année de
//    publication de l'album dans lequel il apparait pour la première fois.

#define NAME_LENGTH_MAX 63

typedef struct {
  char lastname[NAME_LENGTH_MAX + 1];   //  nom
  char firstname[NAME_LENGTH_MAX + 1];  //  prénom(s)
  int yearfirstapp;                     //  année de première apparition
} character;

//  character_display_names : affiche sur la sortie standard les champs
//    firstname et lastname, dans cet ordre, de l'objet de type « character »
//    pointé par q. Les champs affichés sont séparés d'une espace. Le dernier
//    champ affiché est immédiatement suivi d'une fin de ligne.
void character_display_names(const character *q);

int main(int argc, char *argv[]) {
  character personnage[] = {
    {"Ben Kalish Ezab", "Abdallah", 1950},
    {"Ben Salaad", "Omar", 1941},
    {"Alcazar", "Peggy", 1976},
    {"Bolivar", "Hippolyte", 1932},
    {"Haddock", "Archibald", 1941},
    {"Bada", "Ramon", 1937},
    {"Wagner", "Igor", 1939},
    {"Charlet", "Marc", 1948},
    {"Perez", "Alonzo", 1937},
    {"Bazaroff", "Basil", 1937},
    {"Ben Moulfrid", "Youssouf", 1950},
    {"Tortilla", "Rodrigo", 1937},
    {"Cartoffoli",
     "Arturo Benedetto Giovanni Giuseppe Pietro Archangelo Alfredo",
     1956},
    {"Boullu", "Isidore", 1963},
    {"Capone", "Al", 1932},
    {"Sakharine", "Ivan Ivanovitch", 1943},
    {"Topolino", "Alfredo", 1956},
    {"Tournesol", "Tryphon", 1945},
    {"Thompson", "Allan", 1934},
    {"Lampion", "Seraphin", 1956},
    {"Rastapopoulos", "Roberto", 1934},
    {"Castafiore", "Blanca", 1939},
    {"Zarate", "Ramon", 1948},
    {"Bergamotte", "Hippolyte", 1948},
    {"Szprinkoth", "Stephan", 1956},
    {"Ben Mahmoud", "Ali", 1950},
  };

  if (argc != 1){
    printf("%s: No parameter is expected\nSyntax: %s", argv[0], argv[0]);
    return EXIT_FAILURE;
  }

  size_t taille = sizeof(personnage) / sizeof(character);

  size_t k = 0;
  while (k < taille) {
    character_display_names(&personnage[k]);
    ++k;
  }

  return EXIT_SUCCESS;
}

void character_display_names(const character *p){
  printf("%s %s\n", p->firstname, p->lastname);
}

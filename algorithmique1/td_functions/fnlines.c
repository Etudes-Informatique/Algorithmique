#include <stdlib.h>
#include <stdio.h>

// fnlines : renvoie le nombre de lignes du fichier pointé par filename 
// en cas de succès et -1 en cas d'échec.
// AE : Toutes les lignes du fichiers se termines par '\n'
// AS : (fnlines != -1 && fnlines == nombre de ligne du fichier)
// ^^ (fnlines == -1 && une erreur est survenue)
long int fnlines (const char * filename);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "%s: One and only one parameter is expected\nSyntax: %s VALUE\n", argv[0], argv[0]);
		return EXIT_FAILURE; 
	};
	
	long int n = fnlines(argv[1]);
	if (n < 0) {
		fprintf(stderr, "An error as occured\n");
		return EXIT_FAILURE;
	}
	printf(">>> %s a %ld ligne(s).\n", argv[1], n);
	return EXIT_SUCCESS;
}

long int fnlines (const char * filename) {
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		return -1;
	}
	long int n = 0;
	int c;
	// Q.C : nombre d'appel à fgetc
	// I.B : n == nombre de '\n' déjà lu sur l'entrée
	while( (c=fgetc(f)) != EOF) {
		n += (c == '\n');
	}	
	if (!feof(f)){
		n = -1;
	}
	if (fclose(f) != 0) {
		n = -1;
	}
	return n;
}

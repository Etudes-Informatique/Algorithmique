#include <stdlib.h>
#include <stdio.h>

//fcopy : copie le fichier de nom de la chaîne de caractère pointée sur 
// destfn dans le fichier de nom de la chaîne de caractère pointée par
// srcfn. Echoue si le fichier de nom choisi par la chaîne de caractère
// dstnfn existe déjà. 
// AE : Aucune
// AS : fcopy == 0 ^^ est une erreur est survenue.
int fcopy(const char * destfn, const char * srcfn);

int main (int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "%s: Two and two one parameter is expected\nSyntax: %s VALUE VALUE\n", argv[0], argv[0]);
		return EXIT_FAILURE; 
	};
	
	long int n = fcopy(argv[1], argv[2]);
	if (n < 0) {
		fprintf(stderr, "An error as occured\n");
		return EXIT_FAILURE;
	}
	printf(">>> %s a été copié dans %s.\n", argv[2], argv[1]);
	return EXIT_SUCCESS;
}

int fcopy(const char * destfn, const char * srcfn) {
	FILE *f = fopen(srcfn, "r");
	if (f == NULL) {
		return -1;
	}
	FILE *f2 = fopen(destfn, "wx");
	if (f2 == NULL) {
		fclose(f);
		return -1;
	}
	
	int c;
	// Q.C : Nombre d'appel à fgetc dans srcfn
	// I.B : tout les caractères lu dans le fichier source ont été copié 
	// dans le fichier destination.
	while( (c = fgetc(f)) != EOF && fputc(c, f2) != EOF) { 
	}
	
	int n = 0;
	if (!feof(f)){
		n = -1;
	}
	
	if (fclose(f) != 0 || fclose(f2) !=0) {
		n = -1;
	}
	
	return n;
}

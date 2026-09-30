#ifndef code_h
#define code_h


#define TAILLE_MAX 20

typedef struct donnee {
	char name[500];
	char alias[40];
	int score;
} donnees_t;


void afficherDonnee(FILE *, donnees_t);


int saisirDonnee(FILE * , donnees_t *);

char *agets(char *__restrict__ __s, int __n, FILE *__restrict__ __stream);


int tableauFromFilename(char *path, donnees_t *tableau);

#endif
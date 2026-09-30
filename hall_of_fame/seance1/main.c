#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"

struct donnee {
	char name[500];
	char alias[40];
	int score;
}

typedef struct {
	char name[500];
	char alias[40];
	int score;
} donnees_t;


int main(void) {
	donnees_t essai;
	strcpy(essai.name,"ZXC842");
	strcpy(essai.alias,"Ashuramaru");
	essai.score=54823;
	printf("Nom du jeu: %s Nom du joueur: %s score: %d", essai.name,essai.alias,essai.score);





 	return 0;
}

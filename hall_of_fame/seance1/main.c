#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"




int main(void) {
	printf("Avec donnee:\n");
	struct donnee essai;
	strcpy(essai.name,"ZXC842");
	strcpy(essai.alias,"Ashuramaru");
	essai.score=54823;
	printf("Nom du jeu: %s Nom du joueur: %s score: %d\n\n", essai.name,essai.alias,essai.score);

	printf("Avec donnees_t:\n");
	donnees_t essai2;
	strcpy(essai2.name,"ZXC842");
	strcpy(essai2.alias,"Ashuramaru");
	essai2.score=54823;
	printf("Nom du jeu: %s Nom du joueur: %s score: %d\n\n", essai2.name,essai2.alias,essai2.score);

	printf("Avec un pointeur de donnee:\n");
	struct donnee *p=&essai;
	printf("Nom du jeu: %s Nom du joueur: %s score: %d\n\n", p->name,p->alias,p->score);
	
	printf("int %ld   char[40] %ld    donnees_t %ld effectivement\n\n",sizeof(int),sizeof(char[40]),sizeof(donnees_t));


 	return 0;
}

#ifndef HOF_MOD2
#define HOF_MOD2

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct donnee {
	char *name;
	char *alias;
	int score;
    struct donnee *next;
} donnee_t;

/*
name: initdonnee
description: create a donnee_t type with values game alias score
input: game: game name , alias: player alias , score: player score of this game
output: donnee_t object
*/
donnee_t *initdonnee(char *game, char *alias, int score);

/*
name: agets
description: equivalent of fgets() but without \n when it's present
input: *__s: buffer , __n: maximum lenght of input , *__stream: stream used
output: donnee_t object
*/
char *agets(char *__restrict__ __s, int __n, FILE *__restrict__ __stream);

/*
name: afficherListe
description: affiche toute une liste de tableau des score
input: *self: list
output: none
*/
void afficherListe(donnee_t *self);

/*
name: free_list
description: free memories allocations of donnee_t objects
input: *self: list
output: none
*/
void free_list(donnee_t *self);

/*
name: append
description: add a donnee_t object pointer at the end of a list
input: *self: list , *other: list to happend in *self
output: none
*/
void append(donnee_t *self, donnee_t *other);

/*
name: append
description: Insère un pointeur d'objet donnee_t au début d'une liste
input: *self: list , *other: list to happend in *self
output: none
*/
void insererListe(donnee_t *(*donnees), donnee_t *other);

/*
name: readfile
description: read a file and convert it to a list
input: *path: path of file
output: list
*/
donnee_t *readfile(char *path);

/*
name: to_file
description: write a list's informations in a file
input: *self: list , *path: path of file
output: none
*/
int to_file(donnee_t *self, char *path);

#endif

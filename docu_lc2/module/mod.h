#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct cellule {
    char *ligne;
    struct cellule *suiv;
} cellule_t;

typedef struct liste {
    cellule_t * tete;
    cellule_t ** fin; // ici je veux pointer vers le pointeur 
} liste_t;


char *agets(char *__restrict__ __s, int __n, FILE *__restrict__ __stream);


void show_list(liste_t *self);


void free_list(liste_t *list);

void append(liste_t *list, char *text);

void addfirst(liste_t *list, char *text);

liste_t *init_void_list();


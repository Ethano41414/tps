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



char *agets(char *__restrict__ __s, int __n, FILE *__restrict__ __stream) {
    if (fgets(__s,__n,__stream)==NULL)
        return NULL;
    for (int i=0;i<__n && __s[i]!='\0';i++)
        if (__s[i]=='\n') {
            __s[i]='\0';
            break;
        }
    return __s;
}


void show_list(liste_t *self) {
    cellule_t *chain=self->tete;
    while (chain!=NULL) {
        printf("%s\n",chain->ligne);
        chain=chain->suiv;
    }
}


void free_list(liste_t *list) {
    cellule_t *obj=list->tete;
    cellule_t *p;
    while (obj!=NULL) {
        free(obj->ligne);
        p=obj->suiv;
        free(obj);
        obj=p;
    }
    free(list);
}

void append(liste_t *list, char *text) {
    cellule_t *cell=malloc(sizeof(cellule_t)); //cellulle independante
    cell->ligne=malloc(strlen(text)+1);
    strcpy(cell->ligne,text);
    cell->suiv=NULL;

    *list->fin=cell; // ajout de la cellulle dans la liste
    list->fin=&cell->suiv;
}

void addfirst(liste_t *list, char *text) {
    cellule_t *cell=malloc(sizeof(cellule_t)); //cellulle independante
    cell->ligne=malloc(strlen(text)+1);
    strcpy(cell->ligne,text);
    
    
    cell->suiv=list->tete;
    list->tete=cell; // ajout de la cellulle dans la liste
}

liste_t *init_void_list() {
    liste_t *list=malloc(sizeof(liste_t));
    list->tete=NULL;
    list->fin=&list->tete;
    return list;
}


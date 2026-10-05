#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct cellule {
    char           * ligne;
    struct cellule * suiv;
} cellule_t;

typedef struct liste {
    cellule_t  * tete;
    cellule_t ** fin; // ici je veux pointer vers le pointeur 
} liste_t;

/*---------------------------------------------------------------*/
/* agets   Fonctionne comme fgets en ommetant le \n              */
/*                                                               */
/* En entrée: *__s __n taille maximale du texte , __stream flux  */
/*                                                               */
/* En sortie: char*                                              */
/*---------------------------------------------------------------*/
char *agets(char *__restrict__ __s, int __n, FILE *__restrict__ __stream);

/*-----------------------------------------*/
/* show_list   Affiche les objets liste_t  */
/*                                         */
/* En entrée: *list Objet liste_t          */
/*                                         */
/* En sortie: Rien                         */
/*-----------------------------------------*/
void show_list(liste_t *self);

/*-----------------------------------------------------------*/
/* free_list   Libère la mémoire de tout un objet liste_t    */
/*                                                           */
/* En entrée: *list objet liste_t                            */
/*                                                           */
/* En sortie: Rien                                           */
/*-----------------------------------------------------------*/
void free_list(liste_t *list);

/*----------------------------------------------------------------------*/
/* append   Ajoute une chaine de caractères à la fin d'un objet list_t  */
/*                                                                      */
/* En entrée: *list objet liste_t , *text texte à implémenter           */
/*                                                                      */
/* En sortie: Rien                                                      */
/*----------------------------------------------------------------------*/
void append(liste_t *list, char *text);

/*-----------------------------------------------------------------------*/
/* addfirst  Ajoute une chaine de caractères au début d'un objet list_t  */
/*                                                                       */
/* En entrée: *list objet liste_t , *text texte à implémenter            */
/*                                                                       */
/* En sortie: Rien                                                       */
/*-----------------------------------------------------------------------*/
void addfirst(liste_t *list, char *text);

/*--------------------------------------------*/
/* addfirst  Initialise un objet list_t vide  */
/*                                            */
/* En entrée: Rien                            */
/*                                            */
/* En sortie: Objet liste_t vide              */
/*--------------------------------------------*/
liste_t *init_void_list();


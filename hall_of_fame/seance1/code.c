#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"


#define LOG(A) do {             \
    fprintf(stderr, "%s\n", A); \
} while(0)


typedef struct donnees {
    int score;
    char nom[100];
    char alias[40];
};

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


/*
// un petit commentaire ?
void afficherDonnee(FILE * file, donnee_t d) {
   // TO DO
}

// un petit commentaire ?
void saisirDonnee(FILE *file, donnee_t * p){
   // TO DO
}
*/

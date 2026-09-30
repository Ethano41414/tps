#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"



#define LOG(A) do {             \
    fprintf(stderr, "%s\n", A); \
} while(0)


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



void afficherDonnee(FILE *file, donnees_t d) {
    fprintf(file,"%s : %s avec %d\n",d.name,d.alias,d.score);
}

int saisirDonnee(FILE *file, donnees_t * p){
    char ert[20];
    if (agets(p->name,500,file)==NULL) return 0;
    if (agets(p->alias,40,file)==NULL) return 0;
    if (agets(ert,20,file)==NULL) return 0;
    p->score=atoi(ert);
    return 1;
}

int tableauFromFilename(char *path, donnees_t *tableau) {
    int i=0;
    FILE*f=fopen(path,"r");
    if (f==NULL) return 0;
    while (saisirDonnee(f,&tableau[i])) {
        i++;
    }
    fclose(f);
    return i;
}
#include "mod.h"

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

donnee_t *initdonnee(char *game, char *alias, int score) {
    donnee_t *p=malloc(sizeof(donnee_t));
    if (p==NULL) return NULL;
    p->name=malloc(500);
    p->alias=malloc(40);
    if (p->name==NULL||p->alias==NULL) {
        free(p->name);
        free(p->alias);
        free(p);
        return NULL;
    }
    strcpy(p->name,game);
    strcpy(p->alias,alias);
    p->score=score;
    p->next=NULL;
    return p;
}

void free_list(donnee_t *self) {
    if (self==NULL) return;
    if (self->next!=NULL)
        free_list(self->next);
    free(self->name);
    free(self->alias);
    free(self);
    self=NULL;
}

void afficherListe(donnee_t *self) {
    while (self!=NULL) {
        printf("Game: %s  Alias: %s  score: %d\n",self->name,self->alias,self->score);
        self=self->next;
    } 
}


void append(donnee_t *self, donnee_t *other) {
    while (self->next!=NULL) self=self->next;
    self->next=other;
}

void insererListe(donnee_t *(*donnees), donnee_t *other) { //insert at 0
    other->next=*donnees;
    *donnees=other;
}

donnee_t *readfile(char *path) {
    char game[500],alias[40],scor[20];
    FILE *f=fopen(path,"r");
    if (f==NULL) return NULL;
    if (agets(game,500,f)==NULL) {
        fclose(f);
        return NULL;
    }
    agets(alias,40,f);
    agets(scor,20,f);
    donnee_t *list=initdonnee(game,alias,atoi(scor));
    while (agets(game,500,f)!=NULL) {
        agets(alias,40,f);
        agets(scor,20,f);
        append(list,initdonnee(game,alias,atoi(scor)));
    }
    fclose(f);
    return list;
}

int to_file(donnee_t *self, char *path) {
    FILE *f=fopen(path,"w");
    if (f==NULL) return 0;
    while (self!=NULL) {
        fprintf(f,"%s\n%s\n%d\n",self->name,self->alias,self->score);
        self=self->next;
    }
    fclose(f);
    return 1;
}

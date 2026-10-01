#include "mod.h"

void ask_charp(char *text, char *rep, int n) {
    printf("%s",text);
    agets(rep,n,stdin);
}

void ask_int(char *text, int *num) {
    char txt[200];
    printf("%s",text);
    agets(txt,30,stdin);
    *num=atoi(txt);
}

int main() {
    // /*partie 1->2*/
    // donnee_t *donnees=initdonnee("Valorant","Cyntia",563843453); // réel
    // append(donnees,initdonnee("Homori","Kim",563848015));
    // append(donnees,initdonnee("Call of duty","Saadia",83848015));

    // insererListe(&donnees, initdonnee("Artista","Ethan",48015));
    
    // afficherListe(donnees);

    // free_list(donnees);

    /*partie 3*/
    donnee_t *list=NULL,*p;
    int b=1,index;
    char rep, text[200];
    rep='n';
    while (b) {
        ask_charp("\np (print)   i (insert first)   a (append)   c (change)   s (save in a file)    r (read a file)    m (make a list)   q (quit)\nYour order: ",text,200);
        rep=text[0];
        switch (rep) {
        case 'p':
            if (list==NULL) printf("Undefined list");
            else afficherListe(list);
            break;
        case 'i':
            p=initdonnee("","",0);
            ask_charp("Game name: ",p->name,200);
            ask_charp("Player alias: ",p->alias,40);
            ask_int("Score: ",&p->score);
            insererListe(&list,p);
            break;
        case 'a':
            p=initdonnee("","",0);
            ask_charp("Game name: ",p->name,200);
            ask_charp("Player alias: ",p->alias,40);
            ask_int("Score: ",&p->score);
            append(list,p);
            break;
        case 'c':
            ask_int("index where change: ",&index);
            p=list;
            for (int i=0;i<index;i++) p=p->next;
            ask_charp("Game name: ",p->name,200);
            ask_charp("Player alias: ",p->alias,40);
            ask_int("Score: ",&p->score);
            p=NULL;
            break;
        case 's':
            ask_charp("Give a name file: ",text,200);
            to_file(list,text);
            break;
        case 'r':
            free_list(list);
            ask_charp("Give a name file: ",text,200);
            list=readfile(text);
            break;
        case 'm':
            if (list!=NULL) {
                printf("list already defined");
                break;
            }
            list=initdonnee("","",0);
            ask_charp("Game name: ",list->name,200);
            ask_charp("Player alias: ",list->alias,40);
            ask_int("Score: ",&list->score);
            break;
        case 'q':
            free_list(list);
            b=0;
            break;
        }
    }

    return 0;
}

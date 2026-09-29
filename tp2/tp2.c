#include <stdio.h>
#include <stdlib.h>

// par valeur ne fonctionne pas car les variables locales sont des copies des variables passées
void echangeParAdresse(char *a, char *b) {
    char tmp=*a;
    *a=*b;
    *b=tmp;
}


int compter1(char * chaine){ // tant que la valeur du pointeur en (pointeur de la chaine+i n'est pas le marqueur de fin de texte alors i++)
    int i = 0;
    while (*(chaine+i) != '\0')
        ++i;
    return i;
}

int compter2(char * chaine) { //on a un garde-fou s qui n'avance pas et chaine avance
    char *s = chaine;
    while (*chaine != '\0')
        ++chaine;
    return chaine - s;
}

int compter3(char *chaine) { // retourne l'opposé du nombre de caracteres en comptant le caractere de fin
    char *s = chaine;
    while (*s++);
    return chaine - s;
}

int strcmp(char *c1, char *c2) {
    while (*c1 && *c1==*c2) {c1++;c2++;}
    return *c1-*c2;
}


void saisir(char *s) {
    printf("Saisir une chaine\n");
    scanf("%s",s);
}


int main() {
    /*partie 1-->3*/
    int i=5  , *ptri  = &i;
    char c1 = 'E', *ptrc1 = &c1;
    double d=64416855.46875, *ptrd=&d;


    printf("i valeur pointée: %d  adresse dans le pointeur: %p  adresse du pointeur: %p\n",*ptri,ptri,&ptri);
    printf("c1 valeur pointée: %c  adresse dans le pointeur: %p  adresse du pointeur: %p\n",*ptrc1,ptrc1,&ptrc1);
    printf("d valeur pointée: %f  adresse dans le pointeur: %p  adresse du pointeur: %p\n",*ptrd,ptrd,&ptrd);
    
    ptrd+=2;// l'adresse du pointeur reste la même. Mais l'adresse dans le pointeur se décale à droite de 2*sizeof(double)=16octets
    printf("d valeur pointée: %f  adresse dans le pointeur: %p  adresse du pointeur: %p\n",*ptrd,ptrd,&ptrd);

    char c2='2',*ptrc2=&c2;
    char tmp=*ptrc1;            // *ptrc1=*ptrc1+*ptrc2
    *ptrc1=*ptrc2;             // *ptrc2=*ptrc1-*ptrc2
    *ptrc2=tmp;                // *ptrc1=*ptrc1-*ptrc2
    printf("c1=%c   c2=%c\n",c1,c2);

    echangeParAdresse(ptrc1,ptrc2);
    printf("echange avec echangeParAdresse(ptrc1,ptrc2)     c1=%c   c2=%c\n",c1,c2);

    // /*partie 4.1*/
    // int tab[] = {0,1,2,3,4,5};

    // printf("%lu %lu %lu\n", sizeof(char), sizeof(int), sizeof(double));

    // int  *p1;
    // char *p2;

    // p1=tab;
    // ++p1;
    // printf("%d\n", *p1); // on est en tab[1] avec le ++p1;

    // p2 = (char *) p1;
    // p2 += sizeof(int); // passage du premier octet de l'int tab[1] au premier octet de l'int tab[2]

    // printf("%d\n", *((int*)p2)); // on recupere la valeur associée pointeur char que l'on a reconverti en pointeur int
    // printf("%d\n", *(p1+6));  // on recupere la valeur associée pointeur associé à la valeur de tab[7] --> segfault ou un nombre random

    // p1 = NULL;
    // //printf("%d", *p1); //p1 n'existe plus donc n'est plus associé à un truc particulier

    // /*partie 4.2*/
    // char * s1 = "loic";
    // //*s1 = 'L';          // 1  segmentation fault    (zone mémoire non modifiable)
    // printf("%s", s1);
    // printf("%c", *s1);   // lit 'l'
    // printf("%s", s1+2);    // 2 lit 'loic' sans les deux premiers caracteres donc "ic"
    // printf("%s", ++s1); // 3

    // char s2[] = "isima";
    // s2[0] = 'I';
    // printf("%s", s2);
    // //printf("%s", ++s2);  // 4  s2 n'est pas un pointeur mais un tableau

    /*partie 5*/
    // char s[50];
    // printf("Entrer votre prenom. ");
    // saisir(s);
    // printf("Bonjour %s!\n", s);

    // if (strcmp(s,"ddd")==0) printf("bizarre \n");

    

    // /*partie 6*/
    // double *tab=malloc(1000000*sizeof(double));
    // for (int i=0;i<1000000;i++) {tab[i]=i*i; printf("%d ",tab[i]);}
    // free(tab);
    return 0;
}
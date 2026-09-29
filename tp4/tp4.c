#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct { // on cré l'objet guichet
    char name;
    int o;
} guichet;

guichet GUICHET(char name) { //avec sa fonction d'initialisation
    guichet gu;
    gu.name=name;
    gu.o=0;
    return gu;
}


/* oh ça ? c'était pour le fun
typedef struct {
    double x;
    double y;
} vect;
vect VECT(double x, double y) {
    vect v;
    v.x=x;
    v.y=y;
    return v;
}*/



void closenopen1(guichet* *tab,int nb) {
    for (int i=0;i<nb;i++) tab[i]->o=0;
    tab[rand()%nb]->o=1;
}



int main() { // a la main c'était long on aurais pu faire un for et definir les objets guichets pendant la boucle avec guichets[i].name='A'+i;
    guichet guichetA=GUICHET('A');guichet guichetB=GUICHET('B');guichet guichetC=GUICHET('C');guichet guichetD=GUICHET('D');
    guichet guichetE=GUICHET('E');guichet guichetF=GUICHET('F');guichet guichetG=GUICHET('G');guichet guichetH=GUICHET('H');
    guichet guichetI=GUICHET('I');guichet guichetJ=GUICHET('J');guichet guichetK=GUICHET('K');guichet guichetL=GUICHET('L');
    guichet guichetM=GUICHET('M');guichet guichetN=GUICHET('N');guichet guichetO=GUICHET('O');
    guichet *guichets[15];
    guichets[0]=&guichetA;guichets[1]=&guichetB;guichets[2]=&guichetC;guichets[3]=&guichetD;guichets[4]=&guichetE;guichets[5]=&guichetF;
    guichets[6]=&guichetG;guichets[7]=&guichetH;guichets[8]=&guichetI;guichets[9]=&guichetJ;guichets[10]=&guichetK;guichets[11]=&guichetL;
    guichets[12]=&guichetM;guichets[13]=&guichetN;guichets[14]=&guichetO;

    srand(time(0));
    closenopen1(guichets,15);
    for (int i=0;i<15;i++) printf("%c %d\n",guichets[i]->name,guichets[i]->o);
    return 0;
}






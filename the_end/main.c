#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <dirent.h>

/*partie 1*/

double moyenne(int nombre, ...) {
    double  result = 0;
    int     nb     = 0;
    va_list liste;

    va_start(liste, nombre);
    while (nombre>0) {
        result += nombre;
        nb     += 1;
        nombre = va_arg(liste, int);
    }
    va_end(liste);
    if (nb>0) result /= nb;
    return result;
}


void show_fold(char *txt) {
    struct dirent * lecture;
	DIR *rep;
	rep = opendir(txt);
	while ((lecture = readdir(rep))) {
	    printf("%s\n", lecture->d_name);
	}
	closedir(rep);
}


void show_repertory_lists(char *txt, ...) {
    va_list list;
    va_start(list,txt);
    while (txt!=NULL) {
        printf("Dossier: %s\n",txt);
        show_fold(txt);
        txt=va_arg(list, char*);
    }
    va_end(list);
}


/*partie 2*/

#define TRI(type, t, n, comparaison) \
do { \
    for (int i = 1; i < (n); i++) { \
        type cle = (t)[i]; \
        int j = i - 1; \
        while (j >= 0 && comparaison((t)[j], cle)) { \
            (t)[j + 1] = (t)[j]; \
            j--; \
        } \
        (t)[j + 1] = cle; \
    } \
} while (0)

int inferieur(int a, int b) {
    return a < b;
}
int superieur(int a, int b) {
    return a > b;
}
int inferieurd(double a, double b) {
    return a < b;
}
int superieurd(double a, double b) {
    return a > b;
}

void print(int t[], int n) {
    for(int i = 0; i<n; ++i)
       printf("%d ", t[i]);
    printf("\n");
}
void printd(double t[], int n) {
    for(int i = 0; i<n; ++i)
       printf("%.1f ", t[i]);
    printf("\n");
}

void tri(int t[], int n) {
    for (int i = 1; i<n; i++) {
        double cle = t[i];
        int j = i - 1;

        while (!inferieur(j,0) &&inferieur(cle,t[j])) {
            t[j + 1] = t[j];
            --j;
        }
        t[j + 1] = cle;
    }
}

/*partie 3*/

typedef struct {
    char name[100];
    char language[50];
    int annee;
} donnee_t;


int comparer_donnees(const void *d1,const void *d2) {
    const donnee_t *a=d1;
    const donnee_t *b=d2;
    return ((a->annee>b->annee)-(a->annee<b->annee));
}

int comparer_language(const void *d1,const void *d2) {
    const donnee_t *a=d1;
    const donnee_t *b=d2;
    return ((a->language>b->language)-(a->language<b->language));
}


int main() {
    // /*partie 1*/
    // printf("%lf\n", moyenne(-1));
    // printf("%lf\n", moyenne(2, 2, 5, -1));
    // show_repertory_lists("./tp2","./calculatrice","./tp3",NULL);

    // /*partie 2*/
    // int t [] = { 3, 1, 5, 2, 10, 7};

    // print(t, 6);
    // // tri(t, 6);
    // // print(t, 6);

    // TRI(int,t,6,inferieur);
    // print(t, 6);
    // TRI(int,t,6,superieur);
    // print(t, 6);
    // printf("\nDouble:\n");
    // double d [] = { 2.5, 7.8, 4.5, 4.6, 10.2};
    // printd(d, 5);
    // TRI(double,d,5,superieurd);
    // printd(d, 5);
    // TRI(double,d,5,inferieurd);
    // printd(d, 5);

    /*partie 3*/
    donnee_t tab[4]= {{"Gosling","Java",1993},{"Van Rossum","Python",1991},{"Stroustrup","C++",1983},{"Ritchie","C",1972}};
    size_t n=sizeof(tab)/sizeof(tab[0]);
    for (size_t i=0;i<n;i++)
        printf("Nom: %s   Language: %s   Annee: %d\n",tab[i].name,tab[i].language,tab[i].annee);
    
    FILE *f=fopen("datas.txt","w+");
    if (f==NULL)
        return 1;
    fwrite(tab,sizeof(tab[0]),n,f);
    fclose(f);
    printf("\nAprès sorting annee:\n");
    qsort(tab,n,sizeof tab[0],comparer_donnees);
    for (size_t i=0;i<n;i++)
        printf("Nom: %s   Language: %s   Annee: %d\n",tab[i].name,tab[i].language,tab[i].annee);
    printf("\nAprès sorting annee:\n");
    qsort(tab,n,sizeof tab[0],comparer_language);
    for (size_t i=0;i<n;i++)
        printf("Nom: %s   Language: %s   Annee: %d\n",tab[i].name,tab[i].language,tab[i].annee);
    return 0;
}

/*
type char*
les valeurs ne seraies pas misent dans le fichier automatiquement

liste chainée, il faudrais ecrire au fur et a mesure


*/

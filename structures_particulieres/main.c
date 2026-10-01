#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*pt1*/
enum semaine {
    LUNDI,
    MARDI,
    MERCREDI,
    JEUDI,
    VENDREDI,
    SAMEDI,
    DIMANCHE
};

enum mois {
    JANVIER,
    FEVRIER,
    MARS,
    AVRIL,
    MAI,
    JUIN,
    JUILLET,
    AOUT,
    SEPTEMBRE,
    OCTOBRE,
    NOVEMBRE,
    DECEMBRE
};

/*pt2*/
struct couleur {
    int r:8;
    int v:8;
    int b:8;
};
struct couleur_basique {int r;int v;int b;};


/*pt3*/
struct paire_s { int a; double b;} s1;
union  paire_u { int a; double b;} u1;

struct cartesien {
    double x;
    double y;
};

struct polaire {
    double r;
    double t;
};

enum type_point {
    CARTESIEN,
    POLAIRE
};

typedef struct {
    enum type_point type;

    union {
        struct cartesien cartesien;
        struct polaire polaire;
    };
} point;

point vers_polaire(point p) {
    if (p.type==POLAIRE) return p;
    p.type=POLAIRE;
    p.polaire.r=sqrt(p.cartesien.x*p.cartesien.x+p.cartesien.y*p.cartesien.y);
    p.polaire.t=atan2(p.cartesien.y,p.cartesien.x);
    return p;
}

point vers_cartesien(point p) {
    if (p.type==CARTESIEN) return p;
    p.type=CARTESIEN;
    double a=p.polaire.r,b=p.polaire.t;
    p.cartesien.x=a*cos(b);
    p.cartesien.y=a*sin(b);
    return p;
}

double distance(point p1, point p2) {
    p1=vers_cartesien(p1);
    p2=vers_cartesien(p2);
    double a=p2.cartesien.x-p1.cartesien.x , b=p2.cartesien.y-p1.cartesien.y;
    return sqrt(a*a+b*b);
}

point *init_point(enum type_point type,double a, double b) {
    point *p=malloc(sizeof(point));
    p->type=type;
    if (type==POLAIRE) p->polaire.r=a,p->polaire.t=b;
    else p->cartesien.x=a,p->cartesien.y=b;
    return p;
}

void free_point(point *p) {free(p);}


int main() {
    // /*partie 1*/
    // enum semaine jour=MARDI;
    // enum mois mo=SEPTEMBRE;
    // for (enum semaine i=LUNDI;i<=DIMANCHE;i++)
    //     printf("%d ",i);
    // printf("\njour: %d        mois: %d\n",jour,mo);

    // /*partie 2*/
    // printf("Si sizeof(int)=4 octets couleur est de taille %ld , mais avec struct color int c:8 couleur est de taille %ld\n",sizeof(struct couleur_basique),sizeof(struct couleur));
    
    // printf("taille necessaire pour une image de 3024x1964 avec couleur_basique: %ld octets\n",3024*1964*sizeof(struct couleur_basique));
    // printf("taille necessaire pour une image de 3024x1964 avec couleur: %ld octets\n",3024*1964*sizeof(struct couleur));

    /*partie 3*/
    s1.a = 5;
    s1.b = 10.0;
    u1.a = 5;
    u1.b = 10.0;
    printf("s1 a,b %d , %f\n",s1.a,s1.b);
    printf("u1 a,b %d , %f\n",u1.a,u1.b); // on constate que la valeur de 'a' à changé en même temps que l'affectation de 'b'
    
    point p0;
    p0.type=CARTESIEN;
    p0.cartesien.x=1;
    p0.cartesien.y=1;
    printf("p0=(%lf, %lf)\n",p0.cartesien.x,p0.cartesien.y);

    point *p1=init_point(CARTESIEN,1,1),*p2=init_point(CARTESIEN,5,5),*p3=init_point(CARTESIEN,1,0),*p4=init_point(POLAIRE,1,M_PI),*p5=init_point(POLAIRE,1,M_PI_2),*p6=init_point(POLAIRE,3,3*M_PI_2);
    
    printf("Distances:\np1p2 %lf\np3p4 %lf\np5p6 %lf\n",distance(*p1,*p2),distance(*p3,*p4),distance(*p5,*p6));

    free(p1);free(p2);free(p3);free(p4);free(p5);free(p6);
    return 0;
}



#ifndef C3__VECTEUR_H
#define C3__VECTEUR_H
#include "matrix.h"

typedef double* VecteurType;

void vecteurToFile(FILE*flux, VecteurType vecteur, int ordre);
VecteurType vecteurFromFileByName(char *path,int *order);
double produitScalaire();
void liberer_vecteur(VecteurType *p_vecteur);
VecteurType matVectmul(mat,VecteurType,int,int);
#endif
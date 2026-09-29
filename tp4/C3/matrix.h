#ifndef MATRIXMOD4_H
#define MATRIXMOD4_H
#include <stdio.h>
#include <stdlib.h>
typedef double** mat;


mat initmat(int n, int m);

void freemat(mat pM,int nb_row);

void matrixToFile(FILE *flux, mat M, int ordre);

mat matrixFromFileByName(char *path,int *order);


#endif


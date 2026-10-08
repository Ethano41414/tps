#ifndef GARDIEN_UNIQUE_CODE_H
#define GARDIEN_UNIQUE_CODE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

extern char *OPER_NAMES[];

extern double (*OPER_FN[])(double);

extern double (*tab2[])(double,double);

typedef enum ope {ID,SIN,COS,LOG,EXP,NONE} OP;


/*---------------------------------------------------------------*/
/* agets   Fonctionne comme fgets en ommetant le \n              */
/*                                                               */
/* En entrée: *__s __n taille maximale du texte , __stream flux  */
/*                                                               */
/* En sortie: char*                                              */
/*---------------------------------------------------------------*/
char *agets(char *__restrict__ __s, int __n, FILE *__restrict__ __stream);

OP identification(char *input);

double evalf(double x, OP operator);

void calcul(FILE *__stream, OP operator, double a, double b, double delta);



double identite(double x);
double erreur(double other __attribute__((unused)));

double (*identification_par_fonction(char *input))(double);

void calcul_fonctionnel(FILE *__stream, double (*func)(double), double a, double b, double delta);



double sum(double a, double b);
double sub(double a, double b);
double mul(double a, double b);
double divis(double a, double b);
double op_err(double a __attribute__((unused)), double b __attribute__((unused)));
double nthroot(double x, double n);
double xsquared(double x);
double modulo(double x, double mod);

double (*identification_operator(char o))(double,double);

void calcul_fonctionnel2(FILE *__stream, double (*funcop)(double,double), double (*func1)(double), double (*func2)(double), double a, double b, double delta);


double (*identification_operator2(char o))(double,double);


#endif

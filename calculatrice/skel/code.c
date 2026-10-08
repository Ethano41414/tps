#include "code.h"


double (*OPER_FN[])(double)={identite,sin,cos,log,exp,erreur};
//NULL ne fonctionne pas
char *OPER_NAMES[]={"x","sin(x)","cos(x)","log(x)","exp(x)",0};

double (*tab2[])(double, double) = {mul, sum, op_err, sub, op_err, divis};


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

OP identification(char *input) {
    if (strcmp(input,OPER_NAMES[0])==0) return ID;
    else if (strcmp(input,OPER_NAMES[1])==0) return SIN;
    else if (strcmp(input,OPER_NAMES[2])==0) return COS;
    else if (strcmp(input,OPER_NAMES[3])==0) return LOG;
    else if (strcmp(input,OPER_NAMES[4])==0) return EXP;
    return NONE;
}


double evalf(double x, OP operator) {
    if (operator==ID) return x;
    if (operator==SIN) return sin(x);
    if (operator==COS) return cos(x);
    if (operator==LOG) return log(x);
    if (operator==EXP) return exp(x);
    return 0;
}


void calcul(FILE *__stream, OP operator, double a, double b, double delta) {
    double tmpres;
    for (double i=0.0;i<=(b-a+1e-6);i+=delta) {
        tmpres=evalf(a+i,operator);
        fprintf(__stream,"%lf ",tmpres);
    }
}




double identite(double x) {
    return x;
}

double erreur(double other __attribute__((unused))) {
    fprintf(stderr,"ERROR: Unrecognized expression");
    return 0;
}

double (*identification_par_fonction(char *input))(double) {
    if (strcmp(input,OPER_NAMES[0])==0) return OPER_FN[0];
    else if (strcmp(input,OPER_NAMES[1])==0) return OPER_FN[1];
    else if (strcmp(input,OPER_NAMES[2])==0) return OPER_FN[2];
    else if (strcmp(input,OPER_NAMES[3])==0) return OPER_FN[3];
    else if (strcmp(input,OPER_NAMES[4])==0) return OPER_FN[4];
    return OPER_FN[5];
}


void calcul_fonctionnel(FILE *__stream, double (*func)(double), double a, double b, double delta) {
    double tmpres;
    for (double i=0.0;i<=(b-a+1e-6);i+=delta) {
        tmpres=func(a+i);
        fprintf(__stream,"%lf ",tmpres);
    }
}

double sum(double a, double b){return a+b;}
double sub(double a, double b){return a-b;}
double mul(double a, double b){return a*b;}
double divis(double a, double b){return a/b;}
double op_err(double a __attribute__((unused)), double b __attribute__((unused))) {
    fprintf(stderr,"ERROR: Unrecognized expression");
    return 0;
}
double nthroot(double x, double n) {
    return pow(x,1.0/n);
}
double xsquared(double x) {
    return x*x;
}
double modulo(double x, double mod) {
    while (x>=mod)
        x-=mod;
    return x;
}

double (*identification_operator(char o))(double,double) {
    switch (o) {
    case '+':
        return sum;
    case '-':
        return sub;
    case '*':
        return mul;
    case '/':
        return divis;
    case '@':
        return pow;
    default:
        return op_err;
    }
}


void calcul_fonctionnel2(FILE *__stream, double (*funcop)(double,double), double (*func1)(double), double (*func2)(double), double a, double b, double delta) {
    double tmpres;
    for (double i=0.0;i<=(b-a+1e-6);i+=delta) {
        tmpres=a+i;
        tmpres=funcop(func1(tmpres),func2(tmpres));
        fprintf(__stream,"%lf ",tmpres);
    }
}

double (*identification_operator2(char o))(double,double) {
    if ('*'<=o&&o<=('*'+5))
        return tab2[o-'*'];
    else
        return op_err;
}




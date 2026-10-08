#include "code.h"

char expression[100],tmptxt[100];
char txt1[50],txt2[50],opc;
double a=0.0,b=-10.0,step=-1.0;

int commonpart() {
	printf("Sur l'intervalle ?\n");
	while (a>b) {
		printf("Borne inférieure: ");
		agets(tmptxt,100,stdin);
		a=atof(tmptxt);
		printf("Borne supérieure: ");
		agets(tmptxt,100,stdin);
		b=atof(tmptxt);
	}
	while (!(step>0)) {
		printf("Par pas de: ");
		agets(tmptxt,100,stdin);
		if (tmptxt[0]=='n')
			step=1.0;
		else
			step=atof(tmptxt);
	}
	return 0;
}


int calculatrice_simple() {
	OP func;
	printf("f(x)=");
	agets(expression,100,stdin);
	if ((func=identification(expression))==NONE) {
		printf("Expression non connue\n\n");
		return 1;
	}
	if (commonpart()) return 1;
	calcul(stdout,func,a,b,step);
	printf("\n");
	return 0;
}

int calculatrice_fonctionnelle() {
	printf("f(x)=");
	agets(expression,100,stdin);
	double (*func)(double)=identification_par_fonction(expression);
	if (commonpart()) return 1;
	calcul_fonctionnel(stdout,func,a,b,step);
	printf("\n");
	return 0;
}

int calculatrice_fonctionnelle2() {
	printf("f(x)=");
	agets(expression,100,stdin);
	sscanf(expression,"%s %c %s",txt1,&opc,txt2);
	double (*func1)(double)=identification_par_fonction(txt1);
	double (*func2)(double)=identification_par_fonction(txt2);
	double (*funcop)(double,double)=identification_operator(opc);
	if (commonpart()) return 1;
	calcul_fonctionnel2(stdout,funcop,func1,func2,a,b,step);
	printf("\n");
	return 0;
}

int calculatrice_fonctionnelle3() {
	printf("f(x)=");
	agets(expression,100,stdin);
	sscanf(expression,"%s %c %s",txt1,&opc,txt2);
	double (*func1)(double)=identification_par_fonction(txt1);
	double (*func2)(double)=identification_par_fonction(txt2);
	double (*funcop)(double,double)=identification_operator2(opc);
	if (commonpart()) return 1;
	calcul_fonctionnel2(stdout,funcop,func1,func2,a,b,step);
	printf("\n");
	return 0;
}


int main() {
	//return calculatrice_simple();
	//return calculatrice_fonctionnelle();
	//return calculatrice_fonctionnelle2();
	return calculatrice_fonctionnelle3();
}

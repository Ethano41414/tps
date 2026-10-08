#include "module.h"
#include "code.h"



char expression_reelle[]="(5(sin(cos(x+5))-1)+10)+((x+sin(x))/(x-1))";

char expression_textuelle[]="x 5 + cos sin 1 - 5 * 10 + x sin x + x 1 - / +";

double **p;

double (*get_func_from_str(char *txt))(double) {
	if (!strcmp(txt,"sin")) return sin;
	if (!strcmp(txt,"cos")) return cos;
	if (!strcmp(txt,"tan")) return tan;
	if (!strcmp(txt,"asin")) return asin;
	if (!strcmp(txt,"acos")) return acos;
	if (!strcmp(txt,"atan")) return atan;
	if (!strcmp(txt,"sqrt")) return sqrt;
	if (!strcmp(txt,"floor")) return floor;
	if (!strcmp(txt,"ceil")) return ceil;
	if (!strcmp(txt,"round")) return round;
	if (!strcmp(txt,"abs")) return fabs;
	if (!strcmp(txt,"²")) return xsquared;
	if (!strcmp(txt,"ln")) return log;
	if (!strcmp(txt,"log10")) return log10;
	if (!strcmp(txt,"log2")) return log2;
	return NULL;
}

double (*get_ope_from_str(char *txt))(double,double) {
	if (strlen(txt)==1) {
        switch (*txt) {
			case '+': return sum;
			case '-': return sub;
			case '*': return mul;
			case '/': return divis;
			case '^': return pow;
			case '@': return nthroot;
			case '%': return modulo;
		}
	}
	return NULL;
}

double *generate_x_values(double a, double b, double step) {
	if (step<=0||b<a)
		return NULL;
	ul n=(ul)floor((b-a)/step)+1;
	double *values=malloc((n+1)*sizeof(double));
	if (values==NULL)
		return NULL;
	for (ul i=0;i<n;i++)
		values[i]=a+i*step;
	values[n]=NAN;
	return values;
}

double *calculus_intervall_values(double *abscisses, partition *tree) {
	ul lent=0;
	while (!isnan(abscisses[lent])) lent++;
	
	double *values=malloc(lent*sizeof(double));
	values[lent]=NAN;
	for (ul i=0;i<lent;i++) {
		values[i]=evaluate(abscisses[i],tree);
		if (values[i]==NAN)printf("null retour");
	}
	return values;
}


partition *generate_tree(char *expression) {
	ul number_of_imbrications=15;
    functree *tree=malloc(sizeof(functree));
	tree->unused=0;
	tree->ppart=malloc(number_of_imbrications*sizeof(partition*));
	if (tree->ppart==NULL) {
		fprintf(stderr,"ERROR: not enought memory to allocate partitions table");
		return NULL;
	}
	for (ul i=0;i<number_of_imbrications;i++) tree->ppart[i]=NULL;

	ul expression_size=strlen(expression),i=0,j;
	char curr_expression[50];
	partition *cell;

	while (i<expression_size) {
		j=i;
		while ((j<expression_size)&&(expression[j]!=' ')) {
			j++;
		}
		segment(curr_expression,expression,i,j);
		TYPE_t type=get_type(curr_expression);
		if (type==NONETYPE) {
			fprintf(stderr,"ERROR: operator/func/variable %s is not a known one\n",curr_expression);
			for (ul k=0;k<tree->unused;k++)
    			free_partition(tree->ppart[k]);
			free(tree->ppart);
			free(tree);
			return NULL;
		}
		cell=malloc(sizeof(partition));
		if (cell==NULL) {
			fprintf(stderr,"ERROR: not enought memory to allocate for a new operand\n");
			return NULL;
		}
		if (VALUE==type) {
			if (tree->unused>=number_of_imbrications) {
				fprintf(stderr, "ERROR: expression too deeply imbricated\n");
				return NULL;
			}
			cell->type=type;
			cell->value=atof(curr_expression);
			tree->ppart[tree->unused]=cell;
			tree->unused++;
		} else if (type==X) {
			if (tree->unused>=number_of_imbrications) {
				fprintf(stderr, "ERROR: expression too deeply imbricated\n");
				return NULL;
			}
			cell->type=type;
			tree->ppart[tree->unused]=cell;
			tree->unused++;
		} else if (type==FUNCTION) {
			if (tree->unused==0) {
				fprintf(stderr,"ERROR: %s need a value before it\n",curr_expression);
				free(cell);
				return NULL;
			}
			cell->type=type;
			cell->function.func=get_func_from_str(curr_expression);
			cell->function.node=tree->ppart[tree->unused-1];
			tree->ppart[tree->unused-1]=cell;
		} else if (type==OPERATION) {
			if (tree->unused<2) {
				fprintf(stderr,"ERROR: not enought operand for %s\n",curr_expression);
				free(cell);
				return NULL;
			}
			cell->type=type;
			cell->operator.ope=get_ope_from_str(curr_expression);
			cell->operator.node1=tree->ppart[tree->unused-2];
			cell->operator.node2=tree->ppart[tree->unused-1];
			tree->ppart[tree->unused-2]=cell;
			tree->ppart[tree->unused-1]=NULL;
			tree->unused--;
		}
		i=j;
		i++;
	}
	if (tree->unused!=1) {
		fprintf(stderr,"ERROR: invalid expression\n");
		for (ul k=0;k<tree->unused;k++)
    		free_partition(tree->ppart[k]);
		free(tree->ppart);
		free(tree);
		return NULL;
	}
	partition *p=tree->ppart[0];
	tree->ppart[0]=NULL;
	free(tree->ppart);
	free(tree);
	printf("\n");
    return p;
}

int game() {
    char expression[1000],tmptxt[100];
    double a=0.0,b=-10.0,step=-1.0;
	partition *tree;
    printf("f(x)=");
	agets(expression,1000,stdin);

    if (!(tree=generate_tree(expression))) {
        return 1;
	}

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

    double *abscisses=generate_x_values(a,b,step);
    double *values_list=calculus_intervall_values(abscisses,tree);

    double *p=values_list;
    while (!isnan(*p)) {
        printf("%lf ",*p);
        p++;
    }
	printf("\n");
	free(abscisses);
	free(values_list);
    return 0;
}


int main() {
	return game();
}

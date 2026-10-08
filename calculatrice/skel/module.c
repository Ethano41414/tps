#include "module.h"





void segment(char *dest, char *text, ul st, ul ed) {
    if (st<=ed) {
        memcpy(dest,text+st,ed-st);
        dest[ed-st]='\0';
    }
}

TYPE_t get_type(char *txt) {
    char *end;
    strtod(txt,&end);
    if (end!=txt&&*end=='\0') return VALUE;
    if (!strcmp(txt,"pi")) return VALUE;
    if (!strcmp(txt,"e")) return VALUE;
    if (strlen(txt)==1) {
        switch (*txt) {
        case '+':
        case '-':
        case '*': 
        case '/': 
        case '^': //pow
        case '@':  //racine n ieme
        case '%': return OPERATION; // modulo
        case 'x': return X;
        default: return NONETYPE;
        }
    }
    if (!strcmp(txt,"sin")) return FUNCTION;
	if (!strcmp(txt,"cos")) return FUNCTION;
	if (!strcmp(txt,"tan")) return FUNCTION;
	if (!strcmp(txt,"asin")) return FUNCTION;
	if (!strcmp(txt,"acos")) return FUNCTION;
	if (!strcmp(txt,"atan")) return FUNCTION;
	if (!strcmp(txt,"sqrt")) return FUNCTION;
	if (!strcmp(txt,"floor")) return FUNCTION;
	if (!strcmp(txt,"ceil")) return FUNCTION;
	if (!strcmp(txt,"round")) return FUNCTION;
	if (!strcmp(txt,"abs")) return FUNCTION;
	if (!strcmp(txt,"²")) return FUNCTION;
	if (!strcmp(txt,"ln")) return FUNCTION;
	if (!strcmp(txt,"log10")) return FUNCTION;
	if (!strcmp(txt,"log2")) return FUNCTION;
    return NONETYPE;
}

void free_partition(partition *part) {
    if (part==NULL)
        return;
    if (part->type==FUNCTION) free_partition(part->function.node);
    else if (part->type==OPERATION) {
        free_partition(part->operator.node1);
        free_partition(part->operator.node2);
    }
    free(part);
}


double evaluate(double x, partition *tree) {
    switch (tree->type) {
        case X: return x;
        case VALUE: return tree->value;
        case FUNCTION: return tree->function.func(evaluate(x,tree->function.node));
        case OPERATION: return tree->operator.ope(evaluate(x,tree->operator.node1),evaluate(x,tree->operator.node2));
        default: return NAN;
    }
    return NAN;
}








void print_tree(partition *tree) {
    if (tree->type==FUNCTION) {
        printf("fun(");
        print_tree(tree->function.node);
        printf(")");
    } else if (tree->type==OPERATION) {
        printf("( ");
        print_tree(tree->operator.node1);
        printf(" ope ");
        print_tree(tree->operator.node2);
        printf(" )");
    } else if (tree->type==X) {
        printf("x");
    } else if (tree->type==VALUE) {
        printf("%lf",tree->value);
    }
}




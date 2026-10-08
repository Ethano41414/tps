#ifndef MODULE_H
#define MODULE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef unsigned long ul;

typedef enum {NONETYPE,OPERATION,FUNCTION,X,VALUE} TYPE_t;

typedef struct partie {
	TYPE_t type;
	union {
		double value;
		struct {
			double (*ope)(double,double);
			struct partie *node1;
			struct partie *node2;
		} operator;
		struct {
			double (*func)(double);
			struct partie *node;
		} function;
	};
} partition;

typedef struct {
	ul unused;
    partition **ppart;
} functree;


void segment(char *dest, char *text, ul st, ul ed);

TYPE_t get_type(char *txt);

void free_partition(partition *part);

double evaluate(double x, partition *tree);

void print_tree(partition *tree);

#endif
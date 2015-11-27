#ifndef _STACK_H_
#define _STACK_H_
//type of exp
#define typeexp double
#include <stdio.h>
#include <stdlib.h>

//stack for expression
typedef struct _expr{
	char op;
	double num;
	struct _expr* next;
}expr;


expr* popexp(expr** head);

void pushexp(expr** head, expr* push);

void freeexp(expr** head);

void revertexp(expr** head);

#endif
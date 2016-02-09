#ifndef _STACK_H_
#define _STACK_H_
//type of exp (legal types: long long, double)
//change only both
#define typeexp double
#define typeexpnum  0//long long = 1; double = 0;

#include <stdio.h>
#include <stdlib.h>

//stack for expression
typedef struct _expr{
	char op;
	typeexp num;
	struct _expr* next;
}expr;


expr* popexp(expr** head);

void pushexp(expr** head, expr* push);

//free all list
void freeexp(expr** head);

//revert list
void revertexp(expr** head);

#endif
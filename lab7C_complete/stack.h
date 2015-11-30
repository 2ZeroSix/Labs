#ifndef _STACK_H_
#define _STACK_H_
//type of exp (legal types: long long, double)
//change only both
#define typeexp long long
#define typeexpnum  1//long long = 1; double = 0;

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

void freeexp(expr** head);

void revertexp(expr** head);

#endif
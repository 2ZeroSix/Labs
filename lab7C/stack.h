#ifndef _STACK_H_
#define _STACK_H_
//type of exp
#define typeexp double

//stack for expression
typedef struct _exp
{
	char op;
	typeexp num;
	struct _exp* next;
}exp;


exp* popexp(exp** head);

void pushexp(exp** head, exp* push);

void freeexp(exp** head);

void revertexp(exp** head);

#endif
#include "calc.h"




void main()
{
	expr* head;
	typeexp* result;
	if (readexp(&head))
	{
		(result = calcexp(head)) ? printf("%f", result) : printf("division by zero");//or something else
		freeexp(&head);
	}
	else
	{
		printf("syntax error");
	}
}
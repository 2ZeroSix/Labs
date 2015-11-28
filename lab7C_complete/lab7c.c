#include "calc.h"




void main()
{
	expr* head;
	typeexp* result;
	if (readexp(&head))
	{
		if (result = calcexp(&head))
		{
			(typeexpnum) ? printf("%lld", *result) : printf("%f", *result);
		}
		else
		{
			printf("division by zero");//or something else
		}
		freeexp(&head);
	}
	else
	{
		printf("syntax error");
	}
}
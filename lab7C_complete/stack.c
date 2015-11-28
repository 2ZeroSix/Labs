#include "stack.h"


expr* popexp(expr** head)
{
	expr* temp = NULL;
	if (head)
	{
		temp = *head;
		if (*head)
			*head = (*head)->next;
	}
	return temp;
}

void pushexp(expr** head, expr* push)
{
	if (push && head)
	{
		push->next = *head;
		(*head) = push; 
	}
	return;
}

void freeexp(expr** head)
{
	expr* temp;
	while(head && (*head))
	{
		temp = (*head);
		(*head) = (*head)->next;
		free(temp);
	}
}

void revertexp(expr** head)
{
	expr *cur = NULL, *prev1 = NULL, *prev2 = NULL;
	if(*head)
		cur = *head;
	while(cur)
	{ 
		if(prev1)
		{
			prev1->next = prev2; 
		}
		prev2 = prev1;
		prev1 = cur;
		cur = cur->next;
	}
	if (prev1)
		prev1->next = prev2;
	*head = prev1;
	return;
}